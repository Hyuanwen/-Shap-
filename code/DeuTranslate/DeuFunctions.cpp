#include "stdafx.h"
#include "DeuFunctions.h"

void PutStringCellVal(Excel::_WorksheetPtr _sheet, char * szRowCol , double dbVal)
{
	if(szRowCol == NULL)
	{
		return ;
	}

	//char * szVal = new char[100];
	//sprintf( szVal , "%.15lf" , dbVal );
	_variant_t      _tVal(dbVal);
	Excel::RangePtr _rx;
	_rx = _sheet->GetRange(szRowCol);

	//_rx->PutValue( _tVal , xlRangeValueDefault);
	_rx->NumberFormatLocal = "0.000000000000000";
	_rx->PutItem(1,1,_tVal);

	char * szLog = new char[200];
	sprintf( szLog , "CELL= %s , VALUE = %s " , szRowCol ,(LPSTR)_bstr_t(_tVal) );
	LOGSTR(szLog);
	delete szLog;
	return ;
}

void PutStringCellVal(Excel::_WorksheetPtr _sheet, long irow , long icol , double dbVal)
{
	if(icol<1 || irow<1)
	{
		return ;
	}

	//char * szVal = new char[100];
	//sprintf( szVal , "%.15lf" , dbVal );
	_variant_t _tVal(dbVal);
	char       Letter[100];
	Num2Letter( irow ,icol ,Letter );

	Excel::RangePtr _rx;
	_rx = _sheet->GetRange(Letter);

	//_rx->PutValue( _tVal , xlRangeValueDefault);
	_rx->NumberFormatLocal = "0.000000000000000";
	_rx->PutItem(1,1,_tVal);

	char * szLog = new char[200];
	sprintf( szLog , "CELL= %s , VALUE = %s " , Letter ,(LPSTR)_bstr_t(_tVal) );
	LOGSTR(szLog);
	delete szLog;
	return ;
}

double GetDoubleCellVal(Excel::_WorksheetPtr _sheet, char * szRowCol)
{
	double     dx = 0;
	_variant_t _tx;
	_variant_t _des_tx;

	Excel::RangePtr _rx;
	if(szRowCol == NULL)
	{
		return -1;
	}

	_rx = _sheet->GetRange(szRowCol);
	//_rx = _range->GetItem( _variant_t(irow) ,_variant_t(icol) );
	_tx = _rx->GetValue();

	if(_tx.vt != VT_R8)
	{
		_des_tx.ChangeType(VT_R8,&_tx);
	}
	else
	{
		_des_tx=_tx;
	}

	dx=(double)_des_tx;

	return dx;
}

double GetDoubleCellVal(Excel::_WorksheetPtr _sheet, long irow , long icol)
{
	double dx = 0;
	_variant_t _tx;
	_variant_t _des_tx;

	char Letter[100];
	Num2Letter( irow ,icol ,Letter );

	Excel::RangePtr _rx;
	if(icol>0 && irow>0)
	{		
		_rx = _sheet->GetRange(Letter);
		//_rx = _range->GetItem( _variant_t(irow) ,_variant_t(icol) );
		_tx = _rx->GetValue();

		if(_tx.vt != VT_R8)
		{
			_des_tx.ChangeType(VT_R8,&_tx);
		}
		else
		{
			_des_tx=_tx;
		}

		dx=(double)_des_tx;
	}

	return dx;
}

char * GetLetter( int iRow , char * szCol)
{
	if( strcmp( szCol , "0" ) == 0 )
	{
		return NULL;
	}

	char * Letter = new char[100];
	char * sz_r = new char[200];
	sz_r = itoa( iRow , sz_r ,10 );

	strcpy( Letter , szCol );
	strcat( Letter , sz_r );

	delete sz_r;

	return Letter;
}

SDO_geometry * CloneGeometry(const SDO_geometry & geo)
{
	SDO_geometry  *poutGeo = new SDO_geometry ;
	SDO_geometry  &outGeo  = * poutGeo; 

	memcpy( poutGeo , &geo ,sizeof(SDO_geometry) );

	int eleSize = outGeo.obj.elemInfoSize;
	int ordiSize = outGeo.obj.ordinatesSize;

	outGeo.obj.elemInfoQueue_ = new int[eleSize];
	outGeo.obj.ordinatesQueue_= new double[ordiSize];

	memcpy( poutGeo->obj.elemInfoQueue_ , geo.obj.elemInfoQueue_ , geo.obj.elemInfoSize * sizeof(int) );

	return poutGeo;
}