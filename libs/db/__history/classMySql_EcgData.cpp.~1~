//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql_EcgData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#define TABLE "ecgdata"
//---------------------------------------------------------------------------
cMySqlEcgData::cMySqlEcgData(cMySqlWork& worker)
	{
	fwork = &worker;
	}
//---------------------------------------------------------------------------
cMySqlEcgData::~cMySqlEcgData()
	{
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::doQuery(String q)
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
/******************   Funktionen: speichern   ******************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlEcgData::save(sEcgData data)
	{
	//Row muss vorher gesetzt sein
	String s = DataToLongtext(data);
	String q =
		"INSERT INTO `ecgdata` (`Sessions_ID`, `Subjects_ID`, `Positions_ID`, `States_ID`, `Postures_ID`, `BPSys`, `BPDia`, `Puls`, `Note`, `ECG`) VALUES (" +
		String(data.session)  + ", " +
		String(data.person)   + ", " +
		String(data.position) + ", " +
		String(data.state)    + ", " +
		String(data.posture)  + ", " +
		String(data.bpsys)    + ", " +
		String(data.bpdia)    + ", " +
		String(data.puls)     + ", " +
		"'" + data.note + "'," +
		"'" + s + "')";

	if (!fwork->send(q))
		return fail(fwork->error_code, fwork->error_msg);
	else
		{
		//Datensatz wieder reinladen, damit aufrufende Komponenten damit
		//weiterarbeiten können
		return getLast();
		}
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: laden   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlEcgData::loadTable()
	{
	String q = "SELECT * FROM `" + String(TABLE) + "`";
	return doQuery(q);
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::loadByIdent(int ecg)
	{
	String condition = "ID = " + String(ecg);
	return load(condition);
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::loadByPerson(int person)
	{
	String condition = "Subjects_ID = " + String(person);
	return load(condition);
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::loadBySession(int session)
	{
	String condition = "Sessions_ID = " + String(session);
	return load(condition);
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::load(String condition)
	{
	if (condition == "") return fail(1, "Es wurde keine Bedingung übergeben");
	String q = "SELECT * FROM `" + String(TABLE) + "` WHERE " + condition;
		
	if (!doQuery(q))
		return fail(fwork->error_code, fwork->error_msg);

	if (fres == NULL) return fail(fwork->error_code, fwork->error_msg);
	frow = mysql_fetch_row(fres);
	if (frow == NULL) return fail(fwork->error_code, fwork->error_msg);
	if (!getRow())    return fail(1, "Die Datenzeile konnte nicht eingelesen werden.");
	return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::nextRow()
	{
	if (!fwork->isReady())
		return fail(1, "MySql-Verbindung wurde nicht initialisiert");

	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;
	if (!getRow())    return false;

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::getLast()
	{
	String q = "SELECT * FROM `" + String(TABLE) + "` ORDER BY ID DESC LIMIT 1";
	if (!fwork->query(q))
		return false;

	fres = fwork->getResult();
	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;
	if (!getRow())    return false;

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen: löschen   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cMySqlEcgData::deleteByIdent(int ident)
	{
	//DELETE FROM `ecg`.`ecgdata` WHERE  `Ident`=51;
	String q = "DELETE FROM `" + String(TABLE) + "` WHERE `ID` = " + String(ident);
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
int cMySqlEcgData::getSize()
	{
	if (!loadTable())
		{
		fail(fwork->error_code, fwork->error_msg);
		return -1;
		}

	return get_num_rows();
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::getRow()
	{
	//aus row die fdata-Werte lesen
	if (frow == NULL) return false;

	fdata.ident    = atoi(frow[0]);
	fdata.session  = atoi(frow[1]);
	fdata.person   = atoi(frow[2]);
	fdata.position = atoi(frow[3]);
	fdata.state    = atoi(frow[4]);
	fdata.posture  = atoi(frow[5]);
	fdata.bpsys    = atoi(frow[6]);
	fdata.bpdia    = atoi(frow[7]);
	fdata.puls     = atoi(frow[8]);
	fdata.note     = frow[9];

	//Die EKG-Werte sind als semikolon-getrennter Longtext gespeichert
	if (!LongstrToData(String(frow[10]), fdata))
		return fail(6, "Das Longtext-Feld 'Werte' konnte nicht eingelesen werden");

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::LongstrToData(String str, sEcgData& data)
	{
	//todo use fTools-Funktionen
	int pos; String ww;
	int ix = 0;
	char feld[32];
	while ((pos = str.Pos(";")) > 0)
		{
		sprintf(feld, "%s", str.SubString(0, pos-1));
		str = str.SubString(pos+1, 99999);

		data.werte[ix] = atof(feld);
		data.array_werte[ix].push_back(ix); //ix = zeit
		data.array_werte[ix].push_back(atof(feld));
		ix++;
		}

	if (str != "")
		{
		sprintf(feld, "%s", str);
		data.werte[ix] = atof(feld);
		data.array_werte[ix].push_back(ix); //ix = zeit
		data.array_werte[ix].push_back(atof(feld));
		}

	return true;
	}
//---------------------------------------------------------------------------
String cMySqlEcgData::DataToLongtext(sEcgData data)
	{
	//todo use fTools-Funktionen
	String s = "";
	char feld[64]; double wert;
	for (int i = 0; i < 3000; i++)
		{
		sprintf(feld, "%.8f", data.werte[i]);
    	wert = atof(feld);
		if (i == 0)
			s = String(wert);
		else
			s += ";" + String(wert);
		}
		
	return s;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   getter und setter   ********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
sEcgData cMySqlEcgData::get_data()
	{
	return fdata;
	}
//---------------------------------------------------------------------------
int cMySqlEcgData::get_num_rows()
	{
	return mysql_num_rows(fres);
	}
//---------------------------------------------------------------------------