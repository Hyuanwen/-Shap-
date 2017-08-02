#include "StdAfx.h"
#include "EllipManager.h"

CEllipManager::CEllipManager()
{
	char                                szFilePath[MAX_PATH+1] = {0};

	::GetModuleFileName(NULL, szFilePath, MAX_PATH);

	m_EllipPath = szFilePath;
	int ipos = m_EllipPath.rfind(_T("\\"), m_EllipPath.length()-1);
	m_EllipPath = m_EllipPath.substr(0, ipos);
}

CEllipManager::~CEllipManager()
{
}

HRESULT CEllipManager::GetEllipTypeByEllipName(std::string strEllipName, CoordinateType * pCoordinateType)
{
	std::string                         strPathName;

	GetEllipFilePath(strEllipName, &strPathName);
	GetEllipTypeByPath(strPathName, pCoordinateType);

	return S_OK;
}

HRESULT CEllipManager::GetEllipByEllipName(std::string strEllipName, CDeuEllipse * pDeuEllipse)
{
	std::string                         strPathName;

    GetEllipFilePath(strEllipName, &strPathName);
    GetEllipInfo(strPathName, pDeuEllipse);

	return S_OK;
}

//ͨ��һ���ļ�·��������������ϵ����
HRESULT CEllipManager::GetEllipTypeByPath(std::string strPathName, CoordinateType * pCoordinateType)
{
	CFile                                File;
	char *                               chWkt;
	const char *                         pDatum = NULL;

	if (!File.Open(strPathName.c_str(), CFile::modeRead))
	{
		return S_FALSE;
	}

	int i = File.GetLength();
	chWkt = new char[i+1];
	memset(chWkt, '\0', sizeof(i+1));
	File.Read(chWkt, i);

	OGRErr gerr = m_OGRSpatialReference.importFromWkt(&chWkt);
	if (gerr != OGRERR_NONE)
	{
		return S_FALSE;
	}

	//�ж�����ϵ����
	if (m_OGRSpatialReference.IsProjected())
	{
		* pCoordinateType = GeoProjected;
	}
	else if (m_OGRSpatialReference.IsGeocentric())
	{
		* pCoordinateType = GeoCentic;
	}
	else if (m_OGRSpatialReference.IsGeographic())
	{
		* pCoordinateType = GeoDetic;
	}
	else
	{
		* pCoordinateType = All;
	}

	return S_OK;
}

//ͨ��һ���ļ�·����������������ͶӰ������Ϣ
HRESULT CEllipManager::GetEllipInfo(std::string strPathName, CDeuEllipse * pDeuEllipse)
{
    CFile                                File;
	char *                               chWkt;
	CoordinateType                       EllipType;
	const char *                         pDatum = NULL;

	File.Open(strPathName.c_str(), CFile::modeRead);
	int i = File.GetLength();
	chWkt = new char[i+1];
	memset(chWkt, '\0', sizeof(i+1));
	File.Read(chWkt, i);

	OGRErr gerr = m_OGRSpatialReference.importFromWkt(&chWkt);
	if (gerr != OGRERR_NONE)
	{
		return S_FALSE;
	}

	//�ж�����ϵ����
	if (m_OGRSpatialReference.IsProjected())
	{
		EllipType = GeoProjected;
	}
	else if (m_OGRSpatialReference.IsGeocentric())
	{
		EllipType = GeoCentic;
	}
	else if (m_OGRSpatialReference.IsGeographic())
	{
		EllipType = GeoDetic;
	}
	else
	{
		EllipType = All;
	}

	switch (EllipType)
	{
		//����ͶӰ����ϵ�������Ϣ
	case GeoProjected:

		//���ó���Ͷ���
		pDeuEllipse->putref_Major(m_OGRSpatialReference.GetSemiMajor());
		pDeuEllipse->putref_Minor(m_OGRSpatialReference.GetSemiMinor());

		//���õ���
		pDeuEllipse->putref_Flatening(double(1.0/m_OGRSpatialReference.GetInvFlattening()));

		//�������뾭��
		pDeuEllipse->putref_Centrol_Long(m_OGRSpatialReference.GetProjParm(SRS_PP_CENTRAL_MERIDIAN, 0.0));
		

		//��������ͶӰ����
		pDeuEllipse->putref_Prj_Name(m_OGRSpatialReference.GetAttrValue(_T("PROJCS")));
        pDeuEllipse->putref_Prj_Type(m_OGRSpatialReference.GetAttrValue(_T("PROJECTION")));

		//���ö���ƫ��ֵ
	    pDeuEllipse->putref_False_E(m_OGRSpatialReference.GetProjParm(SRS_PP_FALSE_EASTING, 0.0));
		pDeuEllipse->putref_False_N(m_OGRSpatialReference.GetProjParm(SRS_PP_FALSE_NORTHING, 0.0));

		break;
	case GeoCentic:
		break;

		//���ô������ϵ�������Ϣ
	case GeoDetic:
		
		pDeuEllipse->putref_Ellip_Name(m_OGRSpatialReference.GetAttrValue(_T("DATUM")));

		//���ó���Ͷ���
        pDeuEllipse->putref_Major(m_OGRSpatialReference.GetSemiMajor());
		pDeuEllipse->putref_Minor(m_OGRSpatialReference.GetSemiMinor());

		//���õ���
		pDeuEllipse->putref_Flatening(double(1.0/m_OGRSpatialReference.GetInvFlattening()));

		//��������
		pDeuEllipse->putref_Prj_Name(_T(""));
		pDeuEllipse->putref_Prj_Type(_T(""));
		pDeuEllipse->putref_False_N(0);
		pDeuEllipse->putref_False_E(0);

		break;
	default:
		break;
	}

	return S_OK;
}

//ͨ��һ������ϵ���ļ��� ���Ҹ��ļ�����ϵͳ�е�λ�� 
HRESULT CEllipManager::GetEllipFilePath(std::string strFileName, std::string * pstrFilePath)
{
	std::string								strPath = _T("");
	int										nPos = 0;
	vector<std::string>                     StrResult;

	//����������ļ���
	strPath = strFileName + _T(".") + _T("prj");
    FindFile(m_EllipPath, strPath, &StrResult);

    if (StrResult.size() == 0)
    {
		return S_FALSE;
    }
	else if (StrResult.size() == 1)
	{
		*pstrFilePath = StrResult.at(0);
	}
	else if (StrResult.size() > 1)
	{
		return S_FALSE;
	}

	return S_OK;
}

BOOL CEllipManager::FindFile(const std::string strPathRoot, const std::string strFileName, vector<std::string> * pStrResult)
{
	std::string                             strTmp;
	std::string                             strPathRootTmp;
	std::string                             strResult;
	std::string                             strFindPath;

	if (strPathRoot.length() <= 0)
	{
		return FALSE;
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

		//����ҵ������ļ��У��ݹ��ȥ  
		if (finder.IsDirectory()&&!finder.IsDots())  
		{  
			strPathRootTmp = strPathRoot  + _T("\\") + finder.GetFileName().GetBuffer(finder.GetFileName().GetLength());
			FindFile(strPathRootTmp, strFileName, pStrResult);  
		}  

		//����ҵ����ļ���������·����ӽ��ַ�������,��Сд������  
		CString  strFindName = finder.GetFileName();
		if (finder.GetFileName().CompareNoCase(strFileName.c_str())==0)  
		{  
			strResult = finder.GetFilePath().GetBuffer(finder.GetFilePath().GetLength());
			pStrResult->push_back(strResult);  
		}  
	}  

	return TRUE;
}