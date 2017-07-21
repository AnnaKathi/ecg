//---------------------------------------------------------------------------
#pragma hdrstop

#include "classDerivate.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cDerivate::cDerivate()
	: fmath(new cMath), farray(new cArray)
	{
	}
//---------------------------------------------------------------------------
cDerivate::~cDerivate()
	{
	if (fmath)  delete fmath;
	if (farray) delete farray;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/******************   Funktionen   *****************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
bool cDerivate::build(iarray_t array)
	{
	farr = fmath->calcDerivate(array);
	return ok();
	}
//---------------------------------------------------------------------------
bool cDerivate::redisplay(TImage* img)
	{
	return farray->redisplay(farr, img);
	}
//---------------------------------------------------------------------------
bool cDerivate::movingAv(int window, bool CalcBegin) //default CalcBegin=true
	{
	farr = farray->movingAv(farr, window, CalcBegin);

	if (!farray->error)
		{
		//die Werte inputVonIdx, inputBisIdx, inputVonMsec, inputBisMsec,
		//inputMinWert und inputMaxWert müssen neu gesetzt werden
		farray->resetValues(farr, farr_charac);
		return ok();
		}
	else
		return fail(farray->error_code, farray->error_msg);
	}
//---------------------------------------------------------------------------
int cDerivate::cut(int vonMsec, int bisMsec)
	{
	farr = farray->cut(farr, vonMsec, bisMsec);

	if (!farray->error)
		{
		//die Werte inputVonIdx, inputBisIdx, inputVonMsec, inputBisMsec,
		//inputMinWert und inputMaxWert müssen neu gesetzt werden
		farray->resetValues(farr, farr_charac);
		return ok();
		}
	else
		return fail(farray->error_code, farray->error_msg);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   getter und setter   **************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
iarray_t& cDerivate::get_array()
	{
	return farr;
	}
//---------------------------------------------------------------------------

