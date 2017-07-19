//---------------------------------------------------------------------------
#ifndef definitionsH
#define definitionsH
//---------------------------------------------------------------------------
//----- Datenbank-Handling --------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/* Lage in der ein EKG aufgenommen wurde, z.B. liegend oder stehend */
enum eLage
	{
	lageNone = 0,
	lageLiegend,
	lageSitzend,
	lageStehend,
	lageGehend
	};
//---------------------------------------------------------------------------
/* State (Zustand) in dem ein EKG erfasst wurde, z.B. 'in Ruhe' */
enum eState
	{
	stateNone = 0,
	stateInRuhe,         //keine Bewegung vor der Messung, bis Puls 80 ??
	stateNachWenigBew,	 //leichte Bewegung vor der Messung, ab Puls 80 ??
	stateNachMittelBew,  //mäßige Bewegung vor der Messung, ab Puls 120 ??
	stateNachVielBew,    //viel Bewegung vor der Messung, ab Puls 160 ??
	stateInBew           //während der Bewegung
	};
//---------------------------------------------------------------------------
/* Position (Platzierung der Elektroden) zu denen ein EKG-Signal gehört */
enum ePosition
	{
	posNone = 0,
	posBrustNormal, //Brust rechts und links, "normale" Position
	posBrustEng,	//Brustbein oben eng ("Kettenanhänger")
	posHandBack,	//Handrücken
	posBack			//Rücken unter den Schulterblättern
	};
//---------------------------------------------------------------------------
/* Format der einzulesenden Datei */
enum eDatFormat
	{
	formatNone = 0, //kein Format gesetzt, einfach zeilenweise parsen
	formatADS,		//Format ADS1298 von Texas Instruments
	};
//---------------------------------------------------------------------------
/* Modus der baseForms */
enum eListMode
	{
	eShow = 0,  	//Datensätze anzeigen, DblClick = Datensatz ändern
	eSingleSelect,	//Datensätze anzeigen, DblClick = einen Datensatz auswählen
	eMultiSelect,	//Datensätze anzeigen, DblClick = mehrere Idents auswählen
	};
//---------------------------------------------------------------------------
#endif
