#pragma once

#define EllipListType_Folder  0 //�ļ���
#define EllipListType_File    1 //����ϵ�ļ�

class CDeuEllipList
{
public:
	CDeuEllipList();
	~CDeuEllipList();

public:
	HRESULT             GreateEllipList(std::string strPathRoot);
	int                 GetListType();
	std::vector<string> GetEllipList();

private:
	HRESULT GetFolderList(std::string strPathRoot, vector<std::string> * pFolderList);
	HRESULT GetFileList(std::string strPathRoot, vector<std::string> * pFileList);
	HRESULT GetListType(std::string strPathRoot);

private:
	int                        m_ListType;

public:
	std::vector<string>        m_EllipList;
};
