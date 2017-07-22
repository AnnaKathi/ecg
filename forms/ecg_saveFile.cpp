//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ecg_saveFile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmAddFile *fmAddFile;
//---------------------------------------------------------------------------
bool DlgSaveEcgFile(TForm* Papa)
	{
	TfmAddFile* Form = new TfmAddFile(Papa);
	bool rc = false;

	if (Form)
		{
		rc = Form->Execute();
		delete Form;
		}
	return rc;
	}
//---------------------------------------------------------------------------
bool TfmAddFile::Execute()
	{
	ShowModal();
	return true;
	}
//---------------------------------------------------------------------------
__fastcall TfmAddFile::TfmAddFile(TComponent* Owner)
	: TForm(Owner)
    , fmysql(cMySql::getRef())
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmAddFile::~TfmAddFile()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddFile::FormCreate(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddFile::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	fmysql.postures.listInCombo(cbPosture, 1);
	fmysql.sessions.listInCombo(cbSession, 1);
	fmysql.people.listInCombo(cbPerson,    2);
	fmysql.states.listInCombo(cbState,     1);

	ftools.FormLoad(this);
	if (FormComplete()) ShowFile(edEkg->Text);
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddFile::FormClose(TObject *Sender, TCloseAction &Action)
	{
	ftools.FormSave(this);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void TfmAddFile::JobStart(int max)
	{
	pbJob->Max = max;
	pbJob->Position = 0;
	pbJob->Visible = true;
	}
//---------------------------------------------------------------------------
void TfmAddFile::JobTick(int pos) //pos ist mit 0 vorbesetzt
	{
	pbJob->Position += pos;
	}
//---------------------------------------------------------------------------
void TfmAddFile::JobEnd()
	{
	pbJob->Visible = false;
	}
//---------------------------------------------------------------------------
bool TfmAddFile::FormComplete()
	{
	if (edEkg->Text    == "") return false;
	if (edRpeaks->Text == "") return false;

	if (cbChannel56->ItemIndex <= 0) return false;
	if (cbSaveLeads->ItemIndex < 0)  return false;

	if (cbSession->ItemIndex < 0) return false;
	if (cbPerson->ItemIndex  < 0) return false;
	if (cbState->ItemIndex   < 0) return false;
	if (cbPosture->ItemIndex < 0) return false;

	if (edBPSys->Text == "") return false;
	if (edBPDia->Text == "") return false;
	if (edPuls->Text  == "") return false;

	return true;
	}
//---------------------------------------------------------------------------
bool TfmAddFile::ShowFile(String ecgFile)
	{
	if (ecgFile == "" || !FileExists(ecgFile))
		{
		ftools.ErrBox("Die Datei <%s> konnte nicht gefunden werden", ecgFile);
		return false;
		}


	eSave save = eSave(cbSaveLeads->ItemIndex);
	if (save < eSaveAll || save > eSave56Only)
		{
		ftools.ErrBox("Die Save-Einstellungen stimmen nicht.");
		return false;
		}

	eChannel channel = eChannel(cbChannel56->ItemIndex);
	if (channel <= eNone)
		{
		ftools.ErrBox("Die Channel-Einstellungen stimmen nicht.");
		return false;
		}

	fecg2.number = 2; fecg2.file = ecgFile; fecg2.image = img2;
	fecg3.number = 3; fecg3.file = ecgFile; fecg3.image = img3;
	fecg4.number = 4; fecg4.file = ecgFile; fecg4.image = img4;
	fecg5.number = 5; fecg5.file = ecgFile; fecg5.image = img5;
	fecg6.number = 6; fecg6.file = ecgFile; fecg6.image = img6;
	fecg7.number = 7; fecg7.file = ecgFile; fecg7.image = img7;
	fecg8.number = 8; fecg8.file = ecgFile; fecg8.image = img8;

	fecg12.number = 12; fecg12.file = ecgFile; fecg12.image = img12;
	fecg34.number = 34; fecg34.file = ecgFile; fecg34.image = img34;
	fecg56.number = 56; fecg56.file = ecgFile; fecg56.image = img56;

	JobStart(9); if (!DisplayEcg(fecg2,  eChannel2))  return false;
	JobTick();   if (!DisplayEcg(fecg3,  eChannel3))  return false;
	JobTick();   if (!DisplayEcg(fecg4,  eChannel4))  return false;
	JobTick();   if (!DisplayEcg(fecg5,  eChannel5))  return false;
	JobTick();   if (!DisplayEcg(fecg6,  eChannel6))  return false;
	JobTick();   if (!DisplayEcg(fecg7,  eChannel7))  return false;
	JobTick();   if (!DisplayEcg(fecg8,  eChannel8))  return false;
	JobTick();   if (!DisplayEcg(fecg12, eChannel12)) return false;
	JobTick();   if (!DisplayEcg(fecg34, eChannel34)) return false;

	JobTick(); if (!DisplayEcg(fecg56, eChannel56Hand))	return false;
	JobEnd();

	return true;
	}
//---------------------------------------------------------------------------
bool TfmAddFile::DisplayEcg(cEcg& fecg, eChannel channel)
	{
	if (!fecg.data.getFile(fecg.file, formatADS, "\t", channel, 0, 3000))
		{
		ftools.ErrBox("Die Datei <%s> konnte nicht eingelesen werden.\r\n"
			"Die Klasse cEcg (%) meldet: %s", fecg.file, fecg.number, fecg.error_msg);
		return false;
		}
	else
		fecg.data.redisplay(fecg.image);
    return true;
	}
//---------------------------------------------------------------------------
bool TfmAddFile::SaveFile()
	{
	if (!FormComplete())
		{
		ftools.ErrBox("Das Formular ist nicht vollständig!");
		return false;
		}

	JobStart(11);

	//fecg-Klassen sind durch ShowFile() gefüllt worden
	sEcgData data;
	data.session  = (int)cbSession->Items->Objects[cbSession->ItemIndex];
	data.person   = (int)cbPerson->Items->Objects[cbPerson->ItemIndex];
	data.state    = (int)cbState->Items->Objects[cbState->ItemIndex];
	data.posture  = (int)cbPosture->Items->Objects[cbPosture->ItemIndex];
	data.bpsys    = edBPSys->Text.ToInt();
	data.bpdia    = edBPDia->Text.ToInt();
	data.puls     = edPuls->Text.ToInt();
	data.visBeats = edRpeaks->Text.ToInt();
	data.note     = mNote->Text;

	int count = 0;
	if (cbSaveLeads->ItemIndex == eSaveAll)
		{
		JobTick(); if (!SaveLead(fecg2,  data, eChannel2))  return false; count++;
		JobTick(); if (!SaveLead(fecg3,  data, eChannel3))  return false; count++;
		JobTick(); if (!SaveLead(fecg4,  data, eChannel4))  return false; count++;
		JobTick(); if (!SaveLead(fecg5,  data, eChannel5))  return false; count++;
		JobTick(); if (!SaveLead(fecg6,  data, eChannel6))  return false; count++;
		JobTick(); if (!SaveLead(fecg7,  data, eChannel7))  return false; count++;
		JobTick(); if (!SaveLead(fecg8,  data, eChannel8))  return false; count++;
		JobTick(); if (!SaveLead(fecg12, data, eChannel12)) return false; count++;
		JobTick(); if (!SaveLead(fecg34, data, eChannel34)) return false; count++;
		}

	JobTick();
	if (cbChannel56->ItemIndex == 1)
		{
		if (!SaveLead(fecg56, data, eChannel56Hand))
			return false;
		}
	else if (cbChannel56->ItemIndex == 2)
		{
		if (!SaveLead(fecg56, data, eChannel56Hals))
			return false;
		}
	else if (cbChannel56->ItemIndex == 3)
		{
		if (!SaveLead(fecg56, data, eChannel56Ohren))
			return false;
		}
	count++;

	JobTick();
	ftools.MsgBox("Speichern erfolgreich, es wurden %s Signal(e) gespeichert", String(count));
    JobEnd();
	return true;
	}
//---------------------------------------------------------------------------
bool TfmAddFile::SaveLead(cEcg& fecg, sEcgData& data, eChannel channel)
	{
    data.channel = channel;
	data.array_werte = fecg.data.data_array;
	if (!fmysql.ecg.saveWithArray(data))
		{
		ftools.ErrBox("Kanal %s konnte nicht gespeichert werden. "
			"Die Klasse cMySql meldet: %s", String(fecg.number), String(fmysql.ecg.error_msg));
		return false;
		}
	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmAddFile::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddFile::acSaveExecute(TObject *Sender)
	{
	SaveFile();
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddFile::acSaveUpdate(TObject *Sender)
	{
	if (FormComplete()) acSave->Enabled = true;
	else                acSave->Enabled = false;
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddFile::acLoadFileExecute(TObject *Sender)
	{
	if (!OpenDialog->Execute()) return;
	edEkg->Text = OpenDialog->FileName;
	ShowFile(edEkg->Text);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmAddFile::FormKeyPress(TObject *Sender, System::WideChar &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmAddFile::cbChannelTest1Change(TObject *Sender)
	{
	String file = edEkg->Text;
	if (!FileExists(file)) return;
	ShowFile(file);
	}
//---------------------------------------------------------------------------

