// DlgEllipManager.cpp : 实现文件
//

#include "stdafx.h"
#include "DeuDlgEllipManager.h"
#include "DeuAddGeodeticDlg.h"
#include "DeuAddProjectedDlg.h"

#define Coordinate _T("CoordinateSystems")

// CDeuDlgEllipManager 对话框
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

// CDeuDlgEllipManager 消息处理程序
void CDeuDlgEllipManager::OnBnClickedBtnFile()
{
	CFileDialog      FileDialog(true, _T("坐标系"), _T("*.prj"), OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, _T("坐标系(*.prj)"), NULL);
	std::string      strPath;
	std::string      strEllipName;
	TiXmlDocument    ParameterXml;
	char             szFilePath[MAX_PATH+1] = {0};
	std::string      strEllipPath;

	//获得坐标系的文件存储路径
    ::GetModuleFileName(NULL, szFilePath, MAX_PATH);
	strEllipPath = szFilePath;
	int ipos = strEllipPath.rfind(_T("\\"), strEllipPath.length()-1);
	strEllipPath = strEllipPath.substr(0, ipos);
	strEllipPath = strEllipPath + _T("\\") + Coordinate;

	FileDialog.m_ofn.lpstrInitialDir = strEllipPath.c_str();
	FileDialog.m_ofn.lpstrTitle = _T("选择坐标系");
	if(FileDialog.DoModal() == IDOK)
	{
		m_strEllipName = FileDialog.GetFileName();
		int i = m_strEllipName.Find(_T("."));
		m_strEllipName = m_strEllipName.Left(i);
		strEllipName = m_strEllipName;

		//将选择的文件写进日志文件
		/*
        GetXmlPath(&strPath);
		bool loadOkay = ParameterXml.LoadFile(strPath);
		if (loadOkay != true)
		{
			//创建
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

	//防止文件名中包含多个'.'
	//int i = m_strEllipName.Find(_T("."));
	int i = m_strEllipName.ReverseFind('.');
	m_strEllipName = m_strEllipName.Left(i);

	OnOK();
}

BOOL CDeuDlgEllipManager::OnInitDialog()
{
	CDialog::OnInitDialog();

	//m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_List.InsertColumn(0, _T("坐标系名"), LVCFMT_CENTER, 380);
	//DispChoiceByXml();

	if(m_bManager == FALSE)
	{
		m_ctlGeographic.ShowWindow(SW_HIDE);
		m_ctlProjected.ShowWindow(SW_HIDE);		
	}

	//获得对应的运行环境值
    GetEllipPath(&m_EllipPath);

	//对树木控件做处理
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

	//获得EXE的运行路径
	::GetModuleFileName(NULL, szFilePath, MAX_PATH);
	strSysInfoPath = szFilePath;
	int ipos = strSysInfoPath.rfind(_T("\\"), strSysInfoPath.length()-1);
	strSysInfoPath = strSysInfoPath.substr(0, ipos+1);

	//创建一个空的xml
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

	//插入之前先做删除处理 遍历xml 查找是否有和已经名称一致的历史记录 有则删除
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

	//获得根元素
	//TiXmlElement * rootElement = ParameterXml.FirstChildElement();

	//创建一个元素
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

	//获得根元素
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

//构建坐标系管理树的相关代码
HRESULT CDeuDlgEllipManager::GetEllipPath(std::string * pEllipPath)
{
	char                                    szFilePath[MAX_PATH+1] = {0};
	std::string                             strEllipPath;

	//获得坐标系的文件存储路径
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

//获得每一个节点在文件系统中对应的path
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

	//获得当前EXE的运行路径
    GetEllipPath(&EllipPath);
    * pFilePath = EllipPath + _T("\\") + FilePath;

	return S_OK;
}

//往树中增加一个节点
HRESULT CDeuDlgEllipManager::ApendNode(HTREEITEM hParentItem, std::string NodeName)
{
    HTREEITEM hItem = NULL;
	hItem = m_ViewTree.InsertItem(NodeName.c_str(), hParentItem);
	ApendNullNode(hItem);

	return S_OK;
}

//增加一个空节点
HRESULT	CDeuDlgEllipManager::ApendNullNode(HTREEITEM hParentItem)
{
    m_ViewTree.InsertItem(_T(""), hParentItem, TVI_LAST);

	return S_OK;
}

//删除父亲节点下的所有子节点
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
	//::MapWindowPoints(HWND_DESKTOP,pNMHDR->hwndFrom, &ht.pt, 1); //把屏幕坐标转换成控件坐标
	//TreeView_HitTest(pNMHDR->hwndFrom, &ht);				     //确定点击的是哪一项

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


