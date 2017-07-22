//---------------------------------------------------------------------------
#ifndef ecg_dbviewerSignaleH
#define ecg_dbviewerSignaleH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include <libs/db/classMySql.h>
#include <libs/core/classTools.h>
#include <libs/core/classArray.h>
#include <libs/core/classEcg.h>
//---------------------------------------------------------------------------
class TfmViewSignal : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TPanel *pnBottom;
	TButton *Button1;
	TProgressBar *pbJob;
	TBevel *Bevel2;
	TTimer *tStartup;
	TActionList *ActionList;
	TAction *acClose;
	TListView *lvSignale;
	TPanel *pnClient;
	TImage *img;
	TMemo *mMsg;
	TButton *Button2;
	TButton *Button3;
	TAction *acPrevSignal;
	TAction *acNextSignal;
	TButton *Button4;
	TAction *acShowSignal;
	TAction *acCalcRpeaks;
	TButton *Button5;
	TButton *Button6;
	TAction *acCheckAllSignals;
	TCheckBox *cxAusgabe;
	TComboBox *cbCheckSignale;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall lvSignaleDblClick(TObject *Sender);
	void __fastcall acPrevSignalExecute(TObject *Sender);
	void __fastcall acNextSignalExecute(TObject *Sender);
	void __fastcall acShowSignalExecute(TObject *Sender);
	void __fastcall acCalcRpeaksExecute(TObject *Sender);
	void __fastcall acCheckAllSignalsExecute(TObject *Sender);

private:
	cMySql&     fmysql;
	cTools      ftools;
	cArray      farray;
	cEcg        fecg;

	void 		print(char* msg, ...);
	void 		LoadSignale();
	void        ShowSignal(int id);
	void        GetRpeaks(int id);

    bool        bAbort;
	void        CheckAllSignals();
	bool 		CheckSignal(int id, int& rpeaks_erwartet, int& rpeaks_gefunden);

public:
	__fastcall TfmViewSignal(TComponent* Owner);
	__fastcall ~TfmViewSignal();

	bool 		Execute();
};
//---------------------------------------------------------------------------
bool DlgDbViewerSignale(TForm* Papa);
//---------------------------------------------------------------------------
#endif
