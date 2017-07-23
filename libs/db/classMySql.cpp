//TODO: atoi überall umstellen auf String(fro2[x]).ToIntDef(0);
//---------------------------------------------------------------------------
#pragma hdrstop

#include <stdio.h>

#include "classMySql.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
INSTALL_GLOBALVAR_GUARD(cMySql, myptr)

/*
namespace {
	cMySql* myptr;
	struct globalvar_guard
		{
		friend cMySql;

		globalvar_guard()
			{
			}

		~globalvar_guard()
			{
			if (myptr)
				{
				delete myptr;
				myptr = 0;
				}
			}
		};
	globalvar_guard _guard;
	}
*/
//---------------------------------------------------------------------------
cMySql& cMySql::getRef()
	{
	if (myptr == 0)
		{
		myptr = new cMySql();
		}
	return *myptr;
	}
//---------------------------------------------------------------------------
cMySql::cMySql()
	: cBase()
    , fwork(cMySqlWork::getRef())
	{
	}
//---------------------------------------------------------------------------
void cMySql::init()
	{
	//todo -oms: bitte nach refac aus klasse entfernern
	fecg      = new cMySqlEcgData();
	fpeople   = new cMySqlPeople();
	fsessions = new cMySqlSession();
	ffeatures = new cMySqlFeature();

	fdiseases    = new cMySqlDescDb("diseases");
	fplaces      = new cMySqlDescDb("places");
	fresearchers = new cMySqlDescDb("researchers");
	fpostures    = new cMySqlDescDb("postures");
	fstates      = new cMySqlDescDb("states");
	fchannels    = new cMySqlDescDb("channels");
	falgpreproc  = new cMySqlDescDb("algpreprocessing");
	falgrpeaks   = new cMySqlDescDb("algrpeaks");
	falgfeatures = new cMySqlDescDb("algfeatures");
	}
//---------------------------------------------------------------------------
cMySql::~cMySql()
	{
	}
//---------------------------------------------------------------------------
void cMySql::shutdown()
	{
//	if (fwork)     delete fwork;
	if (fecg)      delete fecg;
	if (fpeople)   delete fpeople;
	if (fsessions) delete fsessions;
	if (ffeatures) delete ffeatures;

	if (fdiseases)    delete fdiseases; 		if (fplaces)    delete fplaces;
	if (fresearchers) delete fresearchers;		if (fpostures)  delete fpostures;
	if (fchannels)    delete fchannels; 		if (fstates)    delete fstates;
	if (falgfeatures) delete falgfeatures;		if (falgrpeaks) delete falgrpeaks;
	if (falgpreproc)  delete falgpreproc;
	}
//---------------------------------------------------------------------------
bool cMySql::create()
	{
	//erstellt die komplette (leere) Datenbank
	if (!fwork.script("create_all_databases"))
		return fail(fwork.error_code, fwork.error_msg);

	if (Application->MessageBox(
			L"Möchtest Du die Datenbank mit Dummy-Daten für die Grunddefinitionen "
			"füllen lassen (Erkrankungen, Orte, Untersuchender, Lagen, Stati, "
			"Positionen und Algorithmen) ?",
		L"Datenbank füllen ?",
		MB_YESNO) == IDYES)
		{
		//füllt die Datenbank mit Dummy-Datensätzen
		if (!fwork.script("insert_dummy_data_basic"))
			return fail(fwork.error_code, fwork.error_msg);
		}

	if (Application->MessageBox(
			L"Möchtest Du die Datenbank mit Dummy-Daten für Sessions "
			"füllen lassen (Personen, Seesions, EKG-Daten) ?",
		L"Datenbank füllen ?",
		MB_YESNO) == IDYES)
		{
		//füllt die Datenbank mit Dummy-Datensätzen
		if (!fwork.script("insert_dummy_data_sessions"))
			return fail(fwork.error_code, fwork.error_msg);
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
				L"Achtung: Die Datenbank 'ecg' wird mit allen zugehörigen "
				"Tabellen und Daten gelöscht. Dieser Prozess kann nicht "
				"zurückgenommen werden!\n\n"
				"Bist Du sicher, dass Du die Datenbank wirklich löschen willst? ",
			L"DATENBANK LÖSCHEN ?",
			MB_YESNO) == IDNO)
			return false;

		if (Application->MessageBox(
			L"Bist Du wirklich, wirklich sicher?\n(Vermeidung PN-Fehler)",
			L"DATENBANK LÖSCHEN ?",
			MB_YESNO) == IDNO)
			return false;

		String q = "DROP DATABASE `ecg`";
		if (!fwork.send(q))
			return fail(error_code, error_msg);

		Application->MessageBox(L"Datenbank gelöscht", L"Erfolgreich", MB_OK);
		}

	return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::dbExists()
	{
	String q = "SHOW DATABASES like 'ecg'";
	if (!fwork.query(q))
		return fail(fwork.error_code, fwork.error_msg);

	if (fwork.num_rows > 0) //Datenbank gibt es
		return true;
	else
		return false;
	}
//---------------------------------------------------------------------------
bool cMySql::tabExists(String tabelle)
	{
	String q = ftools.fmt("SHOW TABLES like '%s'", tabelle.c_str());

	if (!fwork.query(q))
		return fail(fwork.error_code, fwork.error_msg);

	if (fwork.num_rows > 0) //Tabelle gibt es
		return true;
	else
		return false;
	}
//---------------------------------------------------------------------------
bool cMySql::open()
	{
	if (!fwork.open())
		return fail(fwork.error_code, fwork.error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::openWithoutDb()
	{
	if (!fwork.openWithoutDb())
		return fail(fwork.error_code, fwork.error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::close()
	{
	if (!fwork.close())
		return fail(fwork.error_code, fwork.error_msg);
	else
		return ok();
	}
//---------------------------------------------------------------------------
bool cMySql::listTabs(TListView* lv)
	{
	if (!fwork.listIn(lv))
		return fail(fwork.error_code, fwork.error_msg);
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
cMySqlDescDb& cMySql::get_channels()
	{
	return *fchannels;
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

