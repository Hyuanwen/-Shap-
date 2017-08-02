#include "stdafx.h"
#include "ArcGISAuthorization.h"


CArcGisAuthorization::CArcGisAuthorization()
{

}

CArcGisAuthorization::~CArcGisAuthorization()
{
	/*if (NULL != m_pAoInitialize)
	{
		m_pAoInitialize->Release();
	}*/

	Shutdown();
}

HRESULT CArcGisAuthorization::Init()
{
	HRESULT hr = ::CoCreateInstance(CLSID_AoInitialize, NULL, CLSCTX_INPROC_SERVER, IID_IAoInitialize, (void**)&m_pAoInitialize);
	if (NULL == m_pAoInitialize)
	{
		return S_FALSE;
	}
	
	return hr;
}

void CArcGisAuthorization::Shutdown()
{	
	if (m_pAoInitialize != NULL)
	{
		m_pAoInitialize->Shutdown();
	}	
}

VARIANT_BOOL CArcGisAuthorization::InitializeLicense(esriLicenseProductCode product)
{
	esriLicenseStatus				licenseStatus = esriLicenseFailure;

	m_pAoInitialize->IsProductCodeAvailable(product, &licenseStatus);

	if (licenseStatus == esriLicenseAvailable)
	{
		m_pAoInitialize->Initialize(product, &licenseStatus);
	}

	return (licenseStatus == esriLicenseCheckedOut);

}

HRESULT CArcGisAuthorization::ArcGisLiscense()
{	

	if (!InitializeLicense(/*esriLicenseProductCodeEngine*/esriLicenseProductCodeEngineGeoDB))
	{	
		if (!InitializeLicense(esriLicenseProductCodeEngine))	
		{	
	/*		if (!InitializeLicense(esriLicenseProductCodeArcView))
			{
				if (!InitializeLicense(esriLicenseProductCodeArcEditor))
				{
					if (!InitializeLicense(esriLicenseProductCodeArcInfo))
					{*/
						//MessageBox(NULL, "Exiting Application: License Initialization failed", "Error", MB_OK);
						LOGSTR("ArcSDE Initialization failed");
						return S_FALSE;
					//}
				//}
			//}
		}
	}

	return S_OK;
}

