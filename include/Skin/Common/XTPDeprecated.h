// XTPDeprecated.h : deprecated (obsolete) members
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
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
#if !defined(__XTPDEPRECATED_H__)
#define __XTPDEPRECATED_H__
//}}AFX_CODEJOCK_PRIVATE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//{{AFX_CODEJOCK_PRIVATE

// deprecated class names
#define CXTManageState              CXTPManageState
#define CXTDialogState              CXTPDialogState

// deprecated structure names
#define XT_AUX_DATA                 CXTAuxData
#define XT_LOGFONT                  CXTLogFont
#define XT_NONCLIENTMETRICS         CXTNonClientMetrics

#define CXTBarFolder                CXTOutBarFolder
#define CXTBarItem                  CXTOutBarItem
#define CXTEditGroup                CXTEditListBoxToolBar
#define CXTEditItem                 CXTOutBarEditItem

// deprecated global functions
#define InitXtremeExtDLL            XTFuncInitDLL
#define XTPContextMenu              XTFuncContextMenu
#define _xtAfxChangeWindowFont      XTFuncChangeWindowFont
#define _xtAfxDrawEmbossed          XTFuncDrawEmbossed
#define _xtAfxDrawShadedRect        XTFuncDrawShadedRect
#define _xtAfxLoadSysColorBitmap    XTFuncLoadSysColorBitmap
#define _xtAfxChildWindowFromPoint  XTFuncChildWindowFromPoint
#define _xtAfxStripMnemonics        XTFuncStripMnemonics
#define _xtAfxExist                 XTFuncPathExists
#define _xtAfxPathFindNextComponent XTFuncPathFindNextComponent
#define _xtAfxCreateView            XTFuncCreateView
#define _xtAfxShowPrintPreview      XT_ERROR_MSG("_xtAfxShowPrintPreview is deprecated (obsolete).\nSee the \"PrintPreview\" sample for more details.")

// deprecated helper macros
#define _delete(x) SAFE_DELETE(x)
#define _deleteArray(x) SAFE_DELETE_AR(x)

// Deprecated enumerators
#define ANIMATIONTYPE               XTAnimationType

#define eSTYLE                      XTFontStyle
#define XT_FLB_NAME_GUI             xtFontGUI
#define XT_FLB_NAME_SAMPLE          xtFontSample
#define XT_FLB_BOTH                 xtFontBoth

#define icon_type                   XTArrowIcon
#define arrow_left                  xtArrowIconLeft
#define arrow_left_home             xtArrowIconLeftHome
#define arrow_right                 xtArrowIconRight
#define arrow_right_home            xtArrowIconRightHome

#define FOLDER_HILIGHT              XTMouseState
#define F_NORMAL                    xtMouseNormal
#define F_SELECT                    xtMouseSelect
#define F_HILIGHT                   xtMouseHover

#define EFlags                      XTResize
#define SZ_NOSIZEICON               xtResizeNoSizeIcon
#define SZ_NOHORISONTAL             xtResizeNoHorisontal
#define SZ_NOVERTICAL               xtResizeNoVertical
#define SZ_NOMINSIZE                xtResizeNoMinsize
#define SZ_NOCLIPCHILDREN           xtResizeNoClipChildren
#define SZ_NOTRANSPARENTGROUP       xtResizeNoTransparentGroup

#define FindAttribs                 XTFindType
#define type_drive                  xtFindTypeDrive
#define type_folder                 xtFindTypeFolder

#define XT_DATA_TYPE                XTSortType
#define DT_INT                      xtSortInt
#define DT_STRING                   xtSortString
#define DT_DATETIME                 xtSortDateTime
#define DT_DEC                      xtSortDecimal

#define XT_NAVBTNFLAGS              XTNavBtnState
#define XT_SHOW_ARROWS              xtNavBtnArrows
#define XT_SHOW_CLOSE               xtNavBtnClose
#define XT_SHOW_ALL                 xtNavBtnShowAll

// deprecated global data
#define xtAfxData                   XTAuxData()
#define xtVerInfo                   *XTOSVersionInfo()


// docking panes defines:
#define dockLeftOf                  xtpPaneDockLeft
#define dockRightOf                 xtpPaneDockRight
#define dockTopOf                   xtpPaneDockTop
#define dockBottomOf                xtpPaneDockBottom

#define typeDockingPane             xtpPaneTypeDockingPane
#define typeTabbedContainer         xtpPaneTypeTabbedContainer
#define typeSplitterContainer       xtpPaneTypeSplitterContainer
#define typeMiniWnd                 xtpPaneTypeMiniWnd
#define typeClient                  xtpPaneTypeClient
#define typeAutoHidePanel           xtpPaneTypeAutoHidePanel

// property grid defines
#define CXTPItemConstraints         CXTPPropertyGridItemConstraints
#define XTP_PROPERTYSORT            XTPPropertyGridSortOrder
#define pgiHasEdit                  xtpGridItemHasEdit
#define pgiHasExpandButton          xtpGridItemHasExpandButton
#define pgiHasComboButton           xtpGridItemHasComboButton

#define Categorized                 xtpGridSortCategorized
#define Alphabetical                xtpGridSortAlphabetical
#define NoSort                      xtpGridSortNoSort

// tab manager
#define XTP_TABCOLOR_BLUE           xtpTabColorBlue
#define XTP_TABCOLOR_YELLOW         xtpTabColorYellow
#define XTP_TABCOLOR_GREEN          xtpTabColorGreen
#define XTP_TABCOLOR_RED            xtpTabColorRed
#define XTP_TABCOLOR_PURPLE         xtpTabColorPurple
#define XTP_TABCOLOR_CYAN           xtpTabColorCyan
#define XTP_TABCOLOR_ORANGE         xtpTabColorOrange
#define XTP_TABCOLOR_MAGENTA        xtpTabColorMagenta
#define XTP_TABMANAGER_BUTTON_LEFT  xtpTabNavigateButtonLeft
#define XTP_TABMANAGER_BUTTON_RIGHT xtpTabNavigateButtonRight
#define XTP_TABMANAGER_BUTTON_CLOSE xtpTabNavigateButtonClose

// CommandBars
#define XTP_COMMANDBARS_OPTIONS     CXTPCommandBarsOptions
#define XTP_GRADIENT_COLOR          CXTPPaintManagerColorGradient
#define CXTStatusBar                CXTPStatusBar
#define CXTIconPane                 CXTPStatusBarIconPane
#define CXTLogoPane                 CXTPStatusBarLogoPane
#define CXTBasePane                 CXTPStatusBarPaneWnd



#define XT_IDS_CLR_BROWN               9901
#define XT_IDS_CLR_OLIVE_GREEN         9902
#define XT_IDS_CLR_DARK_GREEN          9903
#define XT_IDS_CLR_DARK_TEAL           9904
#define XT_IDS_CLR_DARK_BLUE           9905
#define XT_IDS_CLR_INDIGO              9906
#define XT_IDS_CLR_GRAY80              9907
#define XT_IDS_CLR_DARK_RED            9908
#define XT_IDS_CLR_ORANGE              9909
#define XT_IDS_CLR_DARK_YELLOW         9910
#define XT_IDS_CLR_GREEN               9911
#define XT_IDS_CLR_TEAL                9912
#define XT_IDS_CLR_BLUE                9913
#define XT_IDS_CLR_BLUEGRAY            9914
#define XT_IDS_CLR_GRAY50              9915
#define XT_IDS_CLR_RED                 9916
#define XT_IDS_CLR_LIGHTORANGE         9917
#define XT_IDS_CLR_LIME                9918
#define XT_IDS_CLR_SEA_GREEN           9919
#define XT_IDS_CLR_AQUA                9920
#define XT_IDS_CLR_LIGHT_BLUE          9921
#define XT_IDS_CLR_VIOLET              9922
#define XT_IDS_CLR_GRAY40              9923
#define XT_IDS_CLR_PINK                9924
#define XT_IDS_CLR_GOLD                9925
#define XT_IDS_CLR_YELLOW              9926
#define XT_IDS_CLR_BRIGHT_GREEN        9927
#define XT_IDS_CLR_TURQUOISE           9928
#define XT_IDS_CLR_SKY_BLUE            9929
#define XT_IDS_CLR_PLUM                9930
#define XT_IDS_CLR_GRAY25              9931
#define XT_IDS_CLR_ROSE                9932
#define XT_IDS_CLR_TAN                 9933
#define XT_IDS_CLR_LIGHT_YELLOW        9934
#define XT_IDS_CLR_LIGHT_GREEN         9935
#define XT_IDS_CLR_LIGHT_TURQUOISE     9936
#define XT_IDS_CLR_PALE_BLUE           9937
#define XT_IDS_CLR_LAVENDER            9938
#define XT_IDS_CLR_WHITE               9939
#define XT_IDS_CLR_GRAY                9940
#define XT_IDS_CLR_MAROON              9941
#define XT_IDS_CLR_OLIVE               9942
#define XT_IDS_CLR_NAVY                9943
#define XT_IDS_CLR_PURPLE              9944
#define XT_IDS_CLR_SILVER              9945
#define XT_IDS_CLR_FUCHSIA             9946
#define XT_IDS_CLR_NOFILL              9947
#define XT_IDS_CLR_AUTOMATIC           9948
#define XT_IDS_CLR_MORE                9949

//}}AFX_CODEJOCK_PRIVATE

//////////////////////////////////////////////////////////////////////

#endif // #if !defined(__XTPDEPRECATED_H__)