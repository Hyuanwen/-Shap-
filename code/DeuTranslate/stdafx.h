// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE 类
#include <afxodlgs.h>       // MFC OLE 对话框类
#include <afxdisp.h>        // MFC 自动化类
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
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT


#pragma warning(disable : 4018)
#pragma warning(disable : 4067)
#pragma warning(disable : 4996)
#pragma warning(disable : 4244)
#pragma warning(disable : 4482)
