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



DeuTxtIO::DeuTxtIO()
{
	
	m_nDocFlags = 0;
}

DeuTxtIO::~DeuTxtIO()
{

}

bool DeuTxtIO::Load(MCD_CSTR szFileName)
{
	if ( m_nDocFlags & (MDF_READFILE|MDF_WRITEFILE) )
		return false;
	if ( ! ReadTextFile(szFileName, m_strDoc, &m_strResult, &m_nDocFlags) )
		return false;
	return true;
}

bool DeuTxtIO::ReadTextFile(MCD_CSTR_FILENAME szFileName, MCD_STR& strDoc, MCD_STR* pstrResult, int* pnDocFlags, MCD_STR* pstrEncoding)
{
	bool bSuccess = true ;


	FILE* fp = NULL;
	
	m_nDocFlags = DeuFileIO::MDF_READFILE ;  

	MCD_PCSZ_FILENAME pMode = MCD_T_FILENAME("rb");
	if ( m_nDocFlags & DeuFileIO::MDF_APPENDFILE )
		pMode = MCD_T_FILENAME("ab");
	else if ( m_nDocFlags & DeuFileIO::MDF_WRITEFILE )
		pMode = MCD_T_FILENAME("wb");
	

	MCD_FOPEN(fp,szFileName,pMode);

	int nFileByteLen = 0;

	if ( m_nDocFlags & DeuFileIO::MDF_READFILE )
	{
		// Get file length
		MCD_FSEEK( fp, 0, SEEK_END );
		
		nFileByteLen = MCD_FTELL( fp );
		MCD_FSEEK( fp, 0, SEEK_SET );

	}
	
	
	//MCD_CHAR* pBuffer = MCD_GETBUFFER(strDoc,nFileByteLen);
	char * pBuffer = new char[nFileByteLen];
	bSuccess = ( fread( pBuffer, nFileByteLen, 1, fp ) == 1 );
	
	strDoc = pBuffer;

	//// Static utility method to load text file into strDoc
	////
	//FilePos file;
	//file.m_nDocFlags = (pnDocFlags?*pnDocFlags:0) | MDF_READFILE;
	//bool bSuccess = file.FileOpen( szFileName );
	//if ( pstrResult )
	//	*pstrResult = file.m_strIOResult;
	//MCD_STRCLEAR(strDoc);
	//if ( bSuccess )
	//{
	//	file.FileSpecifyEncoding( pstrEncoding );
	//	file.m_nOpFileByteLen = (int)((long)(file.m_nFileByteLen - file.m_nFileByteOffset));
	//	bSuccess = file.FileReadText( strDoc );
	//	file.FileClose();
	//	if ( pstrResult )
	//		*pstrResult += file.m_strIOResult;
	//	if ( pnDocFlags )
	//		*pnDocFlags = file.m_nDocFlags;
	//}
	return bSuccess;
	
}

