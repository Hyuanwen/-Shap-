// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE ��
#include <afxodlgs.h>       // MFC OLE �Ի�����
#include <afxdisp.h>        // MFC �Զ�����
#endif // _AFX_NO_OLE_SUPPORT

#include <fstream>
#include <math.h>
#include <comutil.h>
#include <comdef.h>

//#include "DeuTranslate.h"
#define OTL_ORA9I
#include "DeuDef.h"
#include "Grid.h"
#include "DeuExcel.h"
#include "DeuProject.h"
#include "DeuConn.h"
#include "GridTranslate.h"

//add by chenyong 2014-3-25
#include "ComLib.h"
#import "libid:b691e011-1797-432e-907a-4d8c69339129" rename("EOF","_EOF")
using namespace ADODB;

/*#import "C:\Program Files (x86)\Common Files\System\ADO\msado15.dll" rename("EOF", "_EOF")
#import "C:\Program Files (x86)\Common Files\Microsoft Shared\OFFICE12\mso.dll" rename("RGB", "MSRGB")
#import "C:\Program Files (x86)\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB" raw_interfaces_only, \
	rename("Reference", "ignorethis"), rename("VBE", "JOEVBE")
#import "D:\install\office 2007\Office12\EXCEL.exe" exclude("IFont", "IPicture") \
	rename("RGB", "ignorethis"), rename("DialogBox", "ignorethis"), rename("VBE", "JOEVBE"), \
	rename("ReplaceText", "JOEReplaceText"), rename("CopyFile","JOECopyFile"), \
	rename("FindText", "JOEFindText"), rename("NoPrompt", "JOENoPrompt")

using namespace ADODB;
using namespace Office;
using namespace VBIDE;
using namespace Excel;*/

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT


#pragma warning(disable : 4018)
#pragma warning(disable : 4067)
#pragma warning(disable : 4996)
#pragma warning(disable : 4244)
#pragma warning(disable : 4482)
