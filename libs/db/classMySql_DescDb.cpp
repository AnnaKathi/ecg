/* wird verwendet für alle "Decription" Datenbanken, die lediglich einen ident
 * und die Bezeichnugn enthalten:
 *
 *  - diseases
 *  - researchers
 *  - lagen
 *  - states
 *  - platzierungen
 *  - algorithmen
 *  - orte
 */
//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql_DescDb.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cMySqlDescDb::cMySqlDescDb(cMySqlWork& worker, String tabelle)
	{
	fwork = &worker;
	fTabelle = tabelle;
	}
//---------------------------------------------------------------------------
cMySqlDescDb::~cMySqlDescDb()
	{
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: laden   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlDescDb::get(int ident)
	{
	String q = "SELECT * FROM `" + String(fTabelle) + "` WHERE `ID` = " + String(ident);
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;

	fdata.ident   = atoi(frow[0]);
	sprintf(fdata.name, "%.127s", frow[1]);

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlDescDb::loadTable(String order) //order ist vorbesetzt mit ""
	{
	if (!fwork->loadTable(fTabelle, order))
		return fail(fwork->error_code, fwork->error_msg);

	fres = fwork->getResult();
	return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlDescDb::nextRow()
	{
	if (!fwork->isReady())
		return fail(1, "MySql-Verbindung wurde nicht initialisiert");

	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;

	fdata.ident   = atoi(frow[0]);
	sprintf(fdata.name, "%.127s", frow[1]);

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: speichern   ******************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlDescDb::insert(sDescData data)
	{
	String q = "INSERT INTO " + String(fTabelle) + " ";
	q+= "(`Name`) VALUES ";
	q+= "(";
	q+= "'" + String(data.name) + "'";
	q+= ")";

	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlDescDb::update(sDescData data)
	{
	String q = "UPDATE " + String(fTabelle) + " SET ";
	q+= "Name='" + String(data.name) + "' ";
	q+= "WHERE ID=" + String(data.ident);

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
String cMySqlDescDb::getNameOf(int ident) //eine Bezeichnugn einer Erkrankung
	{
	MYSQL_RES* res_old = fres; //aktuelle Position speichern

	String name = "";
	String q = "SELECT * FROM `" + String(fTabelle) + "` WHERE `ID` = " + String(ident);
	if (!fwork->query(q))
		name = "- nicht gefunden (" + String(ident) + ") -";
	else
		{
		fres = fwork->getResult();
		frow = mysql_fetch_row(fres);
		if (frow == NULL) return "";

		name = String(frow[1]);
		}

	fres = res_old; //Position zurücksetzen
	return name;
	}
//---------------------------------------------------------------------------
sarray_t cMySqlDescDb::getNamesOf(sarray_t idents) //Liste mit Bez. auffüllen
	{
	sarray_t res; res.clear();
	int ix = 0;
	for (sarray_itr itr = idents.begin(); itr != idents.end(); itr++)
		{
		slist_t& v = itr->second;
		res[ix].push_back(v[0]);
		res[ix].push_back(getNameOf(v[0].ToInt()));
		ix++;
		}

	return res;
	}
//---------------------------------------------------------------------------
int cMySqlDescDb::getSize()
	{
	if (!loadTable())
		{
		fail(fwork->error_code, fwork->error_msg);
		return -1;
		}

	return get_num_rows();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: Daten anzeigen   *************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlDescDb::listInCombo(TComboBox* cb, int mode) //mode ist mit 0 vorbesetzt
	{
	//Alle Erkrankungen aus der DB in der ComboBox anzeigen,
	//der mode bestimmt was angezeigt wird
	if (!loadTable("Name ASC"))
		return fail(fwork->error_code, fwork->error_msg);

	cb->Items->Clear();
	String dis;
	cb->Items->AddObject("- alle Daten -", (TObject*)0);
	while (nextRow())
		{
		//todo Kennzeichnung in DB aufnehmen und hier mit einbauen
		if (mode == 1)  dis = String(fdata.name) + " (" + String(fdata.ident) + ")";
		else 			dis = String(fdata.name);

		cb->Items->AddObject(dis, (TObject*)fdata.ident);
		}

	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: löschen   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlDescDb::deleteByIdent(int ident)
	{
	//DELETE FROM `ecg`.`ecgdata` WHERE  `Ident`=51;
	String q = "DELETE FROM `" + String(fTabelle) + "` WHERE `ID` = " + String(ident);
	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   getter und setter   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
sDescData cMySqlDescDb::get_data()
	{
	return fdata;
	}
//---------------------------------------------------------------------------
int cMySqlDescDb::get_num_rows()
	{
	return mysql_num_rows(fres);
	}
//---------------------------------------------------------------------------
String cMySqlDescDb::get_my_name()
	{
	return fTabelle;
	}
//---------------------------------------------------------------------------
