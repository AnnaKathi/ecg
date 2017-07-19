//---------------------------------------------------------------------------
#ifndef classMySqlH
#define classMySqlH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../basics/classBase.h"
#include "../basics/classTools.h"
#include "classMySql_Work.h"
#include "classMySql_EcgData.h"
#include "classMySql_People.h"
#include "classMySql_Session.h"
#include "classMySql_Features.h"
#include "classMySql_DescDb.h"
//---------------------------------------------------------------------------
class PACKAGE cMySql : public cBase
	{
public:
	cMySql();
	~cMySql();

	bool 	create();
	bool 	drop();
	bool	dbExists();
	bool	tabExists(String tabelle);

	bool 	open();
	bool 	openWithoutDb();
	bool	close();

	bool	listTabs(TListView* lv);

__property cMySqlEcgData&  ecg      = { read=get_ecg };
__property cMySqlPeople&   people   = { read=get_people   };
__property cMySqlSession&  sessions = { read=get_sessions };
__property cMySqlFeature&  features = { read=get_features };

__property cMySqlDescDb&   researchers = { read=get_researchers  };
__property cMySqlDescDb&   algpreproc  = { read=get_alg_preproc  };
__property cMySqlDescDb&   algrpeaks   = { read=get_alg_rpeaks   };
__property cMySqlDescDb&   algfeatures = { read=get_alg_features };
__property cMySqlDescDb&   positions   = { read=get_positions    };
__property cMySqlDescDb&   diseases    = { read=get_diseases     };
__property cMySqlDescDb&   states      = { read=get_states       };
__property cMySqlDescDb&   postures    = { read=get_postures     };
__property cMySqlDescDb&   places      = { read=get_places       };

private:
	cTools			ftools;
	cMySqlWork*		fwork;

	cMySqlEcgData*	fecg;
	cMySqlEcgData&  get_ecg();

	cMySqlPeople*	fpeople;
	cMySqlPeople&	get_people();

	cMySqlSession*	fsessions;
	cMySqlSession&	get_sessions();

	cMySqlFeature*	ffeatures;
	cMySqlFeature&	get_features();

	//description databases
	cMySqlDescDb*	fdiseases;     cMySqlDescDb&	get_diseases();
	cMySqlDescDb*	fplaces;       cMySqlDescDb&	get_places();
	cMySqlDescDb*	fresearchers;  cMySqlDescDb&	get_researchers();
	cMySqlDescDb*	fpostures;     cMySqlDescDb&	get_postures();
	cMySqlDescDb*	fstates;       cMySqlDescDb&	get_states();
	cMySqlDescDb*	fpositions;    cMySqlDescDb&	get_positions();
	cMySqlDescDb*	falgpreproc;   cMySqlDescDb&	get_alg_preproc();
	cMySqlDescDb*	falgrpeaks;    cMySqlDescDb&	get_alg_rpeaks();
	cMySqlDescDb*	falgfeatures;  cMySqlDescDb&	get_alg_features();
	};
//---------------------------------------------------------------------------
#endif
