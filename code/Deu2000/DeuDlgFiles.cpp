// DeuDlgFiles.cpp : 实现文件
//

#include "stdafx.h"
#include "DeuDlgFiles.h"
#include "DeuGlobal.h"

//修改处
#include "stdlib.h"
#include "direct.h"
#include "io.h"


// CDeuDlgFiles 对话框
IMPLEMENT_DYNAMIC(CDeuDlgFiles, CXTResizeDialog)

CDeuDlgFiles::CDeuDlgFiles(TranformType _ParentType, CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CDeuDlgFiles::IDD, pParent)
{
	_TType = _ParentType;
	switch (_ParentType)
	{
	case VECTOR:
		p_Parent_Vector = (CDeuVectorTranDlg*)pParent;
		break;
	case  VECTOR_PROJ:
		p_Parent_Vector_Prj = (CDeuVectorProjectTranDlg*)pParent;
		break;

	case RASTER:
		p_Parent_Raster = (CDeuRasterTranDlg*)pParent;
		break;

	case RASTER_PROJ:
		p_Parent_Raster_Prj = (CDeuRasterProjectTranDlg*)pParent;
		break;

	}
	
}

CDeuDlgFiles::~CDeuDlgFiles()
{
}

void CDeuDlgFiles::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);	
	DDX_Control(pDX, IDC_LIST_FILES, m_Listbox);
	DDX_Control(pDX, IDC_CHECK1, m_Checkbtn);
	DDX_Control(pDX, IDC_COMBO_PATH, m_combo);
}


BEGIN_MESSAGE_MAP(CDeuDlgFiles, CXTResizeDialog)
	ON_BN_CLICKED(IDC_BTN_EXPLORER, &CDeuDlgFiles::OnBnClickedBtnExplorer)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECK1, &CDeuDlgFiles::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BTN_OK, &CDeuDlgFiles::OnBnClickedBtnOk)
	
	ON_CBN_SELCHANGE(IDC_COMBO_PATH, OnSelchangeCombo1)

	ON_WM_CLOSE()
END_MESSAGE_MAP()




const int COLUMN_MAIL_ICON   =  0;
const int COLUMN_CHECK_ICON  =  2;

// CDeuDlgFiles 消息处理程序

BOOL CDeuDlgFiles::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	//修改处
	m_combo.SetMRURegKey ( _T("Combobox MRU") );
    m_combo.SetMRUValueFormat ( _T("File #%d") );

	m_combo.SetAutoRefreshAfterAdd ( TRUE );
    m_combo.SetAutoSaveAfterAdd ( TRUE );

    m_combo.LoadMRU();
	m_combo.SetMaxMRUSize ( 10 );
    m_combo.RefreshCtrl();

	ZeroMemory(dir, sizeof(dir));
	//m_Checkbtn.SetCheck(1);

	//保存最近一次的路径记录，并查找对应的文件记录
	if(!strLastPath.IsEmpty())
	{
		lstrcpy(dir, strLastPath);
		CStatic* p_path = (CStatic*)GetDlgItem(IDC_COMBO_PATH);
		p_path->SetWindowText(strLastPath);
		while(m_Listbox.GetCount() > 0)
		{
			m_Listbox.DeleteString(0);
		}

		//加载已经遍历到的文件
		//this->FindFile(strLastPath.GetBuffer());

		

		switch (_TType)
		{
		case VECTOR:
			{			
				LoadList( p_Parent_Vector );
			}
			break;
		case VECTOR_PROJ:
			{
				LoadList( p_Parent_Vector_Prj );
			}
			break;
		case RASTER:
			{
				LoadList( p_Parent_Raster );
			}
			break;
		case RASTER_PROJ:
			{
				LoadList( p_Parent_Raster_Prj ); 
			}
			break;
		default:
			break;
		}

		//==================================



		//----------------------------------

		int n=m_Listbox.GetCount();
		if(n == 0)
		{
			m_Listbox.AddString("暂无对应文件");
		}
	}

	SetResize(IDC_COMBO_PATH, SZ_TOP_LEFT, SZ_TOP_RIGHT);
	SetResize(IDC_LIST_FILES, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);

	//将外部传进来的路径赋值给内部的临时变量
	strLastPath_In = strLastPath;

	return TRUE;
}

void WINAPI FindFile(CDeuDlgFiles* pwnd);

int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)   
{
	if(uMsg == BFFM_INITIALIZED)
	{   

		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);

	}

	return 0;   
} 

void CDeuDlgFiles::OnBnClickedBtnExplorer()
{
	//char Tmpdir[MAX_PATH];
	//AfxSelectDirDlg(Tmpdir);

/*	CString									strPath = _T("");
	int										nPos(0);
	::GetModuleFileName(NULL, strPath.GetBufferSetLength(MAX_PATH+1), MAX_PATH);
	strPath.ReleaseBuffer();

	nPos = strPath.ReverseFind('\\');
	strPath = strPath.Left(nPos);
	strPath=strPath+"\\Path.ini";

	char path[MAX_PATH]=_T("");
	LPITEMIDLIST ppidl=NULL;
	GetPrivateProfileString(_T("SECTION"),_T("Path"),NULL,path,sizeof(path),(LPCTSTR)strPath);

	LPSHELLFOLDER  IpsfDeskTop;
	HRESULT hres;
	ULONG ulEaten,ulAttribe;
	SHGetDesktopFolder(&IpsfDeskTop);
	TCHAR     Wpath[MAX_PATH*2];
	MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,path,MAX_PATH,(LPWSTR)Wpath,MAX_PATH*2);
	LPWSTR    PsePath=(LPWSTR)Wpath;
	hres=IpsfDeskTop->ParseDisplayName(NULL,NULL,PsePath,&ulEaten,&ppidl,&ulAttribe);
	hres=IpsfDeskTop->Release();
	if (FAILED(hres))
	{
		ppidl=NULL;
	}
*/

	//修改处 
	BROWSEINFO br;
	CString strFolderPath;
	char Buffer[MAX_PATH];
	br.hwndOwner=m_hWnd;
	br.iImage=NULL;
	br.lParam=0;
	br.lpfn=NULL;
	br.lpfn = BrowseCallbackProc;
	br.lpszTitle="选择要修改的文件";
	br.pidlRoot=NULL;
	br.pszDisplayName=Buffer;
    br.ulFlags = BIF_EDITBOX|BIF_NEWDIALOGSTYLE;   

	memset(Buffer, '\0', sizeof(Buffer));

	//处理一下 begin
	CFileFind   finder;

	if(finder.FindFile(strLastPath_In)==FALSE) 
	{
		br.lParam =0;

		br.lpfn = NULL;
	} 
	else
	{
		br.lParam = (long)(strLastPath_In.GetBuffer(strLastPath_In.GetLength()));

		br.lpfn = BrowseCallbackProc;
	}
	//处理一下 pidlRoot 需要获得一个原有路径的LPITEMIDLIST end

	LPITEMIDLIST lpPath=SHBrowseForFolder(&br);

/*    ppidl=lpPath;
	if (ppidl!=NULL)
	{	
		SHGetPathFromIDList(ppidl,path);
	    WritePrivateProfileString(_T("SECTION"),_T("Path"),path,(LPCSTR)strPath);
	}

*/

	if (lpPath)
	{
		SHGetPathFromIDList(lpPath,Buffer);
		strFolderPath=Buffer;
		SetDlgItemText(IDC_COMBO_PATH,strFolderPath);
		strLastPath_In = strFolderPath;
	}
	
	if(strlen(Buffer) != 0)
	{
		/*CStatic* p_path = (CStatic*)GetDlgItem(IDC_STATIC_PATH);
		p_path->SetWindowText(Buffer);*/	

		while(m_Listbox.GetCount() > 0)
		{
			m_Listbox.DeleteString(0);
		}
		
		strcpy(dir, Buffer);
		//加载遍历到的文件
		this->FindFile(Buffer);

		int n=m_Listbox.GetCount();
		if(n == 0)
		{
			m_Listbox.AddString("暂无对应文件");
		}
		/*else
		{

			n = n-1;
			while(n >= 0)
			{
				m_Listbox.SetCheck(n, 1);
				n--;
			}
		}*/
	}
} 

//yzg 增加选址路径的记忆功能 2013-2-1 begin
HRESULT CDeuDlgFiles::SHPathToPIDL(LPCTSTR szPath, LPITEMIDLIST* ppidl)
{
	LPSHELLFOLDER pShellFolder = NULL;
	OLECHAR wszPath[MAX_PATH] = {0};
	ULONG nCharsParsed = 0;

	// Get an IShellFolder interface pointer
	HRESULT hr = SHGetDesktopFolder(&pShellFolder);
	if(FAILED(hr))
		return hr;

	// Convert the path name to Unicode
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szPath, -1, wszPath, MAX_PATH);

	// Call ParseDisplayName() to do the job
	hr = pShellFolder->ParseDisplayName(NULL, NULL, wszPath, &nCharsParsed, ppidl, NULL);

	// Clean up
	pShellFolder->Release();
	return hr;
}
//yzg 增加选址路径的记忆功能 2013-2-1 end



void CDeuDlgFiles::FindFile(char *p_find)
{
	//CDeuDlgFiles* pwnd = (CDeuDlgFiles*)lpParam;
	
	int num=0;
	char sz_find[MAX_PATH];	
	char szFile[MAX_PATH];
	WIN32_FIND_DATA FindFileData;

	strcpy(sz_find, p_find);
	strcat(sz_find, "\\*.*");

	HANDLE hFind = ::FindFirstFile(sz_find, &FindFileData);

	CString str, m_str2;

	int n = 0;
	while(TRUE)
	{

		//如果是文件夹
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(FindFileData.cFileName[0] != '.')
			{
				//找到的包含文件夹
				strcpy(szFile, p_find);
				strcat(szFile, "\\");
				strcat(szFile, FindFileData.cFileName);
				//strcat(p_find, szFile);
				FindFile(szFile);
			}
		}
		else
		{
			char *pdest = FindFileData.cFileName;
			m_str2 =  FindFileData.cFileName;

			str = strrchr(pdest, '.');
			str.Replace(".", "");
			
			//add by chenyong 2014-1-17 不区分大小写文件扩展名
			str = str.MakeLower();
			
			if(strFileType.Compare(sz_TranType_Vector[0]) == 0)
			{
				if(str == "shp")
				{
					InsertListBox(p_find, FindFileData.cFileName, n);
				}
			}
			else if(strFileType.Compare(sz_TranType_Vector[1]) == 0)
			{
				if(str == "mif" || str == "tab")
				{
					InsertListBox(p_find, FindFileData.cFileName, n);
				}
			}
			else if(strFileType.Compare(sz_TranType_Vector[2]) == 0) //DXF
			{
				if(str == "dxf")
				{
					InsertListBox(p_find, FindFileData.cFileName, n);
				}
			}
			else if(strFileType.Compare(sz_TranType_Vector[3]) == 0)	//AVCE00
			{
				if(str == "e00")
				{
					InsertListBox(p_find, FindFileData.cFileName, n);
				}
			}
			else if(strFileType.Compare(sz_TranType_Vector[4]) == 0) //oracle
			{

			}
			else if ( strFileType.Compare(sz_TranType_Vector[5]) == 0 )
			{
				if( str == "xlsx" || str == "xls" )
				{
					InsertListBox(p_find, FindFileData.cFileName, n);
				}
			}
			else if ( strFileType.Compare(sz_TranType_Vector[6]) == 0 )
			{
				if( str == "adf"&&num==0  )
				{
					InsertListBox(p_find, FindFileData.cFileName, n);
					num++;
				}
			}
			else if(strFileType.Compare(sz_TranType_Raster[0]) == 0)
			{
				if(str == "tif")
				{
					InsertListBox(p_find, FindFileData.cFileName, n);
				}
			}
			else if(strFileType.Compare(sz_TranType_Raster[1]) == 0)
			{
				if(str == "img")
				{
					InsertListBox(p_find, FindFileData.cFileName, n);
				}
			}
			else if(strFileType.Compare(sz_TranType_Raster[2]) == 0)
			{
				if(str == "bil")
				{
					InsertListBox(p_find, FindFileData.cFileName, n);
				}
			}
			else if(strFileType.Compare(sz_TranType_Raster[3]) == 0)
			{
				if(str == "asc")
				{
					InsertListBox(p_find, FindFileData.cFileName, n);
				}
			}
			else if(strFileType.Compare(sz_TranType_Raster[4]) == 0)
			{
				if(str == "bmp")
				{
					InsertListBox(p_find, FindFileData.cFileName, n);
				}
			}

			n++;
		}

		if(!FindNextFile(hFind, &FindFileData)) break;

	}

	if ( INVALID_HANDLE_VALUE != hFind )
	{
		::FindClose(hFind);
	}
	
}


void CDeuDlgFiles::InsertListBox(char *p_find, char* filename, int nIndex)
{
	char sz_tmp[MAX_PATH];
	char sz_tmpnew[MAX_PATH];
	ZeroMemory(sz_tmp, sizeof(sz_tmp));
	ZeroMemory(sz_tmpnew, sizeof(sz_tmpnew));

	if ( strFileType.Compare(sz_TranType_Vector[6]) == 0 )
	{
		strcpy(sz_tmp, p_find);
	}
	else
	{	
		strcpy(sz_tmp, p_find);
		strcat(sz_tmp, "\\");
		strcat(sz_tmp, filename);
		strcat(sz_tmp,  "\0\0");
	}


	m_Listbox.AddString(sz_tmp);
	
	#define ListAdd(obj) obj->_FilsList.Add(sz_tmp);

	switch (_TType)
	{
	case VECTOR:
		{
			ListAdd(p_Parent_Vector);
		}
		break;	
	case VECTOR_PROJ:
		{
			ListAdd(p_Parent_Vector_Prj);
		}
		break;
	case RASTER:
		{
			ListAdd(p_Parent_Raster);
		}
		break;
	case RASTER_PROJ:
		{
			ListAdd(p_Parent_Raster_Prj);
		}
		break;
	default:
		break;
	}

}


//大小
void CDeuDlgFiles::OnSize(UINT nType, int cx, int cy)
{
	CButton* p_btn = (CButton*)this->GetDlgItem(IDC_BTN_EXPLORER);
	CButton* p_btnok = (CButton*)this->GetDlgItem(IDC_BTN_OK);
	if(p_btn->GetSafeHwnd())
	{
		CXTResizeDialog::OnSize(nType, cx, cy);

		CRect rc, btnRc;
		this->GetWindowRect(&rc);
		p_btnok->GetWindowRect(&btnRc);

		//确认按钮
		int nWidth = btnRc.Width();
		btnRc.left = rc.right-nWidth-10;
		btnRc.right = rc.right-10;		
		ScreenToClient(&btnRc);		
		p_btnok->MoveWindow(btnRc, 1);
		p_btnok->Invalidate();

		//浏览按钮
		p_btn->GetWindowRect(&btnRc);
		int nWidth2 = btnRc.Width();
		btnRc.left = rc.right-nWidth-nWidth2-18;
		btnRc.right = rc.right-nWidth2-18;		
		ScreenToClient(&btnRc);		
		p_btn->MoveWindow(btnRc, 1);
		p_btn->Invalidate();

		m_Checkbtn.GetWindowRect(&btnRc);
		int nHeight = btnRc.Height();
		btnRc .top = rc.bottom - nHeight - 10;
		btnRc.bottom = rc.bottom - 10;
		ScreenToClient(&btnRc);	
		m_Checkbtn.MoveWindow(&btnRc);
	}

	
}

void CDeuDlgFiles::OnBnClickedCheck1()
{
	int n=m_Listbox.GetCount();
	if(m_Checkbtn.GetCheck())
	{
		while(n >= 0)
		{
			m_Listbox.SetCheck(n, 1);
			n--;
		}
	}
	else
	{
		while(n >= 0)
		{
			m_Listbox.SetCheck(n, 0);
			n--;
		}
	}
}

void CDeuDlgFiles::OnBnClickedBtnOk()
{
	//修改处
	CFileFind find;
	CString   cstrFile;

    m_combo.GetWindowText( cstrFile );
	 
    if ( find.FindFile( cstrFile ) )
        {
        find.FindNextFile();
        SetDlgItemInt ( IDC_STATIC, find.GetLength(), FALSE );
        m_combo.AddToMRU ( cstrFile );
        }
    else
        {
        SetDlgItemText ( IDC_STATIC, _T("<error>") );
        }

	if(strlen(dir) != 0)
	{
		strLastPath.Format("%s", dir);
	}
	else
	{
		strLastPath = "";
	}

	SaveSelectFiles();
	this->OnOK();
}


//窗口关闭
void CDeuDlgFiles::OnClose()
{
	SaveSelectFiles();
	
	CXTResizeDialog::OnClose();

}

//保存已经选中的文件
void CDeuDlgFiles::SaveSelectFiles()
{

	switch (_TType)
	{
	case VECTOR:
		{
			p_Parent_Vector->_FilsList_selected.RemoveAll();
		}
		break;
	case VECTOR_PROJ:
		{
			p_Parent_Vector_Prj->_FilsList_selected.RemoveAll();
		}
		break;
	case RASTER:
		{
			p_Parent_Raster->_FilsList_selected.RemoveAll();
		}
		break;
	case RASTER_PROJ:
		{
			p_Parent_Raster_Prj->_FilsList_selected.RemoveAll();
		}
		break;
	default:
		break;
	}


	CString m_str;
	int n = m_Listbox.GetCount()-1;
	while(n >= 0)
	{
		if(m_Listbox.GetCheck(n))
		{
			m_Listbox.GetText(n, m_str);
			switch (_TType)
			{
			case VECTOR:
				{
					p_Parent_Vector->_FilsList_selected.Add(m_str);
				}
				break;
			case VECTOR_PROJ:
				{
					p_Parent_Vector_Prj->_FilsList_selected.Add(m_str);
				}
				break;

			case RASTER:
				{
					p_Parent_Raster->_FilsList_selected.Add(m_str);
				}
				break;
			case RASTER_PROJ:
				{
					p_Parent_Raster_Prj->_FilsList_selected.Add(m_str);
				}
				break;

			}
		}
		n--;
	}
	
}

BOOL CDeuDlgFiles::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    //if(IsDlgButtonChecked(IDC_SEX1))　
	//if (pMsg->message == WM_KEYDOWN)
	//{

	//	if (pMsg->wParam == VK_RETURN)
	//	{
	//		 OnGetSize();
	//	}
//	}

	 
	 


	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{    
			 int nID = IsDlgButtonChecked(IDC_BTN_OK);
			 if(nID == IDC_BTN_OK)
			 {
				 OnBnClickedBtnOk();
			 }
			 else  
			{
			     pMsg->wParam = VK_TAB;
				 OnBnClickedBtnOk();
			}
		}		
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDeuDlgFiles::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	//修改处
	char *cstrfile;
	int cursel = m_combo.GetCurSel();
	CString pzfile = m_combo.m_pMRU->m_arrNames[cursel];
	cstrfile = (char*)  pzfile.GetString();
 
		while(m_Listbox.GetCount() > 0)
		{
			m_Listbox.DeleteString(0);
		}
		
		//
		//加载遍历到的文件
		this->FindFile(cstrfile);

		int n=m_Listbox.GetCount();
		if(n == 0)
		{
			m_Listbox.AddString("暂无对应文件");
		}

	strcpy(dir,cstrfile);

	if(strlen(dir) != 0)
	{
		strLastPath.Format("%s", dir);
	}
	else
	{
		strLastPath = "";
	}

	SaveSelectFiles();
}

