#ifndef _ARCSDE_CONNECTION_H
#define _ARCSDE_CONNECTION_H



class CArcSDEConnection
{
public:
	CArcSDEConnection();
	~CArcSDEConnection();

public:


	HRESULT	ConnectToSDE(const CString& strServer, 
							const CString& strInstance, 
							const CString& strDatabase, 
							const CString& strUser, 
							const CString& strPassword,
							const CString& strVersion,
							 IWorkspace** poutWorkspace
							 );

};
#endif


