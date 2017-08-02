#include "stdafx.h"
#include "DeuTranslate.h"

CDeuDatabase::CDeuDatabase()
{

}

CDeuDatabase::~CDeuDatabase()
{

}

void CDeuDatabase::get_Conn(VARIANT** pVal) const
{
	*pVal = ((VARIANT*)m_pConn);
}

void CDeuDatabase::putref_Conn(VARIANT* newVal)
{
	m_pConn = (CDeuConn*)newVal;
}

HRESULT	CDeuDatabase::GetTabList(VARIANT** vTabList) const
{
	OGRDataSource *poDS = m_pConn->DataSource;
	
	//layer to feature
	int lyrCount=0;
	lyrCount=poDS->GetLayerCount();

#if 1
	SAFEARRAYBOUND saBound[2];		// 1表示一维数组
	saBound[0].cElements = lyrCount;// 20表示有20个元素
	saBound[0].lLbound = 0;         // 0表示从0开始
	SAFEARRAY *p;
	p = SafeArrayCreate(VT_BSTR,1,saBound);  //创建SafeArray

	//获得源图层
	OGRLayer  *TmppoLayer = NULL;
	OGRLayer  *poLayer = NULL;
	for (long i=0;i<lyrCount;i++)
	{
		TmppoLayer=poDS->GetLayer(i);
		LPSTR LyrName = (LPSTR)TmppoLayer->GetLayerDefn()->GetName();

		BSTR *pData;
		SafeArrayAccessData(p,(void **) &pData);

		//for linux
		pData[i] = _bstr_t(LyrName);
		char *pTemp = LyrName;
		int count = strlen(LyrName);

		SafeArrayUnaccessData(p);
	}

	VARIANT varBand;
	varBand.vt = VT_SAFEARRAY|VT_LPSTR;
	varBand.parray = p;

	*vTabList = (VARIANT*)&varBand;
#endif

	return S_OK;
}

HRESULT	CDeuDatabase::Connect(const CString& strConnString)
{
	if (m_ConnPool == NULL)
	{
		return S_FALSE;
	}

	LONG ConnId;
	HRESULT hr = m_ConnPool->Connect(strConnString,ConnId);
	
	//m_pConn	
	VARIANT* p_Conn;
	m_ConnPool->get_Conn( ConnId, &p_Conn );
	m_pConn = (CDeuConn*) p_Conn;

	return hr;
}

HRESULT CDeuDatabase::get_ConnPool(CDeuConnPool** pVal) const
{
	*pVal = m_ConnPool;
	return S_OK;
}

HRESULT CDeuDatabase::putref_ConnPool(CDeuConnPool* newVal)
{
	m_ConnPool = newVal;
	return S_OK;
}