#include "StdAfx.h"
#include "GridParameter.h"
#include "TinyXml/tinyxml.h"

CGridParameter::CGridParameter(void)
{
}

CGridParameter::CGridParameter(std::string strFileName)
{
	m_strPath = strFileName;
}

CGridParameter::~CGridParameter(void)
{
}

HRESULT CGridParameter::InitGridParameter()
{
	if (m_strPath.empty())
	{
		return S_FALSE;
	}

	bool loadOkay = m_ParameterXml.LoadFile(m_strPath);
	if (loadOkay != true)
	{
		return S_FALSE;
	}

    GetGridParametersByXml(&m_ParameterList);

	return S_OK;
}

HRESULT CGridParameter::InitGridParameter(std::string strFileName)
{
	m_strPath = strFileName;

	if (m_strPath.empty())
	{
		return S_FALSE;
	}

	bool loadOkay = m_ParameterXml.LoadFile(m_strPath);
	if (loadOkay != true)
	{
		return S_FALSE;
	}

	GetGridParametersByXml(&m_ParameterList);

	return S_OK;
}

HRESULT CGridParameter::GetParameterBySheet(std::string strSheetNum, GridParameter * pGridFormat)
{
	vector<GridParameter>::iterator         iter;

    pGridFormat->DB_DB = 0;
    pGridFormat->DB_DN = 0;
    pGridFormat->DB_XB = 0;
    pGridFormat->DB_XN = 0;
    pGridFormat->DL_DB = 0;
    pGridFormat->DL_DN = 0;
    pGridFormat->DL_XB = 0;
    pGridFormat->DL_XN = 0;
	
	for (iter = m_ParameterList.begin(); iter != m_ParameterList.end(); iter ++)
	{
		if (strcmp(strSheetNum.c_str(), iter->szFrame) == 0)
		{
			strcpy(pGridFormat->szFrame, iter->szFrame);
			pGridFormat->DB_DB = iter->DB_DB;
			pGridFormat->DB_DN = iter->DB_DN;
			pGridFormat->DB_XB = iter->DB_XB;
			pGridFormat->DB_XN = iter->DB_XN;
			pGridFormat->DL_DB = iter->DL_DB;
			pGridFormat->DL_DN = iter->DL_DN;
			pGridFormat->DL_XB = iter->DL_XB;
			pGridFormat->DL_XN = iter->DL_XN;

			break;
		}
	}

	return S_OK;
}

//创建一个专门用于保存格网参数的Xml文件
HRESULT CGridParameter::GreatParameterXml(LPCSTR chPath, LPCSTR chName)
{
	char                          chFilePath[512];

	strcpy(chFilePath, chPath);
	strcat(chFilePath, chName);

	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
	TiXmlElement * element = new TiXmlElement( "GridParameters" );
	TiXmlText * text = new TiXmlText( "" );
	element->LinkEndChild( text );
	m_ParameterXml.LinkEndChild( decl );
	m_ParameterXml.LinkEndChild( element );
	m_ParameterXml.SaveFile( chFilePath );

	m_strPath = chFilePath;

	return S_OK;
}

HRESULT CGridParameter::GreatParameterXml(std::string strPath, std::string strName)
{
	std::string                   strFilePath;

	strFilePath = strPath + strName;

	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
	TiXmlElement * element = new TiXmlElement( "GridParameters" );
	TiXmlText * text = new TiXmlText( "" );
	element->LinkEndChild( text );
	m_ParameterXml.LinkEndChild( decl );
	m_ParameterXml.LinkEndChild( element );
	m_ParameterXml.SaveFile( strFilePath );

	m_strPath = strFilePath;

	return S_OK;
}

//向xml中插入一组格网参数
HRESULT CGridParameter::InsertParameter(GridParameter GridFormat)
{
	char                          chdouble[16] = {0};

	//加载文件
	bool loadOkay = m_ParameterXml.LoadFile(m_strPath);
	if (loadOkay != true)
	{
		return S_FALSE;
	}

	//获得根元素
	TiXmlElement * rootElement = m_ParameterXml.FirstChildElement();

	//创建一个元素
	TiXmlElement * pParameter = new TiXmlElement(GRID_GridParameter);

	//FRame
	TiXmlElement * pFRame = new TiXmlElement(GRID_Frame);
	TiXmlText * pFrameText = new TiXmlText(GridFormat.szFrame);
	pFRame->LinkEndChild(pFrameText);

	//DB_XN
	TiXmlElement * pDB_XN = new TiXmlElement(GRID_DB_XN);
	sprintf(chdouble, "%.10f", GridFormat.DB_XN);
	TiXmlText * pDB_XNText = new TiXmlText(chdouble);
	pDB_XN->LinkEndChild(pDB_XNText);

	//DL_XN
	TiXmlElement * pDL_XN = new TiXmlElement(GRID_DL_XN);
	memset(chdouble, '\0', sizeof(chdouble));
	sprintf(chdouble, "%.10f", GridFormat.DL_XN);
	TiXmlText * pDL_XNText = new TiXmlText(chdouble);
	pDL_XN->LinkEndChild(pDL_XNText);

	//DB_XB
	TiXmlElement * pDB_XB = new TiXmlElement(GRID_DB_XB);
	memset(chdouble, '\0', sizeof(chdouble));
	sprintf(chdouble, "%.10f", GridFormat.DB_XB);
	TiXmlText * pDB_XBText = new TiXmlText(chdouble);
	pDB_XB->LinkEndChild(pDB_XBText);

	//DL_XB
	TiXmlElement * pDL_XB = new TiXmlElement(GRID_DL_XB);
	memset(chdouble, '\0', sizeof(chdouble));
	sprintf(chdouble, "%.10f", GridFormat.DL_XB);
	TiXmlText * pDL_XBText = new TiXmlText(chdouble);
	pDL_XB->LinkEndChild(pDL_XBText);

	//DB_DB
	TiXmlElement * pDB_DB = new TiXmlElement(GRID_DB_DB);
	memset(chdouble, '\0', sizeof(chdouble));
	sprintf(chdouble, "%.10f", GridFormat.DB_DB);
	TiXmlText * pDB_DBText = new TiXmlText(chdouble);
	pDB_DB->LinkEndChild(pDB_DBText);

	//DL_DB
	TiXmlElement * pDL_DB = new TiXmlElement(GRID_DL_DB);
	memset(chdouble, '\0', sizeof(chdouble));
	sprintf(chdouble, "%.10f", GridFormat.DL_DB);
	TiXmlText * pDL_DBText = new TiXmlText(chdouble);
	pDL_DB->LinkEndChild(pDL_DBText);

	//DB_DN
	TiXmlElement * pDB_DN = new TiXmlElement(GRID_DB_DN);
	memset(chdouble, '\0', sizeof(chdouble));
	sprintf(chdouble, "%.10f", GridFormat.DB_DN);
	TiXmlText * pDB_DNText = new TiXmlText(chdouble);
	pDB_DN->LinkEndChild(pDB_DNText);

	//DL_DN
	TiXmlElement * pDL_DN = new TiXmlElement(GRID_DL_DN);
	memset(chdouble, '\0', sizeof(chdouble));
	sprintf(chdouble, "%.10f", GridFormat.DL_DN);
	TiXmlText * pDL_DNText = new TiXmlText(chdouble);
	pDL_DN->LinkEndChild(pDL_DNText);

	pParameter->LinkEndChild(pFRame);
	pParameter->LinkEndChild(pDB_XN);
	pParameter->LinkEndChild(pDL_XN);
	pParameter->LinkEndChild(pDB_XB);
	pParameter->LinkEndChild(pDL_XB);
	pParameter->LinkEndChild(pDB_DB);
	pParameter->LinkEndChild(pDL_DB);
	pParameter->LinkEndChild(pDB_DN);
	pParameter->LinkEndChild(pDL_DN);
	rootElement->LinkEndChild(pParameter);

	m_ParameterXml.SaveFile();

	return S_OK;
}

HRESULT CGridParameter::GetGridParametersByXml(std::vector<GridParameter> * pGetGridParameterList)
{ 
	const char *                  chVal = NULL;
	const char *                  chItem = NULL;
	TiXmlElement *                rootElement = NULL;
	TiXmlElement *                ParameterElement = NULL;
	TiXmlElement *                itemElement = NULL;
	GridParameter                 GridFormat;

/*	bool loadOkay = m_ParameterXml.LoadFile();
	if (loadOkay != true)
	{
		return S_FALSE;
	}*/

	//获得根元素
	rootElement = m_ParameterXml.FirstChildElement();
	ParameterElement = rootElement->FirstChildElement();

	while (ParameterElement != NULL)
	{
		itemElement = ParameterElement->FirstChildElement();
		while (itemElement != NULL)
		{
			chItem = itemElement->ToElement()->Value();
			chVal = itemElement->FirstChild()->Value();

			if (strcmp(chItem, GRID_Frame) == 0) 
			{
				strcpy(GridFormat.szFrame, chVal);
			}
			else if(strcmp(chItem, GRID_DB_DB) == 0)
			{
				GridFormat.DB_DB = atof(chVal);
			}
			else if(strcmp(chItem, GRID_DB_DN) == 0)
			{
				GridFormat.DB_DN = atof(chVal);
			}
			else if(strcmp(chItem, GRID_DB_XB) == 0)
			{
				GridFormat.DB_XB = atof(chVal);
			}
			else if(strcmp(chItem, GRID_DB_XN) == 0)
			{
				GridFormat.DB_XN = atof(chVal);
			}
			else if(strcmp(chItem, GRID_DL_DB) == 0)
			{
				GridFormat.DL_DB = atof(chVal);
			}
			else if(strcmp(chItem, GRID_DL_DN) == 0)
			{
				GridFormat.DL_DN = atof(chVal);
			}
			else if(strcmp(chItem, GRID_DL_XB) == 0)
			{
				GridFormat.DL_XB = atof(chVal);
			}
			else if(strcmp(chItem, GRID_DL_XN) == 0)
			{
				GridFormat.DL_XN = atof(chVal);
			}

			itemElement = itemElement->NextSiblingElement();
		}

		pGetGridParameterList->push_back(GridFormat);
		ParameterElement = ParameterElement->NextSiblingElement();
	}

	return S_OK;
}