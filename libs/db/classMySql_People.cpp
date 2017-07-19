//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql_People.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#define TABLE  "subjects"
#define SUBDIS "subdiseases"
//---------------------------------------------------------------------------
cMySqlPeople::cMySqlPeople(cMySqlWork& worker)
	{
	fwork = &worker;
	}
//---------------------------------------------------------------------------
cMySqlPeople::~cMySqlPeople()
	{
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::doQuery(String q)
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
bool cMySqlPeople::parse()
	{
	if (frow == NULL) return false;
	fdata.ident   = atoi(frow[0]);
	sprintf(fdata.firstname, "%.127s", frow[1]);
	sprintf(fdata.lastname,  "%.127s", frow[2]);
	fdata.sex = atoi(frow[3]);
	fdata.age = atoi(frow[4]);
	fdata.height = atoi(frow[5]);
	fdata.weight = atoi(frow[6]);
	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::get(int person)
	{
	String q = "SELECT * FROM `" + String(TABLE) + "` WHERE `ID` = " + String(person);
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	return parse();
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::loadTable(String order) //order ist vorbesetzt mit ""
	{
	if (!fwork->loadTable(TABLE, order))
		return fail(fwork->error_code, fwork->error_msg);

	fres = fwork->getResult();
	return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::nextRow()
	{
	if (!fwork->isReady())
		return fail(1, "MySql-Verbindung wurde nicht initialisiert");

	frow = mysql_fetch_row(fres);
	return parse();
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::getLast()
	{
	String q = "SELECT * FROM " + String(TABLE) + " ORDER BY ID DESC LIMIT 1";
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	return parse();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: speichern   ******************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlPeople::insert(sPeople data)
	{
	//INSERT INTO `ecg`.`subjects` (`Vorname`, `Nachname`) VALUES ('Otto', 'Mustermann');
	String q = "INSERT INTO " + String(TABLE) + " ";
	q+= "(`Firstname`, `Lastname`, `Sex`, `Age`, `Height`, `Weight`) VALUES ";
	q+= "(";
	q+= "'" + String(data.firstname) + "', ";
	q+= "'" + String(data.lastname)  + "', ";
	q+= "'" + String(data.sex)	     + "', ";
	q+= "'" + String(data.age)	     + "', ";
	q+= "'" + String(data.height)    + "', ";
	q+= "'" + String(data.weight)    + "'";
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
bool cMySqlPeople::update(sPeople data)
	{
	//UPDATE `ecg`.`subjects` SET `Vorname`='Otto', `Nachname`='Mustermann' WHERE  `Ident`=7;
	String q = "UPDATE " + String(TABLE) + " SET ";
	q+= "Firstname='" + String(data.firstname) + "',";
	q+= "Lastname='"  + String(data.lastname)  + "',";
	q+= "Sex='" + String(data.sex) + "',";
	q+= "Age='" + String(data.age) + "',";
	q+= "Height='" + String(data.height) + "',";
	q+= "Weight='" + String(data.weight) + "'";
	q+= "WHERE ID=" + String(data.ident);

	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlPeople::saveDiseases(int person, sarray_t diseases)
	{
	//zuerst die bestehenden Verknüpfungen löschen, dann die Werte abspeichern
	String q = "DELETE FROM `" + String(SUBDIS) + "` WHERE `subjects_ID` = " + String(person);
	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);

	for (sarray_itr itr = diseases.begin(); itr != diseases.end(); itr++)
		{
		slist_t& v = itr->second;
		q = "INSERT INTO " + String(SUBDIS) + " (`subjects_ID`, `diseases_ID`) VALUES ";
		q+= "(";
		q+= "'" + String(person) + "',";
		q+= "'" + String(v[0])   + "'";
		q+= ")";

		if (!fwork->send(q))
			return fail(fwork->error_code, fwork->error_msg);
		}
	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: Datenfelder   ****************************/
/***************************************************************************/
//---------------------------------------------------------------------------
String cMySqlPeople::getNameOf(int person)
	{
	MYSQL_RES* res_old = fres; //aktuelle Position speichern

	String name = "";
	String q = "SELECT * FROM `" + String(TABLE) + "` WHERE `ID` = " + String(person);
	if (!fwork->query(q))
		name = "- nicht gefunden (" + String(person) + ") -";
	else
		{
		fres = fwork->getResult();
		frow = mysql_fetch_row(fres);
		if (frow == NULL) return "";

		name = String(frow[1]) + " " + String(frow[2]);
		}

	fres = res_old; //Position zurücksetzen
	return name;
	}
//---------------------------------------------------------------------------
sarray_t cMySqlPeople::getDiseasesOf(int person)
	{
	sarray_t result; result.clear();
	if (person <= 0) return result;
	MYSQL_RES* res_old = fres; //aktuelle Position speichern

	String q = "SELECT * FROM `" + String(SUBDIS) + "` WHERE `Subjects_ID` = " + String(person);
	if (fwork->query(q))
		{
		int count = 0;
		fres = fwork->getResult();
		while ((frow = mysql_fetch_row(fres)) != NULL)
			{
			result[count].push_back(atoi(frow[1]));
			count++;
			}
		}

	fres = res_old; //Position zurücksetzen
	return result;
	}
//---------------------------------------------------------------------------
int cMySqlPeople::getSize()
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
bool cMySqlPeople::listInCombo(TComboBox* cb, int mode) //mode ist mit 0 vorbesetzt
	{
	//Alle Personen aus der DB in der ComboBox anzeigen, der mode bestimmt
	//was angezeigt wird
	if (!loadTable("Lastname ASC"))
		return fail(fwork->error_code, fwork->error_msg);

	cb->Items->Clear();
	String pers;
	while (nextRow())
		{
		if (mode == 1)  	pers = String(fdata.lastname)  + ", " + String(fdata.firstname);
		else if (mode == 2)	pers = String(fdata.firstname) + " " + String(fdata.lastname);
		else pers = String(fdata.lastname)  + ", " + String(fdata.firstname);

		cb->Items->AddObject(pers, (TObject*)fdata.ident);
		}

	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: löschen   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlPeople::deleteByIdent(int ident)
	{
	String q = "DELETE FROM `" + String(TABLE) + "` WHERE `ID` = " + String(ident);
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
sPeople cMySqlPeople::get_data()
	{
	return fdata;
	}
//---------------------------------------------------------------------------
int cMySqlPeople::get_num_rows()
	{
	return mysql_num_rows(fres);
	}
//---------------------------------------------------------------------------
