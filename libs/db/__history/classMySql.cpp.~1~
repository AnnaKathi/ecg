//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cMySql::cMySql()
	{
	fwork     = new cMySqlWork();
	fecg      = new cMySqlEcgData(*fwork);
	fpeople   = new cMySqlPeople(*fwork);
	fsessions = new cMySqlSession(*fwork);
	ffeatures = new cMySqlFeature(*fwork);

	fdiseases    = new cMySqlDescDb(*fwork, "diseases");
	fplaces      = new cMySqlDescDb(*fwork, "places");
	fresearchers = new cMySqlDescDb(*fwork, "researchers");
	fpostures    = new cMySqlDescDb(*fwork, "postures");
	fstates      = new cMySqlDescDb(*fwork, "states");
	fpositions   = new cMySqlDescDb(*fwork, "positions");
	falgpreproc  = new cMySqlDescDb(*fwork, "algpreprocessing");
	falgrpeaks   = new cMySqlDescDb(*fwork, "algrpeaks");
	falgfeatures = new cMySqlDescDb(*fwork, "algfeatures");
	}
//---------------------------------------------------------------------------
cMySql::~cMySql()
	{
	if (fwork)     delete fwork;
	if (fecg)      delete fecg;
	if (fpeople)   delete fpeople;
	if (fsessions) delete fsessions;
	if (ffeatures) delete ffeatures;

	if (fdiseases)    delete fdiseases; 		if (fplaces)    delete fplaces;
	if (fresearchers) delete fresearchers;		if (fpostures)  delete fpostures;
	if (fpositions)   delete fpositions;		if (fstates)    delete fstates;
	if (falgfeatures) delete falgfeatures;		if (falgrpeaks) delete falgrpeaks;
	if (falgpreproc)  delete falgpreproc;
	}
//---------------------------------------------------------------------------
bool cMySql::create()
	{
	//erstellt die komplette (leere) Datenbank
	if (!fwork->script("create_all_databases"))
		return fail(fwork->error_code, fwork->error_msg);

	if (Application->MessageBox(
		ftools.fmt(
			"Möchtest Du die Datenbank mit Dummy-Daten für die Grunddefinitionen "
			"füllen lassen (Erkrankungen, Orte, Untersuchender, Lagen, Stati, "
			"Positionen und Algorithmen) ?").c_str(),
		"Datenbank füllen ?",
		MB_YESNO) == IDYES)
		{
		//füllt die Datenbank mit Dummy-Datensätzen
		if (!fwork->script("insert_dummy_data_basic"))
			return fail(fwork->error_code, fwork->error_msg);
		}

	if (Application->MessageBox(
		ftools.fmt(
			"Möchtest Du die Datenbank mit Dummy-Daten für Sessions "
			"füllen lassen (Personen, Seesions, EKG-Daten) ?").c_str(),
		"Datenbank füllen ?",
		MB_YESNO) == IDYES)
		{
		//füllt die Datenbank mit Dummy-Datensätzen
		if (!fwork->script("insert_dummy_data_sessions"))
			return fail(fwork->error_code, fwork->error_msg);
		}

	return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::drop()
	{
	//falls noch eine ecg-Datenbank vorhanden ist -> löschen
	if (dbExists())
		{
		if (Application->MessageBox(
			ftools.fmt(
				"Achtung: Die Datenbank 'ecg' wird mit allen zugehörigen "
				"Tabellen und Daten gelöscht. Dieser Prozess kann nicht "
				"zurückgenommen werden!\n\n"
				"Bist Du sicher, dass Du die Datenbank wirklich löschen willst? ").c_str(),
			"DATENBANK LÖSCHEN ?",
			MB_YESNO) == IDNO)
			return false;

		if (Application->MessageBox(
			ftools.fmt("Bist Du wirklich, wirklich sicher?\n(Vermeidung PN-Fehler)").c_str(),
			"DATENBANK LÖSCHEN ?",
			MB_YESNO) == IDNO)
			return false;

		String q = "DROP DATABASE `ecg`";
		if (!fwork->send(q))
			return fail(error_code, error_msg);

		Application->MessageBox("Datenbank gelöscht", "Erfolgreich", MB_OK);
		}

	return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::dbExists()
	{
	String q = "SHOW DATABASES like 'ecg'";
	if (!fwork->query(q))
		return fail(fwork->error_code, fwork->error_msg);

	if (fwork->num_rows > 0) //Datenbank gibt es
		return true;
	else
		return false;
	}
//---------------------------------------------------------------------------
bool cMySql::tabExists(String tabelle)
	{
	String q = ftools.fmt("SHOW TABLES like '%s'", tabelle);

	if (!fwork->query(q))
		return fail(fwork->error_code, fwork->error_msg);

	if (fwork->num_rows > 0) //Tabelle gibt es
		return true;
	else
		return false;
	}
//---------------------------------------------------------------------------
bool cMySql::open()
	{
	if (!fwork->open())
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::openWithoutDb()
	{
	if (!fwork->openWithoutDb())
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::close()
	{
	if (!fwork->close())
		return fail(fwork->error_code, fwork->error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::listTabs(TListView* lv)
	{
	if (!fwork->listIn(lv))
		return fail(fwork->error_code, fwork->error_msg);
	else
    	return ok();
	}
//---------------------------------------------------------------------------
//-- eigenständige databases ------------------------------------------------
//---------------------------------------------------------------------------
cMySqlEcgData& cMySql::get_ecg()
	{
	return *fecg;
	}
//---------------------------------------------------------------------------
cMySqlPeople& cMySql::get_people()
	{
	return *fpeople;
	}
//---------------------------------------------------------------------------
cMySqlSession& cMySql::get_sessions()
	{
	return *fsessions;
	}
//---------------------------------------------------------------------------
cMySqlFeature& cMySql::get_features()
	{
	return *ffeatures;
	}
//---------------------------------------------------------------------------
//-- description databases --------------------------------------------------
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_diseases()
	{
	return *fdiseases;
	}
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_places()
	{
	return *fplaces;
	}
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_researchers()
	{
	return *fresearchers;
	}
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_postures()
	{
	return *fpostures;
	}
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_states()
	{
	return *fstates;
	}
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_positions()
	{
	return *fpositions;
	}
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_alg_preproc()
	{
	return *falgpreproc;
	}
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_alg_rpeaks()
	{
	return *falgrpeaks;
	}
//---------------------------------------------------------------------------
cMySqlDescDb& cMySql::get_alg_features()
	{
	return *falgfeatures;
	}
//---------------------------------------------------------------------------

