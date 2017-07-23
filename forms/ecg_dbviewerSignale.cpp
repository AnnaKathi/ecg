//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "ecg_dbviewerSignale.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmViewSignal *fmViewSignal;
//---------------------------------------------------------------------------
bool DlgDbViewerSignale(TForm* Papa)
	{
	TfmViewSignal* Form = new TfmViewSignal(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmViewSignal::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmViewSignal::TfmViewSignal(TComponent* Owner)
	: TForm(Owner)
    , fmysql(cMySql::getRef())
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmViewSignal::~TfmViewSignal()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmViewSignal::FormCreate(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmViewSignal::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	ftools.FormLoad(this);
	fmysql.sessions.listInCombo(cbFSession, 1);
	fmysql.people.listInCombo(cbFPerson, 2);
	fmysql.channels.listInCombo(cbFChannel, 1);

	LoadSignale();
	pnClient->Visible = true;

	TListItem* item = lvSignale->Items->Item[0];
    lvSignale->Selected = item;
	int id = (int)item->Data;
	ShowSignal(id);
	GetRpeaks(id);
	}
//---------------------------------------------------------------------------
void __fastcall TfmViewSignal::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmViewSignal::print(char* msg, ...)
	{
	char    buffer[512];
	int     nsiz;
	va_list argptr;

	va_start(argptr, msg);
	nsiz = vsnprintf(0, 0, msg, argptr);
	if (nsiz >= sizeof(buffer)-2) nsiz = sizeof(buffer)-2;

	vsnprintf(buffer, nsiz, msg, argptr);
	buffer[nsiz] = 0;

	mMsg->Lines->Add(buffer);
	va_end(argptr);
	}
//---------------------------------------------------------------------------
int TfmViewSignal::getSelectedListItem()
	{
	if (lvSignale->SelCount <= 0) return -1;
	TListItem* item = lvSignale->Selected;
	int id = (int)item->Data;
	return id;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/************   Funktionen: Daten laden, anzeigen und ändern   *************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmViewSignal::LoadSignale()
	{
	lvSignale->Items->Clear();
	sEcgData filter = BuildFilter();
	if (!fmysql.ecg.loadFilteredTable(filter))
		{
		ftools.ErrBox("Die Datenbank 'ecgdata' konnte nicht geladen werden. "
			"Die Klasse cMySql meldet: %s", AnsiString(fmysql.ecg.error_msg));
		return;
		}

	ftools.JobStart(pbJob, fmysql.ecg.num_rows);
	TListItem* item;
	sEcgData data;
	while (fmysql.ecg.nextRow())
		{
		ftools.JobTick();
		data = fmysql.ecg.row;
		item = lvSignale->Items->Add();
		item->Data     = (void*)data.ident;
		item->Caption  = String(data.ident);
		item->SubItems->Add(fmysql.sessions.getStampOf(data.session));
		item->SubItems->Add(fmysql.people.getNameOf(data.person));
		item->SubItems->Add(fmysql.channels.getNameOf(data.channel));
		item->SubItems->Add(fmysql.states.getNameOf(data.state));
		item->SubItems->Add(fmysql.postures.getNameOf(data.posture));
		}

	ftools.JobEnd();
	}
//---------------------------------------------------------------------------
sEcgData TfmViewSignal::BuildFilter()
	{
	sEcgData filter;
	filter.session   = cbFSession->ItemIndex;
	filter.person    = cbFPerson->ItemIndex;
	filter.channel   = cbFChannel->ItemIndex;
	filter.usability = cbFUsability->ItemIndex;

    //todo
	filter.state    = 0;
	filter.posture  = 0;
	filter.bpsys    = 0;
	filter.bpdia    = 0;
	filter.puls     = 0;
	filter.visBeats = 0;
	filter.note     = "";
	return filter;
	}
//---------------------------------------------------------------------------
void TfmViewSignal::ShowSignal(int id)
	{
	mMsg->Lines->Clear();
	if (!fmysql.ecg.loadByIdent(id))
		{
		ftools.ErrBox("Das EKG-Signal <%d> kann nicht geladen werden. "
			"Die Klasse cEcg meldet: %s", id, AnsiString(fmysql.ecg.error_msg));
		return;
		}

	fecg.data.getFromDb(fmysql.ecg.row.array_werte);
	fecg.data.redisplay(img);
    cbUsability->ItemIndex = fmysql.ecg.row.usability;

	print("Visuell identifizierte R-Peaks: \t%d", fmysql.ecg.row.visBeats);
	}
//---------------------------------------------------------------------------
void TfmViewSignal::SaveUsability(int id, int usability)
	{
	if (!fmysql.ecg.update("usability", usability, id))
		{
		ftools.ErrBox("Das EKG-Signal <%d> konnte nicht geändert werden. "
			"Die Klasse cMySql meldet: %s", id, AnsiString(fmysql.ecg.error_msg));
		}
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/***********   Funktionen: RPeaks für dieses Signal berechnen   ************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmViewSignal::GetRpeaks(int id)
	{
	//Daten sind schon von ShowSignal geladen worden
	if (!fecg.data.buildDerivates())
		{
		ftools.ErrBox("Es konnten keine Ableitungen gebildet werden. "
			"Die Klasse cData meldet: %s", AnsiString(fecg.data.error_msg));
		return;
		}

	iarray_t rpeaks_deriv = fecg.rpeaks.find(fecg.data.derivate1.deriv_array, NULL);
	int anz = rpeaks_deriv.size();
	if (anz <= 0)
		{
		ftools.ErrBox("Es konnten keine (Ableitung-)R-Peaks ermittelt werden. "
			"Die Klasse cData meldet: %s", AnsiString(fecg.data.error_msg));
		return;
		}

	iarray_t rpeaks = farray.getOriginalPoints(fecg.data.data_array, rpeaks_deriv);
	anz = rpeaks.size();
	if (anz <= 0)
		{
		ftools.ErrBox("Es konnten keine (Original-)R-Peaks ermittelt werden. "
			"Die Klasse cData meldet: %s", AnsiString(fecg.data.error_msg));
		return;
		}

	farray.displayPoints(fecg.data.data_array, rpeaks, img);
	if (anz == fmysql.ecg.row.visBeats)
		print("--> %d Rpeaks gefunden = identisch", anz);
	else
		print("### %d Rpeaks gefunden = NICHT IDENTISCH", anz);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/*********   Funktionen: RPeaks für alle Signale berechnen   ***************/
/***************************************************************************/
//---------------------------------------------------------------------------
//todo: in Klasse Rpeaks auslagern
void TfmViewSignal::CheckAllSignals()
	{
	int rpeaks_erwartet = 0;
	int rpeaks_gefunden = 0;
	int signal_korrekt  = 0;
	int signal_falsch   = 0;

	//Todo: nur die gewünschten Datensätze laden (posture)
	int posture   = cbCheckAllPosture->ItemIndex;
	int usability = cbCheckAllUsability->ItemIndex;
	if (!fmysql.ecg.loadTable())
		{
		ftools.ErrBox("Die Tabelle ecgdata konnte nicht geladen werden. "
			"Die Klasse cMySqlEcgData meldet: %s", AnsiString(fmysql.ecg.error_msg));
		return;
		}

	bAbort = false;
	bool bAusgabe = cxAusgabe->Checked;

	ftools.JobStart(pbJob, fmysql.ecg.getSize());
	int count = 0;
	while (fmysql.ecg.nextRow())
		{
		ftools.JobTick();
		if (posture > 0)
			{
			if (posture != fmysql.ecg.row.posture)
				continue;
			}

		if (usability > 0)
			{
			if (usability != fmysql.ecg.row.usability)
                continue;
			}

		count++;
		if (CheckSignal(fmysql.ecg.row.ident, rpeaks_erwartet, rpeaks_gefunden))
			{
			signal_korrekt++;
			if (bAusgabe) print("- Ecg <%03d> korrekt berechnet", fmysql.ecg.row.ident);
			}
		else
			{
			signal_falsch++;
			if (bAusgabe) print("# Ecg <%03d> FALSCH berechnet", fmysql.ecg.row.ident);
			}

		if (bAbort) break;
		}
	ftools.JobEnd();

	print("--------------------------------------");
	print("");
	print("Auswertung:");
	print("\tSignale bearbeitet: \t%d", count);
	print("\tSignale korrekt: \t%d", signal_korrekt);
	print("\tSignale falsch: \t%d", signal_falsch);
	print("\tR-Peaks erwartet: \t%d", rpeaks_erwartet);
	print("\tR-Peaks gefunden: \t%d", rpeaks_gefunden);
	print("");

	double anteil1 = (double)signal_korrekt / (double)count * 100;
	double anteil2 = (double)rpeaks_gefunden / (double)rpeaks_erwartet * 100;

	print("%.2f %s der Signale wurden korrekt berechnet", anteil1, "%");
	print("%.2f %s der erwarteten R-Peaks wurden gefunden", anteil2, "%");
	}
//---------------------------------------------------------------------------
bool TfmViewSignal::CheckSignal(int id, int& rpeaks_erwartet, int& rpeaks_gefunden)
	{
	fecg.data.getFromDb(fmysql.ecg.row.array_werte);
	if (!fecg.data.buildDerivates())
		{
		ftools.ErrBox("Es konnten keine Ableitungen gebildet werden. "
			"Die Klasse cData meldet: %s", AnsiString(fecg.data.error_msg));
		bAbort = false;
		return false;
		}

	iarray_t rpeaks_deriv = fecg.rpeaks.find(fecg.data.derivate1.deriv_array, NULL);
	int anz = rpeaks_deriv.size();
	if (anz <= 0)
		{
		ftools.ErrBox("Es konnten keine (Ableitung-)R-Peaks ermittelt werden. "
			"Die Klasse cData meldet: %s", AnsiString(fecg.data.error_msg));
		bAbort = false;
		return false;
		}

	iarray_t rpeaks = farray.getOriginalPoints(fecg.data.data_array, rpeaks_deriv);
	anz = rpeaks.size();
	if (anz <= 0)
		{
		ftools.ErrBox("Es konnten keine (Original-)R-Peaks ermittelt werden. "
			"Die Klasse cData meldet: %s", AnsiString(fecg.data.error_msg));
        bAbort = true;
		return false;
		}

	rpeaks_erwartet += fmysql.ecg.row.visBeats;
    rpeaks_gefunden += anz;
	if (anz == fmysql.ecg.row.visBeats)
		return true;
	else
		return false;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmViewSignal::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmViewSignal::acLoadDbExecute(TObject *Sender)
	{
    LoadSignale();
	}
//---------------------------------------------------------------------------
void __fastcall TfmViewSignal::acPrevSignalExecute(TObject *Sender)
	{
	if (lvSignale->Items->Count <= 0) return;
	if (lvSignale->Selected == NULL || lvSignale->ItemIndex == 0)
		{
		TListItem* item = lvSignale->Items->Item[0];
		lvSignale->Selected = item;
		}
	else
		{
		int ix = lvSignale->ItemIndex -1;
		if (ix < 0) ix = 0;
		TListItem* item = lvSignale->Items->Item[ix];
		lvSignale->Selected = item;
		}

	acShowSignalExecute(Sender);
    acCalcRpeaksExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmViewSignal::acNextSignalExecute(TObject *Sender)
	{
	if (lvSignale->Items->Count <= 0) return;
	int last = lvSignale->Items->Count-1;
	if (lvSignale->Selected == NULL || lvSignale->ItemIndex == last)
		{
		TListItem* item = lvSignale->Items->Item[last];
		lvSignale->Selected = item;
		}
	else
		{
		int ix = lvSignale->ItemIndex+1;
		if (ix > last) ix = last;
		TListItem* item = lvSignale->Items->Item[ix];
		lvSignale->Selected = item;
		}

	acShowSignalExecute(Sender);
    acCalcRpeaksExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmViewSignal::acShowSignalExecute(TObject *Sender)
	{
	int id = getSelectedListItem();
	if (id <= 0) return;
	ShowSignal(id);
	}
//---------------------------------------------------------------------------
void __fastcall TfmViewSignal::acChangeUsabilityExecute(TObject *Sender)
	{
	int id = getSelectedListItem();
	if (id <= 0) return;

	int usability = cbUsability->ItemIndex;
	if (usability <= 0) return;

	SaveUsability(id, usability);
	}
//---------------------------------------------------------------------------
void __fastcall TfmViewSignal::acCalcRpeaksExecute(TObject *Sender)
	{
	int id = getSelectedListItem();
	if (id <= 0) return;
    GetRpeaks(id);
	}
//---------------------------------------------------------------------------
void __fastcall TfmViewSignal::acCheckAllSignalsExecute(TObject *Sender)
	{
	CheckAllSignals();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmViewSignal::FormKeyPress(TObject *Sender, System::WideChar &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmViewSignal::lvSignaleDblClick(TObject *Sender)
	{
	acShowSignalExecute(Sender);
	acCalcRpeaksExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmViewSignal::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
	{
	 if (Shift.Contains(ssCtrl) && Key == 0x31)
		{
		cbUsability->ItemIndex = 1;
		acChangeUsabilityExecute(Sender);
		}
	else if (Shift.Contains(ssCtrl) && Key == 0x32)
		{
		cbUsability->ItemIndex = 2;
		acChangeUsabilityExecute(Sender);
		}
	else if (Shift.Contains(ssCtrl) && Key == 0x33)
		{
		cbUsability->ItemIndex = 3;
		acChangeUsabilityExecute(Sender);
		}
	}
//---------------------------------------------------------------------------

