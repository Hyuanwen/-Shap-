/******************************************************************************
* $Id: DeuFileIO.h 1 2010-08-17 14:38:05Z daifeng $
*
* Project:  DeuFileIO 1.0
* Purpose:  Primary (private) include file for DeuFileIO API, and constants.
* Author:   daifeng, <nuistbaker@126.com>
*
******************************************************************************/

#ifndef DEUFILEIO_H_INCLUDE
#define DEUFILEIO_H_INCLUDE

#include <stdio.h>
#include <vector>

// Major build options
// MARKUP_WCHAR wide char (2-byte UTF-16 on Windows, 4-byte UTF-32 on Linux and OS X)
// MARKUP_MBCS ANSI/double-byte strings on Windows
// MARKUP_STL (default except VC++) use STL strings instead of MFC strings
// MARKUP_SAFESTR to use string _s functions in VC++ 2005 (_MSC_VER >= 1400)
// MARKUP_WINCONV (default for VC++) for Windows API character conversion
// MARKUP_ICONV (default for GNU) for character conversion on Linux and OS X and other platforms
// MARKUP_STDCONV to use neither WINCONV or ICONV, falls back to setlocale based conversion for ANSI
//
#if _MSC_VER > 1000 // VC++
#pragma once
#if ! defined(MARKUP_SAFESTR) // not VC++ safe strings
#pragma warning(disable:4996) // VC++ 2005 deprecated function warnings
#endif // not VC++ safe strings
#if defined(MARKUP_STL) && _MSC_VER < 1400 // STL pre VC++ 2005
#pragma warning(disable:4786) // std::string long names
#endif // VC++ 2005 STL
#else // not VC++
#if ! defined(MARKUP_STL)
#define MARKUP_STL
#endif // not STL
#if defined(__GNUC__) && ! defined(MARKUP_ICONV) && ! defined(MARKUP_STDCONV) && ! defined(MARKUP_WINCONV)
#define MARKUP_ICONV
#endif // GNUC and not ICONV not STDCONV not WINCONV
#endif // not VC++
#if (defined(_UNICODE) || defined(UNICODE)) && ! defined(MARKUP_WCHAR)
#define MARKUP_WCHAR
#endif // _UNICODE or UNICODE
#if (defined(_MBCS) || defined(MBCS)) && ! defined(MARKUP_MBCS)
#define MARKUP_MBCS
#endif // _MBCS and not MBCS
#if ! defined(MARKUP_SIZEOFWCHAR)
#if __SIZEOF_WCHAR_T__ == 4 || __WCHAR_MAX__ > 0x10000
#define MARKUP_SIZEOFWCHAR 4
#else // sizeof(wchar_t) != 4
#define MARKUP_SIZEOFWCHAR 2
#endif // sizeof(wchar_t) != 4
#endif // not MARKUP_SIZEOFWCHAR
#if ! defined(MARKUP_WINCONV) && ! defined(MARKUP_STDCONV) && ! defined(MARKUP_ICONV)
#define MARKUP_WINCONV
#endif // not WINCONV not STDCONV not ICONV
#if ! defined(MARKUP_FILEBLOCKSIZE)
#define MARKUP_FILEBLOCKSIZE 16384
#endif

// Text type and function defines (compiler and build-option dependent)
// 
#define MCD_ACP 0
#define MCD_UTF8 65001
#define MCD_UTF16 1200
#define MCD_UTF32 65005
#if defined(MARKUP_WCHAR)
#define MCD_CHAR wchar_t
#define MCD_PCSZ const wchar_t*
#define MCD_PSZLEN (int)wcslen
#define MCD_PSZCHR wcschr
#define MCD_PSZSTR wcsstr
#define MCD_PSZTOL wcstol
#define MCD_PSZNCMP wcsncmp
#if defined(MARKUP_SAFESTR) // VC++ safe strings
#define MCD_SSZ(sz) sz,(sizeof(sz)/sizeof(MCD_CHAR))
#define MCD_PSZCPY(sz,p) wcscpy_s(MCD_SSZ(sz),p)
#define MCD_PSZNCPY(sz,p,n) wcsncpy_s(MCD_SSZ(sz),p,n)
#define MCD_PSZCAT(sz,p) wcscat_s(MCD_SSZ(sz),p)
#define MCD_SPRINTF swprintf_s
#define MCD_FOPEN(f,n,m) {if(_wfopen_s(&f,n,m)!=0)f=NULL;}
#else // not VC++ safe strings
#if defined(__GNUC__)
#define MCD_SSZ(sz) sz,(sizeof(sz)/sizeof(MCD_CHAR))
#else // not GNUC
#define MCD_SSZ(sz) sz
#endif // not GNUC
#define MCD_PSZCPY wcscpy
#define MCD_PSZNCPY wcsncpy
#define MCD_PSZCAT wcscat
#define MCD_SPRINTF swprintf
#define MCD_FOPEN(f,n,m) f=_wfopen(n,m)
#endif // not VC++ safe strings
#define MCD_T(s) L ## s
#if MARKUP_SIZEOFWCHAR == 4 // sizeof(wchar_t) == 4
#define MCD_ENC MCD_T("UTF-32")
#else // sizeof(wchar_t) == 2
#define MCD_ENC MCD_T("UTF-16")
#endif
#define MCD_CLEN(p) 1
#else // not MARKUP_WCHAR
#define MCD_CHAR char
#define MCD_PCSZ const char*
#define MCD_PSZLEN (int)strlen
#define MCD_PSZCHR strchr
#define MCD_PSZSTR strstr
#define MCD_PSZTOL strtol
#define MCD_PSZNCMP strncmp
#if defined(MARKUP_SAFESTR) // VC++ safe strings
#define MCD_SSZ(sz) sz,(sizeof(sz)/sizeof(MCD_CHAR))
#define MCD_PSZCPY(sz,p) strcpy_s(MCD_SSZ(sz),p)
#define MCD_PSZNCPY(sz,p,n) strncpy_s(MCD_SSZ(sz),p,n)
#define MCD_PSZCAT(sz,p) strcat_s(MCD_SSZ(sz),p)
#define MCD_SPRINTF sprintf_s
#define MCD_FOPEN(f,n,m) {if(fopen_s(&f,n,m)!=0)f=NULL;}
#else // not VC++ safe strings
#define MCD_SSZ(sz) sz
#define MCD_PSZCPY strcpy
#define MCD_PSZNCPY strncpy
#define MCD_PSZCAT strcat
#define MCD_SPRINTF sprintf
#define MCD_FOPEN(f,n,m) f=fopen(n,m)
#endif // not VC++ safe strings
#define MCD_T(s) s
#if defined(MARKUP_MBCS) // MBCS/double byte
#define MCD_ENC MCD_T("")
#if defined(MARKUP_WINCONV)
#define MCD_CLEN(p) (int)_mbclen((const unsigned char*)p)
#else // not WINCONV
#define MCD_CLEN(p) (int)mblen(p,MB_CUR_MAX)
#endif // not WINCONV
#else // not MBCS/double byte
#define MCD_ENC MCD_T("UTF-8")
#define MCD_CLEN(p) 1
#endif // not MBCS/double byte
#endif // not MARKUP_WCHAR
#if _MSC_VER < 1000 // not VC++
#define MCD_STRERROR strerror(errno)
#endif // not VC++

// String type and function defines (compiler and build-option dependent)
// Define MARKUP_STL to use STL strings
//
#if defined(MARKUP_STL) // STL
#include <string>
#if defined(MARKUP_WCHAR)
#define MCD_STR std::wstring
#else // not MARKUP_WCHAR
#define MCD_STR std::string
#endif // not MARKUP_WCHAR
#define MCD_2PCSZ(s) s.c_str()
#define MCD_STRLENGTH(s) (int)s.size()
#define MCD_STRCLEAR(s) s.erase()
#define MCD_STRCLEARSIZE(s) MCD_STR t; s.swap(t)
#define MCD_STRISEMPTY(s) s.empty()
#define MCD_STRMID(s,n,l) s.substr(n,l)
#define MCD_STRASSIGN(s,p,n) s.assign(p,n)
#define MCD_STRCAPACITY(s) (int)s.capacity()
#define MCD_STRINSERTREPLACE(d,i,r,s) d.replace(i,r,s)
#define MCD_GETBUFFER(s,n) new MCD_CHAR[n+1]; s.reserve(n)
#define MCD_RELEASEBUFFER(s,p,n) s.assign(p,n); delete[]p
#define MCD_BLDRESERVE(s,n) s.reserve(n)
#define MCD_BLDCHECK(s,n,d) ;
#define MCD_BLDRELEASE(s) ;
#define MCD_BLDAPPENDN(s,p,n) s.append(p,n)
#define MCD_BLDAPPEND(s,p) s.append(p)
#define MCD_BLDAPPEND1(s,c) s+=(MCD_CHAR)(c)
#else // not STL, i.e. MFC
#include <afx.h>
#define MCD_STR CString
#define MCD_2PCSZ(s) ((MCD_PCSZ)s)
#define MCD_STRLENGTH(s) s.GetLength()
#define MCD_STRCLEAR(s) s.Empty()
#define MCD_STRCLEARSIZE(s) s=MCD_STR()
#define MCD_STRISEMPTY(s) s.IsEmpty()
#define MCD_STRMID(s,n,l) s.Mid(n,l)
#define MCD_STRASSIGN(s,p,n) memcpy(s.GetBuffer(n),p,(n)*sizeof(MCD_CHAR));s.ReleaseBuffer(n);
#define MCD_STRCAPACITY(s) (((CStringData*)((MCD_PCSZ)s)-1)->nAllocLength)
#define MCD_GETBUFFER(s,n) s.GetBuffer(n)
#define MCD_RELEASEBUFFER(s,p,n) s.ReleaseBuffer(n)
#define MCD_BLDRESERVE(s,n) MCD_CHAR*pD=s.GetBuffer(n); int nL=0
#define MCD_BLDCHECK(s,n,d) if(nL+(int)(d)>n){s.ReleaseBuffer(nL);n<<=2;pD=s.GetBuffer(n);}
#define MCD_BLDRELEASE(s) s.ReleaseBuffer(nL)
#define MCD_BLDAPPENDN(s,p,n) MCD_PSZNCPY(&pD[nL],p,n);nL+=n
#define MCD_BLDAPPEND(s,p) MCD_PSZCPY(&pD[nL],p);nL+=MCD_PSZLEN(p)
#define MCD_BLDAPPEND1(s,c) pD[nL++]=(MCD_CHAR)(c)
#endif // not STL

enum MarkupResultCode
{
	MRC_COUNT    = 1,
	MRC_TYPE     = 2,
	MRC_NUMBER   = 4,
	MRC_ENCODING = 8,
	MRC_LENGTH   = 16,
	MRC_MODIFY   = 32,
	MRC_MSG      = 64
};

#define MCD_CSTR_FILENAME MCD_CSTR

// Allow function args to accept string objects as constant string pointers
struct MCD_CSTR
{
	MCD_CSTR() { pcsz=NULL; };
	MCD_CSTR( MCD_PCSZ p ) { pcsz=p; };
	MCD_CSTR( const MCD_STR& s ) { pcsz = MCD_2PCSZ(s); };
	operator MCD_PCSZ() const { return pcsz; };
	MCD_PCSZ pcsz;
};

// On Linux and OS X, filenames are not specified in wchar_t
#if defined(MARKUP_WCHAR) && defined(__GNUC__)
#undef MCD_FOPEN
#define MCD_FOPEN(f,n,m) f=fopen(n,m)
#define MCD_T_FILENAME(s) s
#define MCD_PCSZ_FILENAME const char*
struct MCD_CSTR_FILENAME
{
	MCD_CSTR_FILENAME() { pcsz=NULL; };
	MCD_CSTR_FILENAME( MCD_PCSZ_FILENAME p ) { pcsz=p; };
	MCD_CSTR_FILENAME( const std::string& s ) { pcsz = s.c_str(); };
	operator MCD_PCSZ_FILENAME() const { return pcsz; };
	MCD_PCSZ_FILENAME pcsz;
};
#else // not WCHAR GNUC
#define MCD_CSTR_FILENAME MCD_CSTR
#define MCD_T_FILENAME MCD_T
#define MCD_PCSZ_FILENAME MCD_PCSZ
#endif // not WCHAR GNUC



#if defined(__GNUC__)
#define MCD_FSEEK fseeko
#define MCD_FTELL ftello
#define MCD_INTFILEOFFSET off_t
#elif _MSC_VER >= 1000 && defined(MARKUP_HUGEFILE) // VC++ HUGEFILE
#if _MSC_VER < 1400 // before VC++ 2005
extern "C" int __cdecl _fseeki64(FILE *, __int64, int);
extern "C" __int64 __cdecl _ftelli64(FILE *);
#endif // before VC++ 2005
#define MCD_FSEEK _fseeki64
#define MCD_FTELL _ftelli64
#define MCD_INTFILEOFFSET __int64
#else // not GNU or VC++ HUGEFILE
#define MCD_FSEEK fseek
#define MCD_FTELL ftell
#define MCD_INTFILEOFFSET long
#endif // not GNU or VC++ HUGEFILE

//////////////////////////////////////////////////////////////////////////
std::vector<MCD_STR> GetAllRows(MCD_STR strDoc);
MCD_STR GetItem(MCD_STR strRow,int col,MCD_STR strSep)	;
//////////////////////////////////////////////////////////////////////////

class DeuFileIO
{
public:
	DeuFileIO(){}  ;
	virtual ~DeuFileIO() {} ;
	
public:
	virtual bool Load(MCD_CSTR szFileName) = 0;
	
public:
	enum DeuDocFlags
	{
		MDF_UTF16LEFILE = 1,
		MDF_UTF8PREAMBLE = 4,
		MDF_IGNORECASE = 8,
		MDF_READFILE = 16,
		MDF_WRITEFILE = 32,
		MDF_APPENDFILE = 64,
		MDF_UTF16BEFILE = 128
	};


};

//////////////////////////////////////////////////////////////////////////
//
#include "BasicExcel.h"
//////////////////////////////////////////////////////////////////////////


class DeuExcelIO : public DeuFileIO
{
public:
	DeuExcelIO();
	~DeuExcelIO();
public:
	virtual bool Load(MCD_CSTR szFileName);
	virtual size_t GetTotalWorkSheets();
	//virtual BasicExcelWorksheet GetWorksheet(size_t sheetIndex);
	virtual double GetItem(size_t sheetIndex, size_t row, size_t col );

public:
	YExcel::BasicExcel m_e;

};

class DeuTxtIO : public DeuFileIO
{
public:
	DeuTxtIO();
	~DeuTxtIO();
public:
	virtual bool Load(MCD_CSTR szFileName);
	virtual bool ReadTextFile(MCD_CSTR_FILENAME szFileName, MCD_STR& strDoc, MCD_STR* pstrResult, int* pnDocFlags, MCD_STR* pstrEncoding = NULL);

public:
	MCD_STR m_strDoc;
	MCD_STR m_strResult;
	MCD_STR m_strEncoding;
	int m_nDocFlags;

};

template<typename T>
class DeuTxtIOTable : public DeuTxtIO
{
public:
	DeuTxtIOTable();
	~DeuTxtIOTable();

public:
	virtual void MakeTable();
	virtual void put_Separated(MCD_STR strSep);
	virtual void put_Format(T t);

	virtual std::vector<MCD_STR>& get_Rows();
	virtual MCD_STR get_Item(int row,int col);


private:
	std::vector<MCD_STR> m_Rows;//行的集合
	MCD_STR m_Sep;//分隔符号
	T m_t;
};


template<typename T>
DeuTxtIOTable<T>::DeuTxtIOTable()
{

}

template<typename T>
DeuTxtIOTable<T>::~DeuTxtIOTable()
{

}

template<typename T>
void DeuTxtIOTable<T>::MakeTable()
{
	//将文件分成表格
	MCD_STR strDoc = m_strDoc;

	//获得所有行
	m_Rows = GetAllRows(strDoc);

	//每行获得各个字段


	return ;
}

template<typename T>
std::vector<MCD_STR>& DeuTxtIOTable<T>::get_Rows()
{
	return m_Rows;
}

template<typename T>
MCD_STR DeuTxtIOTable<T>::get_Item(int row,int col)
{
	MCD_STR strRow = m_Rows[row];


	//自定义解析方式	
	return m_t.GetItem(strRow,col);

	//通用解析方式
	//return GetItem(strRow,col,m_Sep)	;
}

template<typename T>
void DeuTxtIOTable<T>::put_Separated(MCD_STR strSep)
{
	m_Sep = strSep;
}

template<typename T>
void DeuTxtIOTable<T>::put_Format(T t)
{
	m_t = t ;
}

#endif