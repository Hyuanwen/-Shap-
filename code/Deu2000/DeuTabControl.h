#pragma once


class CDeuTabControl : public CXTPTabControl
{
	DECLARE_DYNAMIC(CDeuTabControl)

public:
	CDeuTabControl();
	virtual ~CDeuTabControl();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnNavigateButtonClick(CXTPTabManagerNavigateButton* pButton);

public:
	char sz_Type[20];
	CWnd* pPanelWnd;

};


