//---------------------------------------------------------------------------
#ifndef classMySql_EcgDataH
#define classMySql_EcgDataH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include <libs/core/classBase.h>
#include <libs/core/classTools.h>
#include "classMySql_Work.h"
//---------------------------------------------------------------------------
struct sEcgData
	{
	int			ident;
	int			session;
	int			person;
	int			channel;
	int			state;
	int			posture;
	int			bpsys;
	int			bpdia;
	int			puls;
    int         usability;
	String		note;
	double		werte[3000];
	iarray_t	array_werte;
    int         visBeats;
	};
//---------------------------------------------------------------------------
class PACKAGE cMySqlEcgData : public cBase
	{
public:
	cMySqlEcgData();
	~cMySqlEcgData();

	bool 	save(sEcgData data);
	bool 	saveWithArray(sEcgData data);

	//UPDATE `ecg`.`ecgdata` SET `Usability`=4 WHERE  `ID`=64;
	bool    update(String feld, String newcontent, int ident);

	bool    findDup(sEcgData data);

	bool	loadTable(); //lädt die ganze Tabelle
    bool    loadFilteredTable(sEcgData filter);
	bool	loadByIdent(int ecg);
	bool	loadByPerson(int person); //lädt nur die Daten von Person
	bool	loadBySession(int session);

	bool 	getLast();

	bool	nextRow();

	bool	deleteByIdent(int ident);

	//-- Datenfelder
	int 	getSize();
	bool 	getRow();


__property sEcgData row = { read=get_data };
__property int num_rows = { read=get_num_rows };

private:
	cTools			ftools;

	bool 			LongstrToData(String str, double* werte);
	String 			DataToLongtext(double* werte);
	String 			ArrayToLongtext(iarray_t array);

	bool			load(String condition);
	void 			addCondition(String& condition, String feld, String filter);


	//-- MySql-Variablen und -Funktionen
	sEcgData		fdata;
	sEcgData		get_data();

	cMySqlWork&		fwork;

	MYSQL_RES*  	fres; //SQL-Daten
	MYSQL_ROW		frow;
	int				get_num_rows();

	bool			doQuery(String q);
	};
//---------------------------------------------------------------------------
#endif
