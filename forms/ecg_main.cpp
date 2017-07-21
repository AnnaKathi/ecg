//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <libs/db/classMySql.h>

#include "ecg_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmMain *fmMain;
//cMySql __declspec(dllimport) fmysql;
//---------------------------------------------------------------------------
__fastcall TfmMain::TfmMain(TComponent* Owner)
	: TForm(Owner)
    , fmysql(cMySql::getRef())
	{
	fmysql.init();
	}
//---------------------------------------------------------------------------
__fastcall TfmMain::~TfmMain()
	{
	fmysql.shutdown();
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormCreate(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	Cursor = crHourGlass;

	//Testschalter NoMySql berücksichtigen, ermöglichst einen Testbetrieb ohne MySql
	TIniFile* Ini = new TIniFile(ftools.GetIniFile());
	bNoMySql = Ini->ReadBool("MySql", "NoMySql", false);
	delete Ini;

	setStatus("startup EcgTool...loading MySql-Database");

	/* TODO
	if (ftools.GetComputerBS() != "Windows")
		{
		if (Application->MessageBox(
			ftools.fmt(
				"Es wurde das Betriebssystem '%s' erkannt.\r\n\r\n"
				"Das Programm ist (vorläufig) auf ein Windows-Betriebssystem ausgelegt. "
				"Einige Funktionen sind mit anderen Betriebssystemem unter Umständen "
				"nicht verfügbar.\r\n\r\n"
				"Soll das EcgTool-Programm abgebrochen werden?",
				ftools.GetComputerBS()).c_str(),
			"Falsches Betriebssystem", MB_YESNO) == ID_YES)
			{
			Close();
			return;
			}
		}
	setStatus(ftools.GetComputer(), 2);
	*/
	/* TODO
	if (ftools.GetComputerProzessor() != "64Bit")
		{
		Application->MessageBox(
			ftools.fmt(
				"Es wurde der Systemtyp '%s' erkannt.\r\n\r\n"
				"Das Programm ist auf ein 64Bit-Windows-Betriebssystem ausgelegt. "
				"Einige Funktionen sind mit anderen Betriebssystemem unter Umständen "
				"nicht verfügbar, z.B. die Choi-SVM-Klassifizierung.\r\n\r\n",
				ftools.cpData.BSProzessor).c_str(),
			"Warnung 64Bit-System", MB_OK);
		setStatus("## 32Bit-System ggf. nicht ausreichend ##", 2);
		}
	else
		setStatus("64Bit-System  - ok", 2);
	*/

	if (!setupDatabase())
		{
		Close();
		return;
		}

	setStatus("startup EcgTool...reading MySql-Database");
	setDbInfo();

	setStatus("Startup finished - ready to go");

	Cursor = crDefault;
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormClose(TObject *Sender, TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
bool TfmMain::setupDatabase()
	{
	if (bNoMySql)
		return true; //simulieren, die DB wär geöffnet worden

	//falls die Datenbank nicht vorhanden ist, anlegen
	setStatus("startup Database...checking existance");
	if (!fmysql.openWithoutDb())
		{
		Application->MessageBox(
			ftools.fmt(
				"Die MySql-Datenbankverbindung konnte nicht geprüft werden. "
				"Die Funktion meldet: %s", fmysql.error_msg.c_str()
				).c_str(),
			L"Fehler beim Öffnen der Datenbank",
			MB_OK);
		return false;
		}

	setStatus("startup Database...checking existance, MySql found");
	if (!fmysql.dbExists())
		{
		if (Application->MessageBox(
			ftools.fmt(
				"Die MySql-Datenbank 'ecg' ist nicht vorhanden. "
				"Soll sie nun vom Programm erstellt werden ?\n\n"
				"Ansonsten wird das Programm abgebrochen.").c_str(),
			L"Datenbank erstellen ?",
			MB_YESNO) == IDNO)
			{
			fmysql.close();
			return false;
			}

		setStatus("startup Database...creating database");
		if (!fmysql.create())
			{
			Application->MessageBox(
				ftools.fmt(
					"Die MySql-Datenbank 'ecg' konnte nicht initialisiert werden. "
					"Die Funktion meldet: %s", fmysql.error_msg.c_str()).c_str(),
				L"Fehler beim Öffnen der Datenbank",
				MB_OK);
			return false;
			}
		}

	setStatus("startup Database...checking existance, DB found");
	if (!fmysql.close())
		;

	//Datenbank öffnen
	setStatus("startup Database...opening database");
	if (!fmysql.open())
		{
		Application->MessageBox(
			ftools.fmt(
				"Die MySql-Datenbank 'ecg' konnte nicht geöffnet werden. "
				"Die Funktion meldet: %s", fmysql.error_msg).c_str(),
			L"Fehler beim Öffnen der Datenbank",
			MB_OK);
		return false;
		}

	setStatus("startup Database...ready");
	return true;
	}
//---------------------------------------------------------------------------
void TfmMain::setStatus(String status, int panel) //panel ist vorbesetzt mit 0
	{
	StatusBar->Panels->Items[panel]->Text = status;
	}
//---------------------------------------------------------------------------
void TfmMain::setDbInfo()
	{
	if (bNoMySql)
		setStatus("### MySql-Datenbank wird nicht verwendet ###", 1);
	else
        //TODO %s wieder in %d umwandeln
		setStatus(
		ftools.fmt("%d Personen, %d Sessions, %d EKG-Datensätze, %d Features",
		fmysql.people.getSize(),
		fmysql.sessions.getSize(),
		fmysql.ecg.getSize(),
		fmysql.features.getSize()), 1);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormKeyPress(TObject *Sender, System::WideChar &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		Close();
        }
	}
//---------------------------------------------------------------------------
//---  Testbuttons  ---------------------------------------------------------
//---------------------------------------------------------------------------
void TfmMain::ln(String line)
	{
	mInfo->Lines->Add(line);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btTestMySqlClick(TObject *Sender)
	{
	cMySqlPeople& pp = fmysql.people;

	ln(ftools.fmt("Datenbank-Test 'People'"));

	ln(ftools.fmt("\tAnz. Personen: %s", String(pp.getSize())));

	sPeople p;
	sprintf(p.firstname, "%s", "Otto");
	sprintf(p.lastname,  "%s", "Mustermann");
	p.sex       = 0;
	p.age       = 99;
	p.height    = 180;
	p.weight    = 80;

	if (pp.insert(p))
		ln(ftools.fmt("\tPerson hinzugefügt: (%d) %s",
			pp.row.ident, String(pp.row.lastname)));
	else
		{
		ln(ftools.fmt("\t## Fehler, Person konnte nicht gespeichert werden"));
		ln(ftools.fmt("\tMySqlPeople meldet: %s", pp.error_msg));
		return;
		}

	int id = pp.row.ident;
	if (pp.get(id))
		ln(ftools.fmt("\tPerson %d geladen: %s %s",
			pp.row.ident,
			String(pp.row.firstname),
			String(pp.row.lastname)));
	else
		{
		ln(ftools.fmt("\t## Fehler, Person konnte nicht geladen werden"));
		ln(ftools.fmt("\tMySqlPeople meldet: %s", pp.error_msg));
		return;
		}

	if (pp.deleteByIdent(id))
		ln(ftools.fmt("\tPerson %d gelöscht", id));
	else
		{
		ln(ftools.fmt("\t## Fehler, Person konnte nicht gelöscht werden"));
		ln(ftools.fmt("\tMySqlPeople meldet: %s", pp.error_msg));
		return;
		}

	ln("Test-Ende");
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btTestCsvClick(TObject *Sender)
	{
	ln(ftools.fmt("Test Klasse 'cCsv'"));
	String file = "S:\\Anna\\Ecg-Daten\\Nora liegend.txt";
	ln(ftools.fmt("\tEinzulesende Datei: %s", file));

	if (fcsv.OpenFile(file, formatADS, "\t", 3))
		ln(ftools.fmt("\tDatei erfolgreich geöffnet"));
	else
		{
		ln(ftools.fmt("\t## Fehler, Datei konnte nicht geöffnet werden."));
		ln(ftools.fmt("\tcCsv meldet: %s", fcsv.error_msg));
		return;
		}

	if (fcsv.StartAt(0))
		ln(ftools.fmt("\tDatei erfolgreich begonnen"));
	else
		{
		ln(ftools.fmt("\t## Fehler, Datei konnte nicht gestartet werden."));
		ln(ftools.fmt("\tcCsv meldet: %s", fcsv.error_msg));
		return;
		}

	int count = 0;
	ln(ftools.fmt("\tDrucke 10 Testzeilen..."));
	while (fcsv.NextUntil(100))
		{
		count++;
		if (count > 10) break;

		ln(ftools.fmt(
			"\t\t%02d: %.8f \t%.8f \t%.8f",
				fcsv.getLineNo(),
				fcsv.getChannel(1),
				fcsv.getChannel(2),
				fcsv.getChannel(3)));
		}

	fcsv.CloseFile();
	ln("Test-Ende");
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btTestMathClick(TObject *Sender)
	{
	ln(ftools.fmt("Test Klasse 'cMath'"));

	iarray_t array;
	Randomize();

	int wert;
	for (int i = 0; i < 100; i++)
		{
		wert = Random(100);
		array[i].push_back(i);
		array[i].push_back(wert);
		}

	String line = "\t";
	for (int i = 0; i < 100; i++)
		line += String(array[i][1]) + ", ";
	ln(line);

	array = fmath.resort(array, true);
	line = "\t";
	for (iarray_itr itr = array.begin(); itr != array.end(); itr++)
		{
		ilist_t v = itr->second;
		line += String(v[1]) + ", ";
        }
    ln(line);

	array = fmath.calcDerivate(array);
	line = "\t";
	for (iarray_itr itr = array.begin(); itr != array.end(); itr++)
		{
		ilist_t v = itr->second;
		line += String(v[1]) + ", ";
		}
	ln(line);

	ln("Test-Ende");
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btTestArrayClick(TObject *Sender)
	{
	ln(ftools.fmt("Test Klasse 'cArray'"));

	iarray_t array;
	Randomize();

	int wert;
	for (int i = 0; i < 100; i++)
		{
		wert = Random(100);
		array[i].push_back(i);
		array[i].push_back(wert);
		}

	String line = "\t";
	for (iarray_itr itr = array.begin(); itr != array.end(); itr++)
		{
		ilist_t v = itr->second;
		line += String(v[1]) + ", ";
		}
	ln(line);

	farray.redisplay(array, img1);
	double av = farray.calcAvWert(array);
	ln(ftools.fmt("\tDurchschnittswert Original: %.4f", av));

	ln("Test-Ende");
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btTestDataClick(TObject *Sender)
	{
	ln(ftools.fmt("Test Klasse 'cData'"));

	String file = "S:\\Anna\\Ecg-Daten\\Nora liegend.txt";
	if (fdata.getFile(file, formatADS, "\t", 3, 0, 3000))
		ln(ftools.fmt("\tDatei erfolgreich eingelesen: %s", file.c_str()));
	else
		{
		ln(ftools.fmt("\t## Fehler, Datei konnte nicht geladen werden."));
		ln(ftools.fmt("\tcData meldet: %s", fdata.error_msg));
		return;
		}

	fdata.redisplay(img1);

	iarray_t narray = fdata.normalize(fdata.data_array, 100);
	farray.redisplay(narray, img2);

	ln("Test-Ende");
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btTestEcgClick(TObject *Sender)
	{
	ln(ftools.fmt("Test Klasse 'cEcg'"));

	String file = "S:\\Anna\\Ecg-Daten\\Nora liegend.txt";
	if (fecg.data.getFile(file, formatADS, "\t", 3, 0, 3000))
		ln(ftools.fmt("\tDatei erfolgreich eingelesen: %s", file.c_str()));
	else
		{
		ln(ftools.fmt("\t## Fehler, Datei konnte nicht geladen werden."));
		ln(ftools.fmt("\tcEcg meldet: %s", fecg.error_msg));
		return;
		}

	fecg.data.redisplay(img1);

	iarray_t rpeaks = fecg.rpeaks.find(fecg.data.data_array, NULL);
	int n = rpeaks.size();
	ln(ftools.fmt("\tR-Peaks gefunden: %d", n));
	if (n <= 0) return;

	farray.displayPoints(fecg.data.data_array, rpeaks, img1);

	if (fecg.data.buildDerivates())
		ln(ftools.fmt("\tAbleitungen erfolgreich gebildet"));
	else
		{
		ln(ftools.fmt("\t## Fehler, die Ableitungen konnten nicht gebildet werden."));
		ln(ftools.fmt("\tcEcg meldet: %s", fecg.error_msg));
		return;
		}

	farray.redisplay(fecg.data.derivate1.deriv_array, img2);
	farray.redisplay(fecg.data.derivate2.deriv_array, img3);

	iarray_t heart = fecg.heart.calcAvBeat(fecg.data.data_array);
	if (heart.size() > 0)
		ln(ftools.fmt("\tStandardherzschlag erfolgreich gebildet"));
	else
		{
		ln(ftools.fmt("\t## Fehler, der Standardherzschlag konnten nicht gebildet werden."));
		ln(ftools.fmt("\tcEcg meldet: %s", fecg.error_msg));
		return;
		}

	farray.redisplay(heart, img4);

	ln("Test-Ende");
	}
//---------------------------------------------------------------------------

