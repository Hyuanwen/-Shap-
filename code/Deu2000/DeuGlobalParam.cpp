#include "StdAfx.h"

//子框架视图对象数组
CArray<CView*>    _ViewVectorList;
CArray<CView*>    _ViewRasterList;

//任务树节点对象数组
CArray<HTREEITEM> _TreeVectorList;
CArray<HTREEITEM> _TreeRasterList;

//Tab内嵌指针对象
CArray<CWnd*>     _TabVectorList;
CArray<CWnd*>     _TabRasterList;

CString GetStylesPath()
{
	TCHAR szStylesPath[_MAX_PATH];
	VERIFY(::GetModuleFileName(AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));

	CString csStylesPath(szStylesPath);
	int nIndex  = csStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) 
	{
		csStylesPath = csStylesPath.Left(nIndex);
	}
	else 
	{
		csStylesPath.Empty();
	}

	return csStylesPath; // + _T("\\Styles\\");
}

//处理数据库连接串
void PasterDBConn(CString m_str, ORACLEINFO* pOracleInfo)
{
	//这里不用循环，防止数组溢出. //特别说明：这不是一个通用函数
	/*while(IndexStart != -1)
	{
		IndexFinish = m_str.Find(",", IndexStart);
		m_arry.Add(m_str.Mid(IndexStart,  IndexFinish-IndexStart));
		IndexStart = IndexFinish+1;
	}*/

	int IndexStart = 0, IndexFinish=0;

	IndexFinish = m_str.Find(",", IndexStart);
	pOracleInfo->strSID = m_str.Mid(IndexStart,  IndexFinish-IndexStart);

	IndexStart = IndexFinish+1;
	IndexFinish = m_str.Find(",", IndexStart);
	pOracleInfo->strUser = m_str.Mid(IndexStart,  IndexFinish-IndexStart);
	
	//IndexFinish = m_str.Find(",", IndexStart);
	pOracleInfo->strPwd = m_str.Mid(IndexFinish+1);
}

void GetSysCurrentTime(char* szTime)
{
	CTime time = CTime::GetCurrentTime();
	CString strTmp;
	strTmp.Format("%d:%d:%d", time.GetHour(), time.GetMinute(), time.GetSecond());
	lstrcpy(szTime, strTmp);
}

BOOL IsExistDir(const string& strDir)
{
	WIN32_FIND_DATA							filedate;
	BOOL									bResult = FALSE;
	HANDLE									hFind;

	hFind = FindFirstFile(strDir.c_str(), &filedate);
	if ((hFind != INVALID_HANDLE_VALUE) && (filedate.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		bResult = TRUE;
	}

	FindClose(hFind);

	return bResult;
}

BOOL CreateDir(const string& strDir)
{
	SECURITY_ATTRIBUTES	attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength = sizeof(SECURITY_ATTRIBUTES);

	return ::CreateDirectory(strDir.c_str(), &attrib);
}

void DeleteAllFile(const string& strDir)
{
	CFileFind					finder;
	string						strFind = strDir + _T("//*.*");
	BOOL						BExist = finder.FindFile(strFind.c_str());
	CString						strFilePath = _T("");
	while (BExist)
	{
		BExist = finder.FindNextFile();
		strFilePath = finder.GetFilePath();

		if (!finder.IsDirectory())
		{
			CFile file;
			CFileStatus fs;
			file.GetStatus(strFilePath, fs);
			fs.m_attribute = 0;
			file.SetStatus(strFilePath, fs);
			::DeleteFile(strFilePath);
		}
	}
}