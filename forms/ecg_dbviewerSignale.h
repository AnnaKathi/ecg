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
	TComboBox *cbCheckAllPosture;
	TLabel *Label1;
	TComboBox *cbUsability;
	TAction *acChangeUsability;
	TComboBox *cbCheckAllUsability;
	TPanel *pnLeft;
	TListView *lvData;
	TPanel *pnDbFilter;
	TBevel *Bevel3;
	TButton *Button7;
	TAction *acLoadDb;
	TLabel *Label2;
	TLabel *Label3;
	TComboBox *cbFSession;
	TComboBox *cbFPerson;
	TLabel *Label4;
	TLabel *Label5;
	TComboBox *cbFChannel;
	TLabel *Label6;
	TComboBox *cbFUsability;
	TButton *Button8;
	TAction *acCreateBeats;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall lvDataDblClick(TObject *Sender);
	void __fastcall acPrevSignalExecute(TObject *Sender);
	void __fastcall acNextSignalExecute(TObject *Sender);
	void __fastcall acShowSignalExecute(TObject *Sender);
	void __fastcall acCalcRpeaksExecute(TObject *Sender);
	void __fastcall acCheckAllSignalsExecute(TObject *Sender);
	void __fastcall acChangeUsabilityExecute(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall acLoadDbExecute(TObject *Sender);
	void __fastcall acCreateBeatsExecute(TObject *Sender);

private:
	cMySql&     fmysql;
	cTools      ftools;
	cArray      farray;
	cEcg        fecg;
    bool        bIsSignal;

	//-- Hilfsfunktionen
	void 		print(char* msg, ...);
	int         getSelectedListItem();

	//-- Daten laden, anzeigen und ändern
	void 		LoadSignale();
	void 		LoadBeats();
	void        ShowKurve(int id);
	void        SaveUsability(int id, int usability);

	//-- R-Peaks für dieses Signal berechnen
	void        GetRpeaks(int id);

	//-- R-Peaks über alle Signale berechnen, todo: auslagern in Klasse RPeaks
    bool        bAbort;
	void        CheckAllSignals();
	bool 		CheckSignal(int id, int& rpeaks_erwartet, int& rpeaks_gefunden);

	//-- Herzschläge berechnen, todo: auslagern in Klasse ??
    void        CreateHeartbeats();

public:
	__fastcall TfmViewSignal(TComponent* Owner);
	__fastcall ~TfmViewSignal();

	bool 		Execute(bool isSignal);
};
//---------------------------------------------------------------------------
bool DlgDbViewerSignale(TForm* Papa, bool isSignal);
//---------------------------------------------------------------------------
#endif
