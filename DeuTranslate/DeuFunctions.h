#ifndef	_DEUFUNCTIONS_H
#define _DEUFUNCTIONS_H

#include "DeuDef.h"

void	PutStringCellVal(Excel::_WorksheetPtr _sheet, char * szRowCol , double dbVal);
void	PutStringCellVal(Excel::_WorksheetPtr _sheet, long irow , long icol , double dbVal);
//功能：设置值到cell

double	GetDoubleCellVal(Excel::_WorksheetPtr _sheet, char * szRowCol);
double  GetDoubleCellVal(Excel::_WorksheetPtr _sheet, long irow , long icol);
//功能：从cell中获取值

char * GetLetter( int iRow , char * szCol);
//行和列获得Letter

SDO_geometry * CloneGeometry(const SDO_geometry & geo);

#endif