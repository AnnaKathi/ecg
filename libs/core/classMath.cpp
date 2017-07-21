//---------------------------------------------------------------------------
#pragma hdrstop

#include "classMath.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cMath::cMath()
	{
	}
//---------------------------------------------------------------------------
cMath::~cMath()
	{
	}
//---------------------------------------------------------------------------
iarray_t cMath::calcDerivate(iarray_t array)
	{
	iarray_t deriv;
	deriv.clear();

	//erste Ableitung = Steigung von farr
	int zeit;
	int ix = 0;
	double before, lead1, steigung;
	bool first = true;
	for (iarray_itr itr = array.begin(); itr != array.end(); itr++)
		{
		zeit = itr->first;
		ilist_t& v = itr->second;
		lead1 = v[1];

		if (!first)
			{
			steigung = lead1 - before;
			deriv[ix].push_back(zeit);
			deriv[ix].push_back(steigung);
			ix++;
			}

		first = false;
		before = lead1;
		}

	//TEST array
	int n = deriv.size();
	for (iarray_itr itr = deriv.begin(); itr != deriv.end(); itr++)
		{
		zeit = itr->first;
		ilist_t& v = itr->second;
		lead1 = v[1];
    	int bp = 0;
		}

	int bp = 0;

	return deriv;
	}
//---------------------------------------------------------------------------
iarray_t cMath::resort(iarray_t array, bool asc)
	{
	//array in 2. array umschreiben mit wert als key
	iarray_t sort; sort.clear();
	double zeit, lead1;
	int ix = 0;
	for (iarray_itr itr = array.begin(); itr != array.end(); itr++)
		{
		ilist_t& v = itr->second;
		zeit  = v[0];
		lead1 = v[1];

		sort[lead1].push_back(zeit);
		sort[lead1].push_back(lead1);
		}

	if (!asc)
		{
		//umsortieren in absteigendes array
		iarray_t desc; desc.clear();
		iarray_t::reverse_iterator itr_rev;

		int ix = 0;
		for (itr_rev = sort.rbegin(); itr_rev != sort.rend(); itr_rev++)
			{
			ilist_t& v = itr_rev->second;
			zeit  = v[0];
			lead1 = v[1];

			desc[ix].push_back(zeit);
			desc[ix].push_back(lead1);
			ix++;
			}
		sort = desc;
		}
	return sort;
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/**************   private Funktionen   *************************************/
/***************************************************************************/
//---------------------------------------------------------------------------

