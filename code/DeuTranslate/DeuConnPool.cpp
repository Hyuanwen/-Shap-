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
	//�������ַ����������ݿ�
	//file to layer
	OGRRegisterAll();
	RegisterOGROCI();

	//LOGSTR( "Connect.\n" );
	
	//�Ƿ��Ѿ����˴����ӣ������������Ҫ�ٴ�����
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

	//���û�����ӣ����½�һ������
	//��Դ����Դ
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

	//�����Ӽ������ӳ�
	m_Conn.push_back(Conn);

	//���ؽ���ID
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