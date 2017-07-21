//---------------------------------------------------------------------------
#ifndef classHeartbeatH
#define classHeartbeatH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
#include <libs/core/classBase.h>
#include <libs/core/classArray.h>
#include <libs/core/classRpeaks.h>
//---------------------------------------------------------------------------
//! Erstellt und verwaltet den Standardherzschlag eines EKG
/*! Die Klasse cHeartbeat berechnet und verwaltet den Standardherzschlag eines
 *  EKG-Signals. Dafür werden alle einzelnen Herzschläge (von R-Peak bis R-Peak)
 *  übereinander gelegt und aus allen Werten der Durchschnitt gebildet. 
 */
class PACKAGE cHeartbeats : public cBase
	{
public:
	cHeartbeats();  //!< Konstruktor für cHeartbeat
	~cHeartbeats(); //!< Destruktor für cHeartbeat

	//! Metadaten der Kurve zurücksetzen
	/*! Die Metadaten der Kurvendaten werden zurückgesetzt, damit sich die
	 *  nachfolgenden Funktionen auf diese beziehen können. Dieser Aufruf erstellt
	 *  die R-Peaks selbstständig, wenn bereits eine R-Peak-Berechnung vorliegt,
	 *  kann stattdessen reset(curve, rpeaks) verwendet werden.
	 *  /param (std::map) Daten der EKG-Kurve
	 *  /return (bool) true wenn erfolgreich, sonst false
	 */
	bool 		reset(iarray_t curve); //R-Peaks müssen noch gebildet werden

	//! Gibt den ersten R-Peak des Signals zurück
	/*! Auf der übergebenen Kurve wird der erste R-Peak berechnet und zurückgeben.
	 *  Intern wird der Funktionsaufruf auf next() weitergeleitet, first() kann
	 *  für Aufrufe innerhalb einer for-Schleife verwendet werden. Dieser Aufruf
	 *  erstellt die R-Peaks selbstständig, wenn bereits eine R-Peak-Berechnung
	 *  vorliegt, kann stattdessen first(curve, rpeaks) verwendet werden.
	 *  /param (std::map) Daten der EKG-Kurve
	 *  /return (bool) true wenn erfolgreich, sonst false
	 */
	bool 		first(iarray_t curve); //R-Peaks müssen noch gebildet werden

	//! Metadaten der Kurve zurücksetzen
	/*! Die Metadaten der Kurvendaten werden zurückgesetzt, damit sich die
	 *  nachfolgenden Funktionen auf diese beziehen können. Dieser Aufruf erstellt
	 *  die R-Peaks NICHT selbstständig, wenn noch keine R-Peak-Berechnung vorliegt,
	 *  kann stattdessen reset(curve) verwendet werden.
	 *  /param (std::map) Daten der EKG-Kurve
	 *  /param (std::map) R-Peaks der EKG-Kurve
	 *  /return (bool) true wenn erfolgreich, sonst false
	 */
	bool		reset(iarray_t curve, iarray_t rpeaks); //Aufrufender hat RPeaks schon gebildet

	//! Gibt den ersten R-Peak des Signals zurück
	/*! Auf der übergebenen Kurve wird der erste R-Peak berechnet und zurückgeben.
	 *  Intern wird der Funktionsaufruf auf next() weitergeleitet, first() kann
	 *  für Aufrufe innerhalb einer for-Schleife verwendet werden. Dieser Aufruf
	 *  erstellt die R-Peaks NICHT selbstständig, wenn noch keine R-Peak-Berechnung
	 *  vorliegt, kann stattdessen first(curve) verwendet werden.
	 *  /param (std::map) Daten der EKG-Kurve
	 *  /param (std::map) R-Peaks der EKG-Kurve
	 *  /return (bool) true wenn erfolgreich, sonst false
	 */
	bool		first(iarray_t curve, iarray_t rpeaks); //Aufrufender hat RPeaks schon gebildet

	//! Gibt den nächsten R-Peak des Signals zurück
	/*! Auf der übergebenen Kurve wird der nächste R-Peak berechnet und zurückgeben.
	 *  /return (bool) true wenn erfolgreich, sonst false
	 */
	bool		next();

	//! Prüft ob der letzte R-Peak erreicht wurde
	/*! Prüft, ob noch Kurvendaten zur Verfügung stehen ober ob der letzte R-Peak
	 *  erreicht wurde. Kann z.B. für for-Schleifen verwendet werden.
	 *  /return (bool) true wenn keine R-Peaks mehr vorhanden sind, sonst false
	 */
	bool		end();

	//! Berechnet den Standardherzschlag über einem Datenarray
	/*! Über dem übergebenem Datenarray wird der Standardherzschlag berechnet.
	 *  /param (std::map) Daten der EKG-Kurve
	 *  /return (bool) Array mit den Werten des Standardherzschlags
	 */
	iarray_t	calcAvBeat(iarray_t curve);
	bool		rf_calcAvBeat(iarray_t curve);

__property iarray_t   heartbeat = { read=get_heartbeat  }; //!< jeweils ein einzelner Herzschlag, für for-Schleifen z.B.
__property iarray_t   avBeat	= { read=get_AvBeat		}; //!< Standardherzschlag, Durchschnitt aller Herzschläge

private:
	cArray		farray;
	iarray_t	fcurve;
	iarray_t	frpeaks;

	iarray_t	fheartbeat; //jeweils ein einzelner Herzschlag, für first-next
	iarray_t	get_heartbeat();

	iarray_t	fAvBeat; //Standardherzschlag
	iarray_t	get_AvBeat();

	sArrayCha	charac; //todo getter und setter machen

	int			findex;
	};
//---------------------------------------------------------------------------
#endif

