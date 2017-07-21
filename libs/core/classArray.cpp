//---------------------------------------------------------------------------
#pragma hdrstop

#include "classArray.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cArray::cArray()
	{
	set_PointWidth(5);
	set_PointColor(clBlue);
	}
//---------------------------------------------------------------------------
cArray::~cArray()
	{
	}
//---------------------------------------------------------------------------
bool cArray::resetValues(sArrayCha& cha)
	{
	return resetValues(farr, cha);
	}
//---------------------------------------------------------------------------
bool cArray::resetValues(iarray_t& array, sArrayCha& cha)
	{
	if (array.size() <= 0)
		return fail(1, "Das Array ist leer oder nicht vorhanden.");

	//die Werte inputVonIdx, inputBisIdx, inputVonMsec, inputBisMsec,
	//inputMinWert und inputMaxWert müssen neu gesetzt werden
	iarray_itr itr = array.begin();
	int key = itr->first;
	ilist_t v = itr->second;
	double zeit = v[0];
	double wert = v[1];

	cha.VonIdx  = 0;
	cha.VonMsec = zeit;	cha.BisMsec = zeit;
	cha.MinWert = wert;	cha.MaxWert = wert;

	//array umschreiben in ein neues array und dann zurückassoziieren
	iarray_t arrneu = array; array.clear();
	int ix = 0;
	for (itr = arrneu.begin(); itr != arrneu.end(); itr++)
		{
		key = itr->first;
		ilist_t v = itr->second;
		zeit = v[0];
		wert = v[1];

		array[ix].push_back(zeit);
		array[ix].push_back(wert);
		ix++;

		if (key < cha.VonIdx)   cha.VonIdx = key;
		if (key > cha.BisIdx)   cha.BisIdx = key;

		if (zeit < cha.VonMsec) cha.VonMsec = zeit;
		if (zeit > cha.BisMsec) cha.BisMsec = zeit;

		if (wert < cha.MinWert) cha.MinWert = wert;
		if (wert > cha.MaxWert) cha.MaxWert = wert;
		}

	cha.BisIdx = ix-1;
	return ok();
	}
//---------------------------------------------------------------------------
void cArray::clearImg(TImage* img)
	{
	if (img == NULL) return; 
	img->Canvas->Brush->Color = clWhite;
	img->Canvas->FillRect(Rect(0, 0, img->Picture->Width, img->Picture->Height));
	img->Canvas->Pen->Color = clBlack;
	}
//---------------------------------------------------------------------------
bool cArray::redisplayPoints(const iarray_t& curve, const iarray_t& points, TImage* img)
	{
	//erste Kurve zeichnen
	if (!redisplay(curve, img)) return false;
	return displayPoints(curve, points, img);
	}
//---------------------------------------------------------------------------
bool cArray::displayPoints(const iarray_t& curve, iarray_t points, TImage* img)
	{
	farr = curve;
	if (!resetValues(farr_charac))
		return fail(1, "Reset-Values war nicht möglich.");

	double range_x  = farr_charac.BisIdx  - farr_charac.VonIdx;
	double range_y  = farr_charac.MaxWert - farr_charac.MinWert;
	double factor_x = (double)img->Width / range_x;
	double factor_y = (double)img->Height / range_y;

	img->Canvas->Brush->Color = fPointColor;

	double zeit, wert;
	int x, y, y1;

	bool alteBerechnung = false;
	for (int i = 0; i < points.size(); i++)
		{
		zeit = points[i][0];
		wert = points[i][1];

		//Anna 20.07.17: Berechnung angepasst an display()
		if (alteBerechnung)
			{
			wert -= farr_charac.MinWert; //relativ ausrichten

			x  = zeit * factor_x;
			y = img->Height - (wert * factor_y);
			}
		else
			{
			if (farr_charac.MinWert < 0) //es gibt negative Werte in der Kurve
				{
				//MinWert muss mit Null gleichgesetzt werden
				wert += (farr_charac.MinWert * -1);
				}
			else //es gubt keine negativen Werte in der Kurve
				{
				wert -= farr_charac.MinWert; //Kurve relativ unten ausrichten
				}

			x  = zeit * factor_x;
			y1 = wert * factor_y;
			y = img->Height - y1; //Y = 0 ist oben am Bildrand !
			}

		img->Canvas->FillRect(Rect(x-fPointWidth, y-fPointWidth, x+fPointWidth, y+fPointWidth));
		}

/*
		else //neue Berechnung ab dem 22.04.2017
			{
			if (farr_charac.MinWert < 0) //es gibt negative Werte in der Kurve
				{
				//MinWert muss mit Null gleichgesetzt werden
				val += (farr_charac.MinWert * -1);
				}
			else //es gubt keine negativen Werte in der Kurve
				{
				val -= farr_charac.MinWert; //Kurve relativ unten ausrichten
				}

			x  = count * factor_x;
			y1 = val * factor_y;
			y2 = img->Height - y1; //Y = 0 ist oben am Bildrand !
			}
*/
	img->Canvas->Brush->Color = clBlack;
	return ok();
	}
//---------------------------------------------------------------------------
bool cArray::redisplay(const iarray_t& array, TImage* img)
	{
	//Kombination aus clearImg und display, vereinfacht den Aufruf in höheren Klassen
	if (img == NULL) return fail(1, "Es wurde kein Bild übergeben.");
	clearImg(img);
	return display(array, img);
	}
//---------------------------------------------------------------------------
bool cArray::display(const iarray_t& array, TImage* img)
	{
	if (img == NULL)
		return fail(1, "Es wurde kein Bild übergeben.");

	farr = array;
	if (!resetValues(farr_charac))
		return fail(1, "Reset-Values war nicht möglich.");

	//--- Anzahl der x- und y-Werte ausrechnen
	double range_x = farr_charac.BisIdx  - farr_charac.VonIdx;
	double range_y = farr_charac.MaxWert - farr_charac.MinWert;

	if (range_x <= 0) return fail(1, "Die Input-Werte (Index) stimmen nicht");
	if (range_y <= 0) return fail(1, "Die Input-Werte (Value) stimmen nicht");

	//--- Anpassungfaktoren für x- und y-Achse ausrechnen
	double factor_x = (double)img->Width / range_x;
	double factor_y = (double)img->Height / range_y;

	//--> Bild vorbereiten, wird hier nicht gemacht, damit z.B. für den
	//Standardherzschlag mehrere Kurven übereinander gezeichnet werden können
	//d.h. das Löschen von gezeichnetem Inhalt liegt in der Verantwortung des
	//Aufrufenden

	//TEST 22.04.2017 !!
	bool alteBerechnung = false;

	//--- Map-Werte einzeichnen
	int zeit, x, y1, y2;
	double val;
	bool first = true;
	int count = 0;
	for (iarray_itr itr = farr.begin(); itr != farr.end(); itr++)
		{
		count++;

		ilist_t v = itr->second;
		zeit = v[0];
		val  = v[1];

		if (alteBerechnung)
			{
			if (val < 0) val *= -1; //auf positive Werte umrechnen ?
			val -= farr_charac.MinWert; //relativ ausrichten

			x  = count * factor_x;
			y1 = val * factor_y;

			//Y = 0 ist oben am Bildrand !
			y2 = img->Height - y1;
			}

		else //neue Berechnung ab dem 22.04.2017
			{
			if (farr_charac.MinWert < 0) //es gibt negative Werte in der Kurve
				{
				//MinWert muss mit Null gleichgesetzt werden
				val += (farr_charac.MinWert * -1);
				}
			else //es gubt keine negativen Werte in der Kurve
				{
				val -= farr_charac.MinWert; //Kurve relativ unten ausrichten
				}

			x  = zeit * factor_x;
			y1 = val  * factor_y;
			y2 = img->Height - y1; //Y = 0 ist oben am Bildrand !
			}

		if (first)
			{
			img->Canvas->MoveTo(x, y2);
			first = false;
			}
		else
			img->Canvas->LineTo(x, y2);
		}


	return ok();
	}
//---------------------------------------------------------------------------
#define MAX_NO_MOV_AV 250
iarray_t cArray::movingAv(const iarray_t& array, int window, bool CalcBegin)
	{
	farr.clear();
	if (window <= 0)
		{
		fail(1, "Das Fenster ist zu klein: " + String(window));
		return farr;
		}

	else if (window > array.size())
		{
		//Das Fenster ist größer als die Anzahl enthaltener Werte
		String m = "Das Fenster ist zu groß. Fenster = " + String(window) +
			", Anzahl Elemente im Array = " + String(farr.size());
		fail(1, m);
		return farr;
		}

	else if (window > MAX_NO_MOV_AV)
		{
		//Das Fenster ist größer als die maximal mögliche Anzahl
		String m =
			"Das Fenster ist größer als die maximal mögliche Breite. Fenster = "
			+ String(window) + ", Maximal möglich = " + String(MAX_NO_MOV_AV);
		fail(1, m);
		return farr;
		}

	farr = array;

	double mov[MAX_NO_MOV_AV];
	for (int i = 0; i < MAX_NO_MOV_AV; i++)
		mov[i] = 0.0;

	iarray_t neu;
	iarray_itr ineu;
	neu.clear();

	double zeit, lead1;
	double summe, mittel;
	int count = -1;
	int new_index = 0;
	for (iarray_itr itr = farr.begin(); itr != farr.end(); itr++)
		{
		count++;
		ilist_t& v = itr->second;
		zeit  = v[0];
		lead1 = v[1];

		if (count < window)
			{
			//es sind noch nicht genug Werte im array vorhanden, Wert hinten anhängen
			mov[count] = lead1;

			//wenn calcBegin=true dann trotzdem Mittelwert ausrechnen,
			//sonst unveränderten Wert aus dem Array übernehmen
			if (CalcBegin)
				{
				summe = 0;
				for (int a = 0; a <= count; a++)
					summe += mov[a];
				mittel = summe / (count+1);

				neu[new_index].push_back(zeit);
				neu[new_index].push_back(mittel);
				new_index++;
				}
			else
				{
				//Anfangswerte dienen nur zur Berechnung, aus dem Array werden
				//sie aber entfernt, weil die Fensterbreite noch nicht
				//erreicht ist
				/* das hier nicht machen !
				neu[i].push_back(zeit);
				neu[i].push_back(lead1);
				*/
				}
			continue;
			}

		//genug Werte vorhanden, alle Werte eins nach vorn schieben
		for (int a = 0; a < (window-1); a++)
			mov[a] = mov[a+1];
		mov[window-1] = lead1;

		summe = 0;
		for (int a = 0; a < window; a++)
			summe += mov[a];
		mittel = summe / window;

		neu[new_index].push_back(zeit);
		neu[new_index].push_back(mittel);
		new_index++;
		}

	//Werte wieder zurückschreiben ins array
	farr.clear();
	int ix = 0;
	for (ineu = neu.begin(); ineu != neu.end(); ineu++)
		{
		ilist_t& v = ineu->second;
		farr[ix].push_back(v[0]);
		farr[ix].push_back(v[1]);
		ix++;
		}

	ok();
	return farr;
	}
//---------------------------------------------------------------------------
iarray_t cArray::cut(iarray_t& array, int vonMsec, int bisMsec)
	{
	farr.clear();
	resetValues(array, farr_charac);

	if (vonMsec < farr_charac.VonMsec)
		{
		String m = "Der übergebene Wert 'Von' ist kleiner als der "
			"Anfangswert der Kurve: " + String(farr_charac.VonMsec);
		fail(1, m);
		return farr;
		}

	if (bisMsec > farr_charac.BisMsec)
		{
		String m = "Der übergebene Wert 'Bis' ist größer als der "
			"Endwert der Kurve: " + String(farr_charac.BisMsec);
		fail(1, m);
		return farr;
		}

	farr = array;

	int key, zeit;
	int count = 0;

	bool bUseOldCode = false; //Anna 23.04.17

	if (bUseOldCode)
		{
		//reverse Iterator, läuft von hinten nach vorne
		iarray_t::reverse_iterator itr_rev = farr.rbegin();
		do
			{
			key = itr_rev->first;
			ilist_t v = itr_rev->second;
			zeit = v[0];

			if (zeit < vonMsec) break;    //Wert liegt nach gewünschtem (reverse) Abschnitt
			if (zeit > bisMsec)
				{
				//Wert liegt vor gewünschtem (reverse) Abschnitt
				itr_rev++;
				continue;
				}

			farr.erase(key);
			count++;
			} while (itr_rev != farr.rend());
		}
	else
		{
		//neues Array bilden statt das bestehende zu manipulieren
		iarray_t arr;
		int count = 0;  double wert;
		for (iarray_itr itr = farr.begin(); itr != farr.end(); itr++)
			{
			key = itr->first;
			ilist_t v = itr->second;
			zeit = v[0];
			wert = v[1];

			if (zeit >= vonMsec && zeit <= bisMsec)
				{
				//Wert liegt im abzuschneidendem Abschnitt -> überspringen
				continue;
				}

			arr[count].push_back(zeit);
			arr[count].push_back(wert);
			count++;
			}
		farr = arr;
		}

	ok();
	return farr;
	}
//---------------------------------------------------------------------------
iarray_t cArray::get(iarray_t& array, int vonMsec, int bisMsec)
	{
	//den angegebenen Bereich rausschneiden und zurückgeben
	farr.clear();
	resetValues(array, farr_charac);

	if (vonMsec < farr_charac.VonMsec)
		{
		String m = "Der übergebene Wert 'Von' ist kleiner als der "
			"Anfangswert der Kurve: " + String(farr_charac.VonMsec);
		fail(1, m);
		return farr;
		}

	if (bisMsec > farr_charac.BisMsec)
		{
		String m = "Der übergebene Wert 'Bis' ist größer als der "
			"Endwert der Kurve: " + String(farr_charac.BisMsec);
		fail(1, m);
		return farr;
		}

	farr = array;

	iarray_t arr;
	int count = 0;  int zeit; double wert;
	for (iarray_itr itr = farr.begin(); itr != farr.end(); itr++)
		{
		ilist_t v = itr->second;
		zeit = v[0];
		wert = v[1];

		if (zeit <= vonMsec || zeit >= bisMsec)
			{
			//Wert liegt außerhalb des gewünschten Bereichs -> überspringen
			continue;
			}

		arr[count].push_back(zeit);
		arr[count].push_back(wert);
		count++;
		}
	farr = arr;

	ok();
	return farr;
	}
//---------------------------------------------------------------------------
iarray_t cArray::remove(const iarray_t& source, const iarray_t& remove, int val_index) //val_index ist mit 0 vorbesetzt
	{
	//aus dem Array "source" alle Einträge entfernen, die auch in "remove"
	//enthalten sind, identifiziert werden sollen Übereinstimmungen anhand des
	//second-Feld "val_index"

	iarray_t res; res.clear();
	double vals, valr, wert;
	int zeit;
	int count = 0;
	for (iarray_citr src = source.begin(); src != source.end(); src++)
		{
		ilist_t vs = src->second;
		vals = vs[val_index];

		bool found = false;
		for (iarray_citr rev = remove.begin(); rev != remove.end(); rev++)
			{
			ilist_t vr = rev->second;
			valr = vr[val_index];

			if (valr == vals)
				{
				found = true;
				break;
				}
			}

		if (!found)
			{
			zeit = vs[0];
			wert = vs[1];
			res[count].push_back(zeit);
			res[count].push_back(wert);
			count++;
			}
		}

	return res;
	}
//---------------------------------------------------------------------------
double cArray::calcAvWert(const iarray_t& array)
	{
	if (array.size() <= 0) return 0.0;

	double sum = 0.0;
	double wert;
	for (iarray_citr itr = array.begin(); itr != array.end(); itr++)
		{
		ilist_t v = itr->second;
		wert = v[1];
		sum += wert;
		}

	double res = sum / array.size();
	return res;
	}
//---------------------------------------------------------------------------
void cArray::set_PointWidth(int width)
	{
	fPointWidth = width;
	}
//---------------------------------------------------------------------------
void cArray::set_PointColor(TColor cl)
	{
	fPointColor = cl;
	}
//---------------------------------------------------------------------------

