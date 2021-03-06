//---------------------------------------------------------------------------
#ifndef classMySql_WorkH
#define classMySql_WorkH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <IniFiles.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include <libs/core/classBase.h>
#include <libs/core/classTools.h>
#include <libs/etc/mysql/mysql.h>
//---------------------------------------------------------------------------
struct sMySqlData
	{
	String 	serv;
	String 	user;
	String 	pass;
	String 	data;
	int 	port;
	};
//---------------------------------------------------------------------------
class PACKAGE cMySqlWork : public cBase
	{
public:
	cMySqlWork();
	~cMySqlWork();

	static cMySqlWork& getRef();

	bool 		open();
	bool 		openWithoutDb();
	bool		close();

	bool		isReady();       //wurde open() erfolgreich durchgef�hrt?
	bool		query(String q); //f�hrt ein store_result durch
	bool		send(String q);  //f�hrt nur das Kommando aus (z.B. delete) ohne store_result
	bool 		script(String script_name); //f�hrt eine sql-Datei aus
	MYSQL_RES*  getResult();     //Resultate zur�ckgeben

	//-- Daten laden
	bool		loadTable(String tab, String order = "");

	bool		listIn(TListView* lv);

__property int num_rows = { read=get_num_rows };

private:
	cTools			ftools;

	//SQL-Daten
	sMySqlData      sMySqlData;
	MYSQL*      	fsql;
	MYSQL*      	fcon;
	MYSQL_RES*  	fres;
	MYSQL_ROW		frow;
	int				get_num_rows();

	String          error_message;
	wchar_t* 		error();

	bool			bMySqlConnected;

	};
//---------------------------------------------------------------------------
#endif
