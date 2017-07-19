//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql_Session.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#define TABLE "sessions"
#define SESRE "sessionresearchers"
//---------------------------------------------------------------------------
cMySqlSession::cMySqlSession(cMySqlWork& worker)
	{
	fwork = &worker;
	}
//---------------------------------------------------------------------------
cMySqlSession::~cMySqlSession()
	{
	}
//---------------------------------------------------------------------------
bool cMySqlSession::doQuery(String q)
	{
	if (!fwork->query(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		{
		fres = fwork->getResult();
		return ok();
		}
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: laden   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlSession::get(int session)
	{
	String q = "SELECT * FROM `" + String(TABLE) + "` WHERE `ID` = " + String(session);
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;
	if (!ParseRow()) return false;

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlSession::loadTable(String order) //order ist vorbesetzt mit ""
	{
	if (!fwork->loadTable(TABLE, order))
		return fail(fwork->error_code, fwork->error_msg);

	fres = fwork->getResult();
	return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlSession::nextRow()
	{
	if (!fwork->isReady())
		return fail(1, "MySql-Verbindung wurde nicht initialisiert");

	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;
	if (!ParseRow()) return false;

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlSession::getLast()
	{
	String q = "SELECT * FROM " + String(TABLE) + " ORDER BY ID DESC LIMIT 1";
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;
	if (!ParseRow()) return false;

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: speichern   ******************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlSession::insert(sSession data)
	{
	String q = "INSERT INTO " + String(TABLE) + " ";
	q+= "(`places_ID`, `Temperatur`, `Humidity`, `Stamp`, `Note`) VALUES ";
	q+= "(";
	q+= "'" + String(data.place) + "', ";
	q+= "'" + String(data.temp)  + "', ";
	q+= "'" + String(data.luft)  + "', ";
	q+= "'" + data.stamp     + "', ";
	q+= "'" + data.note + "'";
	q+= ")";

	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		{
		//Datensatz wieder reinladen, damit aufrufende Komponenten damit
		//weiterarbeiten können (letzten Datensatz nach Ident laden)
		return getLast();
		}
	}
//---------------------------------------------------------------------------
bool cMySqlSession::update(sSession data)
	{
	//UPDATE `ecg`.`subjects` SET `Vorname`='Otto', `Nachname`='Mustermann' WHERE  `Ident`=7;
	String q = "UPDATE " + String(TABLE) + " SET ";
	q+= "places_ID='"  + String(data.place)       + "',";
	q+= "Stamp='"    + data.stamp     + "',";
	q+= "Temperatur='"  + String(data.temp)     + "',";
	q+= "Humidity='"    + String(data.luft)     + "',";
	q+= "Note='"     + data.note + "' ";
	q+= "WHERE ID="  + String(data.ident);

	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlSession::insertResearcher(int session, int researcher)
	{
	if (session <= 0 || researcher <= 0) return false;

	String q = "INSERT INTO `" + String(SESRE) + "` ";
	q += "(`Sessions_ID`, `Researchers_ID`) VALUES ";
	q += "(";
	q += "'" + String(session)    + "', ";
	q += "'" + String(researcher) + "'";
	q += ")";

	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: Datenfelder   ****************************/
/***************************************************************************/
//---------------------------------------------------------------------------
int cMySqlSession::getSize()
	{
	if (!loadTable())
		{
		fail(fwork->error_code, fwork->error_msg);
		return -1;
		}

	return get_num_rows();
	}
//---------------------------------------------------------------------------
bool cMySqlSession::ParseRow()
	{
	fdata.ident = atoi(frow[0]);
	fdata.place = atoi(frow[1]);
	fdata.stamp = String(frow[2]);
	fdata.temp  = atof(frow[3]);
	fdata.luft  = atof(frow[4]);
	fdata.note  = String(frow[5]);
	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: Daten anzeigen   *************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlSession::listInCombo(TComboBox* cb, int mode) //mode ist mit 0 vorbesetzt
	{
	//Alle Sessions aus der DB in der ComboBox anzeigen, der mode bestimmt
	//was angezeigt wird
	if (!loadTable(""))
		return fail(fwork->error_code, fwork->error_msg);

	cb->Items->Clear();
	String str;
	cb->Items->AddObject("- alle Daten -", (TObject*)0);
	while (nextRow())
		{
		if (mode == 1)  str = fdata.stamp; //2017-05-31 11:03:41
		else 			str = fdata.stamp; //todo Datum umdrehen

		cb->Items->AddObject(str, (TObject*)fdata.ident);
		}

	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: löschen   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlSession::deleteByIdent(int ident)
	{
	String q = "DELETE FROM `" + String(TABLE) + "` WHERE `ID` = " + String(ident);
	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		{
		//Session_Researchers löschen
		q = "DELETE FROM `" + String(SESRE) + "` WHERE `Sessions_ID` = " + String(ident);
		if (!fwork->send(q))
			return fail(fwork->error_code, fwork->error_msg);
		}
		
	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   getter und setter   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
sSession cMySqlSession::get_data()
	{
	return fdata;
	}
//---------------------------------------------------------------------------
int cMySqlSession::get_num_rows()
	{
	return mysql_num_rows(fres);
	}
//---------------------------------------------------------------------------
