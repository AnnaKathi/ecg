//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql_Work.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
INSTALL_GLOBALVAR_GUARD(cMySqlWork, myptr)
//---------------------------------------------------------------------------
cMySqlWork& cMySqlWork::getRef()
	{
	if (myptr == 0)
		{
		myptr = new cMySqlWork();
		}
	return *myptr;
	}
//---------------------------------------------------------------------------
cMySqlWork::cMySqlWork()
	{
	bMySqlConnected = false;

	//erst einmal als Klartext aus Ini-Datei lesen, todo: umstellen auf Dialog?
	TIniFile* Ini = new TIniFile(ftools.GetIniFile());
	sMySqlData.serv = Ini->ReadString("MySql", "Server", "localhost");
	sMySqlData.user = Ini->ReadString("MySql", "User",   "root");

	//Passwort kann sich an den versch. AP unterscheiden
	String pwd = Ini->ReadString("MySql", "Pwd" + ftools.GetComputer(), "");
	if (pwd == "") pwd = Ini->ReadString("MySql", "Pwd", "");
	sMySqlData.pass = pwd;

	sMySqlData.data = Ini->ReadString("MySql",  "Data",   "ecg");
	sMySqlData.port = Ini->ReadInteger("MySql", "Port",   3306);
	delete Ini;
	}
//---------------------------------------------------------------------------
cMySqlWork::~cMySqlWork()
	{
	}
//---------------------------------------------------------------------------
bool cMySqlWork::open()
	{
	if ((fsql = mysql_init(NULL)) == 0)
		return fail(1, "Das MYSQL-System kann nicht initialisiert werden!");

	fcon = mysql_real_connect(
		fsql,
		AnsiString(sMySqlData.serv).c_str(),
		AnsiString(sMySqlData.user).c_str(),
		AnsiString(sMySqlData.pass).c_str(),
		AnsiString(sMySqlData.data).c_str(),
		sMySqlData.port,
		NULL,
		0);

	if (fcon == NULL)
		return fail(1, "Fehler beim Verbindungsaufbau! MYSQL meldet: " + String(mysql_error(fsql)));
	else
		{
		bMySqlConnected = true;
		return ok();
		}
	}
//---------------------------------------------------------------------------
bool cMySqlWork::openWithoutDb()
	{
	if ((fsql = mysql_init(NULL)) == 0)
		return fail(1, "Das MYSQL-System kann nicht initialisiert werden!");

	fcon = mysql_real_connect(
		fsql,
		AnsiString(sMySqlData.serv).c_str(),
		AnsiString(sMySqlData.user).c_str(),
		AnsiString(sMySqlData.pass).c_str(),
		NULL,
		sMySqlData.port,
		NULL,
		0);

	if (fcon == NULL)
		return fail(1, "Fehler beim Verbindungsaufbau! MYSQL meldet: " + String(mysql_error(fsql)));
	else
		{
		bMySqlConnected = true;
		return ok();
		}
	}
//---------------------------------------------------------------------------
bool cMySqlWork::close()
	{
	bMySqlConnected = false;
	mysql_close(fsql);
	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlWork::isReady()
	{
	if (!bMySqlConnected) return false;
	if (fsql == NULL || fcon == NULL) return false;
	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   Abfragen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlWork::query(String q)
	{
	if (!bMySqlConnected)
		return fail(2, "Datenbank wurde nicht initialisiert");

	if (mysql_real_query(fcon, AnsiString(q).c_str(), q.Length()) != 0)
		return fail(2, ftools.fmt("Fehler in QUERY: %d", error()));

	if ((fres = mysql_store_result(fcon)) == NULL)
		return fail(2, ftools.fmt("Fehler in STORE_RESULT: %d", error()));

	if (mysql_num_rows(fres) == 0)
		return ok(); //not: fail(2, msg.c_str());
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlWork::send(String q)
	{
	if (!bMySqlConnected)
		return fail(3, "Datenbank wurde nicht initialisiert");

	if (mysql_real_query(fcon, AnsiString(q).c_str(), q.Length()) != 0)
		return fail(3, ftools.fmt("Fehler in QUERY: %s", error()));

	return ok();
	}
//---------------------------------------------------------------------------
wchar_t* cMySqlWork::error()
	{
	error_message = mysql_error(fcon);
	return error_message.c_str();
    }
//---------------------------------------------------------------------------
bool cMySqlWork::script(String script_name)
	{
	//Datei wird im Unterverzeichnis "script" erwartet!
	char script[MAX_PATH];
	sprintf(script, "%s\\libs\\db\\mysql_scripts\\script_%s.sql", AnsiString(ftools.GetProgramPath()).c_str(), AnsiString(script_name).c_str());
	FILE* fp = fopen(script, "r");
	if (fp == NULL)
		return fail(4, ftools.fmt("Skript-Datei konnte nicht gefunden werden (%s)", script));

	String q = "";
	String line;
	char rowbuf[2048];
	bool fehler = false;
	while (fgets(rowbuf, sizeof(rowbuf)-1, fp) != NULL)
		{
		line = String(rowbuf);
		ftools.replace(line, "\n", "");
		line = line.Trim();

		if (line.SubString(1,1) == "#") //Kommentar
			continue;

		if (line.SubString(line.Length(), 1) == ";") //Leerzeile faken
			{
			q+= line;
			line = "";
			}

		if (line == "")
			{
			//Befehl zuende -> absenden
			if (q == "") continue;
			
			if (!send(q))
				{
				fehler = true;
				break;
				}

			q = "";
			}
		else
			{
			//Befehl noch nicht vollständig
			q += line;
			}
		}

	fclose(fp);

	if (!fehler && q != "")
		{
		//es gibt noch einen nicht abgesendeten Befehl
		if (!send(q))
			fehler = true;
		}

	if (fehler)
		return fail(error_code, error_msg);

	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Daten laden   ****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlWork::loadTable(String tab, String order) //order ist mit "" vorbesetzt
	{
	String q = "SELECT * FROM " + String(tab);
	if (order != "") q += " ORDER BY " + order;

	if (!query(q))
		return fail(error_code, error_msg);
	else
		{
		fres = getResult();
		return ok();
		}
	}
//---------------------------------------------------------------------------
bool cMySqlWork::listIn(TListView* lv)
	{
	if (lv == NULL) return fail(4, "Es wurde keine ListView übergeben");
	lv->Items->Clear();
	
	String q = "SHOW TABLES";

	if (!query(q))
		return fail(error_code, error_msg);

	if (mysql_num_rows(fres) <= 0) //keine Tabellen vorhanden
		return fail(4, "Die Datenbank enthält keine Tabellen");

	String name; int anz; TListItem* item;
	while ((frow = mysql_fetch_row(fres)) != NULL)
		{
		name = String(frow[0]);
		q = ftools.fmt("SELECT * FROM %s", name);

		MYSQL_RES* oldres = fres;
		if (!query(q))
			anz = 0;
		else
			anz = mysql_num_rows(fres);
		fres = oldres;

		item = lv->Items->Add();
		item->Caption = name;
		item->SubItems->Add(String(anz));
		}

	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   getter und setter   **************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
MYSQL_RES* cMySqlWork::getResult()
	{
	return fres;
	}
//---------------------------------------------------------------------------
int cMySqlWork::get_num_rows()
	{
	 return mysql_num_rows(fres);
	}
//---------------------------------------------------------------------------
