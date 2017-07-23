//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <libs/db/classMySql.h>

#include "ecg_saveFile.h"
#include "ecg_viewer.h"
#include "ecg_dbviewerSignale.h"

#include "ecg_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmMain *fmMain;
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
	pnMain->Enabled = false;
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

	pnMain->Enabled = true;
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
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmMain::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acAnalyseEcgExecute(TObject *Sender)
	{
	DlgEcgViewer(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acAnalyseSignalExecute(TObject *Sender)
	{
	DlgDbViewerSignale(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::acEcgFileAddExecute(TObject *Sender)
	{
	DlgSaveEcgFile(this);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormKeyPress(TObject *Sender, System::WideChar &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btClassifySelectClick(TObject *Sender)
	{
	String cl = Sender->ClassName();
	if (cl != "TBitBtn") return;
	TComponent* comp = (TComponent*)Sender;

	POINT pt;
	GetCursorPos(&pt);

		 if (comp->Name == "btAnalysisSelect") PopupMenuAnalysis->Popup(pt.x, pt.y);
	else if (comp->Name == "btDatabaseSelect") PopupMenuDatabase->Popup(pt.x, pt.y);
	else if (comp->Name == "btSessionsSelect") PopupMenuSessions->Popup(pt.x, pt.y);
	else if (comp->Name == "btFeaturesSelect") PopupMenuFeatures->Popup(pt.x, pt.y);
	else if (comp->Name == "btClassifySelect") PopupMenuClassify->Popup(pt.x, pt.y);
	}
//---------------------------------------------------------------------------

