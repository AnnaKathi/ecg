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
	fmysql.positions.listInCombo(cbChannelTest1, 1);
	fmysql.positions.listInCombo(cbChannelTest2, 2);
	fmysql.positions.listInCombo(cbChannel12,    3);
	fmysql.positions.listInCombo(cbChannel34,    4);
	fmysql.positions.listInCombo(cbChannel56,    5);

	fmysql.people.listInCombo(cbPerson, 2);
	fmysql.sessions.listInCombo(cbSession, 1);
	fmysql.states.listInCombo(cbState, 1);
    fmysql.postures.listInCombo(cbPosture, 1);

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
	if (edEkg->Text == "") return false;

	//von den Channeln muss min. einer ausgewählt sein
	if (cbChannelTest1->ItemIndex < 0 && cbChannelTest2->ItemIndex < 0 &&
		cbChannel12->ItemIndex    < 0 && cbChannel34->ItemIndex    < 0 &&
		cbChannel56->ItemIndex    < 0)
        return false;

	if (cbSession->ItemIndex < 0) return false;
	if (cbPerson->ItemIndex  < 0) return false;
	if (cbState->ItemIndex   < 0) return false;
	if (cbPosture->ItemIndex < 0) return false;

	if (edBPSys->Text == "") return false;
	if (edBPDia->Text == "") return false;
	if (edPuls->Text  == "") return false;

	if (edRpeaks1->Text == "") return false;
	if (edRpeaks2->Text == "") return false;
	if (edRpeaks3->Text == "") return false;
	if (edRpeaks4->Text == "") return false;
	if (edRpeaks5->Text == "") return false;

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

	eLead lead1 = eLead(cbChannelTest1->ItemIndex); if (lead1 > eChannel56) lead1 = eChannel56;
	eLead lead2 = eLead(cbChannelTest2->ItemIndex); if (lead2 > eChannel56) lead2 = eChannel56;
	eLead lead3 = eLead(cbChannel12->ItemIndex);    if (lead3 > eChannel56) lead3 = eChannel56;
	eLead lead4 = eLead(cbChannel34->ItemIndex);    if (lead4 > eChannel56) lead4 = eChannel56;
	eLead lead5 = eLead(cbChannel56->ItemIndex);    if (lead5 > eChannel56) lead5 = eChannel56;
	if (lead1 <= eNone && lead2 <= eNone  && lead3 <= eNone &&
		lead4 <= eNone && lead5 <= eNone)
		{
		ftools.ErrBox("Die Channel-Einstellungen stimmen nicht. "
			"Mindestens eine ComboBox ist nicht richtig gesetzt.");
		return false;
		}

	fecg1.number = 1; fecg1.file = ecgFile; fecg1.image = img1;
	fecg2.number = 2; fecg2.file = ecgFile; fecg2.image = img2;
	fecg3.number = 3; fecg3.file = ecgFile; fecg3.image = img3;
	fecg4.number = 4; fecg4.file = ecgFile; fecg4.image = img4;
	fecg5.number = 5; fecg5.file = ecgFile; fecg5.image = img5;


	JobStart(5); if (!DisplayEcg(fecg1, lead1)) return false;
	JobTick();   if (!DisplayEcg(fecg2, lead2)) return false;
	JobTick();   if (!DisplayEcg(fecg3, lead3)) return false;
	JobTick();   if (!DisplayEcg(fecg4, lead4)) return false;
	JobTick();   if (!DisplayEcg(fecg5, lead5)) return false;
	JobTick();   JobEnd();

	return true;
	}
//---------------------------------------------------------------------------
bool TfmAddFile::DisplayEcg(cEcg& fecg, eLead lead)
	{
	if (!fecg.data.getFile(fecg.file, formatADS, "\t", lead, 0, 3000))
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

	JobStart(6);

	//fecg-Klassen sind durch ShowFile() gefüllt worden
	sEcgData data;
	data.session = (int)cbSession->Items->Objects[cbSession->ItemIndex];
	data.person  = (int)cbPerson->Items->Objects[cbPerson->ItemIndex];
	data.state   = (int)cbState->Items->Objects[cbState->ItemIndex];
	data.posture = (int)cbPosture->Items->Objects[cbPosture->ItemIndex];
	data.bpsys   = edBPSys->Text.ToInt();
	data.bpdia   = edBPDia->Text.ToInt();
	data.puls    = edPuls->Text.ToInt();
	data.note    = mNote->Text;

	int count = 0;
	JobTick();
	if (cbChannelTest1->ItemIndex > 0)
		{
		data.position = (int)cbChannelTest1->Items->Objects[cbChannelTest1->ItemIndex];
		data.visBeats = edRpeaks1->Text.ToInt();
		if (!SaveLead(fecg1, data)) return false;
		count++;
		}

	JobTick();
	if (cbChannelTest2->ItemIndex > 0)
		{
		data.position = (int)cbChannelTest2->Items->Objects[cbChannelTest2->ItemIndex];
		data.visBeats = edRpeaks2->Text.ToInt();
		if (!SaveLead(fecg2, data)) return false;
		count++;
		}

	JobTick();
	if (cbChannel12->ItemIndex > 0)
		{
		data.position = (int)cbChannel12->Items->Objects[cbChannel12->ItemIndex];
		data.visBeats = edRpeaks3->Text.ToInt();
		if (!SaveLead(fecg3, data)) return false;
		count++;
		}

	JobTick();
	if (cbChannel34->ItemIndex > 0)
		{
		data.position = (int)cbChannel34->Items->Objects[cbChannel34->ItemIndex];
		data.visBeats = edRpeaks4->Text.ToInt();
		if (!SaveLead(fecg4, data)) return false;
		count++;
		}

	JobTick();
	if (cbChannel56->ItemIndex > 0)
		{
		data.position = (int)cbChannel56->Items->Objects[cbChannel56->ItemIndex];
		data.visBeats = edRpeaks5->Text.ToInt();
		if (!SaveLead(fecg5, data)) return false;
		count++;
		}

	JobTick();
	ftools.MsgBox("Speichern erfolgreich, es wurden %s Signale gespeichert", String(count));
    JobEnd();
	return true;
	}
//---------------------------------------------------------------------------
bool TfmAddFile::SaveLead(cEcg& fecg, sEcgData& data)
	{
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
	if (SaveFile())
    	acCloseExecute(Sender);
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

