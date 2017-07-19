//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ecg_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmMain *fmMain;
//---------------------------------------------------------------------------
__fastcall TfmMain::TfmMain(TComponent* Owner)
	: TForm(Owner)
	{
	}
//---------------------------------------------------------------------------
void __fastcall TfmMain::Button1Click(TObject *Sender)
	{
	TfmBasePeople* fm = CreatePeopleForm(this, pnPeople, eShow);
	fm->Show();
    //
	}
//---------------------------------------------------------------------------
