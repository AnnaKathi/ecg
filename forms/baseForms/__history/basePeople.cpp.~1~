//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>

#include "../classMySql.h"
#include "addPeople.h"
#include "basePeople.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmBasePeople *fmBasePeople;
extern cMySql fmysql;
//---------------------------------------------------------------------------
TfmBasePeople* CreatePeopleForm(TForm* caller, TWinControl* container, eListMode mode)
	{
	return new TfmBasePeople(caller, container, mode);
	}
//---------------------------------------------------------------------------
__fastcall TfmBasePeople::TfmBasePeople(TComponent* Owner, TWinControl* Container, eListMode mode)
	: TForm(Owner)
	{
	tCallback = NULL;
	bSelected = false;
	eMode = mode;
	if (Container)
		snapTo(Container, alClient);
	}
//---------------------------------------------------------------------------
void TfmBasePeople::snapTo(TWinControl* container, TAlign align)
	{
	int realHeight = ClientHeight;
	int realWidth  = ClientWidth;

	Parent  = container;
	Hint    = Caption;
	Caption = "";
	Left    = 0;
	Top     = 0;
	if (align != alNone) Align = align;
	BorderIcons = TBorderIcons();
	BorderStyle = bsNone;

	ParentFont  = true;
	ParentColor = true;

	Height = realHeight;
	Width  = realWidth;
	Show();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::FormShow(TObject *Sender)
	{
	bInShow = false;
	tStartup->Enabled = true;
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::tStartupTimer(TObject *Sender)
	{
	tStartup->Enabled = false;
	laTabelle->Caption = "Personen (subjects)";
	ShowData();
	tStartup->Tag = 1; //signalisiert, dass der Init durchgeführt wurde
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::FormClose(TObject *Sender,
	  TCloseAction &Action)
	{
	//
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: public   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool TfmBasePeople::setCallback(TTimer& timer)
	{
	tCallback = &timer;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmBasePeople::ShowData()
	{
	if (bInShow) return false; //verhindern, dass sich die Funktion selbst überholt
	bInShow = true;
	lvPeople->Items->Clear();
	lvPeople->Items->BeginUpdate();

	if (!fmysql.people.loadTable(""))
		{
		ftools.ErrBox("Die Daten (Personen) konnten nicht geladen werden. "
			"Die Datenbank  meldet: %s", fmysql.people.error_msg);
		return false;
		}

	TListItem* item;
	String name;
	int s;
	while (fmysql.people.nextRow())
		{
		if (!CheckFilter()) continue;

		item = lvPeople->Items->Add();
		int person = fmysql.people.row.ident;
		item->Data = (void*) person;
		item->Caption = String(person);
		item->SubItems->Add(fmysql.people.row.firstname);
		item->SubItems->Add(fmysql.people.row.lastname);
		item->SubItems->Add(String(fmysql.people.row.age));
		s = fmysql.people.row.sex;
		if (s == 1)
			item->SubItems->Add("w");
		else
			item->SubItems->Add("m");
		}

	lvPeople->Items->EndUpdate();
	bInShow = false;
	return true;
	}
//---------------------------------------------------------------------------
bool TfmBasePeople::BuildFilter()
	{
	ffilter.identVon = edIdVon->Text.ToIntDef(-1);
	ffilter.identBis = edIdBis->Text.ToIntDef(-1);

	ffilter.name = edName->Text;

	ffilter.ageVon = edAgeVon->Text.ToIntDef(-1);
	ffilter.ageBis = edAgeBis->Text.ToIntDef(-1);

	ffilter.sex = cbSex->ItemIndex;

	return true;
	}
//---------------------------------------------------------------------------
bool TfmBasePeople::CheckFilter()
	{
	int id = fmysql.people.row.ident;
	if (ffilter.identVon > 0 && id < ffilter.identVon) return false;
	if (ffilter.identBis > 0 && id > ffilter.identBis) return false;

	if (ffilter.name != "")
		{
		//enthält-Suche
		String nn = fmysql.people.getNameOf(id).LowerCase();
		if (nn.Pos(ffilter.name.LowerCase()) <= 0)
			return false;
		}

	if (ffilter.ageVon > 0 && fmysql.people.row.age < ffilter.ageVon) return false;
	if (ffilter.ageBis > 0 && fmysql.people.row.age > ffilter.ageBis) return false;

	if (ffilter.sex > 0)
		{
		if (ffilter.sex == 1 && fmysql.people.row.sex != 0) return false;
		if (ffilter.sex == 2 && fmysql.people.row.sex != 1) return false;
		}

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Actions   ******************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::acAddExecute(TObject *Sender)
	{
	DlgPersonAdd(this);
	ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::acChangeExecute(TObject *Sender)
	{
	if (lvPeople->SelCount <= 0) return;
	TListItem* item = lvPeople->Selected;
	int id = (int)item->Data;
	DlgPersonChange(this, id);
	ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::acDelExecute(TObject *Sender)
	{
	if (lvPeople->SelCount <= 0) return;
	TListItem* item = lvPeople->Selected;
	int id = (int)item->Data;
	if (!fmysql.people.deleteByIdent(id))
		{
		ftools.ErrBox("Die Person <%d> konnten nicht gelöscht werden. "
			"Die Datenbank  meldet: %s", id, fmysql.people.error_msg);
		}
	else
		ShowData();
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::acFilterExecute(TObject *Sender)
	{
	if (tStartup->Tag == 1) //Init wurde schon durchgeführt
		{
		BuildFilter();
		ShowData();
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::acSelectExecute(TObject *Sender)
	{
	//den Ident der ausgewählten Person an das aufrufende Formular zurückgeben
	//todo: als Callback auslegen
	if (!tStartup->Tag == 1) return;
	if (lvPeople->SelCount <= 0) return;
	if (tCallback == NULL) return;
	
	TListItem* item = lvPeople->Selected;
	int id = (int)item->Data;
	if (id <= 0) return;

	bSelected = true;
	iPerson = id;
	tCallback->Enabled = true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   Meldungen vom Formular   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::lvPeopleClick(TObject *Sender)
	{
	TListItem* item = lvPeople->Selected;
	if (item)
		{
		acDel->Enabled    = true;
		acChange->Enabled = true;
		acSelect->Enabled = true;
		}
	else
		{
		acDel->Enabled    = false;
		acChange->Enabled = false;
		acSelect->Enabled = false;
		}

	//ggf. getroffene Auswahl wieder aufheben
	if (bSelected)
		{
		bSelected = false;
		ShowData();
		tCallback->Enabled = true;
		}
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::edIdVonExit(TObject *Sender)
	{
	acFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::edNameChange(TObject *Sender)
	{
	acFilterExecute(Sender);
	}
//---------------------------------------------------------------------------
void __fastcall TfmBasePeople::lvPeopleDblClick(TObject *Sender)
	{
	TListItem* item = lvPeople->Selected;
	if (!item) return;

	if (eMode == eShow)
		acChangeExecute(Sender);
	else if (eMode == eSingleSelect)
		acSelectExecute(Sender);
	else if (eMode == eMultiSelect)
		; //todo
	}
//---------------------------------------------------------------------------

