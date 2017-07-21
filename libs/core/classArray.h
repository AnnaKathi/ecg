//---------------------------------------------------------------------------
#ifndef classArrayH
#define classArrayH
//---------------------------------------------------------------------------
#include <classes.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <libs/core/classBase.h>
//---------------------------------------------------------------------------
typedef struct sARRAYCHA //Charkterwerte eines Arrays
	{
	int			VonIdx;  //kleinster Index
	int			BisIdx;  //größter Index
	int			VonMsec; //kleinster Millisek.wert
	int			BisMsec; //größter Millisek.wert
	double		MinWert; //tiefster Wert (Ausschlag)
	double		MaxWert; //höchster Wert (Ausschlag)
	int			Number;  //Anzahl Datensätze im Array
	} sArrayCha;
//---------------------------------------------------------------------------
//! grundlegende Funktionen auf einem Array
/*! Die Klasse cArray bietet grundlagende Funktionen auf den Werten eines Array
 *  (std::map) an.
 */
class PACKAGE cArray : public cBase
	{
public:
	cArray();
	~cArray();

	sArrayCha	farr_charac; //todo getter und setter machen

	//! lädt die Metadaten eines Array neu
	/*! Die Metadaten (z.B. Millisekunden-Bereich) des übergebenen Arrays werden
	 *  neu geladen. Sollte aufgerufen werden, wenn das Array verändert wird, z.B.
	 *  durch cut, weil andere Funktionen diese Metadaten verwenden könnten.
	 *  /param (std::map) Array das neu zu laden ist
	 *  /param (sArrayCha) Charakteristik-Struktur die gefüllt werden soll
	 *  /return (bool) true im Erfolgsfall, sonst false
	 */
	bool 		resetValues(iarray_t& array, sArrayCha& cha);

	//! Das übergebene Image löschen
	/*! Das übergebene Image wird gelöscht (leer gezeichnet).
	 *  /param (Image) Image in das gelöscht werden soll
	 */
	void 		clearImg(TImage* img);

	//! Daten des übergebenen Array in einem Image anzeigen
	/*! Das übergebene Array wird im übergebenen Image eingezeichnet. Das übergebene
	 *  Image wird NICHT gelöscht, sondern nur neu gezeichnet. D.h. es können mehrere
	 *  Arrays in das gleiche Bild gezeichnet werden. Wenn das nicht gewünscht
	 *  ist, kann redisplay() verwendet werden.
	 *  /param (std::map) Array das verwendet werden soll
	 *  /param (Image) Image in das gezeichnet werden soll
	 *  /return (bool) true im Erfolgsfall, sonst false
	 */
	bool 		display(const iarray_t& array, TImage* img);

	//! Daten des übergebenen Array in einem Image anzeigen
	/*! Das übergebene Array wird im übergebenen Image eingezeichnet. Das übergebene
	 *  Image wird zunächst gelöscht und dann neu gezeichnet. Um mehrere Arrays
	 *  in das gleiche Bild zu zeichnen, kann display() verwendet werden.
	 *  /param (std::map) Array das verwendet werden soll
	 *  /param (Image) Image in das gezeichnet werden soll
	 *  /return (bool) true im Erfolgsfall, sonst false
	 */
	bool 		redisplay(const iarray_t& array, TImage* img); //ruft erst clear und dann display auf

	//! Punkte in eine Kurve einzeichnen
	/*! Das übergebene Array 'curve' wird zunächst im übergebenen Image
	 *  eingezeichnet. Anschließend wird für jeden Punkt aus dem übergebene
	 *  Array 'points' einPunkt in die Kurve eingezeichnet.
	 *  /param (std::map) Array das die Kurvenwerte enthält
	 *  /param (std::map) Array das die Punkte enthält
	 *  /param (Image) Image in das gezeichnet werden soll
	 *  /return (bool) true im Erfolgsfall, sonst false
	 */
	bool 		redisplayPoints(const iarray_t& curve, const iarray_t& points, TImage* img);

	bool 		displayPoints(const iarray_t& curve, iarray_t points, TImage* img);

	//! Gleitenden Durchschnitt über dem übergebenen Array berechnen
	/*! Über dem übergebenen Array wird ein gleitender Durchschnitt berechnet.
	 *  Dabei wird die zu verwendende Fenstergröße übergeben, sowie die
	 *  Information, ob die Anfangswerte (bevor das erste Fenster erreicht
	 *  wird) in die Berechnung einfließen sollen, oder nicht.
	 *  /param (std::map) Array das verwendet werden soll
	 *  /param (int) window, die zu verwendende Fenstergröße
	 *  /param (bool) CalcBegin, soll der Anfang, der vor dem ersten Fenster
	 *		liegt, mit in die Berechnung einfließen? Ist mit true vorbesetzt
	 *  /return (std::map) neues Array mit gleitendem Durchschnitt
	 */
	iarray_t 	movingAv(const iarray_t& array, int window, bool CalcBegin);

	//! Berechnet den Durchschnittswert des Arrays
	/*! Alle Werte des übergebenen Arrays werden addiert und durch die Anzahl
	 *  der enthaltenen Werte geteilt.
	 *  /param (std::map) Array das verwendet werden soll
	 *  /return (double) Durchschnittswert des Arrays 
	 */
	double		calcAvWert(const iarray_t& array);

	//! Daten aus dem übergebenen Array entfernen
	/*! Der Bereich von-bis (Millisekunden) wird aus dem übergebenen Array
	 *  entfernt.
	 *  /param (std::map) Array aus dem Werte entfernt werden sollen
	 *  /param (int) Millisekunden ab der die Daten entfernt werden sollen
	 *  /param (int) Millisekunden bis zu der die Daten entfernt werden sollen
	 *  /return (std::map) neues Array
	 */
	iarray_t 	cut(iarray_t& array, int vonMsec, int bisMsec);

	iarray_t 	get(iarray_t& array, int vonMsec, int bisMsec);

	iarray_t	remove(const iarray_t& source, const iarray_t& remove, int val_index = 0);

__property int PointWidth = { write=set_PointWidth };
__property TColor PointColor = { write=set_PointColor };

private:
	iarray_t	farr;

	bool 		resetValues(sArrayCha& cha);

	int			fPointWidth;
	void		set_PointWidth(int width);

	TColor		fPointColor;
	void		set_PointColor(TColor cl);
	};
//---------------------------------------------------------------------------
#endif
