/******************************************************************************
* $Id: DeuTxtIO.cpp 1504 2010-08-17 14:38:05Z daifeng $
*
* Project:  DeuTxtIO
* Purpose:  
*           
*           
* Author:   daifeng, <nuistbaker@126.com>
*
******************************************************************************/

#include "stdafx.h"
#include "DeuFileIO.h"
using namespace YExcel;


DeuExcelIO:: DeuExcelIO()
{

}

DeuExcelIO::~ DeuExcelIO()
{

}

size_t DeuExcelIO::GetTotalWorkSheets()
{
	return m_e.GetTotalWorkSheets();
}

bool DeuExcelIO::Load(MCD_CSTR szFileName)
{
	//只有unicode的情况
	/*
	int dwSize = wcslen(szFileName);
	char * lpFileName = new char[dwSize*2+1];
	WideCharToMultiByte(CP_OEMCP,NULL,szFileName,-1,lpFileName,dwSize,NULL,FALSE);
	bool bResult = m_e.Load(lpFileName);
	delete lpFileName;
	return bResult;
	*/
	
	int dwSize = strlen(szFileName);
	char * lpFileName = new char[dwSize*2+1];	
	bool bResult = m_e.Load(lpFileName);
	delete lpFileName;
	return bResult;
}

double DeuExcelIO::GetItem(size_t sheetIndex, size_t row, size_t col )
{
	BasicExcelWorksheet* sheet = m_e.GetWorksheet(sheetIndex); 

	BasicExcelCell* cell = sheet->Cell(row,col);
	
	return cell->GetDouble();
}
