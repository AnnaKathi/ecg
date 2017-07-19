//---------------------------------------------------------------------------
#ifndef classBaseH
#define classBaseH
//---------------------------------------------------------------------------
#include <map>
#include <vector>
#include <classes.hpp>
//---------------------------------------------------------------------------
#include "../definitions.h"
//---------------------------------------------------------------------------
typedef std::vector<double> ilist_t;  //double-map
typedef std::map<double,ilist_t> iarray_t;
typedef iarray_t::iterator iarray_itr;
typedef iarray_t::const_iterator iarray_citr;
//---------------------------------------------------------------------------
typedef std::vector<String> slist_t;  //String-map
typedef std::map<String,slist_t> sarray_t;
typedef sarray_t::iterator sarray_itr;
//---------------------------------------------------------------------------
/* allgemeingültige Fehler-Codes, evtl weiter ausbauen */
enum BASE_ERROR_CODES
	{
	CE_OK,              // no error, all things done well
	CE_HARDERRORS,      // real error codes
						// --------------------------------------------------
	CE_EXAMPLE,			// example of real error code if necessary
	};
//---------------------------------------------------------------------------
//! Basisklasse zur Fehler-Vererbung
/*! Die Klassen des Projekt werden grundsätzlich von der Klasse cBase abgeleitet.
 *  Diese kapselt eine Fehler-Nummer und -Nachricht, welche von den abgeleiteten
 *  Klassen verwendet werden können, um Fehlermeldungen an den Aufrufer zurückzugeben.
 */
class PACKAGE cBase
	{
public:
	//! Konstruktor für cBase
	cBase();
	virtual ~cBase();

__property bool     success    = { read=get_success }; //!< Funktion war erfolgreich
__property bool     error      = { read=get_error   }; //!< Funktion war fehlerhaft
__property int      error_code = { read=ferror_code }; //!< Im Fehlerfall: Erzeugter Fehlercode
__property String   error_msg  = { read=ferror_msg  }; //!< Im Fehlerfall: Erzeugte Fehlermeldung

__property String   trigger    = { read=ftrigger, write=set_trigger }; //!< Trigger des Fehlers

protected:
	bool            ferror; 	 //!< Intern: Fehler aufgetreten
	int             ferror_code; //!< Intern: Fehlercode
	String          ferror_msg;  //!< Intern: Fehlermeldung

                	// todo: trigger verwenden?
	String          ftrigger;    //!< Intern: Trigger des Fehlers, wird aktuell nicht verwendet
	void            set_trigger(String value); //!< Intern: Trigger setzen

	bool            ok(); //!< Intern: Funktion war erfolgreich
	bool            fail(const int code, const String& msg); //!< Intern: Funktion war fehlerhaft
	bool            fail(const cBase& cb); //!< Intern: Funktion war fehlerhaft

private:
    bool            get_success();
    bool            get_error();
	};
//---------------------------------------------------------------------------
#endif

