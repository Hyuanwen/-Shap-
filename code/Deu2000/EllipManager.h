#pragma once

class CEllipManager
{
public:
	CEllipManager();
	~CEllipManager();

public:
	HRESULT GetEllipByEllipName(std::string strEllipName, CDeuEllipse * pDeuEllipse);
	HRESULT GetEllipTypeByEllipName(std::string strEllipName, CoordinateType * pCoordinateType);
	HRESULT GetEllipFilePath(std::string strFileName, std::string * pstrFilePath); //alter by chenyong 2013-10-15
private:
	HRESULT GetEllipTypeByPath(std::string strPathName, CoordinateType * pCoordinateType);
	HRESULT GetEllipInfo(std::string strPathName, CDeuEllipse * pDeuEllipse);
	int     FindFile(const std::string strPathRoot, const std::string strFileName, vector<std::string> * pStrResult);

public:
	OGRSpatialReference  m_OGRSpatialReference;
private:
	std::string          m_EllipPath;
};
