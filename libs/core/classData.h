//---------------------------------------------------------------------------
#ifndef classDataH
#define classDataH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <libs/core/classBase.h>
#include <libs/core/classTools.h>
#include <libs/core/classCsv.h>
#include <libs/core/classArray.h>
#include <libs/core/classDerivate.h>
//---------------------------------------------------------------------------
//! Grundfunktionalitäten auf dem Daten-Array
/*! Die Klasse cData bietet Grundfunktionalitäten aufd em array (std::map) an:\r\n
 *  <ul><li>Datei einlesen (Weiterleitung an cCsv)
 *  <li>Gleitenden Durchschnitt berechnen (Weiterleitung an cArray)
 *  <li>Werte entfernen (Weiterleitung an cArray)
 *  <li>Ableitungen berechnen (Weiterleitung an cMath)</ul>
 */
class PACKAGE cData : public cBase
	{
public:
	cData();  //!< Konstruktor von cData
	~cData(); //!< Destruktor von cData

	sArrayCha	farr_charac; //todo getter und setter machen

	//-----------------------------------------------------------------------
	//--- Grundfunktionen ---------------------------------------------------
	//-----------------------------------------------------------------------
		//! Datei einlesen
		/*! Die übergebene Datei wird eingelesen. Dabei kann der einzulesende
		 *  Bereich nach Millisekunden eingeschränkt werden. Der Funktionsaufruf
		 *  wird an cCsv::OpenFile weitergeleitet.
		 *  /param (String) Datei die eingelesen werden soll
		 *  /param (String) Delimeter der für die Datei verwendet werden soll
		 *  /param (int) Millisekunde ab der eingelesen werden soll
		 *  /param (int) Millisekunde bis zu der eingelesen werden soll
		 *  /return (bool) true im Erfolgsfall, sonst false
		 */
		bool		getFile(String file, eDatFormat format, String delim, int lead, int vonMsec, int bisMsec);

		//! Daten des Array in einem Image anzeigen
		/*! Das interne Datenarray wird im übergebenen Image eingezeichnet. Der
		 *  Funktionsaufruf wird an cArray::redisplay weitergeleitet.
		 *  /param (Image) Image in das gezeichnet werden soll
		 *  /return (bool) true im Erfolgsfall, sonst false
		 */
		bool		redisplay(TImage* img);

		//! Gleitenden Durchschnitt über dem internen Datenarray berechnen
		/*! Über dem internen Datenarray wird ein gleitender Durchschnitt berechnet.
		 *  Dabei wird die zu verwendende Fenstergröße übergeben, sowie die
		 *  Information, ob die Anfangswerte (bevor das erste Fenster erreicht
		 *  wird) in die Berechnung einfließen sollen, oder nicht.
		 *  Der Funktionsaufruf wird an cArray::movingAv weitergeleitet.
		 *  /param (int) window, die zu verwendende Fenstergröße
		 *  /param (bool) CalcBegin, soll der Anfang, der vor dem ersten Fenster
		 *		liegt, mit in die Berechnung einfließen? Ist mit true vorbesetzt
		 *  /return (bool) true im Erfolgsfall, sonst false
		 */
		bool		movingAv(int window, bool CalcBegin = true);

		//! Daten aus dem internen Datenarray entfernen
		/*! Der Bereich von-bis (Millisekunden) wird aus dem internen Datenarray
		 *  entfernt. Der Funktionsaufruf wird an cArray::cut weitergeleitet.
		 *  /param (int) Millisekunden ab der die Daten entfernt werden sollen
		 *  /param (int) Millisekunden bis zu der die Daten entfernt werden sollen
		 *  /return (bool) true im Erfolgsfall, sonst false
		 */
		bool		cut(int vonMsec, int bisMsec);

	//-----------------------------------------------------------------------
	//--- mathematische Funktionen ------------------------------------------
	//-----------------------------------------------------------------------
		//! 1. und 2. Ableitung über dme internen Datenarray bilden
		/*! Erstellt über dem internen Datenarray die erste und zweite Ableitung.
		 *  Der Funktionsaufruf wird an cDerivate::build weitergeleitet.
		 *  /return (bool) true im Erfolgsfall, sonst false
		 */
		bool		buildDerivates();

		//! EKG-Signal (array) auf die angegebene Länge normalisieren
		/*! Das übergebene Array wird auf die angegebene Länge normalisiert.
		 *  Wenn das Array verkürzt werden muss, werden in regelmäßigen Abständen
		 *  Werte entfernt. Wenn es verlängert werden muss, werden in
		 *  regelmäßigen Abständen Werte hinzugefügt (Durchschnitt aus dem
		 *  vorangehenden und dem nachfolgenden Wert).
		 *  /param (std::map) array, EKG-Werte die normalisiert werden sollen
		 *  /param (int) length, Länge auf die normliaisert werden soll
		 *  /return (bool) true wenn erfolgreich, sonst false
		 */
		iarray_t	normalize(iarray_t array, int length);

__property iarray_t&  data_array = { read=get_array  }; //!< Internes Datenarray
__property cDerivate& derivate1  = { read=get_deriv1 }; //!< Erste Ableitung
__property cDerivate& derivate2  = { read=get_deriv2 }; //!< Zweite Ableitung

private:
	cTools		ftools;
	cCsv*		fcsv;

	cDerivate*	fderiv1; //erste Ableitung
	cDerivate&	get_deriv1();

	cDerivate*	fderiv2; //zweite Ableitung
	cDerivate&	get_deriv2();

	cArray*		farray; //Klasse mit Grundfunktionalitäten

	iarray_t	farr;  //alle eingelesenen EKG-Werte
	iarray_t&	get_array();

	void 		resetValues();
	};
//---------------------------------------------------------------------------
#endif
