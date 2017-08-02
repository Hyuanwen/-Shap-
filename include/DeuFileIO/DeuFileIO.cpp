/******************************************************************************
* $Id: DeuFileIO.cpp 1504 2010-08-17 14:38:05Z daifeng $
*
* Project:  DeuFileIO
* Purpose:  
*           
*           
* Author:   daifeng, <nuistbaker@126.com>
*
******************************************************************************/

#include "stdafx.h"
#include "DeuFileIO.h"


std::vector<MCD_STR> GetAllRows(MCD_STR strDoc)
{

	std::vector<MCD_STR> vecRows;

	//按回车分行
	int iEnd   = 0 ;
	int iStart = 0 ;
	CString ch = "\r\n";
	while ( iEnd >= 0 )
	{
		iEnd = strDoc.Find(ch,iStart);
		
		CString row = strDoc.Mid(iStart,iEnd - iStart);

		vecRows.push_back(row);

		iStart = iEnd + 2;

	}
	

	return vecRows;
}

MCD_STR GetItem(MCD_STR strRow,int col,MCD_STR strSep)	
{
	std::vector<MCD_STR> vecCols;

	//按回车分行
	int iEnd   = 0 ;
	int iStart = 0 ;
	//CString ch = L",";
	while ( iEnd >= 0 )
	{
		iEnd = strRow.Find(strSep,iStart);
		

		if (iEnd >= 0)
		{
			CString item = strRow.Mid(iStart,iEnd - iStart);

			vecCols.push_back(item);

			iStart = iEnd + 2;

		}
		else
		{
			CString item = strRow.Mid(iStart);

			vecCols.push_back(item);

			iStart = iEnd + 2;

		}
	}

	return vecCols[col];
}