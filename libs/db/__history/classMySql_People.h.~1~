//---------------------------------------------------------------------------
#ifndef classMySql_PeopleH
#define classMySql_PeopleH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "classMySql_Work.h"
//---------------------------------------------------------------------------
struct sPeople
	{
	int			ident;
	char		firstname[128];
	char		lastname[128];
	int			sex; //1 = weiblich, 0 = männlich
	int			age;
	int			height;
	int			weight;
	};
//---------------------------------------------------------------------------
class PACKAGE cMySqlPeople : public cBase
	{
public:
	cMySqlPeople(cMySqlWork& worker);
	~cMySqlPeople();

	//-- Daten laden
	bool 	get(int person); //einzelnen Datensatz laden
	bool	loadTable(String order = ""); //lädt die gesamte Tabelle
	bool	nextRow();
	bool	getLast();

	//-- Daten speichern
	bool	insert(sPeople data);
	bool	update(sPeople data);
	bool 	saveDiseases(int person, sarray_t diseases);

	//-- Daten feststellen
	String 	getNameOf(int person);
	sarray_t getDiseasesOf(int person);
	int		getSize();

	//-- Daten anzeigen
	bool	listInCombo(TComboBox* cb, int mode = 0);

	//-- Daten löschen
	bool 	deleteByIdent(int ident);

__property sPeople row  = { read=get_data };
__property int num_rows = { read=get_num_rows };

private:
	bool			parse();

	sPeople			fdata;
	sPeople			get_data();

	cMySqlWork*		fwork;

	MYSQL_RES*  	fres; //SQL-Daten
	MYSQL_ROW		frow;
	int				get_num_rows();

	bool			doQuery(String q);
	};
//---------------------------------------------------------------------------
#endif
