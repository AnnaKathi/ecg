//---------------------------------------------------------------------------

#ifndef ecg_mainH
#define ecg_mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include <forms/baseForms/basePeople.h>
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TButton *Button1;
	TPanel *pnPeople;
	void __fastcall Button1Click(TObject *Sender);
private:	// Benutzer-Deklarationen

public:		// Benutzer-Deklarationen
	__fastcall TfmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif