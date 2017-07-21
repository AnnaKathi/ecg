//---------------------------------------------------------------------------
#pragma hdrstop

#include "classData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cData::cData()
	: fcsv(new cCsv), farray(new cArray), fderiv1(new cDerivate), fderiv2(new cDerivate)
	{
	}
//---------------------------------------------------------------------------
cData::~cData()
	{
	if (fcsv)    delete fcsv;
	if (farray)  delete farray;
	if (fderiv1) delete fderiv1;
	if (fderiv2) delete fderiv2;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   private Funktionen   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
void cData::resetValues()
	{
	//die Werte inputVonIdx, inputBisIdx, inputVonMsec, inputBisMsec,
	//inputMinWert und inputMaxWert müssen neu gesetzt werden
	iarray_itr itr = farr.begin();
	int key = itr->first;
	ilist_t& v = itr->second;
	double zeit = v[0];
	double wert = v[1];

	farr_charac.VonIdx  = 0;
	farr_charac.VonMsec = zeit;	farr_charac.BisMsec = zeit;
	farr_charac.MinWert = wert;	farr_charac.MaxWert = wert;

	//array umschreiben in ein neues array und dann zurückassoziieren
	iarray_t arrneu = farr; farr.clear();
	int ix = 0;
	for (itr = arrneu.begin(); itr != arrneu.end(); itr++)
		{
		key = itr->first;
		ilist_t& v = itr->second;
		zeit = v[0];
		wert = v[1];

		farr[ix].push_back(zeit);
		farr[ix].push_back(wert);
		ix++;

		if (key < farr_charac.VonIdx) farr_charac.VonIdx = key;
		if (key > farr_charac.BisIdx) farr_charac.BisIdx = key;

		if (zeit < farr_charac.VonMsec) farr_charac.VonMsec = zeit;
		if (zeit > farr_charac.BisMsec) farr_charac.BisMsec = zeit;

		if (wert < farr_charac.MinWert) farr_charac.MinWert = wert;
		if (wert > farr_charac.MaxWert) farr_charac.MaxWert = wert;
		}

	farr_charac.BisIdx = ix-1;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Grundfunktionen   ************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cData::getFile(String file, eDatFormat format, String delim, int lead, int vonMsec, int bisMsec)
	{
	farr.clear();

	if (!fcsv->OpenFile(file, format, delim, lead))
		return fail(fcsv->error_code, fcsv->error_msg);

	if (!fcsv->StartAt(vonMsec))
		return fail(fcsv->error_code, fcsv->error_msg);

	farr_charac.VonMsec = farr_charac.BisMsec = fcsv->getSample();
	farr_charac.MinWert = farr_charac.MaxWert = fcsv->getVal();

	double zeit;
	double lead1;
	int ix = 0;
	do
		{
		zeit  = fcsv->getLineNo(); //todo: fcsv->getSample(); ist in Datei nicht vorhanden
		lead1 = fcsv->getVal();
		farr[ix].push_back(zeit);
		farr[ix].push_back(lead1);
		ix++;

		if (zeit < farr_charac.VonMsec) farr_charac.VonMsec = zeit;
		if (zeit > farr_charac.BisMsec) farr_charac.BisMsec = zeit;

		if (lead1 < farr_charac.MinWert) farr_charac.MinWert = lead1;
		if (lead1 > farr_charac.MaxWert) farr_charac.MaxWert = lead1;
		}
	while (fcsv->NextUntil(bisMsec));

	farr_charac.VonIdx = 0;
	farr_charac.BisIdx = ix-1;
	farr_charac.Number = farr.size();
	return ok();
	}
//---------------------------------------------------------------------------
bool cData::redisplay(TImage* img)
	{
    return farray->redisplay(farr, img);
	}
//---------------------------------------------------------------------------
bool cData::movingAv(int window, bool CalcBegin) //default CalcBegin=true
	{
	farr = farray->movingAv(farr, window, CalcBegin);

	if (!farray->error)
		{
		//die Werte inputVonIdx, inputBisIdx, inputVonMsec, inputBisMsec,
		//inputMinWert und inputMaxWert müssen neu gesetzt werden
		farray->resetValues(farr, farr_charac);
		return ok();
        }
	else
		return fail(farray->error_code, farray->error_msg);
	}
//---------------------------------------------------------------------------
bool cData::cut(int vonMsec, int bisMsec)
	{
	farr = farray->cut(farr, vonMsec, bisMsec);

	if (!farray->error)
		{
		//die Werte inputVonIdx, inputBisIdx, inputVonMsec, inputBisMsec,
		//inputMinWert und inputMaxWert müssen neu gesetzt werden
		farray->resetValues(farr, farr_charac);
		return ok();
		}
	else
		return fail(farray->error_code, farray->error_msg);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/********************   math. Funktionen   *********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cData::buildDerivates()
	{
	if (farr.size() <= 0)
		return fail(1, "Das Daten-Array ist leer");

	if (!fderiv1->build(farr))
		; //todo

	if (!fderiv2->build(fderiv1->deriv_array))
		; //todo
		
	return ok();
	}
//---------------------------------------------------------------------------
iarray_t cData::normalize(iarray_t array, int length)
	{
	bool bLog = false;
	//Array auf die übergebene Länge normalisieren
	//wenn das Array verkürzt werden muss, werden Werte gelöscht, wenn es
	//verlängert werden muss, werden Durchschnittswerte hinzugefügt
	int arraylen = array.size();
	if (arraylen == length) return array; //passt bereits

	iarray_t newarray; newarray.clear();
	if (arraylen > length)
		{
		//Array verkürzen
		int delvals = arraylen - length;  //soviele Werte müssen gelöscht werden
		double blocks  = (double)arraylen / (double)delvals; //alle x Werte einen Wert löschen

		if (bLog) ftools.Log("\t\t\tnormalise: aktuelle Länge = %d", arraylen);
		if (bLog) ftools.Log("\t\t\tnormalise: Werte löschen = %d", delvals);
		if (bLog) ftools.Log("\t\t\tnormalise: Blocks, alle %.2f Werte einen löschen", blocks);

		//der erste Wert wird direkt am Anfang gelöscht (zw. 1. und 2. Wert)
		double pos = 1.0;
		int ix  = 0;
		int key, zeit;
		double wert, newval;

		for (iarray_itr itr = array.begin(); itr != array.end(); itr++)
			{
			key = itr->first;
			ilist_t& v = itr->second;
			zeit = v[0];
			wert = v[1];

			if (key == (int)pos)
				{
				//diesen Wert überspringen
				pos += blocks;
				}
			else
				{
				//bestehenden Wert übertragen
				newarray[ix].push_back(ix);
				newarray[ix].push_back(wert);
				ix++;
				}
			}
		}
	else
		{
		//Array verlängern
		int newvals = length - arraylen;  //soviele neue Werte werden benötigt
		double blocks  = (double)arraylen / (double)newvals; //alle x Werte einen neuen Wert einfügen

		if (bLog) ftools.Log("\t\t\tnormalise: aktuelle Länge = %d", arraylen);
		if (bLog) ftools.Log("\t\t\tnormalise: Werte hinzufügen = %d", newvals);
		if (bLog) ftools.Log("\t\t\tnormalise: Blocks, alle %.2f Werte einen einfügen", blocks);

		//der erste Wert wird direkt am Anfang eingefügt (zw. 1. und 2. Wert)
		double pos = 1.0;
		int ix  = 0;
		int key, zeit;
		double wert, newval;
		double lastwert = 0.0;

		for (iarray_itr itr = array.begin(); itr != array.end(); itr++)
			{
			key = itr->first;
			ilist_t& v = itr->second;
			zeit = v[0];
			wert = v[1];

			//bestehenden Wert übertragen
			newarray[ix].push_back(ix);
			newarray[ix].push_back(wert);
			ix++;
			if (key >= pos)
				{
				//hier einen Wert einfügen
				newval = (lastwert+wert)/2;
				newarray[ix].push_back(ix);
				newarray[ix].push_back(newval);
				ix++;

				pos += blocks;
				}

			lastwert = wert;
			}
		}

	return newarray;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   getter und setter   **************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
iarray_t& cData::get_array()
	{
	return farr;
	}
//---------------------------------------------------------------------------
cDerivate& cData::get_deriv1()
	{
	return *fderiv1;
	}
//---------------------------------------------------------------------------
cDerivate& cData::get_deriv2()
	{
	return *fderiv2;
	}
//---------------------------------------------------------------------------

