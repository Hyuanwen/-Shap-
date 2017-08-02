#pragma once


#include "resource.h"

#include "DeuVectorTranDlg.h"
#include "DeuRasterTranDlg.h"
#include "DeuVectorProjectTranDlg.h"
#include "DeuRasterProjectTranDlg.h"

//修改处
#include "DeuComboBox.h "



class CDeuDlgFiles : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CDeuDlgFiles)

public:
	CDeuDlgFiles(TranformType _ParentType=VECTOR, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgFiles();

// 对话框数据
	enum { IDD = IDD_DLG_FILE };

	//修改处
	CMRUComboBox	m_combo;
	//修改处
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnExplorer();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedBtnOk();

	afx_msg void OnSelchangeCombo1();

	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecords;	

	void FindFile(char *p_find);

	CDeuVectorTranDlg* p_Parent_Vector;
	CDeuRasterTranDlg* p_Parent_Raster;
	CDeuVectorProjectTranDlg* p_Parent_Vector_Prj;
	CDeuRasterProjectTranDlg* p_Parent_Raster_Prj;

//修改处
public:
	CString strFolderPath;
	char m_szInitDir[_MAX_PATH];

public:
	CXTPReportControl m_wndFileCtrl;
	char dir[MAX_PATH];
	CString strFileType, strLastPath, strLastPath_In;
	TranformType _TType;

	HANDLE m_thread;
	DataSrcType _DataSrc;
	
	CCheckListBox m_Listbox;
	CButton m_Checkbtn;

	void SaveSelectFiles();
	void InsertListBox(char *p_find, char* filename, int nIndex);

	HRESULT SHPathToPIDL(LPCTSTR szPath, LPITEMIDLIST* ppidl);

	
public:
		template<class T>
		void LoadList(T p_dlg)
		{
					
			if((p_dlg->_FilsList.GetCount() > 0) 
				&& (p_dlg->_FilsList_selected.GetCount() > 0))
			{
				for(int n=0; n<p_dlg->_FilsList.GetCount(); n++)
				{
					m_Listbox.InsertString(n, p_dlg->_FilsList.GetAt(n));
					for(int m=0; m<p_dlg->_FilsList_selected.GetCount(); m++)
					{
						if(p_dlg->_FilsList_selected.GetAt(m) == p_dlg->_FilsList.GetAt(n))
							m_Listbox.SetCheck(n, 1);
					}
				}
			}
			else if((p_dlg->_FilsList.GetCount() > 0) 
				&& (p_dlg->_FilsList_selected.GetCount() == 0))
			{
				for(int n=0; n<p_dlg->_FilsList.GetCount(); n++)
				{
					m_Listbox.InsertString(n, p_dlg->_FilsList.GetAt(n));
				}
			}
			else if((p_dlg->_FilsList.GetCount() == 0) 
				&& (p_dlg->_FilsList_selected.GetCount() > 0))
			{
				for(int m=0; m<p_dlg->_FilsList_selected.GetCount(); m++)
				{
					m_Listbox.InsertString(m, p_dlg->_FilsList_selected.GetAt(m));
					m_Listbox.SetCheck(m, 1);
				}
			}
		}
};
