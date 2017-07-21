//---------------------------------------------------------------------------
#ifndef ecg_mainH
#define ecg_mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <libs/core/classTools.h>
#include <forms/baseForms/basePeople.h>
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TTimer *tStartup;
	TStatusBar *StatusBar;
	TMemo *mInfo;
	TButton *btTestMySql;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall btTestMySqlClick(TObject *Sender);

private:
	cMySql&     fmysql;
	cTools      ftools;
	bool        bNoMySql;
	bool 		setupDatabase();
	void 		setStatus(String status, int panel = 0);
	void 		setDbInfo();

	void 		ln(String line); //todo: zu Testzwecken, später wieder entfernen

public:
	__fastcall TfmMain(TComponent* Owner);
	__fastcall ~TfmMain();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
