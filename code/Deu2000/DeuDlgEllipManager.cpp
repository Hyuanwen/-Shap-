// DlgEllipManager.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DeuDlgEllipManager.h"
#include "DeuAddGeodeticDlg.h"
#include "DeuAddProjectedDlg.h"

#define Coordinate _T("CoordinateSystems")

// CDeuDlgEllipManager �Ի���
IMPLEMENT_DYNAMIC(CDeuDlgEllipManager, CDialog)
CDeuDlgEllipManager::CDeuDlgEllipManager(CWnd* pParent /*=NULL*/)
				   : CDialog(CDeuDlgEllipManager::IDD, pParent)
{
	m_bManager = FALSE;
}

CDeuDlgEllipManager::~CDeuDlgEllipManager()
{
}

void CDeuDlgEllipManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//	DDX_Control(pDX, IDC_LIST_ELLIP, m_List);
	DDX_Control(pDX, IDC_TREE_ELLIP, m_ViewTree);
	DDX_Control(pDX, IDC_BUTTON_Geographic, m_ctlGeographic);
	DDX_Control(pDX, IDC_BUTTON_PROJECTED, m_ctlProjected);
}

BEGIN_MESSAGE_MAP(CDeuDlgEllipManager, CDialog)
	ON_BN_CLICKED(IDC_BTN_FILE, &CDeuDlgEllipManager::OnBnClickedBtnFile)
	ON_BN_CLICKED(IDOK, &CDeuDlgEllipManager::OnBnClickedOk)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE_ELLIP, &CDeuDlgEllipManager::OnTvnItemexpandingTreeEllip)
	ON_BN_CLICKED(IDC_BUTTON_Geographic, &CDeuDlgEllipManager::OnBnClickedButtonGeographic)
	ON_BN_CLICKED(IDC_BUTTON_PROJECTED, &CDeuDlgEllipManager::OnBnClickedButtonProjected)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_ELLIP, &CDeuDlgEllipManager::OnNMRClickTreeEllip)
END_MESSAGE_MAP()

// CDeuDlgEllipManager ��Ϣ�������
void CDeuDlgEllipManager::OnBnClickedBtnFile()
{
	CFileDialog      FileDialog(true, _T("����ϵ"), _T("*.prj"), OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, _T("����ϵ(*.prj)"), NULL);
	std::string      strPath;
	std::string      strEllipName;
	TiXmlDocument    ParameterXml;
	char             szFilePath[MAX_PATH+1] = {0};
	std::string      strEllipPath;

	//�������ϵ���ļ��洢·��
    ::GetModuleFileName(NULL, szFilePath, MAX_PATH);
	strEllipPath = szFilePath;
	int ipos = strEllipPath.rfind(_T("\\"), strEllipPath.length()-1);
	strEllipPath = strEllipPath.substr(0, ipos);
	strEllipPath = strEllipPath + _T("\\") + Coordinate;

	FileDialog.m_ofn.lpstrInitialDir = strEllipPath.c_str();
	FileDialog.m_ofn.lpstrTitle = _T("ѡ������ϵ");
	if(FileDialog.DoModal() == IDOK)
	{
		m_strEllipName = FileDialog.GetFileName();
		int i = m_strEllipName.Find(_T("."));
		m_strEllipName = m_strEllipName.Left(i);
		strEllipName = m_strEllipName;

		//��ѡ����ļ�д����־�ļ�
		/*
        GetXmlPath(&strPath);
		bool loadOkay = ParameterXml.LoadFile(strPath);
		if (loadOkay != true)
		{
			//����
            GreateXmlForSys(strPath);
			InsertRecordToXml(strPath, strEllipName);
		}
		else if (loadOkay == true)
		{
			InsertRecordToXml(strPath, strEllipName);
		}
		*/
	}

	//DispChoiceByXml();
}

void CDeuDlgEllipManager::OnBnClickedOk()
{
	HTREEITEM hSelectedItem = m_ViewTree.GetSelectedItem();
	m_strEllipName = m_ViewTree.GetItemText(hSelectedItem);

	//��ֹ�ļ����а������'.'
	//int i = m_strEllipName.Find(_T("."));
	int i = m_strEllipName.ReverseFind('.');
	m_strEllipName = m_strEllipName.Left(i);

	OnOK();
}

BOOL CDeuDlgEllipManager::OnInitDialog()
{
	CDialog::OnInitDialog();

	//m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_List.InsertColumn(0, _T("����ϵ��"), LVCFMT_CENTER, 380);
	//DispChoiceByXml();

	if(m_bManager == FALSE)
	{
		m_ctlGeographic.ShowWindow(SW_HIDE);
		m_ctlProjected.ShowWindow(SW_HIDE);		
	}

	//��ö�Ӧ�����л���ֵ
    GetEllipPath(&m_EllipPath);

	//����ľ�ؼ�������
	HTREEITEM hbootRoot = m_ViewTree.InsertItem(_T("CoordinateSystems"));
    ApendNullNode(hbootRoot);

    //m_ViewTree.InsertItem(_T("Geographic Coordinate Systems"), hbootRoot);
	//m_ViewTree.InsertItem(_T("Projected  Coordinate Systems"), hbootRoot);

	return TRUE;
}

HRESULT CDeuDlgEllipManager::GetXmlPath(std::string * pstrPath)
{
	char                 szFilePath[MAX_PATH+1] = {0};
	std::string          strFilePath;
	std::string          strSysInfoPath;
	std::string          strChoiceRecord(_T("ChoiceRecord.xml"));

	//���EXE������·��
	::GetModuleFileName(NULL, szFilePath, MAX_PATH);
	strSysInfoPath = szFilePath;
	int ipos = strSysInfoPath.rfind(_T("\\"), strSysInfoPath.length()-1);
	strSysInfoPath = strSysInfoPath.substr(0, ipos+1);

	//����һ���յ�xml
	*pstrPath = strSysInfoPath + strChoiceRecord;

	return S_OK;
}

HRESULT CDeuDlgEllipManager::GreateXmlForSys(std::string strFilePath)
{
	TiXmlDocument        ParameterXml;

	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
	TiXmlElement * element = new TiXmlElement( "ChoiceRecord" );
	TiXmlText * text = new TiXmlText( "" );
	element->LinkEndChild( text );
	ParameterXml.LinkEndChild( decl );
	ParameterXml.LinkEndChild( element );
	ParameterXml.SaveFile( strFilePath );

	return S_OK;
}

HRESULT CDeuDlgEllipManager::InsertRecordToXml(std::string strPath, std::string strChoice)
{
	TiXmlDocument         ParameterXml;
	TiXmlElement *        rootElement = NULL;
	TiXmlElement *        ParameterElement = NULL;
	const char *          chVal = NULL;

	bool loadOkay = ParameterXml.LoadFile(strPath);
	if (loadOkay != true)
	{
		return S_FALSE;
	}

	//����֮ǰ����ɾ������ ����xml �����Ƿ��к��Ѿ�����һ�µ���ʷ��¼ ����ɾ��
	rootElement = ParameterXml.FirstChildElement();
	if (rootElement == NULL)
	{
		return S_OK;;
	}

	ParameterElement = rootElement->FirstChildElement();
	if (ParameterElement == NULL)
	{
		return S_OK;
	}

	while(ParameterElement != NULL)
	{
		chVal = ParameterElement->FirstChild()->Value();

		if (chVal == strChoice)
		{
			ParameterXml.RemoveChild(ParameterElement);
			break;
		}

		ParameterElement = ParameterElement->NextSiblingElement();
	}

	//��ø�Ԫ��
	//TiXmlElement * rootElement = ParameterXml.FirstChildElement();

	//����һ��Ԫ��
	TiXmlElement * pParameter = new TiXmlElement(EllipseName);
	TiXmlText * pFrameText = new TiXmlText(strChoice);
	pParameter->LinkEndChild(pFrameText);

    rootElement->LinkEndChild(pParameter);
	ParameterXml.SaveFile(strPath);

	return S_OK;
}

HRESULT CDeuDlgEllipManager::DispChoiceByXml()
{
	std::string                             strFilePath;
	TiXmlDocument                           ParameterXml;
	TiXmlElement *                          rootElement = NULL;
	TiXmlElement *                          ParameterElement = NULL;
	const char *                            chVal = NULL;
	std::vector<string>                     ChoiceList;
	std::string                             strChoice;
	std::vector<string>::iterator           iter;

    GetXmlPath(&strFilePath);

	bool loadOkay = ParameterXml.LoadFile(strFilePath);
	if (loadOkay != true)
	{
		return S_FALSE;
	}

	//��ø�Ԫ��
	rootElement = ParameterXml.FirstChildElement();
    if (rootElement == NULL)
    {
		return S_OK;;
    }

	ParameterElement = rootElement->FirstChildElement();
	if (ParameterElement == NULL)
	{
		return S_OK;
	}

	while(ParameterElement != NULL)
	{
		chVal = ParameterElement->FirstChild()->Value();

		ParameterElement = ParameterElement->NextSiblingElement();

		ChoiceList.push_back(chVal);
	}

	for (iter = ChoiceList.begin(); iter != ChoiceList.end(); iter ++)
	{
		//m_List.InsertItem(0, iter->c_str());
	}

	return S_OK;
}

//��������ϵ����������ش���
HRESULT CDeuDlgEllipManager::GetEllipPath(std::string * pEllipPath)
{
	char                                    szFilePath[MAX_PATH+1] = {0};
	std::string                             strEllipPath;

	//�������ϵ���ļ��洢·��
	::GetModuleFileName(NULL, szFilePath, MAX_PATH);
	strEllipPath = szFilePath;
	int ipos = strEllipPath.rfind(_T("\\"), strEllipPath.length()-1);
	strEllipPath = strEllipPath.substr(0, ipos);
	//strEllipPath = strEllipPath + _T("\\") + Coordinate;

	* pEllipPath = strEllipPath;

	return S_OK;
}

void CDeuDlgEllipManager::OnTvnItemexpandingTreeEllip(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW                   pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	std::string                    FilePath;
	CDeuEllipList                  EllipList;
	std::vector<string>::iterator  iter;

	if (pNMTreeView->action == TVE_EXPAND)
	{
		HTREEITEM hSelected = pNMTreeView->itemNew.hItem;
        GetItemPath(hSelected, &FilePath);
        EllipList.GreateEllipList(FilePath);
		DelItemByParent(hSelected);

		for (iter = EllipList.m_EllipList.begin(); iter != EllipList.m_EllipList.end(); iter ++)
		{
			ApendNode(hSelected, iter->data());
		}
	}
	else if (pNMTreeView->action == TVE_COLLAPSE)
	{
		HTREEITEM hSelected = pNMTreeView->itemNew.hItem;
	}

	*pResult = 0;
}

//���ÿһ���ڵ����ļ�ϵͳ�ж�Ӧ��path
HRESULT CDeuDlgEllipManager::GetItemPath(const HTREEITEM hSelected, std::string * pFilePath)
{
    HTREEITEM                         hItem;
	std::string                       FilePath;
	std::string                       EllipPath;
	std::string                       tmpStr;

	FilePath = m_ViewTree.GetItemText(hSelected);
	hItem = m_ViewTree.GetParentItem(hSelected);

	if (hItem == NULL)
	{
		GetEllipPath(&EllipPath);
		* pFilePath = EllipPath + _T("\\") + FilePath;
		return S_OK;
	}

	while (hItem != NULL)
	{
		tmpStr = m_ViewTree.GetItemText(hItem);
		FilePath = tmpStr + _T("\\") + FilePath;
		hItem = m_ViewTree.GetParentItem(hItem);
	}

	//��õ�ǰEXE������·��
    GetEllipPath(&EllipPath);
    * pFilePath = EllipPath + _T("\\") + FilePath;

	return S_OK;
}

//����������һ���ڵ�
HRESULT CDeuDlgEllipManager::ApendNode(HTREEITEM hParentItem, std::string NodeName)
{
    HTREEITEM hItem = NULL;
	hItem = m_ViewTree.InsertItem(NodeName.c_str(), hParentItem);
	ApendNullNode(hItem);

	return S_OK;
}

//����һ���սڵ�
HRESULT	CDeuDlgEllipManager::ApendNullNode(HTREEITEM hParentItem)
{
    m_ViewTree.InsertItem(_T(""), hParentItem, TVI_LAST);

	return S_OK;
}

//ɾ�����׽ڵ��µ������ӽڵ�
HRESULT CDeuDlgEllipManager::DelItemByParent(HTREEITEM hParentItem)
{
	if (hParentItem == NULL)
	{
		return S_OK;
	}

	HTREEITEM			hChildItem = NULL;
	HTREEITEM			hTmpItem = NULL;

	hChildItem = m_ViewTree.GetChildItem(hParentItem);
	while (hChildItem != NULL)
	{
		hTmpItem = hChildItem;
		hChildItem = m_ViewTree.GetNextSiblingItem(hTmpItem);        
		m_ViewTree.DeleteItem(hTmpItem);
	} 

	return S_OK;
}
void CDeuDlgEllipManager::OnBnClickedButtonGeographic()
{
	CDeuAddGeodeticDlg adddlg;
	adddlg.DoModal();
}

void CDeuDlgEllipManager::OnBnClickedButtonProjected()
{
	CDeuAddProjectedDlg adddlg;
	adddlg.DoModal();
}

void CDeuDlgEllipManager::OnNMRClickTreeEllip(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	*pResult = 0;


	//CPoint m_point;
	//DWORD  dwpos = GetMessagePos();

	//TVHITTESTINFO ht = {0};   
	//ht.pt.x = GET_X_LPARAM(dwpos);
	//ht.pt.y = GET_Y_LPARAM(dwpos);
	//::MapWindowPoints(HWND_DESKTOP,pNMHDR->hwndFrom, &ht.pt, 1); //����Ļ����ת���ɿؼ�����
	//TreeView_HitTest(pNMHDR->hwndFrom, &ht);				     //ȷ�����������һ��

	//if(ht.hItem == hTreeGeoDetic)
	//{
	//	::GetCursorPos(&m_point);	
	//	m_menu.GetSubMenu(2)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, m_point.x, m_point.y, this);
	//}
	//else if(m_Treectrl.GetParentItem(ht.hItem) == hTreeGeoDetic)
	//{
	//	::GetCursorPos(&m_point);	
	//	m_menu.GetSubMenu(2)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, m_point.x, m_point.y, this);
	//}
	//else if(ht.hItem == hTreeProjected)
	//{
	//	::GetCursorPos(&m_point);	
	//	m_menu.GetSubMenu(3)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, m_point.x, m_point.y, this);
	//}
	//else if(m_Treectrl.GetParentItem(ht.hItem) == hTreeProjected)
	//{
	//	::GetCursorPos(&m_point);	
	//	m_menu.GetSubMenu(3)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, m_point.x, m_point.y, this);
	//}
}


