//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql_Heartbeats.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#define TABLE "heartbeats"
//---------------------------------------------------------------------------
cMySqlHeartbeats::cMySqlHeartbeats()
	: cBase()
	, fwork(cMySqlWork::getRef())
	{
	}
//---------------------------------------------------------------------------
cMySqlHeartbeats::~cMySqlHeartbeats()
	{
	}
//---------------------------------------------------------------------------
bool cMySqlHeartbeats::doQuery(String q)
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
bool cMySqlHeartbeats::save(sBeatData data)
	{
	//Row muss vorher gesetzt sein
	String s = DataToLongtext(data.werte);

	//Duplicate Entries verhindern !
	//Ein Eintrag ist doppelt, wenn die folgende Kombi schon vorhanden ist:
	//Session - Person - Position - State - Posture
	/* DEBUG, Einträge werden überschrieben, Todo: mit übergeben ob das gewünscht ist
	if (findDup(data))
		return fail(3, "Duplicate Entries: Der Datensatz ist bereits vorhanden");
	*/

	String q =
		"INSERT INTO `" + String(TABLE) +
		"` (`EcgData_ID`, `Sessions_ID`, `Subjects_ID`, `Channels_ID`, `States_ID`, `Postures_ID`, `Nummer`, `Usability`, `Beat`) VALUES (" +
		String(data.ecgdata)   + ", " +
		String(data.session)   + ", " +
		String(data.person)    + ", " +
		String(data.channel)   + ", " +
		String(data.state)     + ", " +
		String(data.posture)   + ", " +
		String(data.nummer)    + ", " +
		String(data.usability) + ", " +
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
bool cMySqlHeartbeats::saveWithArray(sBeatData data)
	{
	//Row muss vorher gesetzt sein
	String s = ArrayToLongtext(data.array_werte);

	//Duplicate Entries verhindern !
	//Ein Eintrag ist doppelt, wenn die folgende Kombi schon vorhanden ist:
	//Session - Person - Position - State - Posture
	/* DEBUG, Einträge werden überschrieben, Todo: mit übergeben ob das gewünscht ist
	if (findDup(data))
		return fail(3, "Duplicate Entries: Der Datensatz ist bereits vorhanden");
	*/

	String q =
		"INSERT INTO `" + String(TABLE) +
		"` (`EcgData_ID`, `Sessions_ID`, `Subjects_ID`, `Channels_ID`, `States_ID`, `Postures_ID`, `Nummer`, `Usability`, `Beat`) VALUES (" +
		String(data.ecgdata)   + ", " +
		String(data.session)   + ", " +
		String(data.person)    + ", " +
		String(data.channel)   + ", " +
		String(data.state)     + ", " +
		String(data.posture)   + ", " +
		String(data.nummer)    + ", " +
		String(data.usability) + ", " +
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
bool cMySqlHeartbeats::update(String feld, String newcontent, int ident)
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
bool cMySqlHeartbeats::findDup(sBeatData data)
	{
	String q = ftools.fmt("SELECT * FROM `%s` WHERE "
		"`EcgData_ID`   = %d AND "
		"`Sessions_ID`  = %d AND "
		"`Subjects_ID`  = %d AND "
		"`Channels_ID`  = %d AND "
		"`States_ID`    = %d AND "
		"`Postures_ID`  = %d AND "
		"`Nummer`       = %d",
		String(TABLE), data.ecgdata, data.session, data.person, data.channel, data.state, data.posture, data.nummer);

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
bool cMySqlHeartbeats::loadTable()
	{
	String q = "SELECT * FROM `" + String(TABLE) + "`";
	return doQuery(q);
	}
//---------------------------------------------------------------------------
bool cMySqlHeartbeats::loadFilteredTable(sBeatData filter)
	{
	String condition = "";
	if (filter.ident     > 0) addCondition(condition, "ID", String(filter.ident));
	if (filter.ecgdata   > 0) addCondition(condition, "ecgdata_ID",  String(filter.ecgdata));
	if (filter.session   > 0) addCondition(condition, "sessions_ID", String(filter.session));
	if (filter.person    > 0) addCondition(condition, "subjects_ID", String(filter.person));
	if (filter.channel   > 0) addCondition(condition, "channels_ID", String(filter.channel));
	if (filter.state     > 0) addCondition(condition, "states_ID",   String(filter.state));
	if (filter.posture   > 0) addCondition(condition, "postures_ID", String(filter.posture));

	if (filter.nummer    > 0) addCondition(condition, "Nummer",      String(filter.nummer));
	if (filter.usability > 0) addCondition(condition, "Usability",   String(filter.usability));

	if (condition == "")
		return loadTable();
	else
		return load(condition);
	}
//---------------------------------------------------------------------------
void cMySqlHeartbeats::addCondition(String& condition, String feld, String filter)
	{
	if (condition == "")
		condition = feld + "='" + filter + "'";
	else
		condition += " AND " + feld + "='" + filter + "'";
	}
//---------------------------------------------------------------------------
bool cMySqlHeartbeats::loadByIdent(int ecg)
	{
	String condition = "ID = " + String(ecg);
	return load(condition);
	}
//---------------------------------------------------------------------------
bool cMySqlHeartbeats::loadByPerson(int person)
	{
	String condition = "Subjects_ID = " + String(person);
	return load(condition);
	}
//---------------------------------------------------------------------------
bool cMySqlHeartbeats::loadBySession(int session)
	{
	String condition = "Sessions_ID = " + String(session);
	return load(condition);
	}
//---------------------------------------------------------------------------
bool cMySqlHeartbeats::load(String condition)
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
bool cMySqlHeartbeats::nextRow()
	{
	if (!fwork.isReady())
		return fail(1, "MySql-Verbindung wurde nicht initialisiert");

	frow = mysql_fetch_row(fres);
	if (frow == NULL) return false;
	if (!getRow())    return false;

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlHeartbeats::getLast()
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
bool cMySqlHeartbeats::deleteByIdent(int ident)
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
int cMySqlHeartbeats::getSize()
	{
	if (!loadTable())
		{
		fail(fwork.error_code, fwork.error_msg);
		return -1;
		}

	return get_num_rows();
	}
//---------------------------------------------------------------------------
bool cMySqlHeartbeats::getRow()
	{
	//aus row die fdata-Werte lesen
	if (frow == NULL) return false;

	fdata.ident     = String(frow[0]).ToIntDef(0);
	fdata.ecgdata   = String(frow[1]).ToIntDef(0);
	fdata.session   = String(frow[2]).ToIntDef(0);
	fdata.person    = String(frow[3]).ToIntDef(0);
	fdata.channel   = String(frow[4]).ToIntDef(0);
	fdata.state     = String(frow[5]).ToIntDef(0);
	fdata.posture   = String(frow[6]).ToIntDef(0);
	fdata.nummer    = String(frow[7]).ToIntDef(0);
	fdata.usability = String(frow[8]).ToIntDef(0);

	//Die EKG-Werte sind als semikolon-getrennter Longtext gespeichert
	int count = 0;
	if (!LongstrToData(String(frow[9]), fdata.werte, count))
		return fail(6, "Das Longtext-Feld 'Werte' konnte nicht eingelesen werden");

	double wert;
	fdata.array_werte.clear();
	for (int i = 0; i < count; i++)
		{
		wert = fdata.werte[i];
		fdata.array_werte[i].push_back(i);
		fdata.array_werte[i].push_back(wert);
		}

	return true;
	}
//---------------------------------------------------------------------------
bool cMySqlHeartbeats::LongstrToData(String str, double* werte, int& count)
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

		if (ix >= 2999)
            break; //zur Sicherheit
		}

	if (str != "")
		{
		sprintf(feld, "%s", AnsiString(str));
		wert = String(feld).ToDouble();
		werte[ix] = wert;
		}

    count = ix;
	return true;
	}
//---------------------------------------------------------------------------
String cMySqlHeartbeats::DataToLongtext(double* werte)
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
String cMySqlHeartbeats::ArrayToLongtext(iarray_t array)
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
sBeatData cMySqlHeartbeats::get_data()
	{
	return fdata;
	}
//---------------------------------------------------------------------------
int cMySqlHeartbeats::get_num_rows()
	{
	return mysql_num_rows(fres);
	}
//---------------------------------------------------------------------------
