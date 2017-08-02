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

//����һ�������ļ���õ��ļ��б����
HRESULT CDeuEllipList::GreateEllipList(std::string strPathRoot)
{
    //�жϸ��ļ�����Ϊ�����ļ��ṹ
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

//����һ��·���µ������ļ���
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

	//��ʼ����  
	CFileFind finder;  
	BOOL bWorking = finder.FindFile(strFindPath.c_str());  

	while(bWorking)  
	{  
		bWorking = finder.FindNextFile();  

		//����ҵ������ļ���
		if (finder.IsDirectory()&&!finder.IsDots())  
		{  
			strTmp = finder.GetFileName();
		    pFolderList->push_back(strTmp);
		}  
	}  

	return S_OK;
}

//����һ��·���µ������ļ�
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

	//��ʼ����  
	CFileFind finder;  
	BOOL bWorking = finder.FindFile(strFindPath.c_str());  

	while(bWorking)  
	{  
		bWorking = finder.FindNextFile();  

		//����ҵ������ļ�
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

	//��ʼ����  
	CFileFind finder;  
	BOOL bWorking = finder.FindFile(strFindPath.c_str());  

	while(bWorking)  
	{  
		bWorking = finder.FindNextFile();  

		FileName = finder.GetFileName();
		BOOL IsDots = finder.IsDots();
		BOOL IsDirectory = finder.IsDirectory();

		//����ҵ������ļ���
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