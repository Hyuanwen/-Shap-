// DeuDlgDataSrcDetail.cpp : 实现文件

#include "stdafx.h"
#include "DeuDlgDataSrcDetail.h"
#include "DeuGlobal.h"

// CDeuDlgDataSrcDetail 对话框
IMPLEMENT_DYNAMIC(CDeuDlgDataSrcDetail, CXTResizeDialog)
CDeuDlgDataSrcDetail::CDeuDlgDataSrcDetail(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CDeuDlgDataSrcDetail::IDD, pParent)
{
	/*m_strTipText = _T("This is where you would display your tip text message...\nThis is where you would display the second line of your tip text message.");
	m_strTipTitle = _T("Tip Message Title");
	m_nMillisecs = 5000;
	m_nDelayMillisecs = 0;
	m_cx = 1;
	m_cy = 1;
	m_nLineSpacing = 5;
	m_bThickBorder = FALSE;
	m_bAlphaShadow = TRUE;
	m_bDropShadow = TRUE;
	m_bMoveTipBelowCursor = FALSE;*/
}

CDeuDlgDataSrcDetail::~CDeuDlgDataSrcDetail()
{
}

void CDeuDlgDataSrcDetail::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLACEHOLDER, m_wndPlaceHolder);
}

BEGIN_MESSAGE_MAP(CDeuDlgDataSrcDetail, CXTResizeDialog)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CDeuDlgDataSrcDetail::OnBnClickedBtnClose)
END_MESSAGE_MAP()

// CDeuDlgDataSrcDetail 消息处理程序
typedef void (CXTPPropertyGridItem::*ITEMFUNCTIONPTR)();
void _DoCollapseExpand(CXTPPropertyGridItems* pItems, ITEMFUNCTIONPTR pFunction)
{
	for (int i = 0; i < pItems->GetCount(); i++)
	{
		CXTPPropertyGridItem* pItem = pItems->GetAt(i);
		if (pItem->HasChilds())
		{
			(pItem->*pFunction)();
			_DoCollapseExpand(pItem->GetChilds(), pFunction);
		}
	}
}

BOOL CDeuDlgDataSrcDetail::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();
	
	/*m_TabCtrl.ModifyStyle(0L, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
	m_TabCtrl.SetDefaultTheme(xtThemeOffice2003);
	m_TabCtrl.Invalidate(FALSE);
	m_TabCtrl.SetAutoCondense(TRUE);

	m_TabCtrl.InsertItem(0, "范围");
	m_TabCtrl.InsertItem(1, "点类型");
	m_TabCtrl.InsertItem(2, "大地坐标");
	
	m_TabCtrl.GetExtendedStyle()*/

	if(_coordtype ==  GeoProjected) 
	{
		for(int n=0; n<GeoDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
		{
			_ProjectedSeries p_Serises = GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n);
			if(p_Serises._name.text == m_Name)
			{
				nIndex = n; //记录索引
				m_wndPlaceHolder.ShowWindow(SW_HIDE);
				CRect rc;
				m_wndPlaceHolder.GetWindowRect( &rc );
				ScreenToClient( &rc );	
				if (m_wndPropertyGrid.Create(rc, this, IDC_PROPERTY_GRID))
				{
					m_wndPropertyGrid.SetVariableItemsHeight(TRUE);

					LOGFONT lf;
					GetFont()->GetLogFont( &lf );

					//基本
					CXTPPropertyGridItem* pBase = m_wndPropertyGrid.AddCategory(_T("基本信息"));
					m_wndPropertyGrid.SetTheme(xtpGridThemeCool);
					pBase->GetCaptionMetrics()->m_clrFore = 0xFF0000;

					CXTPPropertyGridItem* pPS_0_1 = pBase->AddChildItem(new CXTPPropertyGridItem(_T("名称"), p_Serises._name.text));
					pPS_0_1->SetDescription(p_Serises._name.text);

					CXTPPropertyGridItem* pRemark = pBase->AddChildItem(new CXTPPropertyGridItem(_T("备注"), p_Serises._remark.text));
					pRemark->SetDescription(p_Serises._remark.text);
					pRemark->SetReadOnly();

					pBase->Expand();
					pBase->Select();

					//范围
					CXTPPropertyGridItem* pSettings = m_wndPropertyGrid.AddCategory(_T("范围"));
					pSettings->GetCaptionMetrics()->m_clrFore = 0xFF0000;
					pSettings->AddChildItem(new CXTPPropertyGridItem(_T("名称"), p_Serises._envelope._name.text))->SetDescription(p_Serises._envelope._name.text);

					CXTPPropertyGridItem* pItemMin = pSettings->AddChildItem(new CXTPPropertyGridItem(_T("最小值")));
					pItemMin->AddChildItem(new CXTPPropertyGridItem(_T("经度"), p_Serises._envelope._minpoint._long.text));
					pItemMin->AddChildItem(new CXTPPropertyGridItem(_T("纬度"), p_Serises._envelope._minpoint._lat.text))->SetDescription(p_Serises._envelope._minpoint._lat.text);
					pItemMin->Expand();

					CXTPPropertyGridItem* pItemMax =pSettings->AddChildItem(new CXTPPropertyGridItem(_T("最大值")));
					pItemMax->AddChildItem(new CXTPPropertyGridItem(_T("经度"), p_Serises._envelope._maxpoint._long.text))->SetDescription(p_Serises._envelope._maxpoint._long.text);
					pItemMax->AddChildItem(new CXTPPropertyGridItem(_T("纬度"), p_Serises._envelope._maxpoint._lat.text))->SetDescription(p_Serises._envelope._maxpoint._lat.text);
					pItemMax->Expand();

					CXTPPropertyGridItem* pRemark_envelope  = pSettings->AddChildItem(new CXTPPropertyGridItem(_T("备注"), p_Serises._envelope._remark.text));;
					pRemark_envelope->SetDescription(p_Serises._envelope._remark.text);
					pRemark_envelope->SetReadOnly();
					pSettings->Expand();

					//点类型
					CXTPPropertyGridItem* pPointStyle = m_wndPropertyGrid.AddCategory(_T("点类型"));
					pPointStyle->GetCaptionMetrics()->m_clrFore = 0xFF0000;
					CXTPPropertyGridItem* pPS_1_1 = pPointStyle->AddChildItem(new CXTPPropertyGridItem(_T("名称"), p_Serises._pointStyle._name.text));
					pPS_1_1->SetDescription(p_Serises._pointStyle._name.text);
					
					CXTPPropertyGridItem* pPS_1_2 = pPointStyle->AddChildItem(new CXTPPropertyGridItem(_T("维度"), p_Serises._pointStyle._dimensions.text));
					pPS_1_2->SetDescription(p_Serises._pointStyle._dimensions.text);
					
					//1
					CXTPPropertyGridItem* pItemEast = pPointStyle->AddChildItem(new CXTPPropertyGridItem(_T("东方向")));
					pItemEast->Expand();
					CXTPPropertyGridItem* pPS_2_1 = pItemEast->AddChildItem(new CXTPPropertyGridItem(_T("标签"), p_Serises._pointStyle._east._label.text));
					pPS_2_1->SetDescription(p_Serises._pointStyle._east._label.text);
					
					CXTPPropertyGridItem* pItemUnit1 = pItemEast->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._pointStyle._east._unit_1.name));
					pItemUnit1->SetDescription(p_Serises._pointStyle._east._unit_1.name);

					CXTPPropertyGridItem* pPS_2_2_1 = pItemUnit1->AddChildItem(new CXTPPropertyGridItem(_T("简称"), p_Serises._pointStyle._east._unit_1._abbreviation.text));
					pPS_2_2_1->SetDescription(p_Serises._pointStyle._east._unit_1._abbreviation.text);
					
					CXTPPropertyGridItem* pPS_2_2_2 = pItemUnit1->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._pointStyle._east._unit_1._per_Meter.text));
					pPS_2_2_2->SetDescription(p_Serises._pointStyle._east._unit_1._per_Meter.text);
					
					//2
					CXTPPropertyGridItem* pItemNorth = pPointStyle->AddChildItem(new CXTPPropertyGridItem(_T("北方向")));
					pItemNorth->SetReadOnly();
					pItemNorth->Expand();

					CXTPPropertyGridItem* pPS_3_2_1 = pItemNorth->AddChildItem(new CXTPPropertyGridItem(_T("标签"), p_Serises._pointStyle._north._label.text));
					pPS_3_2_1->SetDescription(p_Serises._pointStyle._north._label.text);
					
					CXTPPropertyGridItem* pItemUnit2 = pItemNorth->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._pointStyle._north._unit_1.name));
					pItemUnit2->SetDescription(p_Serises._pointStyle._north._unit_1.name);
					
					CXTPPropertyGridItem* pPS_3_2_2 = pItemUnit2->AddChildItem(new CXTPPropertyGridItem(_T("简称"), p_Serises._pointStyle._north._unit_1._abbreviation.text));
					pPS_3_2_2->SetDescription(p_Serises._pointStyle._north._unit_1._abbreviation.text);
					
					CXTPPropertyGridItem* pPS_3_2_3 = pItemUnit2->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._pointStyle._north._unit_1._per_Meter.text));
					pPS_3_2_3->SetDescription(p_Serises._pointStyle._north._unit_1._per_Meter.text);
					
					//3
					CXTPPropertyGridItem* pItemHeight = pPointStyle->AddChildItem(new CXTPPropertyGridItem(_T("高度")));
					pItemHeight->Expand();
					
					CXTPPropertyGridItem* pPS_4_2_1 = pItemHeight->AddChildItem(new CXTPPropertyGridItem(_T("标签"), p_Serises._pointStyle._ellipsoidHeight._label.text));
					pPS_4_2_1->SetDescription(p_Serises._pointStyle._ellipsoidHeight._label.text);
					
					CXTPPropertyGridItem* pItemUnit3 = pItemHeight->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._pointStyle._ellipsoidHeight._unit_1.name));
					pItemUnit3->SetDescription(p_Serises._pointStyle._ellipsoidHeight._unit_1.name);
					
					CXTPPropertyGridItem* pPS_4_2_2 = pItemUnit3->AddChildItem(new CXTPPropertyGridItem(_T("简称"), p_Serises._pointStyle._ellipsoidHeight._unit_1._abbreviation.text));
					pPS_4_2_2->SetDescription(p_Serises._pointStyle._ellipsoidHeight._unit_1._abbreviation.text);
					
					CXTPPropertyGridItem* pPS_4_2_3 = pItemUnit3->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._pointStyle._ellipsoidHeight._unit_1._per_Meter.text));
					pPS_4_2_3->SetDescription(p_Serises._pointStyle._ellipsoidHeight._unit_1._per_Meter.text);
					
					//4.
					CXTPPropertyGridItem* pPS_4_2_4 = pPointStyle->AddChildItem(new CXTPPropertyGridItem(_T("备注"),p_Serises._pointStyle._remark.text));
					pPS_4_2_4->SetDescription(p_Serises._pointStyle._remark.text);
					pPointStyle->Expand();

					//p_GeodeticSeries p_DeticSerises; 
					CXTPPropertyGridItem* pItemProjected = m_wndPropertyGrid.AddCategory(_T("大地坐标"));
					pItemProjected->SetDescription(p_Serises._remark.text);
					pItemProjected->GetCaptionMetrics()->m_clrFore = 0xFF0000;
					int enumType = 0;
					for(int kk=0; kk<CustDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); kk++)
					{
						if(p_Serises._geodeticPointor.text == CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(kk)._name.text){
							enumType = kk;
						}
					}

					CXTPPropertyGridItem* pPS_5_1_1 = pItemProjected->AddChildItem(new CXTPPropertyGridItemEnum(_T("类型名称"), enumType));
					for(int kk=0; kk<CustDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); kk++)
					{
						pPS_5_1_1->GetConstraints()->AddConstraint(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(kk)._name.text, kk);
					}
					pPS_5_1_1->SetDescription(p_Serises._name.text); //p_Serises._name.text

					pItemProjected->Expand();

					//投影类型
					CXTPPropertyGridItem* pItemProjectedType   = m_wndPropertyGrid.AddCategory(_T("投影类型"));
					pItemProjectedType->GetCaptionMetrics()->m_clrFore = 0xFF0000;
					CXTPPropertyGridItem*  pItemTmp = pItemProjectedType->AddChildItem(new CXTPPropertyGridItem(_T("名称"), p_Serises._projection.text));
					pItemTmp->SetDescription(p_Serises._projection.text);
					pItemTmp->SetReadOnly();
					pItemProjectedType->Expand();

					//其他
					CXTPPropertyGridItem* pItemOther = m_wndPropertyGrid.AddCategory(_T("其他"));
					pItemOther->GetCaptionMetrics()->m_clrFore = 0xFF0000;
					pItemUnit1 = pItemOther->AddChildItem(new CXTPPropertyGridItem(p_Serises._centralMeridian.name, p_Serises._centralMeridian._value.text));				
					pItemUnit1->SetDescription(p_Serises._centralMeridian._value.text);
					pItemUnit1->AddChildItem(new CXTPPropertyGridItem(_T("参数单位"), p_Serises._centralMeridian._uint.text))->SetDescription(p_Serises._centralMeridian._uint.text);

					pItemUnit1 = pItemOther->AddChildItem(new CXTPPropertyGridItem(p_Serises._falseEasting.name, p_Serises._falseEasting._value.text));
					pItemUnit1->SetDescription(p_Serises._falseEasting._value.text);
					pItemUnit1->AddChildItem(new CXTPPropertyGridItem(_T("参数单位"), p_Serises._falseEasting._uint.text))->SetDescription(p_Serises._falseEasting._value.text);

					pItemUnit1 = pItemOther->AddChildItem(new CXTPPropertyGridItem(p_Serises._falseNorthing.name, p_Serises._falseNorthing._value.text));
					pItemUnit1->SetDescription(p_Serises._falseNorthing._value.text);
					pItemUnit1->AddChildItem(new CXTPPropertyGridItem(_T("参数单位"), p_Serises._falseNorthing._uint.text))->SetDescription(p_Serises._falseNorthing._uint.text);

					pItemUnit1 = pItemOther->AddChildItem(new CXTPPropertyGridItem(p_Serises._latitudeOfOrigin.name, p_Serises._latitudeOfOrigin._value.text));
					pItemUnit1->SetDescription(p_Serises._latitudeOfOrigin._value.text);
					pItemUnit1->AddChildItem(new CXTPPropertyGridItem(_T("参数单位"), p_Serises._latitudeOfOrigin._uint.text))->SetDescription(p_Serises._latitudeOfOrigin._uint.text);

					pItemUnit1 = pItemOther->AddChildItem(new CXTPPropertyGridItem(p_Serises._scaleFactor.name, p_Serises._scaleFactor._value.text));
					pItemUnit1->SetDescription(p_Serises._scaleFactor._value.text);
					pItemUnit1->AddChildItem(new CXTPPropertyGridItem(_T("参数单位"), p_Serises._scaleFactor._uint.text))->SetDescription(p_Serises._scaleFactor._uint.text);

					//pItemProjected->AddChildItem(new CXTPPropertyGridItem(_T("备注"), p_Serises._remark.text));
					//pItemProjected->SetDescription(p_Serises._remark.text);
					pItemOther->Expand();
				}
			}
		}
	}
	else if(_coordtype ==  GeoDetic)
	{
		for(int n=0; n<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
		{
			_GeodeticSeries p_Serises = GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n);
			if(p_Serises._name.text == m_Name)
			{
				nIndex = n; //记录索引
				m_wndPlaceHolder.ShowWindow(SW_HIDE);
				CRect rc;
				m_wndPlaceHolder.GetWindowRect( &rc );
				ScreenToClient( &rc );	
				if (m_wndPropertyGrid.Create(rc, this, IDC_PROPERTY_GRID))
				{
					m_wndPropertyGrid.SetVariableItemsHeight(TRUE);

					LOGFONT lf;
					GetFont()->GetLogFont( &lf );

					//大地坐标
					//p_GeodeticSeries p_DeticSerises;
					CXTPPropertyGridItem* pItemGeoDetic = m_wndPropertyGrid.AddCategory(_T("大地坐标"));
					m_wndPropertyGrid.SetTheme(xtpGridThemeCool);
					pItemGeoDetic->SetDescription(p_Serises._remark.text);
					pItemGeoDetic->GetCaptionMetrics()->m_clrFore = 0xFF0000;
					pItemGeoDetic->AddChildItem(new CXTPPropertyGridItem(_T("名称"), p_Serises._name.text))->SetDescription(p_Serises._name.text);

					//1
					CXTPPropertyGridItem* pItemEnvelope = pItemGeoDetic->AddChildItem(new CXTPPropertyGridItem(_T("范围"), p_Serises._envelope._name.text));
					pItemEnvelope->SetDescription(p_Serises._envelope._name.text);

					//1.1
					CXTPPropertyGridItem* pItemMin = pItemEnvelope->AddChildItem(new CXTPPropertyGridItem(_T("最小值")));
					pItemMin->AddChildItem(new CXTPPropertyGridItem(_T("经度"), p_Serises._envelope._minpoint._long.text))->SetDescription(p_Serises._envelope._minpoint._long.text);
					pItemMin->AddChildItem(new CXTPPropertyGridItem(_T("纬度"), p_Serises._envelope._minpoint._lat.text))->SetDescription(p_Serises._envelope._minpoint._lat.text);
					pItemMin->Expand();

					//1.2
					CXTPPropertyGridItem* pItemMax =pItemEnvelope->AddChildItem(new CXTPPropertyGridItem(_T("最大值")));
					pItemMax->AddChildItem(new CXTPPropertyGridItem(_T("经度"), p_Serises._envelope._maxpoint._long.text))->SetDescription(p_Serises._envelope._maxpoint._long.text);
					pItemMax->AddChildItem(new CXTPPropertyGridItem(_T("纬度"), p_Serises._envelope._maxpoint._lat.text))->SetDescription(p_Serises._envelope._maxpoint._lat.text);
					pItemMax->Expand();

					pItemEnvelope->AddChildItem(new CXTPPropertyGridItem(_T("备注"), p_Serises._envelope._remark.text))->SetDescription(p_Serises._envelope._remark.text);
					pItemEnvelope->Expand();

					//2
					CXTPPropertyGridItem* pItemPS= pItemGeoDetic->AddChildItem(new CXTPPropertyGridItem(_T("点类型"), p_Serises._pointStyle._name.text));
					pItemPS->SetDescription(p_Serises._pointStyle._name.text);

					//2.1.1
					CXTPPropertyGridItem* pItemLong = pItemPS->AddChildItem(new CXTPPropertyGridItem(_T("经度")));
					pItemLong->AddChildItem(new CXTPPropertyGridItem(_T("标签"), p_Serises._pointStyle._geoDeticLongForPS._label.text))->SetDescription(p_Serises._pointStyle._geoDeticLongForPS._label.text);;
					CXTPPropertyGridItem* pItemUnit1 = pItemLong->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._pointStyle._geoDeticLongForPS._unit_2._name.text));
					pItemUnit1->SetDescription(p_Serises._pointStyle._geoDeticLongForPS._unit_2._name.text);
					pItemUnit1->AddChildItem(new CXTPPropertyGridItem(_T("简称"), p_Serises._pointStyle._geoDeticLongForPS._unit_2._abbreviation.text))->SetDescription(p_Serises._pointStyle._geoDeticLongForPS._unit_2._abbreviation.text);
					pItemUnit1->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._pointStyle._geoDeticLongForPS._unit_2._per_Degree.text))->SetDescription(p_Serises._pointStyle._geoDeticLongForPS._unit_2._per_Degree.text);
					pItemLong->Expand();

					//2.1.2
					CXTPPropertyGridItem* pItemLat = pItemPS->AddChildItem(new CXTPPropertyGridItem(_T("纬度")));
					pItemLat->AddChildItem(new CXTPPropertyGridItem(_T("标签"), p_Serises._pointStyle._geoDeticLatForPS._label.text))->SetDescription(p_Serises._pointStyle._geoDeticLatForPS._label.text);;				
					CXTPPropertyGridItem* pItemUnit2 = pItemLat->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._pointStyle._geoDeticLatForPS._unit_2._name.text));
					pItemUnit2->SetDescription(p_Serises._pointStyle._geoDeticLatForPS._unit_2._name.text);
					pItemUnit2->AddChildItem(new CXTPPropertyGridItem(_T("简称"), p_Serises._pointStyle._geoDeticLatForPS._unit_2._abbreviation.text))->SetDescription(p_Serises._pointStyle._geoDeticLatForPS._unit_2._abbreviation.text);
					pItemUnit2->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._pointStyle._geoDeticLatForPS._unit_2._per_Degree.text))->SetDescription(p_Serises._pointStyle._geoDeticLatForPS._unit_2._per_Degree.text);				
					pItemLat->Expand();

					//2.1.3
					CXTPPropertyGridItem* pItemHeight = pItemPS->AddChildItem(new CXTPPropertyGridItem(_T("高度"), ""));
					pItemHeight->AddChildItem(new CXTPPropertyGridItem(_T("标签"), p_Serises._pointStyle._ellipsoidHeight._label.text))->SetDescription(p_Serises._pointStyle._ellipsoidHeight._label.text);
					CXTPPropertyGridItem* pItemUnit3 = pItemHeight->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._pointStyle._ellipsoidHeight._unit_1._name.text));
					pItemUnit3->SetDescription(p_Serises._pointStyle._ellipsoidHeight._unit_1._name.text);
					pItemUnit3->AddChildItem(new CXTPPropertyGridItem(_T("简称"), p_Serises._pointStyle._ellipsoidHeight._unit_1._abbreviation.text))->SetDescription(p_Serises._pointStyle._ellipsoidHeight._unit_1._abbreviation.text);
					pItemUnit3->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._pointStyle._ellipsoidHeight._unit_1._per_Meter.text))->SetDescription(p_Serises._pointStyle._ellipsoidHeight._unit_1._per_Meter.text);
					pItemHeight->Expand();

					pItemPS->AddChildItem(new CXTPPropertyGridItem(_T("备注"), p_Serises._pointStyle._remark.text))->SetDescription(p_Serises._pointStyle._remark.text);
					pItemPS->Expand();

					//3.1.0基准
					pItemEnvelope = pItemGeoDetic->AddChildItem(new CXTPPropertyGridItem(_T("基准"), p_Serises._datum._name.text));
					pItemEnvelope->SetDescription(p_Serises._datum._name.text);

					//3.1.1
					pItemMin = pItemEnvelope->AddChildItem(new CXTPPropertyGridItem(_T("椭球"), p_Serises._datum._ellipsoid._name.text));
					pItemMin->SetDescription(p_Serises._datum._ellipsoid._name.text);
					CXTPPropertyGridItem* pItemChild = pItemMin->AddChildItem(new CXTPPropertyGridItem(_T("长半轴"), p_Serises._datum._ellipsoid._semi_Major_Axis._value.text));
					pItemChild->SetDescription(p_Serises._datum._ellipsoid._semi_Major_Axis._value.text);			
					CXTPPropertyGridItem* pItemChild1 = pItemChild->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._datum._ellipsoid._semi_Major_Axis._unit_1._name.text));				
					pItemChild1->SetDescription(p_Serises._datum._ellipsoid._semi_Major_Axis._unit_1._name.text);
					pItemChild1->AddChildItem(new CXTPPropertyGridItem(_T("简称"), p_Serises._datum._ellipsoid._semi_Major_Axis._unit_1._abbreviation.text))->SetDescription(p_Serises._datum._ellipsoid._semi_Major_Axis._unit_1._abbreviation.text);
					pItemChild1->AddChildItem(new CXTPPropertyGridItem(_T("每米单位"), p_Serises._datum._ellipsoid._semi_Major_Axis._unit_1._per_Meter.text))->SetDescription(p_Serises._datum._ellipsoid._semi_Major_Axis._unit_1._per_Meter.text);
					pItemMin->Expand();

					pItemChild = pItemMin->AddChildItem(new CXTPPropertyGridItem(_T("短半轴"), p_Serises._datum._ellipsoid._semi_Minor_Axis._value.text));
					pItemChild->SetDescription(p_Serises._datum._ellipsoid._semi_Minor_Axis._value.text);
					pItemChild1 = pItemChild->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._datum._ellipsoid._semi_Minor_Axis._unit_1._name.text));
					pItemChild1->SetDescription(p_Serises._datum._ellipsoid._semi_Minor_Axis._unit_1._name.text);
					pItemChild1->AddChildItem(new CXTPPropertyGridItem(_T("简称"), p_Serises._datum._ellipsoid._semi_Minor_Axis._unit_1._abbreviation.text))->SetDescription(p_Serises._datum._ellipsoid._semi_Minor_Axis._unit_1._abbreviation.text);
					pItemChild1->AddChildItem(new CXTPPropertyGridItem(_T("每米单位"), p_Serises._datum._ellipsoid._semi_Minor_Axis._unit_1._per_Meter.text))->SetDescription(p_Serises._datum._ellipsoid._semi_Minor_Axis._unit_1._per_Meter.text);

					pItemChild = pItemMin->AddChildItem(new CXTPPropertyGridItem(_T("偏心率"), p_Serises._datum._ellipsoid._inverseFlattening.text));
					pItemChild->SetDescription(p_Serises._datum._ellipsoid._inverseFlattening.text);

					//3.1.2
					pItemMax =pItemEnvelope->AddChildItem(new CXTPPropertyGridItem(_T("本初子午线"), p_Serises._datum._primeMeridian._geoDeticLong._value.text));
					pItemMax->SetDescription(p_Serises._datum._primeMeridian._geoDeticLong._value.text);
					pItemMax->AddChildItem(new CXTPPropertyGridItem(_T("单位"), p_Serises._datum._primeMeridian._geoDeticLong._unit_2._name.text))->SetDescription(p_Serises._datum._primeMeridian._geoDeticLong._unit_2._name.text);
					pItemMax->AddChildItem(new CXTPPropertyGridItem(_T("每度单位"), p_Serises._datum._primeMeridian._geoDeticLong._unit_2._per_Degree.text))->SetDescription(p_Serises._datum._primeMeridian._geoDeticLong._unit_2._per_Degree.text);

					pItemEnvelope->AddChildItem(new CXTPPropertyGridItem(_T("备注"), p_Serises._datum._remark.text))->SetDescription(p_Serises._datum._remark.text);

					pItemEnvelope->Expand();
					pItemGeoDetic->Expand();
				}
			}
		}
	}

	SetResize(IDC_PROPERTY_GRID, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	//_DoCollapseExpand(m_wndPropertyGrid.GetCategories(), &CXTPPropertyGridItem::Expand);

	return TRUE;
}

void CDeuDlgDataSrcDetail::OnBnClickedBtnClose()
{
	this->OnOK();	
}



