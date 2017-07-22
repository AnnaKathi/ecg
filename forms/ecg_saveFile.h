//---------------------------------------------------------------------------
#ifndef ecg_saveFileH
#define ecg_saveFileH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <libs/db/classMySql.h>
#include <libs/core/classTools.h>
#include <libs/core/classEcg.h>
//---------------------------------------------------------------------------
enum eSave {
	eSaveAll = 0,
    eSave56Only
	};
//---------------------------------------------------------------------------
enum eChannel {
	eNone = 0,
	eChannel1 = 1,
	eChannel2,
	eChannel3,
	eChannel4,
	eChannel5,
	eChannel6,
	eChannel7,
	eChannel8,
	eChannel12,
	eChannel34,
	eChannel56Hand,
	eChannel56Hals,
	eChannel56Ohren
	};
//---------------------------------------------------------------------------
class TfmAddFile : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TPanel *pnBottom;
	TBevel *Bevel2;
	TActionList *ActionList;
	TTimer *tStartup;
	TAction *acClose;
	TButton *Button1;
	TAction *acSave;
	TButton *Button2;
	TOpenDialog *OpenDialog;
	TPanel *pnLeft;
	TBevel *Bevel3;
	TLabel *Label1;
	TEdit *edEkg;
	TSpeedButton *SpeedButton1;
	TAction *acLoadFile;
	TLabel *Label2;
	TLabel *Label7;
	TComboBox *cbChannel56;
	TPanel *pnClient;
	TImage *img12;
	TImage *img34;
	TImage *img56;
	TImage *img2;
	TLabel *Label9;
	TLabel *Label10;
	TComboBox *cbPerson;
	TComboBox *cbSession;
	TLabel *Label11;
	TLabel *Label12;
	TComboBox *cbState;
	TComboBox *cbPosture;
	TLabel *Label13;
	TLabel *Label14;
	TEdit *edBPSys;
	TLabel *Label15;
	TEdit *edBPDia;
	TLabel *Label16;
	TEdit *edPuls;
	TMemo *mNote;
	TLabel *Label17;
	TProgressBar *pbJob;
	TLabel *Label3;
	TEdit *edRpeaks;
	TImage *img3;
	TImage *img4;
	TImage *img5;
	TImage *img6;
	TImage *img7;
	TImage *img8;
	TLabel *Label4;
	TComboBox *cbSaveLeads;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acSaveExecute(TObject *Sender);
	void __fastcall acLoadFileExecute(TObject *Sender);
	void __fastcall acSaveUpdate(TObject *Sender);
	void __fastcall cbChannelTest1Change(TObject *Sender);

private:
    cMySql&     fmysql;
	cTools      ftools;

	cEcg        fecg2;
	cEcg        fecg3;
	cEcg        fecg4;
	cEcg        fecg5;
	cEcg        fecg6;
	cEcg        fecg7;
	cEcg        fecg8;
	cEcg        fecg12;
	cEcg        fecg34;
	cEcg        fecg56;

	bool        FormComplete(); //true wenn alles ausgefüllt ist

	bool        ShowFile(String ecgFile);
	bool 		DisplayEcg(cEcg& fecg, eChannel channel);

	bool        SaveFile();
    bool        SaveLead(cEcg& fecg, sEcgData& data, eChannel channel);

public:
	__fastcall TfmAddFile(TComponent* Owner);
	__fastcall ~TfmAddFile();

	bool 		Execute();

};
//---------------------------------------------------------------------------
bool DlgSaveEcgFile(TForm* Papa);
//---------------------------------------------------------------------------
#endif
