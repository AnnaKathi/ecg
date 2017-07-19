//---------------------------------------------------------------------------
#ifndef classMySql_FeaturesH
#define classMySql_FeaturesH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classTools.h"
#include "classMySql_Work.h"
//---------------------------------------------------------------------------
struct sFeature
	{
	int			ident;
	int			ecgId;
	int			algIdPre;
	int			algIdRpeaks;
	int			algIdFeatures;
	String		features;
	};
//---------------------------------------------------------------------------
class PACKAGE cMySqlFeature : public cBase
	{
public:
	cMySqlFeature(cMySqlWork& worker);
	~cMySqlFeature();

	//-- Daten laden
	bool 	get(int feature); //einzelnen Datensatz laden
	bool	loadTable(String order = ""); //lädt die gesamte Tabelle
	bool 	select(int ecg, int preId, int rpeaksId, int featId);
	bool	nextRow();
	bool	getLast();

	//-- Daten speichern
	bool	insert(sFeature data);
	bool	update(sFeature data);

	//-- Daten feststellen
	int		getSize();

	//-- Daten anzeigen
	bool	listInCombo(TComboBox* cb, int mode = 0);

	//-- Daten löschen
	bool 	deleteByIdent(int ident);

__property sFeature row = { read=get_data };
__property int num_rows = { read=get_num_rows };

private:
	cTools			ftools;
	bool			ParseRow();

	sFeature 		fdata;
	sFeature 		get_data();

	cMySqlWork*		fwork;

	MYSQL_RES*  	fres; //SQL-Daten
	MYSQL_ROW		frow;
	int				get_num_rows();

	bool			doQuery(String q);
	};
//---------------------------------------------------------------------------
#endif
