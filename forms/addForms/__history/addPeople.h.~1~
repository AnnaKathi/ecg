//---------------------------------------------------------------------------
#ifndef addPeopleH
#define addPeopleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include "../../basics/classTools.h"
//---------------------------------------------------------------------------
class TfmPerson : public TForm
{
private:
	cTools		ftools;
	bool		bNewPerson;
	int			iPerson;

	bool		SaveData();

__published:	// IDE-verwaltete Komponenten
	TPanel *pnInfo;
	TMemo *mInfo;
	TBevel *Bevel1;
	TTimer *tStartup;
	TActionList *ActionList1;
	TAction *acClose;
	TPanel *Panel1;
	TBevel *Bevel2;
	TAction *acSave;
	TButton *Button1;
	TLabel *Label1;
	TEdit *edVorname;
	TLabel *Label2;
	TEdit *edNachname;
	TLabel *Label3;
	TListView *lvDiseases;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TAction *acDisAdd;
	TAction *acDisDel;
	TButton *Button2;
	TComboBox *cbDiseases;
	TPopupMenu *PopupMenu1;
	TMenuItem *add1;
	TMenuItem *del1;
	TLabel *Label4;
	TComboBox *cbSex;
	TLabel *Label5;
	TEdit *edAge;
	TEdit *edHeight;
	TLabel *Label6;
	TEdit *edWeight;
	TLabel *Label7;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall tStartupTimer(TObject *Sender);
	void __fastcall acCloseExecute(TObject *Sender);
	void __fastcall acSaveExecute(TObject *Sender);
	void __fastcall acDisAddExecute(TObject *Sender);
	void __fastcall acDisDelExecute(TObject *Sender);
	void __fastcall cbDiseasesKeyPress(TObject *Sender, char &Key);
	void __fastcall lvDiseasesClick(TObject *Sender);
	void __fastcall edAgeKeyPress(TObject *Sender, char &Key);

public:
	__fastcall TfmPerson(TComponent* Owner);
	__fastcall ~TfmPerson();

	int 	Execute(int person);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmPerson *fmPerson;
int DlgPersonAdd(TForm* Papa);
int DlgPersonChange(TForm* Papa, int person);
//---------------------------------------------------------------------------
#endif
