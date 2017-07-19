//---------------------------------------------------------------------------
#ifndef classMySql_SessionH
#define classMySql_SessionH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "classMySql_Work.h"
//---------------------------------------------------------------------------
struct sSession
	{
	int			ident;
	int			place;
	String		stamp;
	double		temp;
	double		luft;
	String		note;
	};
//---------------------------------------------------------------------------
class PACKAGE cMySqlSession : public cBase
	{
public:
	cMySqlSession(cMySqlWork& worker);
	~cMySqlSession();

	//-- Daten laden
	bool 	get(int session); //einzelnen Datensatz laden
	bool	loadTable(String order = ""); //lädt die gesamte Tabelle
	bool	nextRow();
	bool	getLast();

	//-- Daten speichern
	bool	insert(sSession data);
	bool	update(sSession data);
	bool	insertResearcher(int session, int researcher);

	//-- Daten feststellen
	int		getSize();

	//-- Daten anzeigen
	bool	listInCombo(TComboBox* cb, int mode = 0);

	//-- Daten löschen
	bool 	deleteByIdent(int ident);

__property sSession row = { read=get_data };
__property int num_rows = { read=get_num_rows };

private:
	bool			ParseRow();
	
	sSession 		fdata;
	sSession 		get_data();

	cMySqlWork*		fwork;

	MYSQL_RES*  	fres; //SQL-Daten
	MYSQL_ROW		frow;
	int				get_num_rows();

	bool			doQuery(String q);
	};
//---------------------------------------------------------------------------
#endif
