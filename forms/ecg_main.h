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

#include <libs/core/classCsv.h>   //nur zu Testzwecken, später wieder entfernen
#include <libs/core/classMath.h>  //nur zu Testzwecken, später wieder entfernen
#include <libs/core/classArray.h> //nur zu Testzwecken, später wieder entfernen
#include <libs/core/classData.h>  //nur zu Testzwecken, später wieder entfernen
#include <libs/core/classEcg.h>   //nur zu Testzwecken, später wieder entfernen
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TTimer *tStartup;
	TStatusBar *StatusBar;
	TMemo *mInfo;
	TButton *btTestMySql;
	TButton *btTestCsv;
	TButton *btTestMath;
	TImage *img3;
	TImage *img2;
	TImage *img1;
	TButton *btTestArray;
	TButton *btTestData;
	TButton *btTestEcg;
	TImage *img4;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall btTestMySqlClick(TObject *Sender);
	void __fastcall btTestCsvClick(TObject *Sender);
	void __fastcall btTestMathClick(TObject *Sender);
	void __fastcall btTestArrayClick(TObject *Sender);
	void __fastcall btTestDataClick(TObject *Sender);
	void __fastcall btTestEcgClick(TObject *Sender);

private:
	cCsv        fcsv;   //nur zu Testzwecken, später wieder entfernen
	cMath       fmath;  //nur zu Testzwecken, später wieder entfernen
	cArray      farray; //nur zu Testzwecken, später wieder entfernen
	cData       fdata;  //nur zu Testzwecken, später wieder entfernen
	cEcg        fecg;   //nur zu Testzwecken, später wieder entfernen

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
