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
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
#include <libs/core/classTools.h>
#include <forms/baseForms/basePeople.h>
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TTimer *tStartup;
	TStatusBar *StatusBar;
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TMainMenu *MainMenu;
	TMenuItem *ools1;
	TMenuItem *EKGuntersuchen1;
	TMenuItem *Datenanalyse1;
	TMenuItem *Datenbank1;
	TMenuItem *Session1;
	TActionList *ActionListGeneral;
	TAction *acClose;
	TPanel *pnMain;
	TBitBtn *btAnalysis;
	TBitBtn *btAnalysisSelect;
	TBitBtn *BitBtn8;
	TBitBtn *btDatabaseSelect;
	TBitBtn *btSessions;
	TBitBtn *btSessionsSelect;
	TBitBtn *btFeatures;
	TBitBtn *btFeaturesSelect;
	TBitBtn *btClassify;
	TBitBtn *btClassifySelect;
	TActionList *ActionListAnalysis;
	TAction *acAnalyseEcg;
	TPopupMenu *PopupMenuAnalysis;
	TMenuItem *EKGSignalanalysieren1;
	TActionList *ActionListDatabase;
	TPopupMenu *PopupMenuDatabase;
	TActionList *ActionList2;
	TPopupMenu *PopupMenuSessions;
	TActionList *ActionListFeatures;
	TPopupMenu *PopupMenuFeatures;
	TActionList *ActionListClassification;
	TPopupMenu *PopupMenuClassify;
	TAction *acEcgFileAdd;
	TMenuItem *EKGDateihinzufgen1;
	TAction *acAnalyseSignal;
	TMenuItem *EKGSignaleanalysieren1;
	TMenuItem *N1;
	TMenuItem *EKGDateianalysierenVorabtests1;
	TMenuItem *EKGSignaleanalysieren2;
	TMenuItem *Features1;
	TMenuItem *Klassifizierung1;
	TMenuItem *HerzschlgeausEKGSignalenseparieren1;
	TAction *acAnalyseBeats;
	TMenuItem *Herzschlgeanalysieren1;
	TMenuItem *Herzschlgeanalysieren2;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall acAnalyseEcgExecute(TObject *Sender);
	void __fastcall acEcgFileAddExecute(TObject *Sender);
	void __fastcall acAnalyseSignalExecute(TObject *Sender);
	void __fastcall btClassifySelectClick(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acAnalyseBeatsExecute(TObject *Sender);

private:
	cMySql&     fmysql;
	cTools      ftools;
	bool        bNoMySql;
	bool 		setupDatabase();
	void 		setStatus(String status, int panel = 0);
	void 		setDbInfo();

    void		CreateHeartbeats(); //todo auslagern in Klasse ??

public:
	__fastcall TfmMain(TComponent* Owner);
	__fastcall ~TfmMain();
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
