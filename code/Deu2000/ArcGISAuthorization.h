/*
 *		��Ŀ��Deu2000�����ǻ�ת�����
 *		���ߣ�chenyong
 *		�������ṩArcGis��Ʒ��֤����
 *		ʱ�䣺2013-4-28
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