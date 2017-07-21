//wird aktuell (noch) nicht verwendet
//---------------------------------------------------------------------------
#pragma hdrstop

#include "classQrs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cQrs::cQrs()
	{
	}
//---------------------------------------------------------------------------
cQrs::~cQrs()
	{
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   public functions   ***********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cQrs::build(iarray_t curve, iarray_t rpeaks)
	{
	bool bLog = true;

	if (curve.size() <= 0)  return fail(1, "Es wurde keine EKG-Kurve übergeben");
	if (rpeaks.size() <= 0) return fail(1, "Es wurden keine R-Peaks übergeben");

	//zuerst die Kurve glätten ???
	//TEST DEBUG curve = farray.movingAv(curve, 25, true);

	int zeit; double peak;
	fTurns.clear(); int count = 0;
	int qrsLength = 120;
	int qrsSide   = qrsLength / 2;
	for (iarray_itr itr = rpeaks.begin(); itr != rpeaks.end(); itr++)
		{
		//der QRS-Bereich kann (sollte) max. 120ms lang sein
		//R liegt ziemlich genau in der Mitte --> von R ausgehend ist der
		//QRS-Bereich max +- 60ms links und rechts verteilt
		ilist_t v = itr->second;
		zeit = v[0];
		peak = v[1];
		if (zeit < qrsSide)
			continue; //R-Peak liegt zu nah am Aufzeichnungsbeginn

		//DEBUG Anna 20.07.17 iarray_t links = farray.cut(curve, zeit-qrsSide, zeit-1);
		//DEBUG Anna 20.07.17 iarray_t rechts = farray.cut(curve, zeit+1, zeit+qrsSide);

		iarray_t links  = farray.get(curve, zeit-qrsSide, zeit-1);
		iarray_t rechts = farray.get(curve, zeit+1, zeit+qrsSide);
		
		if (bLog)
			{
			ftools.Log("\t\tQrsBuild: R-Peak (%d, %.8f), links %d Werte, rechts %d Werte", zeit, peak, links.size(), rechts.size());
			ftools.Log("\t\tSuche links nach Q-Punkt...");
			}

		//Q finden: links den ersten Wendepunkt feststellen
		iarray_itr testitr; ilist_t testv;
		testitr = curve.find(zeit);   testv = testitr->second; double test = testv[1];
		testitr = curve.find(zeit-1); testv = testitr->second; double prev = testv[1];
		testitr = curve.find(zeit-5); testv = testitr->second; double wert = testv[1];

		/* DEBUG Anna 20.07.
		double test = curve[zeit][1];
		double prev = curve[zeit-1][1];
		double wert = curve[zeit-5][1];
		*/

		if (bLog) ftools.Log("\t\tSteigung feststellen: zeit(%d) = %.8f, zeit-1(%d) = %.8f, zeit-5(%d) = %.8f", zeit, test, zeit-1, prev, zeit-5, wert);
		
		//Richtung feststellen
		bool fallend;
		if (prev < wert)
			fallend = true;
		else
			fallend = false;

		if (bLog)
			{
			if (fallend) ftools.Log("\t\t\tlinke Kurve ist fallend");
			else ftools.Log("\t\t\tlinke Kurve ist steigend");
			}

		int QLoc = 0; double QAmp;
		for (int i = zeit-2; i > zeit-qrsSide; i--)
			{
			wert = curve[i][1];
			if (bLog) ftools.Log("\t\t\t%03d: %.8f", i, wert);

			//wert sollte dem Trend folgen, sonst liegt ein Wendepunkt vor
			if ((fallend && wert < prev) || (!fallend && wert > prev))
				{
				prev = wert;
				continue;
				}

			//Wendepunkt gefunden
			QLoc = i;
			QAmp = wert;
			if (bLog) ftools.Log("\t\t\tQ-Punkt gefunden: %d, %.4f", QLoc, QAmp);
			break;
			}

		if (QLoc == 0) continue; //nicht gefunden

		//S finden: rechts den ersten Wendepunkt feststellen
		prev = curve[zeit+1][1];
		wert = curve[zeit+5][1];
		//Richtung feststellen
		if (prev > wert)
			fallend = true;
		else
			fallend = false;

		int SLoc = 0; double SAmp;
		for (int i = zeit+2; i < zeit+qrsSide; i++)
			{
			wert = curve[i][1];

			//wert sollte dem Trend folgen, sonst liegt ein Wendepunkt vor
			if ((fallend && wert < prev) || (!fallend && wert > prev))
				{
				prev = wert;
				continue;
				}

			//Wendepunkt gefunden
			SLoc = i;
			SAmp = wert;
			break;
			}

		if (SLoc == 0) continue; //nicht gefunden

		//alle QRS-Werte gefunden
		fTurns[count].push_back(QLoc);
		fTurns[count].push_back(QAmp);
		fTurns[count].push_back(zeit);
		fTurns[count].push_back(peak);
		fTurns[count].push_back(SLoc);
		fTurns[count].push_back(SAmp);
		count++;
		}

	if (fTurns.size() <= 0) return fail(1, "Es wurden keine Wendepunkte gefunden");
	else return ok();
	}
//---------------------------------------------------------------------------
bool cQrs::reset()
	{
	fIndex = -1;
	return true;
	}
//---------------------------------------------------------------------------
bool cQrs::next()
	{
	fIndex++;
	if (fIndex >= fTurns.size()) return false;

	fArea.Q.zeit = fTurns[fIndex][0];
	fArea.Q.wert = fTurns[fIndex][1];
	fArea.R.zeit = fTurns[fIndex][2];
	fArea.R.wert = fTurns[fIndex][3];
	fArea.S.zeit = fTurns[fIndex][4];
	fArea.S.wert = fTurns[fIndex][5];
	return true;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   private functions   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
int cQrs::findTurn(iarray_t array, int von, int bis)
	{
	//todo
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   getter und setter   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
int cQrs::get_anz_turns()
	{
	return fTurns.size();
	}
//---------------------------------------------------------------------------

