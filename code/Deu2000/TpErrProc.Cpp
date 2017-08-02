#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTpErrProc::CTpErrProc()
	: m_nErrCode(ERR_CODE_NOERR)
	, m_pErrStr(NULL)
	, m_nRetCode(RET_CODE_OK)
{
}

CTpErrProc::CTpErrProc(const CTpErrProc& refVal)
	: m_nErrCode(ERR_CODE_NOERR)
	, m_pErrStr(NULL)
	, m_nRetCode(RET_CODE_OK)
{
    char                szBuf[512];

    refVal.GetErrStr(szBuf, sizeof(szBuf));
    SetErrStr(szBuf);
    m_nErrCode = refVal.GetErrCode();
    m_nRetCode = refVal.GetRetCode();
}

CTpErrProc::CTpErrProc(const CTpErrProc * pVal)
	: m_nErrCode(ERR_CODE_NOERR)
	, m_pErrStr(NULL)
	, m_nRetCode(RET_CODE_OK)
{
    char                szBuf[512];

    pVal->GetErrStr(szBuf, sizeof(szBuf));
    SetErrStr(szBuf);
    m_nErrCode = pVal->GetErrCode();
    m_nRetCode = pVal->GetRetCode();
}




CTpErrProc::CTpErrProc(ERR_TYPE ErrCode, LPCSTR ErrStr)
	: m_nErrCode(ErrCode)
	, m_pErrStr(NULL)
	, m_nRetCode(RET_CODE_OK)
{
	//拷贝错误信息串
	if (ErrStr != NULL)
	{
		int				iErrInfoLen = strlen(ErrStr);

		m_pErrStr = new char[iErrInfoLen + 2];
		if (m_pErrStr != NULL)
			strcpy_s(m_pErrStr, iErrInfoLen + 2, ErrStr);
	}
	//设置返回代码
	if ((ErrCode != ERR_CODE_NOERR) || (m_pErrStr != NULL))
	{
		m_nRetCode = RET_CODE_FAIL;
	}

	//如果设置了返回代码的话，必须设置错误代码
	if (m_nRetCode == RET_CODE_FAIL)
	{
		if (m_nErrCode == ERR_CODE_NOERR)
		{
			m_nErrCode = ERR_CODE_COMM;
		}
	}
}

CTpErrProc::~CTpErrProc()
{
	if (m_pErrStr != NULL)
	{
		delete [] m_pErrStr;
		m_pErrStr = NULL;
	}
}

ERR_TYPE CTpErrProc::GetErrCode() const
{
	return m_nErrCode;
}

ERR_TYPE CTpErrProc::SetErrCode(ERR_TYPE newVal)
{
    UINT                nID;

	m_nErrCode = newVal;
	if (m_nErrCode != ERR_CODE_NOERR)
	{
		m_nRetCode = RET_CODE_FAIL;
	}
	
    nID = 0;
	switch (m_nErrCode)
	{
    case TPERR_NO_ENOUGH_MEM:           nID = 110101;   break;
    case TPERR_CANT_CREATE_COMOBJECT:   nID = 110102;   break;
    case TPERR_FILE_CANT_OPEN:          nID = 110103;   break;
    case TPERR_FILE_CANT_READ:          nID = 110104;   break;

	case TPERR_DB_CANT_CREATE_SESSION:  nID = 110201;   break;
	case TPERR_DB_SVR_DISC_CLT:         nID = 110202;   break;
	case TPERR_DB_COMM_FAIL:            nID = 110203;   break;
	case TPERR_DB_PSW_ERR:              nID = 110204;   break;
	case TPERR_DB_DUPLICATE_KEY:        nID = 110205;   break;
    }
    if (nID != 0)
    {
//        SetErrStr(GetStringId(nID));
    }

	return m_nErrCode;
}


HRESULT CTpErrProc::GetErrStr(char * pStrBuf, long BufLen) const
{
	if ((pStrBuf != NULL) && (BufLen > 0))
	{
		//pStrBuf[0] = '\0';
		memset(pStrBuf, '\0', BufLen);

		if (m_pErrStr != NULL)
		{
			long	len = strlen(m_pErrStr);

			//if (len < BufLen)
			//	strcpy_s(pStrBuf,len, m_pErrStr);
			//else
			//{
			//	memcpy(pStrBuf, m_pErrStr, BufLen);
			//	pStrBuf[BufLen - 1] = '\0';
			//}
			memcpy(pStrBuf, m_pErrStr, BufLen > len ? len : BufLen) ;
		}
	}
	return S_OK;
}

HRESULT CTpErrProc::SetErrStr(LPCSTR newVal)
{
	if (m_pErrStr != NULL)
	{
		delete [] m_pErrStr;
		m_pErrStr = NULL;
	}
	if (newVal != NULL)
	{
		int				iErrInfoLen = strlen(newVal);

		m_pErrStr = new char[iErrInfoLen + 2];
		if (m_pErrStr != NULL)
			strcpy_s(m_pErrStr, iErrInfoLen + 2, newVal);
		//如果设置过错误信息，自动设置错误代码为: 
		if (m_nErrCode == ERR_CODE_NOERR)
		{
			SetErrCode(ERR_CODE_COMM);
		}
	}
	return S_OK;
}

RET_TYPE CTpErrProc::GetRetCode() const
{
	return m_nRetCode;
}

RET_TYPE CTpErrProc::SetRetCode(RET_TYPE newVal)
{
	m_nRetCode = newVal;
	if (m_nRetCode == RET_CODE_FAIL)
	{
		if (m_nErrCode == ERR_CODE_NOERR)
		{
			SetErrCode(ERR_CODE_COMM);
		}
	}
	else
	{
		m_nErrCode = ERR_CODE_NOERR;
	}
	return m_nRetCode;
}

HRESULT CTpErrProc::Reset()
{
	m_nErrCode = ERR_CODE_NOERR;
	if (m_pErrStr != NULL)
		m_pErrStr[0] ='\0';
	m_nRetCode = RET_CODE_OK;
	return S_OK;
}

HRESULT CTpErrProc::SetErrInfo(ERR_TYPE ErrCode, LPCSTR ErrStr, RET_TYPE RetCode)
{
	m_nErrCode = ErrCode;
	if (m_pErrStr != NULL)
	{
		delete [] m_pErrStr;
		m_pErrStr = NULL;
	}
	m_nRetCode = RetCode;

	//拷贝错误信息串
	if (ErrStr != NULL)
	{
		int				iErrInfoLen = strlen(ErrStr);

		m_pErrStr = new char[iErrInfoLen + 2];
		if (m_pErrStr != NULL)
			strcpy_s(m_pErrStr,iErrInfoLen + 2, ErrStr);
	}
	//设置返回代码
	if ((ErrCode != ERR_CODE_NOERR) || (m_pErrStr != NULL))
	{
		SetRetCode(RET_CODE_FAIL);
	}

	return S_OK;
}

UINT CTpErrProc::DispErrInfo()
{
//	return ::MessageBox(::GetActiveWindow(), m_pErrStr, GetStringId(120012), MB_OK);

	return 0;
}
