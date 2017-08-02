/*
 *		项目：Deu2000德毅智慧转换软件
 *		作者：chenyong
 *		描述：提供ArcGis产品验证功能
 *		时间：2013-4-28
 */


#ifndef _ARCGIS_AUTHORIZATION_
#define _ARCGIS_AUTHORIZATION_


class CArcGisAuthorization
{
public:
	CArcGisAuthorization();
	~CArcGisAuthorization();

public:
	HRESULT	Init();
	void	Shutdown();
	HRESULT	ArcGisLiscense();

private:
	VARIANT_BOOL InitializeLicense(esriLicenseProductCode product);

private:
	IAoInitializePtr						m_pAoInitialize;
	//IAoInitialize*						m_pAoInitialize;
};
#endif