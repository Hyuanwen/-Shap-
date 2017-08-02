#include "StdAfx.h"

CDeuEllipList::CDeuEllipList()
{
}

CDeuEllipList::~CDeuEllipList()
{
}


int CDeuEllipList::GetListType()
{
	return m_ListType;
}

std::vector<string> CDeuEllipList::GetEllipList()
{
	return m_EllipList;
}

//构建一个根据文件获得的文件列表对象
HRESULT CDeuEllipList::GreateEllipList(std::string strPathRoot)
{
    //判断该文件夹下为何种文件结构
    GetListType(strPathRoot);

	if (m_ListType == EllipListType_Folder)
	{
		GetFolderList(strPathRoot, &m_EllipList);
	}
	else if (m_ListType == EllipListType_File)
	{
		GetFileList(strPathRoot, &m_EllipList);
	}

	return S_OK;
}

//查找一个路径下的所有文件夹
HRESULT CDeuEllipList::GetFolderList(std::string strPathRoot, vector<std::string> * pFolderList)
{ 
	std::string                             strTmp;
	std::string                             strPathRootTmp;
	std::string                             strFindPath;

	pFolderList->clear();

	if (strPathRoot.length() <= 0)
	{
		return S_FALSE;
	}

	strTmp = strPathRoot.at(strPathRoot.length()-1);
	if (strcmp(strTmp.c_str(), _T("\\")) != 0)
	{
		strFindPath = strPathRoot + _T("\\") + _T("*.*");
	}
	else
	{
		strFindPath = strPathRoot + _T("*.*");
	}

	//开始查找  
	CFileFind finder;  
	BOOL bWorking = finder.FindFile(strFindPath.c_str());  

	while(bWorking)  
	{  
		bWorking = finder.FindNextFile();  

		//如果找到的是文件夹
		if (finder.IsDirectory()&&!finder.IsDots())  
		{  
			strTmp = finder.GetFileName();
		    pFolderList->push_back(strTmp);
		}  
	}  

	return S_OK;
}

//查找一个路径下的所有文件
HRESULT CDeuEllipList::GetFileList(std::string strPathRoot, vector<std::string> * pFileList)
{ 
	std::string                             strTmp;
	std::string                             strPathRootTmp;
	std::string                             strFindPath;
	std::string                             strFindName;

	pFileList->clear();

	if (strPathRoot.length() <= 0)
	{
		return S_FALSE;
	}

	strTmp = strPathRoot.at(strPathRoot.length()-1);
	if (strcmp(strTmp.c_str(), _T("\\")) != 0)
	{
		strFindPath = strPathRoot + _T("\\") + _T("*.*");
	}
	else
	{
		strFindPath = strPathRoot + _T("*.*");
	}

	//开始查找  
	CFileFind finder;  
	BOOL bWorking = finder.FindFile(strFindPath.c_str());  

	while(bWorking)  
	{  
		bWorking = finder.FindNextFile();  

		//如果找到的是文件
		if (!finder.IsDirectory()&&!finder.IsDots())
		{
			strFindName = finder.GetFileName();
			pFileList->push_back(strFindName); 
		}
	}  

	return S_OK;
}

HRESULT CDeuEllipList::GetListType(std::string strPathRoot)
{
	std::string                             strTmp;
	std::string                             strPathRootTmp;
	std::string                             strFindPath;

	CString         FileName;

	if (strPathRoot.length() <= 0)
	{
		return S_FALSE;
	}

	strTmp = strPathRoot.at(strPathRoot.length()-1);
	if (strcmp(strTmp.c_str(), _T("\\")) != 0)
	{
		strFindPath = strPathRoot + _T("\\") + _T("*.*");
	}
	else
	{
		strFindPath = strPathRoot + _T("*.*");
	}

	//开始查找  
	CFileFind finder;  
	BOOL bWorking = finder.FindFile(strFindPath.c_str());  

	while(bWorking)  
	{  
		bWorking = finder.FindNextFile();  

		FileName = finder.GetFileName();
		BOOL IsDots = finder.IsDots();
		BOOL IsDirectory = finder.IsDirectory();

		//如果找到的是文件夹
		if (finder.IsDirectory()&&!finder.IsDots())  
		{  
			m_ListType = EllipListType_Folder;
		}  
		else if (!finder.IsDirectory()&&!finder.IsDots())
		{
			m_ListType = EllipListType_File;
			break;
		}
	}  

	return S_OK;
}