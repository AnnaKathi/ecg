//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql_EcgData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#define TABLE "ecgdata"
//---------------------------------------------------------------------------
cMySqlEcgData::cMySqlEcgData()
	: cBase()
	, fwork(cMySqlWork::getRef())
	{
	}
//---------------------------------------------------------------------------
cMySqlEcgData::~cMySqlEcgData()
	{
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::doQuery(String q)
	{
	if (!fwork.query(q))
		return fail(fwork.error_code, fwork.error_msg);
	else
		{
		fres = fwork.getResult();
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
	String s = DataToLongtext(data.werte);
	String q =
		"INSERT INTO `ecgdata` (`Sessions_ID`, `Subjects_ID`, `Channels_ID`, `States_ID`, `Postures_ID`, `BPSys`, `BPDia`, `Puls`, `VisNoOfBeats`, `Usability`, `Note`, `Signal`) VALUES (" +
		String(data.session)   + ", " +
		String(data.person)    + ", " +
		String(data.channel)   + ", " +
		String(data.state)     + ", " +
		String(data.posture)   + ", " +
		String(data.bpsys)     + ", " +
		String(data.bpdia)     + ", " +
		String(data.puls)      + ", " +
		String(data.visBeats)  + ", " +
		String(data.usability) + ", " +
		"'" + data.note + "'," +
		"'" + s + "')";

	if (!fwork.send(q))
		return fail(fwork.error_code, fwork.error_msg);
	else
		{
		//Datensatz wieder reinladen, damit aufrufende Komponenten damit
		//weiterarbeiten können
		return getLast();
		}
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::saveWithArray(sEcgData data)
	{
	//Row muss vorher gesetzt sein
	String s = ArrayToLongtext(data.array_werte);

	//Duplicate Entries verhindern !
	//Ein Eintrag ist doppelt, wenn die folgende Kombi schon vorhanden ist:
	//Session - Person - Position - State - Posture
	if (findDup(data))
		return fail(3, "Duplicate Entries: Der Datensatz ist bereits vorhanden");

	String q =
		"INSERT INTO `ecgdata` (`Sessions_ID`, `Subjects_ID`, `Channels_ID`, `States_ID`, `Postures_ID`, `BPSys`, `BPDia`, `Puls`, `VisNoOfBeats`, `Usability`, `Note`, `Signal`) VALUES (" +
		String(data.session)   + ", " +
		String(data.person)    + ", " +
		String(data.channel)   + ", " +
		String(data.state)     + ", " +
		String(data.posture)   + ", " +
		String(data.bpsys)     + ", " +
		String(data.bpdia)     + ", " +
		String(data.puls)      + ", " +
		String(data.visBeats)  + ", " +
		String(data.usability) + ", " +
		"'" + data.note + "'," +
		"'" + s + "')";

	if (!fwork.send(q))
		return fail(fwork.error_code, fwork.error_msg);
	else
		{
		//Datensatz wieder reinladen, damit aufrufende Komponenten damit
		//weiterarbeiten können
		return getLast();
		}
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::update(String feld, String newcontent, int ident)
	{
	//UPDATE `ecg`.`ecgdata` SET `Usability`=4 WHERE  `ID`=64;
	String q = ftools.fmt("UPDATE `%s` SET `%s` = '%s' WHERE `ID`=%d",
		String(TABLE), feld.c_str(), newcontent.c_str(), ident);

	if (!fwork.send(q))
		return fail(fwork.error_code, fwork.error_msg);
	else
		{
		//Datensatz wieder reinladen, damit aufrufende Komponenten damit
		//weiterarbeiten können
		return loadByIdent(ident);
		}
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::findDup(sEcgData data)
	{
	String q = ftools.fmt("SELECT * FROM `%s` WHERE "
		"`Sessions_ID`  = %d AND "
		"`Subjects_ID`  = %d AND "
		"`Channels_ID` = %d AND "
		"`States_ID`    = %d AND "
		"`Postures_ID`  = %d",
		String(TABLE), data.session, data.person, data.channel, data.state, data.posture);

	if (!doQuery(q))
		return fail(fwork.error_code, fwork.error_msg);

	if (fres == NULL) return fail(fwork.error_code, fwork.error_msg);

	frow = mysql_fetch_row(fres);
	if (frow != NULL) return true; //Duplicates gefunden
	else return false; //keien Duplicates gefunden
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
bool cMySqlEcgData::loadFilteredTable(sEcgData filter)
	{
	String condition = "";
	if (filter.ident > 0) addCondition(condition, "ID", String(filter.ident));
	if (filter.session > 0) addCondition(condition, "sessions_ID", String(filter.session));
	if (filter.person  > 0) addCondition(condition, "subjects_ID", String(filter.person));
	if (filter.channel > 0) addCondition(condition, "channels_ID", String(filter.channel));
	if (filter.state   > 0) addCondition(condition, "states_ID", String(filter.state));
	if (filter.posture > 0) addCondition(condition, "postures_ID", String(filter.posture));
    //todo BPSys, BPDis, Puls ??

	if (filter.usability > 0) addCondition(condition, "usability",    String(filter.usability));
	if (filter.visBeats  > 0) addCondition(condition, "VisNoOfBeats", String(filter.visBeats));

	if (condition == "")
		return loadTable();
	else
		return load(condition);
	}
//---------------------------------------------------------------------------
void cMySqlEcgData::addCondition(String& condition, String feld, String filter)
	{
	if (condition == "")
		condition = feld + "='" + filter + "'";
	else
		condition += " AND " + feld + "='" + filter + "'";
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
		return fail(fwork.error_code, fwork.error_msg);

	if (fres == NULL) return fail(fwork.error_code, fwork.error_msg);
	frow = mysql_fetch_row(fres);
	if (frow == NULL) return fail(fwork.error_code, fwork.error_msg);
	if (!getRow())    return fail(1, "Die Datenzeile konnte nicht eingelesen werden.");
	return ok();
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::nextRow()
	{
	if (!fwork.isReady())
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
	if (!fwork.query(q))
		return false;

	fres = fwork.getResult();
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
	if (!fwork.send(q))
		return fail(fwork.error_code, fwork.error_msg);
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
		fail(fwork.error_code, fwork.error_msg);
		return -1;
		}

	return get_num_rows();
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::getRow()
	{
	//aus row die fdata-Werte lesen
	if (frow == NULL) return false;

	fdata.ident     = String(frow[0]).ToIntDef(0);
	fdata.session   = String(frow[1]).ToIntDef(0);
	fdata.person    = String(frow[2]).ToIntDef(0);
	fdata.channel   = String(frow[3]).ToIntDef(0);
	fdata.state     = String(frow[4]).ToIntDef(0);
	fdata.posture   = String(frow[5]).ToIntDef(0);
	fdata.bpsys     = String(frow[6]).ToIntDef(0);
	fdata.bpdia     = String(frow[7]).ToIntDef(0);
	fdata.puls      = String(frow[8]).ToIntDef(0);
	fdata.visBeats  = String(frow[9]).ToIntDef(0);
	fdata.usability = String(frow[10]).ToIntDef(0);
	fdata.note      = frow[11];

    String test = String(frow[12]);

	//Die EKG-Werte sind als semikolon-getrennter Longtext gespeichert
	if (!LongstrToData(String(frow[12]), fdata.werte))
		return fail(6, "Das Longtext-Feld 'Werte' konnte nicht eingelesen werden");

	fdata.array_werte = ftools.TextToArray(String(frow[12]), ";");

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlEcgData::LongstrToData(String str, double* werte)
	{
	//todo use fTools-Funktionen
	int pos;
	int ix = 0;
	char feld[32];
	double wert;

	while ((pos = str.Pos(";")) > 0)
		{
		sprintf(feld, "%s", AnsiString(str.SubString(0, pos-1)));
		str = str.SubString(pos+1, 99999);
		wert = String(feld).ToDouble();
		werte[ix] = wert;
        ix++;
		}

	if (str != "")
		{
		sprintf(feld, "%s", AnsiString(str));
		wert = String(feld).ToDouble();
		werte[ix] = wert;
		}

	return true;
	}
//---------------------------------------------------------------------------
String cMySqlEcgData::DataToLongtext(double* werte)
	{
	//todo use fTools-Funktionen
	String s = "";
	char feld[64]; double wert;
	for (int i = 0; i < 3000; i++)
		{
		sprintf(feld, "%.8f", werte[i]);
    	wert = atof(feld);
		if (i == 0)
			s = String(wert);
		else
			s += ";" + String(wert);
		}
		
	return s;
	}
//---------------------------------------------------------------------------
String cMySqlEcgData::ArrayToLongtext(iarray_t array)
	{
	String s = "";
	double wert; bool first = true;
	for (iarray_itr itr = array.begin(); itr != array.end(); itr++)
		{
		ilist_t v = itr->second;
		wert = v[1];
		if (first)
			{
			s = String(wert);
			first =false;
            }
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