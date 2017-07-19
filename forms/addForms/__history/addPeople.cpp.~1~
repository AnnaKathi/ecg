//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "classMySql.h"
#include "addDesc.h"
#include "addPeople.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmPerson *fmPerson;
extern cMySql fmysql;
//---------------------------------------------------------------------------
int DlgPersonAdd(TForm* Papa)
	{
	TfmPerson* Form = new TfmPerson(Papa);
	int ident = -1;

	if (Form)
		{
		ident = Form->Execute(-1);
		delete Form;
		}
	return ident;
	}
//---------------------------------------------------------------------------
int DlgPersonChange(TForm* Papa, int ident)
	{
	TfmPerson* Form = new TfmPerson(Papa);

	if (Form)
		{
		Form->Execute(ident);
		delete Form;
		}
	return ident;
	}
//---------------------------------------------------------------------------
int TfmPerson::Execute(int person)
	{
	iPerson = person;
	person < 0 ? bNewPerson = true : bNewPerson = false;

	ShowModal();
	return iPerson;
	}
//---------------------------------------------------------------------------
__fastcall TfmPerson::TfmPerson(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
__fastcall TfmPerson::~TfmPerson()
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::FormShow(TObject *Sender)
	{
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;

	fmysql.diseases.listInCombo(cbDiseases, 1);
	
	lvDiseases->Items->Clear();
	if (bNewPerson)
		{
		edVorname->Text  = "";
		edNachname->Text = "";
		cbSex->ItemIndex = 0;
		edAge->Text      = "";
		edHeight->Text   = "";
		edWeight->Text   = "";
		}
	else
		{
		if (!fmysql.people.get(iPerson))
			{
			Application->MessageBox(
				ftools.fmt("Die Person <%d> konnte nicht gefunden werden.", iPerson).c_str(),
				"Fehler beim Laden", MB_OK);
			Close();
			return;
			}
		else
			{
			edVorname->Text  = fmysql.people.row.firstname;
			edNachname->Text = fmysql.people.row.lastname;
			cbSex->ItemIndex = fmysql.people.row.sex;
			edAge->Text      = String(fmysql.people.row.age);
			edHeight->Text   = String(fmysql.people.row.height);
			edWeight->Text   = String(fmysql.people.row.weight);


			sarray_t dis;
			dis = fmysql.people.getDiseasesOf(iPerson);
			dis = fmysql.diseases.getNamesOf(dis);

			TListItem* item;
			for (sarray_itr itr = dis.begin(); itr != dis.end(); itr++)
				{
				slist_t& v = itr->second;
				item = lvDiseases->Items->Add();
				item->Data = (void*) v[0].ToInt();
				item->Caption = v[0];
				item->SubItems->Add(v[1]);
				}
			}
		}

	if (bNewPerson) Caption = "Person anlegen";
	else Caption = "Person ändern";
	edVorname->SetFocus();
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::FormClose(TObject *Sender, TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool TfmPerson::SaveData()
	{
	if (edVorname->Text == "" || edNachname->Text == "") return false;
	if (cbSex->ItemIndex < 0) return false;
	if (edAge->Text == "" || edHeight->Text == "" || edWeight->Text == "") return false;

	sPeople data;
	data.ident = iPerson;
	sprintf(data.firstname, "%.127s", edVorname->Text.c_str());
	sprintf(data.lastname,  "%.127s", edNachname->Text.c_str());
	data.sex = cbSex->ItemIndex;
	data.age = edAge->Text.ToInt();
	data.height = edHeight->Text.ToInt();
	data.weight = edWeight->Text.ToInt();

	if (bNewPerson)
		{
		if (!fmysql.people.insert(data))
			{
			//todo Fehlermeldung
			return false;
			}
		else
			iPerson = fmysql.people.row.ident; //wird durch insert gesetzt
		}
		
	else if (!bNewPerson && !fmysql.people.update(data))
		{
		//todo Fehlermeldung
		return false;
		}

	//Erkrankungen speichern
	int dis;
	TListItem* item;
	sarray_t diseases; diseases.clear();
	for (int i = 0; i < lvDiseases->Items->Count; i++)
		{
		item = lvDiseases->Items->Item[i];
		dis = (int)item->Data;
        diseases[i].push_back(String(dis));
		}

	if (!fmysql.people.saveDiseases(iPerson, diseases))
		return false;
	else
		return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmPerson::acCloseExecute(TObject *Sender)
	{
	Close();
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::acSaveExecute(TObject *Sender)
	{
	if (SaveData())
		acCloseExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::acDisAddExecute(TObject *Sender)
	{
	DlgDescDbAdd(this, fmysql.diseases);
	fmysql.diseases.listInCombo(cbDiseases, 1);
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::acDisDelExecute(TObject *Sender)
	{
	if (lvDiseases->SelCount <= 0)
		{
		acDisDel->Enabled = false;
		return;
		}

	TListItem* item = lvDiseases->Selected;
	item->Delete();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmPerson::FormKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_ESCAPE)
		{
		Key = 0;
		acCloseExecute(Sender);
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::cbDiseasesKeyPress(TObject *Sender, char &Key)
	{
	if (Key == VK_RETURN)
		{
		int n = cbDiseases->ItemIndex;

		int id = (int)cbDiseases->Items->Objects[n];
		String dis = cbDiseases->Items->Strings[n];

		TListItem* item = lvDiseases->Items->Add();
		item->Data = (void*) id;
		item->Caption = String(id);
		item->SubItems->Add(dis);
		cbDiseases->DeleteSelected();
		cbDiseases->Text = "";
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::lvDiseasesClick(TObject *Sender)
	{
	if (lvDiseases->SelCount > 0)
		acDisDel->Enabled = true;
	else
		acDisDel->Enabled = false;
	}
//---------------------------------------------------------------------------
void __fastcall TfmPerson::edAgeKeyPress(TObject *Sender, char &Key)
	{
	//todo, nur nummerische Tasten erlauben
	}
//---------------------------------------------------------------------------

