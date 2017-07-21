//---------------------------------------------------------------------------
#ifndef ecg_viewerH
#define ecg_viewerH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
//---------------------------------------------------------------------------
#include <libs/core/classTools.h>
#include <libs/core/classArray.h>
#include <libs/core/classMath.h>
#include <libs/core/classEcg.h>
#include "definitions.h"
//TODO #include "Details.h"
//---------------------------------------------------------------------------
class TfmEcgViewer : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TBevel *Bevel1;
	TBevel *Bevel3;
	TPanel *pnInfo;
	TMemo *mInfo;
	TPanel *pnLeft;
	TBevel *Bevel4;
	TLabel *Label4;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label8;
	TLabel *Label11;
	TBevel *Bevel8;
	TPanel *Panel3;
	TLabel *Label1;
	TSpeedButton *btInputfile;
	TLabel *Label3;
	TLabel *Label2;
	TEdit *edInputfile;
	TComboBox *cbDelim;
	TComboBox *cbFormat;
	TComboBox *cbLead;
	TProgressBar *pbJob;
	TButton *btRead;
	TButton *btMovAv;
	TButton *btCut;
	TEdit *edGl1;
	TEdit *edGl2;
	TEdit *edGl3;
	TEdit *edCutVon;
	TEdit *edCutBis;
	TEdit *edVonSample;
	TEdit *edBisSample;
	TCheckBox *cxDropBegin;
	TPanel *pnBottom;
	TLabel *laCls;
	TMemo *memo;
	TButton *btSave2;
	TButton *btQrsTurns;
	TButton *btRpeaks;
	TPanel *pnClient;
	TImage *imgEcg;
	TBevel *BevelEcg;
	TImage *imgDeriv1;
	TImage *imgDeriv2;
	TBevel *BevelAbl1;
	TBevel *Bevel6;
	TTimer *tStartup;
	TOpenDialog *OpenDialog;
	TTimer *tDetails;
	TSaveDialog *SaveDialog;
	TPopupMenu *PopupMenu1;
	TMenuItem *estSavePic1;
	TSaveDialog *SaveDialog2;
	TActionList *ActionList1;
	TAction *acReadFile;
	TAction *acCutCurve;
	TAction *acMovingAv;
	TButton *btSave;
	TAction *acSaveArffFile;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acReadFileExecute(TObject *Sender);
	void __fastcall btInputfileClick(TObject *Sender);
	void __fastcall acCutCurveExecute(TObject *Sender);
	void __fastcall acMovingAvExecute(TObject *Sender);
	void __fastcall acSaveArffFileExecute(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbLeadChange(TObject *Sender);
	void __fastcall laClsClick(TObject *Sender);
	void __fastcall imgEcgMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall imgEcgMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall imgEcgMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall estSavePic1Click(TObject *Sender);
	void __fastcall btRpeaksClick(TObject *Sender);
	void __fastcall btQrsTurnsClick(TObject *Sender);
	void __fastcall btSave2Click(TObject *Sender);


private:
	cMySql&     fmysql;
	cTools		ftools;
	cEcg		ecg;
	cArray		farray;
	cMath		fmath;

	void 		Print(char* msg, ...);
	bool 		ReadFile(String ecgFile);
	bool		RemoveSegment(int von, int bis);
	bool		MovingAv(int window1, int window2, int window3, bool dropBegin);

	bool 		SaveArffFile();

	bool		bMausMarking;
	int			MausPosBegin;
	int			MausCurrPos;
	int			MausPosEnde;
	void		Line(int x, TColor cl);

	void 		BuildData(sEcgData& data);


public:
	__fastcall TfmEcgViewer(TComponent* Owner);
	__fastcall ~TfmEcgViewer();

	bool 		Execute();
};
//---------------------------------------------------------------------------
bool DlgEcgViewer(TForm* Papa);
//---------------------------------------------------------------------------
#endif
