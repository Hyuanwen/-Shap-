#ifndef	_DEUFUNCTIONS_H
#define _DEUFUNCTIONS_H

#include "DeuDef.h"

void	PutStringCellVal(Excel::_WorksheetPtr _sheet, char * szRowCol , double dbVal);
void	PutStringCellVal(Excel::_WorksheetPtr _sheet, long irow , long icol , double dbVal);
//���ܣ�����ֵ��cell

double	GetDoubleCellVal(Excel::_WorksheetPtr _sheet, char * szRowCol);
double  GetDoubleCellVal(Excel::_WorksheetPtr _sheet, long irow , long icol);
//���ܣ���cell�л�ȡֵ

char * GetLetter( int iRow , char * szCol);
//�к��л��Letter

SDO_geometry * CloneGeometry(const SDO_geometry & geo);

#endif