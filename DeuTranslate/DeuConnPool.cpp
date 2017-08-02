#include "stdafx.h"
#include "DeuTranslate.h"
#include "ogr_oci.h"

CDeuConnPool::CDeuConnPool()
{

}

CDeuConnPool::~CDeuConnPool()
{
	for(std::vector<CDeuConn*>::iterator itor = m_Conn.begin(); itor != m_Conn.end(); itor++)
	{
		delete *itor;
	}
}

void CDeuConnPool::get_ConnCount(long &Val) const
{
	Val = m_Conn.size();
}

void CDeuConnPool::put_ConnCount(long newVal)
{
	
}

HRESULT	CDeuConnPool::Connect(const CString& strConnString, long& ConnId)
{
	//由连接字符串连接数据库
	//file to layer
	OGRRegisterAll();
	RegisterOGROCI();

	//LOGSTR( "Connect.\n" );
	
	//是否已经有了此连接，如果有了则不需要再次连接
	long pCount;
	get_ConnCount(pCount);
	for (int i = 0;i < pCount; i++ )
	{
		CDeuConn* pConn;
		VARIANT*  p_Conn;
		get_Conn( i, &p_Conn );
		pConn = (CDeuConn*) p_Conn;

		CString szConnString = pConn->ConnString;
		if (szConnString == strConnString)
		{			
			ConnId = pConn->ConnId;
			return S_OK;
		}
	}

	//LOGSTR( "begin open.\n" );

	//如果没有连接，则新建一个连接
	//打开源数据源
	OGRDataSource       *poDS;
	poDS = OGRSFDriverRegistrar::Open(strConnString.GetString(), TRUE ,NULL);
	if( poDS == NULL )
	{
		LOGSTR( "Open DataSource failed.\n" );
		return S_FALSE;
	}

	//LOGSTR( "begin end.\n" );
	CDeuConn *Conn = new CDeuConn;
	Conn->DataSource = poDS;
	Conn->ConnId = m_Conn.size();		
	Conn->ConnString = strConnString; 

	//将连接加入连接池
	m_Conn.push_back(Conn);

	//返回接连ID
	ConnId = Conn->ConnId;

	return S_OK;
}

void CDeuConnPool::get_Conn(long ConnId, VARIANT** pVal) const
{
	//OGRDataSource* ds = NULL;
	if (ConnId < 0 || ConnId >= m_Conn.size())
	{
		*pVal = NULL;
		return;
	}

	CDeuConn* pConn = m_Conn[ConnId];
	*pVal = ((VARIANT*)pConn);

	return;
}

void CDeuConnPool::putref_Conn(LONG ConnId, VARIANT* newVal)
{
}

HRESULT CDeuConnPool::DisConnect(LONG ConnId)
{
	CDeuConn *Conn = NULL;
	Conn = m_Conn[ConnId];

	OGRDataSource* ds=Conn->DataSource;
	OGRDataSource::DestroyDataSource( ds );

	return S_OK;
}