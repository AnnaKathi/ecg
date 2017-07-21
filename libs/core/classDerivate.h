//---------------------------------------------------------------------------
#ifndef classDerivateH
#define classDerivateH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <libs/core/classBase.h>
#include <libs/core/classArray.h>
#include <libs/core/classMath.h>
//---------------------------------------------------------------------------
//! erstellt und verwaltet eine Ableitung
/*! Die Klasse cDerivate bildet und verwaltet eine Ableitung über einem Datenarray (std::map)
 */
class PACKAGE cDerivate : public cBase
	{
public:
	cDerivate();  //!< Konstruktor von cDerivate
	~cDerivate(); //!< Destruktor von cDerivate

	sArrayCha	farr_charac; //todo getter und setter machen

	//! Erstellt eine ABleitung über einem Array
	/*! Über dem übergebenen Datenarray (std::map) wird die Ableitung erstellt.
	 *  Der Funktionsaufruf wird an cMath::calcDerivate weitergeleitet.
	 *  /param (std::map) Array über dem die Ableitung erstellt werden soll
	 *  /return (bool) true im Erfolgsfall, sonst false
	 */
	bool		build(iarray_t array);

	//! Zeichnet das interne Ableitungs-Array in ein Image
	/*! Das interne Ableitungsarray wird in das übergebene Image geziechnet.
	 *  Der Funktionsaufruf wird an cArray::redisplay weitergeleitet.
	 *  /param (Image) Image in das gezeichnet werden soll
	 *  /return (bool) true im Erfolgsfall, sonst false
	 */
	bool 		redisplay(TImage* img);

	//! Berechnet den gleitenden Durchschnitt über dem internen Ableitungsarray
	/*! Über dem internen Ableitungsarray wird ein gleitender Durchschnitt berechnet.
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

	//! Daten aus dem internen Ableitungsarray entfernen
	/*! Der Bereich von-bis (Millisekunden) wird aus dem internen Ableitungsarray
	 *  entfernt. Der Funktionsaufruf wird an cArray::cut weitergeleitet.
	 *  /param (int) Millisekunden ab der die Daten entfernt werden sollen
	 *  /param (int) Millisekunden bis zu der die Daten entfernt werden sollen
	 *  /return (bool) true im Erfolgsfall, sonst false
	 */
	int			cut(int vonMsec, int bisMsec);

__property iarray_t&	deriv_array = { read=get_array }; //!< Internes Ableitungsarray

private:
	cMath*		fmath;
	cArray*		farray; //Grundfunktionalitäten

	iarray_t	farr;
	iarray_t&	get_array();
	};
//---------------------------------------------------------------------------
#endif
