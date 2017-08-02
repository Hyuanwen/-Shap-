#include "stdafx.h"
#include "ArcSDEConnection.h"


CArcSDEConnection::CArcSDEConnection()
{

}

CArcSDEConnection::~CArcSDEConnection()
{

}

HRESULT CArcSDEConnection::ConnectToSDE(const CString &strServer
										, const CString &strInstance
										, const CString &strDatabase
										, const CString &strUser
										, const CString &strPassword
										, const CString &strVersion
										, IWorkspace** poutWorkspace)
{

	//IPropertySetPtr								ipPropertySet(CLSID_PropertySet);
	IPropertySet*									ipPropertySet;
	::CoCreateInstance(CLSID_PropertySet, NULL, CLSCTX_INPROC_SERVER, IID_IPropertySet, (void**)&ipPropertySet);

	if (NULL == ipPropertySet)
	{
		return S_FALSE;
	}

	ipPropertySet->SetProperty(_bstr_t("SERVER"), _variant_t(strServer));
	ipPropertySet->SetProperty(_bstr_t("INSTANCE"), _variant_t(strInstance));
	ipPropertySet->SetProperty(_bstr_t("DATABASE"), _variant_t(strDatabase));
	ipPropertySet->SetProperty(_bstr_t("USER"), _variant_t(strUser));
	ipPropertySet->SetProperty(_bstr_t("PASSWORD"), _variant_t(strPassword));
	ipPropertySet->SetProperty(_bstr_t("VERSION"), _variant_t(strVersion));

	CComPtr<IWorkspaceFactory>							ipWorkspaceFactory;

	ipWorkspaceFactory.CoCreateInstance(CLSID_SdeWorkspaceFactory);

	return ipWorkspaceFactory->Open(ipPropertySet, NULL, poutWorkspace);



}

