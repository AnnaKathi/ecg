//---------------------------------------------------------------------------
#ifndef classToolsH
#define classToolsH
//---------------------------------------------------------------------------
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#include "../definitions.h"
#include "../basics/classBase.h"
//---------------------------------------------------------------------------
//! bietet verschiedene Grundfunktionalitäten an
/*! Die Klasse cTools bietet verschiedenen Grundfunktionalitäten an:\r\n
 * <ul><li>Datenkonverter 'Position' (String <-> enum ePosition)
 * <li>Positions-String in ComboBox laden
 * <li>Formular speichern und laden</ul> 
 */
class PACKAGE cTools
	{
public:
	//! Konstruktor für cTools
	cTools();

	//-------------------------------------------------------------------------
	//--- Formulare laden und speichern ---------------------------------------
	//-------------------------------------------------------------------------

		//! Dateipfad der Exe-Datei finden
		/*! Gibt den Pfad der Exe-Datei zurück.
		 *  \return (String) Pfad der Exe-Datei
		 */
		String		GetPath();

		//! Dateiname der Projekt-Inifile erstellen
		/*! Gibt den Namen der Projekt-Inifile zurück. Diese liegt im gleichen
		 *  Verzeichnis wie die exe-Datei.
		 *  \return (String) Dateiname der Ini-File
		 */
		String		GetIniFile();

		//! Formular laden (Position, Ausdehnung, Felder, usw.)
		/*! Lädt die Daten des übergebenen Formular aus der Projekt-Inifile:\r\n
		 *  <ul><li>Position (Left und Top)
		 *  <li>Ausdehnung (Width und Height)
		 *  <li>Inhalte der Edit-Felder
		 *  <li>ItemIndex der ComboBoxen
		 *  <li>Status der Checkboxen (checked)
		 *  \param (TForm) Formular das gespeichert werden soll
		 */
		void 		FormLoad(TForm* fm);

		//! Formular speichern (Position, Ausdehnung, Felder, usw.)
		/*! Speichert die Daten des übergebenen Formular in die Projekt-Inifile:\r\n
		 *  <ul><li>Position (Left und Top)
		 *  <li>Ausdehnung (Width und Height)
		 *  <li>Inhalte der Edit-Felder
		 *  <li>ItemIndex der ComboBoxen
		 *  <li>Status der Checkboxen (checked)
		 *  \param (TForm) Formular das gespeichert werden soll
		 */
		void 		FormSave(TForm* fm);

		void		ListViewLoad(TForm* fm, TListView* lv);
		void		ListViewSave(TForm* fm, TListView* lv);

	//-------------------------------------------------------------------------
	//--- Bildschirm- und Printmeldungen --------------------------------------
	//-------------------------------------------------------------------------

		void		ErrBox(char* msg, ...);
		void		MsgBox(char* msg, ...);

	//-------------------------------------------------------------------------
	//--- String-Funktionen ---------------------------------------------------
	//-------------------------------------------------------------------------

		String		fmt(char* msg, ...);
		int			replace(String& str, String old, String neu);
		iarray_t	TextToArray(String text, String delim);
		String		ArrayToText(iarray_t array, String delim);
	//-------------------------------------------------------------------------
	//--- Sonstige Funktionen -------------------------------------------------
	//-------------------------------------------------------------------------

		//! Feststellen ob das Programm auf einem Heimrechner ausgeführt wird (= im Debugmodus)
		/*! Überprüft ob der ausführende Rechner in der Liste der "HomeStations"
		 *  vorhanden ist. Falls ja, handelt es sich um einen "HeimRechner", d.h.
		 *  das Programm läuft im Debugmodus.\r\n
		 *  Kann verwendet werden um ggf. Testfunktionen o.ä. an oder aus zu schalten.
		 *  /return true wenn es sich beim ausführenden Rechner um einen Heimrechner
		 *		handelt, sonst false
		 */
		bool		IsDebug();

		String		GetComputer();
		String		GetComputerBS();
		String 		GetComputerProzessor();

		bool 		Log(String msg);

private:
	};
//---------------------------------------------------------------------------
#endif
