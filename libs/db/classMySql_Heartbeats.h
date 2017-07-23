//---------------------------------------------------------------------------
#ifndef classMySql_HeartbeatsH
#define classMySql_HeartbeatsH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include <libs/core/classBase.h>
#include <libs/core/classTools.h>
#include "classMySql_Work.h"
//---------------------------------------------------------------------------
struct sBeatData
	{
	int			ident;
    int         ecgdata;
	int			session;
	int			person;
	int			channel;
	int			state;
	int			posture;
	int         nummer;
    int         usability;
	double		werte[3000];
	iarray_t	array_werte;
	};
//---------------------------------------------------------------------------
class PACKAGE cMySqlHeartbeats : public cBase
	{
public:
	cMySqlHeartbeats();
	~cMySqlHeartbeats();

	bool 	save(sBeatData data);
	bool 	saveWithArray(sBeatData data);

	//UPDATE `ecg`.`ecgdata` SET `Usability`=4 WHERE  `ID`=64;
	bool    update(String feld, String newcontent, int ident);

	bool    findDup(sBeatData data);

	bool	loadTable(); //lädt die ganze Tabelle
	bool    loadFilteredTable(sBeatData filter);
	bool	loadByIdent(int ecg);
	bool	loadByPerson(int person); //lädt nur die Daten von Person
	bool	loadBySession(int session);

	bool 	getLast();

	bool	nextRow();

	bool	deleteByIdent(int ident);

	//-- Datenfelder
	int 	getSize();
	bool 	getRow();


__property sBeatData row = { read=get_data };
__property int num_rows = { read=get_num_rows };

private:
	cTools			ftools;

	bool 			LongstrToData(String str, double* werte, int& count);
	String 			DataToLongtext(double* werte);
	String 			ArrayToLongtext(iarray_t array);

	bool			load(String condition);
	void 			addCondition(String& condition, String feld, String filter);


	//-- MySql-Variablen und -Funktionen
	sBeatData		fdata;
	sBeatData		get_data();

	cMySqlWork&		fwork;

	MYSQL_RES*  	fres; //SQL-Daten
	MYSQL_ROW		frow;
	int				get_num_rows();

	bool			doQuery(String q);
	};
//---------------------------------------------------------------------------
#endif
