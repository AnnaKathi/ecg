//---------------------------------------------------------------------------
#pragma hdrstop

#include "classCsv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cCsv::cCsv()
	: fp(0)
	, fpMax(0)
	{
	}
//---------------------------------------------------------------------------
cCsv::~cCsv()
	{
	CloseFile();
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cCsv::OpenFile(String file, eDatFormat format, String delim, int lead)
	{
	if (file == "")
		{
		return fail(EC_NOFILE, "keine Datei übergeben");
		}

	fp = fopen(AnsiString(file).c_str(), "r");
	if (fp == NULL)
		{
		return fail(EC_FNF, "Datei nicht gefunden: " + file);
		}

	strcpy(Delim, AnsiString(delim).c_str());
	Format = format;
	iLead = lead;

	LineCount = -1;

	fseek(fp, 0, SEEK_END);
	fpMax = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return ok();
	}
//---------------------------------------------------------------------------
void cCsv::CloseFile()
	{
	if (fp != NULL)
		{
		fclose(fp);
		fp = NULL;
		}
	}
//---------------------------------------------------------------------------
bool cCsv::Reset()
	{
	if (fseek(fp, 0, SEEK_SET) == 0)
		return ok();
	else
		return fail(EC_FPSEEK, "Filepointer konnte nicht zurückgesetzt werden");
	}
//---------------------------------------------------------------------------
bool cCsv::StartAt(int sample)
	{
	bFirstParse = true;
	if (!Skip()) return false;
	if (sample == -1) //von Anfang an lesen
		return ok();
	else
		{
		int rc = false;
		while (Next())
			{
			if (EcgLine.sample >= sample)
				{
				//genauen Wert oder den nächsten gefunden, EKG-Werte stehen durch
				//Next() bereits in EcgLine
				rc = true;
				break;
				}
			}

		return rc;
		}
	}
//---------------------------------------------------------------------------
bool cCsv::Skip()
	{
	//erste(n) Zeilen ggf. überlesen (Überschriften usw.)
	if (fp == NULL)
		return fail(EC_NOFP, "(skip) keine Datei vorhanden");

	bool fehler = false;
	if (Format == formatNone)
		{
		if (!SkipRow())
			fehler = true;
		}

	else if (Format == formatADS)
		{
		//im ADS-Format sind 8 Zeilen zu überlesen
		//(elf für allg Infos und eine für Überschriften)
		for (int i = 0; i < 8; i++)
			{
			if (!SkipRow())
				{
				fehler = true;
				break;
				}
			}
		}

	return !fehler;
	}
//---------------------------------------------------------------------------
bool cCsv::SkipRow()
	{
	//eine Zeile überspringen
	if (fgets(rowbuf, sizeof(rowbuf)-1, fp) == NULL)
		return fail(EC_NOROW, "(skip) keine Zeile einzulesen");
	return ok();
	}
//---------------------------------------------------------------------------
bool cCsv::First()
	{
	return Next();
	}
//---------------------------------------------------------------------------
bool cCsv::Next()
	{
	if (fp == NULL)
		return fail(EC_NOFP, "(next) keine Datei vorhanden");

	do
		{
		if (fgets(rowbuf, sizeof(rowbuf)-1, fp) == NULL)
			return fail(EC_NOROW, "(skip) keine Zeile einzulesen");

		} while (String(rowbuf) == "\n");

	LineCount++;
	return ParseLine();
	}
//---------------------------------------------------------------------------
bool cCsv::NextUntil(int sample)
	{
	if (!Next()) return false;
	if (sample > 0 && EcgLine.sample > sample)
		{
		//hier aufhören
		return false;
		}
	return true;
	}
//---------------------------------------------------------------------------
bool cCsv::ParseLine()
	{
	//nicht ein bestimmtes Feld einlesen, sondern ganze Zeile einlesen und in
	//der Struktur cEcgLine speichern
	char* pt;
	char feld[32];
	double val;

	EcgLine.sample = LineCount;
	EcgLine.lineno = LineCount;

	//es gibt acht Spalten, die einglesen werden müssen
	pt = strchr(rowbuf, Delim[0]); if (!pt) return false; *pt = 0;
	sprintf(feld, "%s", rowbuf); sprintf(rowbuf, "%s", pt+1);
	pt = strchr(feld, ','); if (pt) *pt = '.'; val = atof(feld);
	EcgLine.ch1 = val;

	pt = strchr(rowbuf, Delim[0]); if (!pt) return false; *pt = 0;
	sprintf(feld, "%s", rowbuf); sprintf(rowbuf, "%s", pt+1);
	pt = strchr(feld, ','); if (pt) *pt = '.'; val = atof(feld);
	EcgLine.ch2 = val;

	pt = strchr(rowbuf, Delim[0]); if (!pt) return false; *pt = 0;
	sprintf(feld, "%s", rowbuf); sprintf(rowbuf, "%s", pt+1);
	pt = strchr(feld, ','); if (pt) *pt = '.'; val = atof(feld);
	EcgLine.ch3 = val;

	pt = strchr(rowbuf, Delim[0]); if (!pt) return false; *pt = 0;
	sprintf(feld, "%s", rowbuf); sprintf(rowbuf, "%s", pt+1);
	pt = strchr(feld, ','); if (pt) *pt = '.'; val = atof(feld);
	EcgLine.ch4 = val;

	pt = strchr(rowbuf, Delim[0]); if (!pt) return false; *pt = 0;
	sprintf(feld, "%s", rowbuf); sprintf(rowbuf, "%s", pt+1);
	pt = strchr(feld, ','); if (pt) *pt = '.'; val = atof(feld);
	EcgLine.ch5 = val;

	pt = strchr(rowbuf, Delim[0]); if (!pt) return false; *pt = 0;
	sprintf(feld, "%s", rowbuf); sprintf(rowbuf, "%s", pt+1);
	pt = strchr(feld, ','); if (pt) *pt = '.'; val = atof(feld);
	EcgLine.ch6 = val;

	pt = strchr(rowbuf, Delim[0]); if (!pt) return false; *pt = 0;
	sprintf(feld, "%s", rowbuf); sprintf(rowbuf, "%s", pt+1);
	pt = strchr(feld, ','); if (pt) *pt = '.'; val = atof(feld);
	EcgLine.ch7 = val;

	sprintf(feld, "%s", rowbuf); 
	pt = strchr(feld, ','); if (pt) *pt = '.'; val = atof(feld);
	EcgLine.ch8 = val;

	//berechnete Ergebnisse
	EcgLine.v12 = EcgLine.ch8 - EcgLine.ch4;
	EcgLine.v34 = EcgLine.ch5 - EcgLine.ch6;
	EcgLine.v56 = EcgLine.ch7 - EcgLine.ch1;

	if (bFirstParse)
		{
		bFirstParse = false;
		EcgLine.min[1] = EcgLine.ch1; EcgLine.min[2] = EcgLine.ch2;
		EcgLine.min[3] = EcgLine.ch3; EcgLine.min[4] = EcgLine.ch4;
		EcgLine.min[5] = EcgLine.ch5; EcgLine.min[6] = EcgLine.ch6;
		EcgLine.min[7] = EcgLine.ch7; EcgLine.min[8] = EcgLine.ch8;

		EcgLine.min[9]  = EcgLine.v12;
		EcgLine.min[10] = EcgLine.v34;
		EcgLine.min[11] = EcgLine.v56;

		EcgLine.max[1] = EcgLine.ch1; EcgLine.max[2] = EcgLine.ch2;
		EcgLine.max[3] = EcgLine.ch3; EcgLine.max[4] = EcgLine.ch4;
		EcgLine.max[5] = EcgLine.ch5; EcgLine.max[6] = EcgLine.ch6;
		EcgLine.max[7] = EcgLine.ch7; EcgLine.max[8] = EcgLine.ch8;

		EcgLine.max[9]  = EcgLine.v12;
		EcgLine.max[10] = EcgLine.v34;
		EcgLine.max[11] = EcgLine.v56;
		}
	else
		{
		if (EcgLine.ch1 < EcgLine.min[1]) EcgLine.min[1] = EcgLine.ch1;
		if (EcgLine.ch2 < EcgLine.min[2]) EcgLine.min[2] = EcgLine.ch2;
		if (EcgLine.ch3 < EcgLine.min[3]) EcgLine.min[3] = EcgLine.ch3;
		if (EcgLine.ch4 < EcgLine.min[4]) EcgLine.min[4] = EcgLine.ch4;
		if (EcgLine.ch5 < EcgLine.min[5]) EcgLine.min[5] = EcgLine.ch5;
		if (EcgLine.ch6 < EcgLine.min[6]) EcgLine.min[6] = EcgLine.ch6;
		if (EcgLine.ch7 < EcgLine.min[7]) EcgLine.min[7] = EcgLine.ch7;
		if (EcgLine.ch8 < EcgLine.min[8]) EcgLine.min[8] = EcgLine.ch8;

		if (EcgLine.ch1 > EcgLine.max[1]) EcgLine.max[1] = EcgLine.ch1;
		if (EcgLine.ch2 > EcgLine.max[2]) EcgLine.max[2] = EcgLine.ch2;
		if (EcgLine.ch3 > EcgLine.max[3]) EcgLine.max[3] = EcgLine.ch3;
		if (EcgLine.ch4 > EcgLine.max[4]) EcgLine.max[4] = EcgLine.ch4;
		if (EcgLine.ch5 > EcgLine.max[5]) EcgLine.max[5] = EcgLine.ch5;
		if (EcgLine.ch6 > EcgLine.max[6]) EcgLine.max[6] = EcgLine.ch6;
		if (EcgLine.ch7 > EcgLine.max[7]) EcgLine.max[7] = EcgLine.ch7;
		if (EcgLine.ch8 > EcgLine.max[8]) EcgLine.max[8] = EcgLine.ch8;
		}
	return true;
	}
//---------------------------------------------------------------------------
bool cCsv::ParseLineOld()
	{
	//die Werte werden Semikolon- oder Tabgetrennt aufgeführt
	char value[128];
	char* pt;
	double val;

	for (int i = 0; i < iLead; i++)
		{
		//Felder überspringen
		pt = strchr(rowbuf, Delim[0]);
		*pt = 0;
		strcpy(rowbuf, pt+1);
		}

	//jetzt kommt das gewünschte Feld
	String feld;
	pt = strchr(rowbuf, Delim[0]);
	if (pt == NULL)
		{
		//Feld ist das letzte Feld
		feld = String(rowbuf);
		}
	else
		{
		//Feld ist nicht das letzte Feld
		*pt = 0;
		feld = String(rowbuf);
		}

	//Komma durch Punkt ersetzen, damit die Nachkommastellen richtig rauskommen
	int n = feld.Pos(",");
	if (n > 0)
		feld = feld.SubString(0, n-1) + "." + feld.SubString(n+1, 9999);
	strcpy(value, AnsiString(feld).c_str());

	val = atof(value);

	EcgLine.sample = LineCount;
	EcgLine.lineno = LineCount;
	EcgLine.ch1 = val;
	return ok();
	}
//---------------------------------------------------------------------------
bool cCsv::ParseLineObsolete()
	{
	//die Werte werden Semikolon- oder Tabgetrennt aufgeführt
	char value[128];
	char* pt;
	double val;

	bool rc = true;
	int max;
	if (Format == formatNone) max = 8;
	else if (Format == formatADS) max = 7;

	String feld;
	for (int i = 0; i <= max; i++)
		{
		pt = strchr(rowbuf, Delim[0]);
		if (pt == NULL && i < max)
			{
			fail(EC_NOFIELD, "(parse) Feld " + String(i) + " konnte nicht eingelesen werden");
			rc = false;
			break;
			}
		else if (pt == NULL)
			{
			//letztes Feld erreicht
			feld = String(rowbuf);
			}
		else
			{
			*pt = 0;
			feld = String(rowbuf);
			strcpy(rowbuf, pt+1);
			}

		//Komma durch Punkt ersetzen, damit die Nachkommastellen richtig rauskommen
		int n = feld.Pos(",");
		if (n > 0)
			feld = feld.SubString(0, n-1) + "." + feld.SubString(n+1, 9999);
		strcpy(value, AnsiString(feld).c_str());

		val = atof(value);

		if (Format == formatNone)
			{
			//1. Spalte = SampleNo, 2. Spalte = LeadI usw.
			switch (i)
				{
				case 0: EcgLine.sample = LineCount; break;
				/* obsolete
				case 1: EcgLine.i      = val;		break;
				case 2: EcgLine.ii     = val; 		break;
				case 3: EcgLine.v1     = val; 		break;
				case 4: EcgLine.v2     = val; 		break;
				case 5: EcgLine.v3     = val; 		break;
				case 6: EcgLine.v4     = val; 		break;
				case 7: EcgLine.v5     = val; 		break;
				case 8: EcgLine.v6     = val; 		break;
				*/
				default: break;
				}
			}

		else if (Format == formatADS)
			{
			//1. Spalte = LeadI, 2. Spalte = LeadII, usw.
			switch (i)
				{
				/* obsolete
				case 0: EcgLine.sample = LineCount;
						EcgLine.i      = val;
						break;
				case 1: EcgLine.ii     = val; 		break;
				case 2: EcgLine.v1     = val; 		break;
				case 3: EcgLine.v2     = val; 		break;
				case 4: EcgLine.v3     = val; 		break;
				case 5: EcgLine.v4     = val; 		break;
				case 6: EcgLine.v5     = val; 		break;
				case 7: EcgLine.v6     = val; 		break;
				*/
				default: break;
				}
			}
		}

	EcgLine.lineno = LineCount;
	return rc;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   getter und setter   **********************************/
/***************************************************************************/
//---------------------------------------------------------------------------
int	cCsv::getFileMax()
	{
	return fpMax;
	}
//---------------------------------------------------------------------------
int	cCsv::getFilePos()
	{
	return ftell(fp);
	}
//---------------------------------------------------------------------------
int cCsv::getLineNo()
	{
	return EcgLine.lineno;
	}
//---------------------------------------------------------------------------
int cCsv::getSample()
	{
	return EcgLine.sample;
	}
//---------------------------------------------------------------------------
double cCsv::getChannel(int channel)
	{
	switch (channel)
		{
		case 1: return EcgLine.ch1;
		case 2: return EcgLine.ch2;
		case 3: return EcgLine.ch3;
		case 4: return EcgLine.ch4;
		case 5: return EcgLine.ch5;
		case 6: return EcgLine.ch6;
		case 7: return EcgLine.ch7;
		case 8: return EcgLine.ch8;
		default: return 0.0;
		}
	}
//---------------------------------------------------------------------------
double cCsv::getC12()
	{
	return EcgLine.v12;
	}
//---------------------------------------------------------------------------
double cCsv::getC34()
	{
	return EcgLine.v34;
	}
//---------------------------------------------------------------------------
double cCsv::getC56()
	{
	return EcgLine.v56;
	}
//---------------------------------------------------------------------------
double cCsv::getVal()
	{
		 if (iLead ==  1) return EcgLine.ch1;
	else if (iLead ==  2) return EcgLine.ch2;
	else if (iLead ==  3) return EcgLine.ch3;
	else if (iLead ==  4) return EcgLine.ch4;
	else if (iLead ==  5) return EcgLine.ch5;
	else if (iLead ==  6) return EcgLine.ch6;
	else if (iLead ==  7) return EcgLine.ch7;
	else if (iLead ==  8) return EcgLine.ch8;

	else if (iLead ==  9) return EcgLine.v12;
	else if (iLead == 10) return EcgLine.v34;
	else if (iLead == 11) return EcgLine.v56;

	else return 0.0;
	}
//---------------------------------------------------------------------------

