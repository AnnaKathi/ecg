//Todo: Standardherzschlag auf bestimmte Zeitdauer normalisieren
//---------------------------------------------------------------------------
#pragma hdrstop

#include "classHeartbeat.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cHeartbeats::cHeartbeats()
	{
	}
//---------------------------------------------------------------------------
cHeartbeats::~cHeartbeats()
	{
	}
//---------------------------------------------------------------------------
bool cHeartbeats::reset(iarray_t curve)
	{
	//erst R-Peaks bilden
	cRpeaks rp;
	iarray_t rpeaks = rp.find(curve, NULL);

	return reset(curve, rpeaks);
	}
//---------------------------------------------------------------------------
bool cHeartbeats::reset(iarray_t curve, iarray_t rpeaks)
	{
	//von r-peak bis r-peak ist jeweils ein Herzschlag
	fcurve  = curve;
	frpeaks = rpeaks;

	if (!farray.resetValues(fcurve, charac))
		return fail(1, "Die Eigenschaftswerte konnten nicht gesetzt werden.");
	farray.farr_charac = charac;

	findex = 0;
	return ok();
	}
//---------------------------------------------------------------------------
bool cHeartbeats::first(iarray_t curve)
	{
	//erst R-Peaks bilden
	cRpeaks rp;
	iarray_t rpeaks = rp.find(curve, NULL);

	return first(curve, rpeaks);
	}
//---------------------------------------------------------------------------
bool cHeartbeats::first(iarray_t curve, iarray_t rpeaks)
	{
	if (!reset(curve, rpeaks))
		return fail(1, "Reset konnte nicht durchgeführt werden");

	return next();
	}
//---------------------------------------------------------------------------
bool cHeartbeats::next()
	{
	//den nächsten Herzschlag "rausschneiden" und in fheartbeat hinterlegen
	//den R-Peak[0] kann man überspringen, weil dieser den Anfang der Kurve,
	//und damit einen unvollständigen Herzschlag darstellt
	findex++;
	if (findex == frpeaks.size())
		return fail(0, "Ende der Kurve erreicht"); //letzter Abschnitt erreicht
	else if (findex >= frpeaks.size())
		return fail(2, "Index überschritten"); //das sollte eig nicht passieren

	int von = frpeaks[findex-1][0]; //Zeitwert vorangegangener R-Peak
	int bis = frpeaks[findex][0];	//Zeitwert aktueller R-Peak

	iarray_t rp = fcurve;
	rp = farray.cut(rp, charac.VonMsec, von-1);
	if (rp.size() <= 0)
		return fail(2, "Fehler beim Erstellen des Herzschlag-Arrays (von)");

	rp = farray.cut(rp, bis-1, charac.BisMsec);
	if (rp.size() <= 0)
		return fail(2, "Fehler beim Erstellen des Herzschlag-Arrays (bis)");

	//das gebildete Array muss neu indexiert werden, damit später der
	//Standardherzschlag gebildet werden kann
	fheartbeat.clear();
	int ix = 0;
	int zeit;
	double wert;
	for (iarray_itr itr = rp.begin(); itr != rp.end(); itr++)
		{
		ilist_t& v = itr->second;
		zeit = v[0];
		wert = v[1];

		fheartbeat[ix].push_back(zeit);
		fheartbeat[ix].push_back(wert);
		ix++;
		}

	return ok();
	}
//---------------------------------------------------------------------------
bool cHeartbeats::end()
	{
	if (findex >= frpeaks.size())
		return true;
	else
		return false;
	}
//---------------------------------------------------------------------------
iarray_t cHeartbeats::calcAvBeat(iarray_t curve)
	{
	fAvBeat.clear();

	if (!reset(curve))
		{
		fail(3, "Funktion 'first' konnte nicht durchgeführt werden.");
		return fAvBeat;
		}

	iarray_t avs; avs.clear(); //Durchschnittswerte
	int key, zeit, count, old_anz, new_anz;
	double wert, old_wert, new_wert;
	while (next())
		{
		//jeweils ein Herzschlag ist in fheartbeat abgespeichert, pro Zeitwert
		//werden alle gefundenen Ausschläge aufaddiert. Im zweiten Feld ist
		//die Anzahl der Werte gespeichert
		//todo Normalisierung einfügen
		for (iarray_itr itr = fheartbeat.begin(); itr != fheartbeat.end(); itr++)
			{
			key = itr->first;
			ilist_t& v = itr->second;
			zeit = v[0];
			wert = v[1];

			if (avs.count(key) > 0)
				{
				iarray_itr old_itr = avs.find(key);
				ilist_t& old_v = old_itr->second;
				old_wert = old_v[0];
				old_anz  = old_v[1];

				new_wert = old_wert + wert;
				new_anz  = old_anz  + 1;
				}
			else
				{
				new_wert = wert;
				new_anz  = 1;
				}

			avs.erase(key); //sonst wird ein neuer Vektor angelegt
			avs[key].push_back(new_wert);
			avs[key].push_back(new_anz);
			}
		}

	for (iarray_itr itr = avs.begin(); itr != avs.end(); itr++)
		{
		key = itr->first;
		ilist_t& v = itr->second;
		wert  = v[0];
		count = v[1];
		zeit  = key + 1; //key beginnt bei 0, Zeit bei 1

		new_wert = wert / (double)count;
		fAvBeat[key].push_back(zeit);
		fAvBeat[key].push_back(new_wert);
		}

	return fAvBeat;
	}
//---------------------------------------------------------------------------
bool cHeartbeats::rf_calcAvBeat(iarray_t curve)
	{
	fAvBeat.clear();

	if (!reset(curve))
		{
		fail(3, "Funktion 'first' konnte nicht durchgeführt werden.");
		return false;
		}

	iarray_t avs; avs.clear(); //Durchschnittswerte
	int key, zeit, count, old_anz, new_anz;
	double wert, old_wert, new_wert;
	while (next())
		{
		//jeweils ein Herzschlag ist in fheartbeat abgespeichert, pro Zeitwert
		//werden alle gefundenen Ausschläge aufaddiert. Im zweiten Feld ist
		//die Anzahl der Werte gespeichert
		//todo Normalisierung einfügen
		for (iarray_itr itr = fheartbeat.begin(); itr != fheartbeat.end(); itr++)
			{
			key = itr->first;
			ilist_t& v = itr->second;
			zeit = v[0];
			wert = v[1];

			if (avs.count(key) > 0)
				{
				iarray_itr old_itr = avs.find(key);
				ilist_t& old_v = old_itr->second;
				old_wert = old_v[0];
				old_anz  = old_v[1];

				new_wert = old_wert + wert;
				new_anz  = old_anz  + 1;
				}
			else
				{
				new_wert = wert;
				new_anz  = 1;
				}

			avs.erase(key); //sonst wird ein neuer Vektor angelegt
			avs[key].push_back(new_wert);
			avs[key].push_back(new_anz);
			}
		}

	for (iarray_itr itr = avs.begin(); itr != avs.end(); itr++)
		{
		key = itr->first;
		ilist_t& v = itr->second;
		wert  = v[0];
		count = v[1];
		zeit  = key + 1; //key beginnt bei 0, Zeit bei 1

		new_wert = wert / (double)count;
		fAvBeat[key].push_back(zeit);
		fAvBeat[key].push_back(new_wert);
		}

	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   private Funktionen   *******************************/
/***************************************************************************/
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   getter und setter   **************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
iarray_t cHeartbeats::get_heartbeat()
	{
	return fheartbeat;
	}
//---------------------------------------------------------------------------
iarray_t cHeartbeats::get_AvBeat()
	{
	return fAvBeat;
	}
//---------------------------------------------------------------------------

