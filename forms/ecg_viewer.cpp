//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <libs/db/classMySql.h>

#include "ecg_viewer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmEcgViewer *fmEcgViewer;
//---------------------------------------------------------------------------
bool DlgEcgViewer(TForm* Papa)
	{
	TfmEcgViewer* Form = new TfmEcgViewer(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmEcgViewer::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmEcgViewer::TfmEcgViewer(TComponent* Owner)
	: TForm(Owner)
    , fmysql(cMySql::getRef())
	{
	bMausMarking = false;

	/* TODO reaktivieren
	fmDetails = new TfmDetails(this);
	fmDetails->Hide();
	bDisplayedDetails = false;
	*/
	}
//---------------------------------------------------------------------------
__fastcall TfmEcgViewer::~TfmEcgViewer()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::FormCreate(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	ftools.FormLoad(this);
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmEcgViewer::Print(char* msg, ...)
	{
	char    buffer[512];
	int     nsiz;
	va_list argptr;

	va_start(argptr, msg);
	nsiz = vsnprintf(0, 0, msg, argptr);
	if (nsiz >= sizeof(buffer)-2) nsiz = sizeof(buffer)-2;

	vsnprintf(buffer, nsiz, msg, argptr);
	buffer[nsiz] = 0;

	memo->Lines->Add(buffer);
	va_end(argptr);
	}
//---------------------------------------------------------------------------
bool TfmEcgViewer::ReadFile(String ecgFile)
	{
	Print("start readFile...");
    if (ecgFile == "" || !FileExists(ecgFile)) return false;

	String delim = ";";
	if (cbDelim->ItemIndex == 1) //Komma
		delim = ",";
	else if (cbDelim->ItemIndex == 2) //Tab
		delim = "\t";

	eDatFormat format;
	if (cbFormat->ItemIndex == 1)
		format = formatADS;
	else
		format = formatNone;

	int lead = cbLead->ItemIndex+1;
	if (lead < 0) lead = 1;

	int vonSamp = edVonSample->Text.ToIntDef(-1);
	int bisSamp = edBisSample->Text.ToIntDef(-1);

	//-- EKG-Daten
	cData& data = ecg.data;
	if (!data.getFile(ecgFile, format, delim, lead, vonSamp, bisSamp))
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return false;
		}
	data.redisplay(imgEcg);

	//-- Erste und zweite Ableitung
	if (!data.buildDerivates())
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return false;
		}
	data.derivate1.redisplay(imgDeriv1);
	data.derivate2.redisplay(imgDeriv2);

	Print("\tDatensätze im Array: %d", data.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", data.farr_charac.VonIdx, data.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", data.farr_charac.VonMsec, data.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", data.farr_charac.MinWert, data.farr_charac.MaxWert);

	Print("...finished readFile");

	/*TODO reaktivieren
	//Detail-Werte anzeigen
	if (!bDisplayedDetails)
		{
		fmDetails->Execute(this, ecg);
		bDisplayedDetails = true;
		}
	else
		fmDetails->Renew(ecg);

	tDetails->Enabled = true;
	*/
	return true;
	}
//---------------------------------------------------------------------------
bool TfmEcgViewer::RemoveSegment(int von, int bis)
	{
    //TODO farray.cut() überarbeiten, funktioniert nicht richtig
	Print("cut curve...");
	if (von < 0 || bis < 0 || bis < von) return false;

	//-- EKG-Daten
	cData& data = ecg.data;
	if (!data.cut(von, bis))
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return false;
		}
	data.redisplay(imgEcg);

	//-- Erste Ableitung
	cDerivate& deriv1 = ecg.data.derivate1;
	if (!deriv1.cut(von, bis))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv1.error_code, deriv1.error_msg);
		return false;
		}
	data.derivate1.redisplay(imgDeriv1);

	//-- Zweite Ableitung
	cDerivate& deriv2 = ecg.data.derivate2;
	if (!deriv2.cut(von, bis))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv2.error_code, deriv2.error_msg);
		return false;
		}
	data.derivate2.redisplay(imgDeriv2);

	Print("\tDatensätze im Array: %d", data.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", data.farr_charac.VonIdx, data.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", data.farr_charac.VonMsec, data.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", data.farr_charac.MinWert, data.farr_charac.MaxWert);

	Print("...finished cutting");

	//Detail-Werte aktualisieren
	//TODO reaktivieren: fmDetails->Renew(ecg);
    return true;
	}
//---------------------------------------------------------------------------
bool TfmEcgViewer::MovingAv(int window1, int window2, int window3, bool dropBegin)
	{
	Print("build moving average...");
	if (window1 <= 0 || window2 <= 0 || window3 <= 0) return false;

	//-- EKG-Daten
	cData& data = ecg.data;
	if (!data.movingAv(window1, !dropBegin))
		{
		Print("## Fehler aufgetreten: %d, %s", data.error_code, data.error_msg);
		return false;
		}
	data.redisplay(imgEcg);

	//-- Erste Ableitung
	cDerivate& deriv1 = ecg.data.derivate1;
	if (!deriv1.movingAv(window2, !dropBegin))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv1.error_code, deriv1.error_msg);
		return false;
		}
	data.derivate1.redisplay(imgDeriv1);

	//-- Zweite Ableitung
	cDerivate& deriv2 = ecg.data.derivate2;
	if (!deriv2.movingAv(window3, !dropBegin))
		{
		Print("## Fehler aufgetreten: %d, %s", deriv2.error_code, deriv2.error_msg);
		return false;
		}
	data.derivate2.redisplay(imgDeriv2);

	Print("\tDatensätze im Array: %d", data.farr_charac.Number);
	Print("\tIndex im Array: %d - %d", data.farr_charac.VonIdx, data.farr_charac.BisIdx);
	Print("\tMSek. im Array: %d - %d", data.farr_charac.VonMsec, data.farr_charac.BisMsec);
	Print("\tWerte im Array: (%.6f) - (%.6f)", data.farr_charac.MinWert, data.farr_charac.MaxWert);

	Print("...finished moving average");

	//Detail-Werte aktuelisieren
	//TODO reaktivieren: fmDetails->Renew(ecg);
    return true;
	}
//---------------------------------------------------------------------------
bool TfmEcgViewer::SaveArffFile()
	{
	//Das angeziegte Lead in herzschläge separieren und diese in eine Textdatei
	//speichern. Wird verwendet um manuell arff-Dateien für Weka aufzubauen.
	ftools.Log("---------------------------");
	ftools.Log("Inside SaveArffFile()");

	iarray_t curve  = ecg.data.data_array;
	iarray_t rpeaks = ecg.rpeaks.find(ecg.data.data_array, NULL);
	if (rpeaks.size() <= 0)
		{
		ftools.Log(
			"Die R-Peaks konnten nicht gebildet werden. ecg.rpeaks meldet: %s",
			ecg.rpeaks.error_msg);
		return false;
		}

	if (!SaveDialog->Execute()) return false;
	String datname = SaveDialog->FileName;

	FILE* fp = fopen(AnsiString(datname).c_str(), "w");

	double wert;
	int zeitvon = 0;
	int zeitbis = 0;
	bool first = true;
	int count = 0;
	for (iarray_itr itr = rpeaks.begin(); itr != rpeaks.end(); itr++)
		{
		zeitvon = zeitbis;
		ilist_t v = itr->second;
		zeitbis = (int)v[0];
		if (first)
			{
			first = false;
			continue;
			}

		count++;
		iarray_t beat = farray.get(curve, zeitvon, zeitbis);
		int n = beat.size();
		ftools.Log("\tHerzschlag %d: %d-%d", count, zeitvon, zeitbis);
		ftools.Log("\t\t%d Werte", n);

		if (n <= 200) //Beat ist zu kurz
			{
			ftools.Log("\t\t-> Beat übersprungen");
			continue;
			}

		beat = ecg.data.normalize(beat, 400);
		ftools.Log("\t\tBeat normalisert, Anz. Werte = %d", beat.size());

		//Herzschlag schreiben, Werte Kommagetrennt hintereinander setzen
		//alle Herzschläge werden auf 400 Werte normalisiert
		bool firstvalue = true;
		for (iarray_itr i = beat.begin(); i != beat.end(); i++)
			{
			ilist_t v = itr->second;
			wert = v[1];
			if (firstvalue)
				{
				firstvalue = false;
				fprintf(fp, "%.6f", wert);
				}
			else
				fprintf(fp, ",%.6f", wert);
			}
		fprintf(fp, "\n");
		ftools.Log("\t\t-> Beat geschrieben");
		}

	fclose(fp);
	Application->MessageBox(L"Datei wurde gespeichert", L"Fertig", MB_OK);

	ftools.Log("End of SaveArffFile()");
	ftools.Log("---------------------------");
    return true;
	}
//---------------------------------------------------------------------------
void TfmEcgViewer::Line(int x, TColor cl)
	{
	//diese X-Pos in der angegebenen Farbe anmalen ohne dass die Kurve übermalt wird
	for (int y = 0; y < imgEcg->Height; y++)
		{
		if (imgEcg->Canvas->Pixels[x][y] == clBlack)
			continue;
		else
			imgEcg->Canvas->Pixels[x][y] = cl;
		}
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::acReadFileExecute(TObject *Sender)
	{
	String ecgFile = edInputfile->Text;
	if (ecgFile == "") return;
	if (!FileExists(ecgFile)) return;

	if (ReadFile(ecgFile))
		; //todo ShowDetail o.ä.
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::acCutCurveExecute(TObject *Sender)
	{
	int von = edCutVon->Text.ToIntDef(-1);
	int bis = edCutBis->Text.ToIntDef(-1);
	if (von < 0 || bis < 0) return;
	if (bis < von) return;

	if (RemoveSegment(von, bis))
		; //todo ShowDetail o.ä.
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::acMovingAvExecute(TObject *Sender)
	{
	int window1 = edGl1->Text.ToIntDef(-1);
	int window2 = edGl2->Text.ToIntDef(-1);
	int window3 = edGl3->Text.ToIntDef(-1);
	if (window1 <= 0 || window2 <= 0 || window3 <= 0) return;

	if (MovingAv(window1, window2, window3, cxDropBegin->Checked))
		; // todo ShowDetail o.ä.
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::acSaveArffFileExecute(TObject *Sender)
	{
    SaveArffFile();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::FormKeyPress(TObject *Sender, System::WideChar &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		Close();
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
	{
	if (Shift.Contains(ssShift) && Key == VK_F11)
		{
		btInputfileClick(Sender);
		}

	else if (Shift.Contains(ssCtrl) && Shift.Contains(ssShift) && Key == 0x44) //"D" -> Detailseite fokussieren
		{
		/* TODO reaktivieren
		if (bDisplayedDetails)
			fmDetails->BringToFront();
		*/
		}

	else if (Shift.Contains(ssCtrl) && Shift.Contains(ssShift))
		{
			 if (Key == 0x31) { cbLead->ItemIndex =  0; cbLeadChange(Sender); }
		else if (Key == 0x32) { cbLead->ItemIndex =  1; cbLeadChange(Sender); }
		else if (Key == 0x33) { cbLead->ItemIndex =  2; cbLeadChange(Sender); }
		else if (Key == 0x34) { cbLead->ItemIndex =  3; cbLeadChange(Sender); }
		else if (Key == 0x35) { cbLead->ItemIndex =  4; cbLeadChange(Sender); }
		else if (Key == 0x36) { cbLead->ItemIndex =  5; cbLeadChange(Sender); }
		else if (Key == 0x37) { cbLead->ItemIndex =  6; cbLeadChange(Sender); }
		else if (Key == 0x38) { cbLead->ItemIndex =  7; cbLeadChange(Sender); }

		else if (Key == 0x51) { cbLead->ItemIndex =  8; cbLeadChange(Sender); }
		else if (Key == 0x41) { cbLead->ItemIndex =  9; cbLeadChange(Sender); }
		else if (Key == 0x59) { cbLead->ItemIndex = 10; cbLeadChange(Sender); }
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::btInputfileClick(TObject *Sender)
	{
	if (OpenDialog->Execute())
		{
		edInputfile->Text = OpenDialog->FileName;
		acReadFileExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::cbLeadChange(TObject *Sender)
	{
	acReadFileExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::laClsClick(TObject *Sender)
	{
	memo->Lines->Clear();
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::imgEcgMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
	{
	//mit der maus kann man den Bereich markieren, der gelöscht werden soll
	//welcher Zeitwert steht an dieser Stelle?

	double prozent = (double)X / (double)imgEcg->Width;

	farray.resetValues(ecg.data.data_array, ecg.data.farr_charac);
	double max = ecg.data.farr_charac.BisMsec;
	double zz  = max * prozent;

	int zeit = (int)zz;
	if (zeit < ecg.data.farr_charac.VonMsec)
		zeit = ecg.data.farr_charac.VonMsec;
	else if (zeit > ecg.data.farr_charac.BisMsec)
		zeit = ecg.data.farr_charac.BisMsec;

	edCutVon->Text = (String)zeit;
	MausPosBegin = X;

	bMausMarking = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::imgEcgMouseMove(TObject *Sender, TShiftState Shift,
		  int X, int Y)
	{
	if (!bMausMarking) return;
	MausCurrPos = X;

	if (MausCurrPos > MausPosBegin)
		{
		for (int x = MausPosBegin; x <= MausCurrPos; x++)
			Line(x, clYellow);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::imgEcgMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
	{
	double prozent = (double)X / (double)imgEcg->Width;

	farray.resetValues(ecg.data.data_array, ecg.data.farr_charac);
	double max = ecg.data.farr_charac.BisMsec;
	double zz  = max * prozent;

	int zeit = (int)zz;
	if (zeit < ecg.data.farr_charac.VonMsec)
		zeit = ecg.data.farr_charac.VonMsec;
	else if (zeit > ecg.data.farr_charac.BisMsec)
		zeit = ecg.data.farr_charac.BisMsec;

	edCutBis->Text = (String)zeit;
	MausPosEnde = X;

	bMausMarking = false;
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::estSavePic1Click(TObject *Sender)
	{
	if (!SaveDialog2->Execute()) return;
	String file = SaveDialog2->FileName;
	imgEcg->Picture->SaveToFile(file);
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::btRpeaksClick(TObject *Sender)
	{
	iarray_t curve = ecg.data.data_array;
	iarray_t rpeak = ecg.rpeaks.find(curve, NULL);
	farray.redisplay(curve, imgDeriv1);
	farray.displayPoints(curve, rpeak, imgDeriv1);
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::btQrsTurnsClick(TObject *Sender)
	{
	//QRS-Punkte bilden und in einem Image anzeigen
	ftools.Log("--------------------------------------------------");
	ftools.Log("Inside 28-Point-Finder");

	iarray_t curve = ecg.data.data_array;
	iarray_t rpeak = ecg.rpeaks.find(curve, imgDeriv1);
	int n = rpeak.size();
	ftools.Log("Anzahl R-Peaks: %d", n);
	if (n <= 0)
		{
		ftools.Log("\t-> Abbruch");
		return;
		}

	if (ecg.qrs.build(curve, rpeak))
		ftools.Log("Qrs-Bereiche gefunden: %d", ecg.qrs.count);
	else
		{
		ftools.Log("Keine Qrs-Bereiche gefunden -> Abbruch");
		return;
		}

	//Test: alle Qrs-Punkte des Signals anzeigen
	iarray_t points;
	ecg.qrs.reset();
	qrsArea qA;
	int ix = 0;
	while (ecg.qrs.next())
		{
		qA = ecg.qrs.QRS;
		points[ix].push_back(qA.Q.zeit); points[ix].push_back(qA.Q.wert); ix++;
		points[ix].push_back(qA.R.zeit); points[ix].push_back(qA.R.wert); ix++;
		points[ix].push_back(qA.S.zeit); points[ix].push_back(qA.S.wert); ix++;
		}

	ftools.Log("Punkte gefunden: %d", ix);
	farray.redisplay(curve, imgDeriv2);
	farray.displayPoints(curve, points, imgDeriv2);

	ftools.Log("--------------------------------------------------");
	}
//---------------------------------------------------------------------------
void __fastcall TfmEcgViewer::btSave2Click(TObject *Sender)
	{
	btSave2->Enabled = false;

	sEcgData data;
	BuildData(data);
	if (!fmysql.ecg.save(data))
		{
		Application->MessageBox(
			ftools.fmt("Daten konnten nicht gespeichert werden. Die Datenbank meldet:\n\n%s", fmysql.ecg.error_msg).c_str(),
			L"FEHLER",
			MB_OK);
		}
	Print("Daten erfolgreich gespeichert, Ident = %d", fmysql.ecg.row.ident);

	btSave2->Enabled = true;
	}
//---------------------------------------------------------------------------
void TfmEcgViewer::BuildData(sEcgData& data)
	{
	data.session  = 1;
	data.person   = 2;
	data.channel  = 1;
	data.state    = 1;
	data.posture  = 1;

	int ix = 0; double wert;
	iarray_t array = ecg.data.data_array;
	for (iarray_itr itr = array.begin(); itr != array.end(); itr++)
		{
		ilist_t& v = itr->second;
		wert = v[1];

		data.werte[ix] = wert;
		ix++;

		if (ix >= 3000) break;
		}
	}
//---------------------------------------------------------------------------

