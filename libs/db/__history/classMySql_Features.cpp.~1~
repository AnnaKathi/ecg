//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql_Features.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#define TABLE "templates"
//---------------------------------------------------------------------------
cMySqlFeature::cMySqlFeature(cMySqlWork& worker)
	{
	fwork = &worker;
	}
//---------------------------------------------------------------------------
cMySqlFeature::~cMySqlFeature()
	{
	}
//---------------------------------------------------------------------------
bool cMySqlFeature::doQuery(String q)
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
bool cMySqlFeature::get(int feature)
	{
	String q = "SELECT * FROM `" + String(TABLE) + "` WHERE `ID` = " + String(feature);
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;
	if (!ParseRow()) return false;

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlFeature::loadTable(String order) //order ist vorbesetzt mit ""
	{
	if (!fwork->loadTable(TABLE, order))
		return fail(fwork->error_code, fwork->error_msg);

	fres = fwork->getResult();
	return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlFeature::select(int ecg, int preId, int rpeaksId, int featId)
	{
	if (ecg      <= 0) return fail(2, "Es wurde kein EKG-Ident übergeben");
	if (preId    <= 0) return fail(2, "Es wurde kein Preprocessing-Ident übergeben");
	if (rpeaksId <= 0) return fail(2, "Es wurde kein RPeak-Ident übergeben");
	if (featId   <= 0) return fail(2, "Es wurde kein Feature-Ident übergeben");

	String q =
		ftools.fmt(
		"SELECT * FROM %s WHERE `EcgData_ID` = %d AND `AlgPreprocessing_ID` = %d AND `AlgRpeaks_ID` = %d AND `AlgFeatures_ID` = %d",
		String(TABLE), ecg, preId, rpeaksId, featId);

	if (!fwork->query(q))
		{
		String test = fwork->error_msg;
		return fail(fwork->error_code, fwork->error_msg);
		}

	//todo return fail() ??
	fres = fwork->getResult();
	if (fres == NULL) return false;

	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;
	if (!ParseRow()) return false;

	return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlFeature::nextRow()
	{
	if (!fwork->isReady())
		return fail(1, "MySql-Verbindung wurde nicht initialisiert");

	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;
	if (!ParseRow()) return false;

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlFeature::getLast()
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
bool cMySqlFeature::insert(sFeature data)
	{
	String q = "INSERT INTO " + String(TABLE) + " ";
	q+= "(`EcgData_ID`, `AlgPreprocessing_ID`, `AlgRpeaks_ID`, `AlgFeatures_ID`, `Template`) VALUES ";
	q+= "(";
	q+= "'" + String(data.ecgId) + "', ";
	q+= "'" + String(data.algIdPre) + "', ";
	q+= "'" + String(data.algIdRpeaks) + "', ";
	q+= "'" + String(data.algIdFeatures) + "', ";
	q+= "'" + data.features + "'";
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
bool cMySqlFeature::update(sFeature data)
	{
	//UPDATE `ecg`.`subjects` SET `Vorname`='Otto', `Nachname`='Mustermann' WHERE  `Ident`=7;
	String q = "UPDATE " + String(TABLE) + " SET ";
	q+= "EcgData_ID='"     + String(data.ecgId)  + "',";
	q+= "AlgPreprocessing_Id='" + String(data.algIdPre)  + "',";
	q+= "AlgRpeaks_Id='"   + String(data.algIdRpeaks)  + "',";
	q+= "AlgFeatures_Id='" + String(data.algIdFeatures)  + "',";
	q+= "Template='"       + data.features       + "' ";
	q+= "WHERE ID="        + String(data.ident);

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
int cMySqlFeature::getSize()
	{
	if (!loadTable())
		{
		fail(fwork->error_code, fwork->error_msg);
		return -1;
		}

	return get_num_rows();
	}
//---------------------------------------------------------------------------
bool cMySqlFeature::ParseRow()
	{
	fdata.ident    = atoi(frow[0]);
	fdata.ecgId    = atoi(frow[1]);
	fdata.algIdPre = atoi(frow[2]);
	fdata.algIdRpeaks   = atoi(frow[3]);
	fdata.algIdFeatures = atoi(frow[4]);
	fdata.features = String(frow[5]);
	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: Daten anzeigen   *************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlFeature::listInCombo(TComboBox* cb, int mode) //mode ist mit 0 vorbesetzt
	{
	//Alle Personen aus der DB in der ComboBox anzeigen, der mode bestimmt
	//was angezeigt wird
	if (!loadTable(""))
		return fail(fwork->error_code, fwork->error_msg);

	cb->Items->Clear();
	String str;
	while (nextRow())
		{
		//todo add mode: get Bez of Alg.
		str =
			String(fdata.ecgId) + "-" +
			String(fdata.algIdPre) + "-" +
			String(fdata.algIdRpeaks) + "-" +
			String(fdata.algIdFeatures);
		cb->Items->AddObject(str, (TObject*)fdata.ident);
		}

	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: löschen   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlFeature::deleteByIdent(int ident)
	{
	String q = "DELETE FROM `" + String(TABLE) + "` WHERE `ID` = " + String(ident);
	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		{
		//Evtl zugehörige Tabellen löschen??
		}
		
	return ok();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   getter und setter   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
sFeature cMySqlFeature::get_data()
	{
	return fdata;
	}
//---------------------------------------------------------------------------
int cMySqlFeature::get_num_rows()
	{
	return mysql_num_rows(fres);
	}
//---------------------------------------------------------------------------