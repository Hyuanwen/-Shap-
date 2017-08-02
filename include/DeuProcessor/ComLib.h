/*
	作用：ado及excel组件库文件导入
	时间：2014-3-25
*/


#ifndef _COMLIB_H_
#define _COMLIB_H_

//mso.dll
#import "libid:2df8d04c-5bfa-101b-bde5-00aa0044de52" raw_interfaces_only rename("RGB", "MSRGB") rename("IAccessible", "IExcelAccessible")

//vbe6ext.olb
#import "libid:0002e157-0000-0000-c000-000000000046" raw_interfaces_only rename("Reference", "ignorethis") rename("VBE","JOEVBE")

//excel.exe
#import "libid:00020813-0000-0000-c000-000000000046" exclude("IFont", "IPicture", "IPoint") \
	rename("RGB", "ignorethis"), rename("DialogBox", "ignorethis"), rename("VBE", "JOEVBE"), \
	rename("ReplaceText", "JOEReplaceText"), rename("CopyFile","JOECopyFile"), \
	rename("FindText", "JOEFindText"), rename("NoPrompt", "JOENoPrompt")

using namespace Office;
using namespace VBIDE;
using namespace Excel;

#endif