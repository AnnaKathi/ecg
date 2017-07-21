//---------------------------------------------------------------------------
#ifndef classMathH
#define classMathH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <libs/core/classBase.h>
//---------------------------------------------------------------------------
//! bietet mathematische Grundfunktionen an
/*! Die Klasse cMath bietet verschiedenen mathematische Grundfunktionen an:\r\n
 *  <ul><li>Ableitung berechnen
 *  <li>Array sortieren</ul>
 */
class PACKAGE cMath : public cBase
	{
public:
	cMath();  //!< Konstruktor für cMath
	~cMath(); //!< Destruktor für cMath

	//! Ableitung über einem Array berechnen
	/*! Erstellt die Ableitung über dem übergebenen Array
	 *  /param (std::map) Array mit double-Werten
	 *  /return (std::map) Array mit Steigungs-Werten = Ableitung
	 */
	iarray_t	calcDerivate(iarray_t array);

	//! Array sortieren (auf- oder absteigend)
	/*! Das übergebene Array wird neu sortiert (auf- oder absteigend)
	 *  /param (std::map) Array das sortiert werden soll
	 *  /param (bool) asc, wenn true wird aufsteigend, sonst absteigend sortiert
	 *  /return (std::map) sortiertes Array
	 */
	iarray_t	resort(iarray_t array, bool asc);

private:

	};
//---------------------------------------------------------------------------
#endif
