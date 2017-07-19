//---------------------------------------------------------------------------
#ifndef classMySql_DescDbH
#define classMySql_DescDbH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classTools.h"
#include "classMySql_Work.h"
//---------------------------------------------------------------------------
struct sDescData
	{
	int			ident;
	char		name[128];
	};
//---------------------------------------------------------------------------
class PACKAGE cMySqlDescDb : public cBase
	{
public:
	cMySqlDescDb(cMySqlWork& worker, String tabelle);
	~cMySqlDescDb();

	//-- Daten laden
	bool	get(int ident);
	bool	loadTable(String order = ""); //lädt die ganze Tabelle
	bool	nextRow();

	//-- Daten speichern
	bool 	insert(sDescData data);
	bool 	update(sDescData data);

	//-- Daten feststellen
	String 	getNameOf(int ident); //eine Bezeichnugn eines Idents feststellen
	sarray_t getNamesOf(sarray_t idents); //Liste mit Bez. auffüllen
	int 	getSize();

	//-- Daten anzeigen
	bool	listInCombo(TComboBox* cb, int mode = 0);

	//-- Daten löschen
	bool	deleteByIdent(int ident);

__property sDescData row = { read=get_data };
__property int num_rows  = { read=get_num_rows };
__property String myName = { read=get_my_name  };

private:
	cTools			ftools;

	String			fTabelle;
	String			get_my_name();

	sDescData		fdata;
	sDescData   	get_data();

	cMySqlWork*		fwork;

	MYSQL_RES*  	fres; //SQL-Daten
	MYSQL_ROW		frow;
	int				get_num_rows();
	};
//---------------------------------------------------------------------------
#endif
