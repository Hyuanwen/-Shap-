// XTPPropertyGridItemOption.h interface for the CXTPPropertyGridItemOption class.
//
// This file is a part of the XTREME PROPERTYGRID MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

//{{AFX_CODEJOCK_PRIVATE
#if !defined(__XTPPROPERTYGRIDITEMOPTION_H__)
#define __XTPPROPERTYGRIDITEMOPTION_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//===========================================================================
// Summary:
//     CXTPPropertyGridItemOption is a CXTPPropertyGridItem derived class.
//===========================================================================
class _XTP_EXT_CLASS CXTPPropertyGridItemOption : public CXTPPropertyGridItem
{
	DECLARE_DYNAMIC(CXTPPropertyGridItemOption)
public:

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPPropertyGridItemOption object.
	// Parameters:
	//     strCaption - Caption of the item.
	//     nID        - Identifier of the item.
	//     nValue     - Initial value for this item.
	//     pBindOption - If not NULL, then the value of this item
	//                  is bound the value of this variable.
	// Remarks:
	//     Class CXTPPropertyGridItemOption has no default constructor.
	//
	//          When using the second constructor, the Identifier (nID) of the
	//          second constructor can be linked with a STRINGTABLE resource
	//          with the same id in such form "Caption\\nDescription".
	//
	//          BINDING:
	//            Variables can be bound to an item in two ways, the first is
	//            to pass in a variable at the time of creation, the second allows
	//            variables to be bound to an item after creation with the
	//            BindToOption member.
	//
	//            Bound variables store the values of the property grid items
	//            and can be accessed without using the property grid methods
	//            and properties.  Bound variables allow the property grid to
	//            store data in variables.  When the value of a PropertyGridItem
	//            is changed, the value of the bound variable will be changed to
	//            the PropertyGridItem value.  The advantage of binding is that
	//            the variable can be used and manipulated without using
	//            PropertyGridItem methods and properties.
	//
	//            NOTE:  If the value of the variable is changed without using
	//            the PropertyGrid, the PropertyGridItem value will not be
	//            updated until you call CXTPPropertyGrid::Refresh.
	// See Also: BindToOption
	//-----------------------------------------------------------------------
	CXTPPropertyGridItemOption(LPCTSTR strCaption, int nValue = 0, int* pBindOption = NULL);
	CXTPPropertyGridItemOption(UINT nID, int nValue = 0, int* pBindOption = NULL);  // <COMBINE CXTPPropertyGridItemColor::CXTPPropertyGridItemColor@LPCTSTR@int@int*>

	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CXTPPropertyGridItemOption object
	//-----------------------------------------------------------------------
	virtual ~CXTPPropertyGridItemOption();

public:
	void SetOption(int nValue);
	void BindToOption(int* pBindOption);
	int GetOption() const;

	void SetCheckBoxStyle(BOOL bCheckBoxStyle = TRUE);
	BOOL IsCheckBoxStyle() const;

protected:
	void OnBeforeInsert();
	void SetValue(CString strValue);

	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	BOOL OnDrawItemValue(CDC& dc, CRect /*rcValue*/);
	void OnLButtonDblClk(UINT /*nFlags*/, CPoint /*point*/);
	BOOL OnLButtonDown(UINT nFlags, CPoint point);
	BOOL OnInpaceControlFocus(BOOL bForward);
	void OnDeselect();
	BOOL OnKeyDown(UINT nChar);
	void ToggleConstraint(int nIndex);


private:
	void _Init(int nValue);

protected:
	int    m_nValue;      // Value of the item.  This will contain the value of the selected constraint, not the text
	int*   m_pBindOption; // Binded value.  This is a pointer to the variable bound to this item.
	BOOL m_bCheckBoxStyle;


};

AFX_INLINE int CXTPPropertyGridItemOption::GetOption() const {
	return m_nValue;
}
AFX_INLINE void CXTPPropertyGridItemOption::SetCheckBoxStyle(BOOL bCheckBoxStyle /*= TRUE*/) {
	m_bCheckBoxStyle = bCheckBoxStyle;
}
AFX_INLINE BOOL CXTPPropertyGridItemOption::IsCheckBoxStyle() const {
	return m_bCheckBoxStyle;
}

#endif //#if !defined(__XTPPROPERTYGRIDITEMOPTION_H__)
