#include "stdafx.h"
#include "ArcSDeVector.h"

clock_t start;
clock_t end;
#define START_TIME 	start = clock();
#define END_TIME	end	  = clock();	

#define SEC_PER_CLOCKS 0.001

#define LOG_USED_TIME \
	int time_i=(end-start)*SEC_PER_CLOCKS;\
	char * time = (char *)malloc(20);\
	itoa(time_i,time,10);\
	LOG("�ܹ���ʱ(��):",time,100);\
	free(time);

CArcSDEVector::CArcSDEVector()
{

}


CArcSDEVector::CArcSDEVector(IWorkspacePtr pWorkspace):m_WorkspaceSrc(pWorkspace)
{

}



CArcSDEVector::~CArcSDEVector()
{

}

HRESULT CArcSDEVector::RegisterWnd(HWND hwnd)
{
	m_hWnd = hwnd;
	return S_OK;
}

void	CArcSDEVector::SetTransParam(IWorkspacePtr pWorkspaceSrc, IWorkspacePtr pWorkspaceDes, const CDeuTrans& trans, const string& strPrjFullPath)
{
	m_WorkspaceSrc = pWorkspaceSrc;
	m_WorkspaceDes = pWorkspaceDes;
	m_Trans = trans;
	m_strPrjFullPath = strPrjFullPath;
}

 HRESULT CArcSDEVector::GetFeatureByType(esriDatasetType type, vector<STR_SDEINFO>& vecDT)
{

	IEnumDatasetPtr							ipEDS = NULL;
	IDatasetPtr								ipDS = NULL;
	BSTR									name;
	HRESULT									hr;
	STR_SDEINFO								sdeInfo;

	ASSERT(m_WorkspaceSrc);

	//1.��ȡ�������ݼ�
	hr = m_WorkspaceSrc->get_Datasets(type, &ipEDS);
	if (FAILED(hr))
	{
		return S_FALSE;
	}

	ipEDS->Reset();

	//2.����
	hr = ipEDS->Next(&ipDS);
	if (FAILED(hr))
	{
		return S_FALSE;
	}

	//ʸ�����ݹ���ʱ�����դ������ѡ�У��ӿ����⣬������Ҫ���ι��� add by chenyong 2015-3-17
	esriDatasetType _type;
	while (ipDS != NULL)
	{
		ipDS->get_Name(&name);
		sdeInfo.strName = _com_util::ConvertBSTRToString(name);
		
		//add by chenyong 2015-3-17 ���ι���
		ipDS->get_Type(&_type);
		if (_type == type)
		{
			switch (type)
			{
			case esriDTFeatureDataset:
				sdeInfo.Type = deuFeatureDataset;	
				break;

			case esriDTFeatureClass:
				sdeInfo.Type = deuFeatureClass;
				break;

			default:
				sdeInfo.Type = deuUnknownType;
				break;
			}

			vecDT.push_back(sdeInfo);
		}

		ipEDS->Next(&ipDS);

	}
	return S_OK;
}

 HRESULT CArcSDEVector::GetAllFeatureNameAndType(vector<STR_SDEINFO>& vecAll)
{
	vecAll.clear();

	GetFeatureByType(esriDTFeatureClass, vecAll);

	GetFeatureByType(esriDTFeatureDataset, vecAll);

	return S_OK;
}
 
 HRESULT CArcSDEVector::TransFeatureDTType(STR_SDEINFO sdeInfo)
 {
	 LOGSTR(":CoordTransSDE");

	 _bstr_t _bstr_filename = (sdeInfo.strName).c_str();
	 LOGSTR((LPSTR)_bstr_filename);
	 LOG_START;
	 START_TIME;

	 IWorkspaceEditPtr			ipWorkspaceEdit = m_WorkspaceDes;
	 HRESULT					hr = S_OK;
	 VARIANT_BOOL				variantEdit = VARIANT_FALSE;
	 
	 switch (sdeInfo.Type)
	 {
	case deuFeatureClass:				
		hr = TransFeatureClass(sdeInfo.strName);
		if (hr==S_FALSE)
		{
			ipWorkspaceEdit->IsBeingEdited(&variantEdit);
			if (variantEdit)
			{
				ipWorkspaceEdit->StopEditOperation();
				ipWorkspaceEdit->UndoEditOperation();
				//ipWorkspaceEdit->StopEditing(VARIANT_FALSE);
			}
		}

		break;

	case deuFeatureDataset:					
		hr = TransFeatureDataset(sdeInfo.strName);
		if (hr==S_FALSE)
		{
			ipWorkspaceEdit->IsBeingEdited(&variantEdit);
			if (variantEdit)
			{
				ipWorkspaceEdit->UndoEditOperation();
				ipWorkspaceEdit->StopEditOperation();
				//ipWorkspaceEdit->StopEditing(VARIANT_FALSE);
			}
		}

		break;

	default:

		break;

	 }

	 END_TIME;
	 LOG_USED_TIME;
	 LOG_END;
	 LOGSTR("=====================================================================");

	 return hr;
 }

 HRESULT CArcSDEVector::TransFeatureClass(const string& strFeatureName)
 {
	IFeatureWorkspacePtr					ipFeatureWorkspace = m_WorkspaceSrc;
	IFeatureWorkspacePtr					ipFeatureWorkspace_des = m_WorkspaceDes;
	IFeatureClassPtr						ipFeatureCls;
	IFeatureClassPtr						ipFeatureCls_Des;
	IFieldsPtr								ipFlds;
	esriFeatureType							FeatureType;
	CComBSTR								strShapeName;
	IUIDPtr									uid;
	IUIDPtr									uid2;
	HRESULT									hRe;
	IFeatureCursorPtr						ipFeatureSor;
	IFeaturePtr								ipFeature;
	IGeometryPtr							ipGeometry;
	esriGeometryType						GeometryType = esriGeometryNull;
	IFeaturePtr								ipFeature_Des;
	IPointCollectionPtr						ipPointCol;
	long									lCount = 0;
	IPointPtr								iptempPoint;
	double									dX_Src = 0;
	double									dY_Src = 0;
	double									dZ_Src = 0;
	double									dX_Des = 0;
	double									dY_Des = 0;
	double									dZ_Des = 0;
	IPointPtr								ipPoint;

	IWorkspaceEditPtr						ipWorkspaceEdit = m_WorkspaceDes;
//	VARIANT									varValue;
	long									lCountVal = 0;
	IFieldsPtr								ipFieldS_Des;
	IFieldPtr								ipField_Des;
	VARIANT_BOOL							varIsEdit = VARIANT_TRUE;
	VARIANT_BOOL							varIsExist = VARIANT_TRUE;

	IPolygon4Ptr							ipPolygon4;
	IGeometryBagPtr							ipGeometryBagExt;
	IGeometryBagPtr							ipGeometryBagInn;
	IEnumGeometryPtr						ipEnumGeometryExt;
	IEnumGeometryPtr						ipEnumGeometryInn;

	IRingPtr								ipRingExt;
	IRingPtr								ipRingInn;
	IGeometryPtr							ipGeometryExt;
	IGeometryPtr							ipGeometryInn;

	IFeatureCursorPtr						ipFeatureCursorDes;
	IFeatureBufferPtr						ipFeatureBufferDes;
	//VARIANT									ID;

	char									szLog[128] = {0};
	sprintf(szLog, _T("��ʼת��Ҫ����%s"), CString(strFeatureName.c_str()));
	LOGSTR(szLog);
	
	hRe = ipFeatureWorkspace->OpenFeatureClass(_bstr_t(strFeatureName.c_str()), &ipFeatureCls);
	if (FAILED(hRe))
	{
		sprintf(szLog, "��Ҫ����%sʧ��,���ش����룺%ld", strFeatureName.c_str(), (long)hRe);
		LOGSTR(szLog);
		return S_FALSE;
	}
	
	ipFeatureCls->get_Fields(&ipFlds);
	ipFeatureCls->get_FeatureType(&FeatureType);
	ipFeatureCls->get_ShapeFieldName(&strShapeName);
	ipFeatureCls->get_CLSID(&uid);
	ipFeatureCls->get_EXTCLSID(&uid2);

 	IFieldCheckerPtr	ipFieldChecker(CLSID_FieldChecker);

 	IFieldPtr		ipField;
	IFieldsPtr		ipValidateFields;
	IEnumFieldErrorPtr		ipFieldError;
	IFieldErrorPtr		FError;
	esriFieldNameErrorType		errType;

	ipFieldChecker->putref_ValidateWorkspace(m_WorkspaceDes);
	ipFieldChecker->Validate(ipFlds, &ipFieldError, &ipValidateFields);

	ipValidateFields->get_FieldCount(&lCountVal);


	long   lFieldIndex = 0;
	if (ipFieldError != NULL)
	{
		ipFieldError->Next(&FError);
		FError->get_FieldError(&errType);
		FError->get_FieldIndex(&lFieldIndex);
	}

	IWorkspaceEdit2Ptr								ipWorkspaceEdit2 = ipWorkspaceEdit;
	VARIANT_BOOL									IsActive = VARIANT_FALSE;

	ipWorkspaceEdit2->get_IsInEditOperation(&IsActive);
	if (IsActive == VARIANT_TRUE)
	{
		AfxMessageBox(_T("�������ڱ�����һ���Ự���̱༭....."));
		return S_FALSE;
	}

	//����Ƿ������ͬ���ֵ����� add by chenyong 2014-2-11
	IWorkspace2Ptr					ipWorkspace2 = m_WorkspaceDes;
	VARIANT_BOOL					varExist = VARIANT_FALSE;

	ipWorkspace2->get_NameExists(esriDTFeatureClass, _bstr_t(strFeatureName.c_str()), &varExist);
	if (varExist)
	{
		sprintf(szLog, _T("Ŀ����д���Ҫ����%s"), strFeatureName.c_str());
		LOGSTR(szLog);
		return S_FALSE;
	}
	
	
	

	//add by chenyong 2013-5-10
	ipWorkspaceEdit->StartEditing(VARIANT_TRUE);
	ipWorkspaceEdit->StartEditOperation();

	//�޸�domain��Χ add by chenyong 2013-12-2


	//�����ռ�ο�ϵ 
	ISpatialReferenceFactoryPtr							ipSpatialFac(CLSID_SpatialReferenceEnvironment);
	ISpatialReferencePtr								ipSpatial;

	hRe = ipSpatialFac->CreateESRISpatialReferenceFromPRJFile(_bstr_t(m_strPrjFullPath.c_str()), &ipSpatial);
	if (FAILED(hRe))
	{
		sprintf(szLog, "�����ռ�ο�ϵʧ��,���ش����룺%ld", (long)hRe);
		LOGSTR(szLog);
		return hRe;
	}

 	long								lindex(0);
 	IFieldPtr							ipFieldShape;
 	IGeometryDefPtr						ipGeometryDef;
 	IGeometryDefEditPtr					ipGeometryDefEdit;

 
 	ipValidateFields->FindFieldByAliasName(_bstr_t("shape"), &lindex);
 	ipValidateFields->get_Field(lindex, &ipFieldShape);
 	ipFieldShape->get_GeometryDef(&ipGeometryDef);
 
 	ISpatialReferencePtr				ipSpatialSrc;
 	double								dXmin(0);
 	double								dYmin(0);
 	double								dXmax(0);
 	double								dYmax(0);
 
 	ipGeometryDef->get_SpatialReference(&ipSpatialSrc);
 	ipSpatialSrc->GetDomain(&dXmin, &dXmax, &dYmin, &dYmax);
 
 	//����ת�����domain��Χ
 	double								dXSrc[4] = {0};
 	double								dYSrc[4] = {0};
 	double								dXDes[4] = {0};
 	double								dYDes[4] = {0};
 	double								dZSrc[4] = {0};
 	double								dZDes[4] = {0};
 
 	dXSrc[0] = dXSrc[3] = dXmin;
 	dXSrc[1] = dXSrc[2] = dXmax;
 	dYSrc[0] = dYSrc[1] = dYmin;
 	dYSrc[2] = dYSrc[3] = dYmax;
 
 	for (int i = 0; i < 4; ++i)
 	{
 		m_Trans.TransSDEVector(dYSrc[i], dXSrc[i], dZSrc[i], dYDes[i], dXDes[i], dZDes[i]);
 	}
 
 
 	dXmin = dXmax = dXDes[0];
 	dYmin = dYmax = dYDes[0];
 
 	for (int i = 1; i < 4; ++i)
 	{
 		dXmax = (dXDes[i] > dXmax) ? dXDes[i] : dXmax;
 		dXmin = (dXDes[i] < dXmin) ? dXDes[i] : dXmin;
 		dYmax = (dYDes[i] > dYmax) ? dYDes[i] : dYmax;
 		dYmin = (dYDes[i] < dYmin) ? dYDes[i] : dYmin;
 	}
 
 	//ipSpatial->SetDomain(dXmin, dXmax, dYmin, dYmax);

	
	ipGeometryDefEdit = ipGeometryDef;

	ipGeometryDefEdit->putref_SpatialReference(ipSpatial);

	IFieldEditPtr			ipFieldEdit = ipFieldShape;
	ipFieldEdit->putref_GeometryDef(ipGeometryDef);

	hRe = ipFeatureWorkspace_des->CreateFeatureClass(_bstr_t(strFeatureName.c_str()), /*ipFlds*/ipValidateFields, uid, uid2, FeatureType, strShapeName, _bstr_t(""), &ipFeatureCls_Des);
	if (FAILED(hRe))
	{
		sprintf(szLog, "��������%sʧ��,���ش����룺%ld", strFeatureName.c_str(), (long)hRe);
		LOGSTR(szLog);
		return S_FALSE;
	}

	//add by chenyong 2013-12-25
	ipFeatureCls_Des->Insert(VARIANT_TRUE, &ipFeatureCursorDes);
	ipFeatureCls_Des->CreateFeatureBuffer(&ipFeatureBufferDes);

	IQueryFilterPtr							ipQueryFilter(CLSID_QueryFilter);
	
	ipQueryFilter->AddField(_bstr_t("SHAPE"));

	hRe = ipFeatureCls->Search(NULL, VARIANT_FALSE, &ipFeatureSor);
	if (FAILED(hRe))
	{
		return S_FALSE;
	}
	ipFeatureSor->NextFeature(&ipFeature);

	//���ӽ����� add by chenyong 2013-12-4
	long					lFeatureCount(0);		//Ҫ���ܸ���
	long					lFeatureDones(0);		//��ת��Ҫ�ظ���
	long					oid = 0;
		
	ipFeatureCls->FeatureCount(NULL, &lFeatureCount);

	unsigned int  Percent = (unsigned int)((lFeatureDones / lFeatureCount)*100);
	::SendMessage(m_hWnd, WM_PROGRESS, 0, Percent);

	while (NULL != ipFeature)
	{
		//ipFeature->get_Shape(&ipGeometry);
		ipFeature->get_ShapeCopy(&ipGeometry);

		ipFeature->get_OID(&oid);
		ipGeometry->get_IsEmpty(&varIsExist);
		if (varIsExist == VARIANT_TRUE)
		{
			if (lFeatureDones % 100 == 0)
			{		
				hRe = ipFeatureCursorDes->Flush();
				if (FAILED(hRe))
				{
					sprintf(szLog, "����Ҫ��ʧ��,���ش����룺%ld", (long)hRe);
					LOGSTR(szLog);
					return S_FALSE;
				}
			}

			//������ add by chenyong 2013-12-4
			++lFeatureDones;

			if (lFeatureDones % 10 == 0)
			{
				Percent = (unsigned int)(lFeatureDones*100 / lFeatureCount);
				::SendMessage(m_hWnd, WM_PROGRESS, 0, Percent);
			}

			ipFeatureSor->NextFeature(&ipFeature);
			continue;
		}

		
		ipGeometry->get_GeometryType(&GeometryType);

		switch (GeometryType)
		{
		case esriGeometryPoint:

			ipPoint = ipGeometry;

			ipPoint->get_X(&dX_Src);
			ipPoint->get_Y(&dY_Src);
			//ipPoint->get_Z(&dZ_Src);

			//�˴���Ҫ��ת������
			m_Trans.TransSDEVector(dY_Src, dX_Src, dZ_Src, dY_Des, dX_Des, dZ_Des);

			hRe = ipPoint->put_X(dX_Des);
			hRe = ipPoint->put_Y(dY_Des);
			//ipPoint->put_Z(dZ_Des);

			
			break;

		case esriGeometryMultipoint:
		case esriGeometryLine:
		case esriGeometryPolyline:

			ipPointCol = ipGeometry;
			ipPointCol->get_PointCount(&lCount);

			for (int i = 0; i < lCount; i++)
			{
				ipPointCol->get_Point(i, &iptempPoint);
				iptempPoint->get_X(&dX_Src);
				iptempPoint->get_Y(&dY_Src);
				//iptempPoint->get_Z(&dZ_Src);

				//�˴���Ҫ��ת�� ����
				m_Trans.TransSDEVector(dY_Src, dX_Src, dZ_Src, dY_Des, dX_Des, dZ_Des);

				iptempPoint->put_X(dX_Des);
				iptempPoint->put_Y(dY_Des);
				//iptempPoint->put_Z(dZ_Des);

				hRe = ipPointCol->UpdatePoint(i, iptempPoint);
			}
			

			break;

		case esriGeometryPolygon:

			/*
				1.�ֳ����⻷����
				2.������һ���㼯��������ʼ��������Σ���������ת��ʱ�����һ���㲻����
			*/

			ipPolygon4 = ipGeometry;
			ipPolygon4->get_ExteriorRingBag(&ipGeometryBagExt);
			ipEnumGeometryExt = ipGeometryBagExt;
			ipEnumGeometryExt->Reset();
			ipEnumGeometryExt->Next(&ipGeometryExt);

			while(NULL != ipGeometryExt)
			{				
				ipRingExt = ipGeometryExt;

				//1. deal with inner rings
				hRe = ipPolygon4->get_InteriorRingBag(ipRingExt, &ipGeometryBagInn);
				if (FAILED(hRe))
				{
					continue;
				}

 				ipEnumGeometryInn = ipGeometryBagInn;
 				ipEnumGeometryInn->Reset();
 				ipEnumGeometryInn->Next(&ipGeometryInn);
 
 				while (NULL != ipGeometryInn)
 				{
 					ipRingInn = ipGeometryInn;
 					ipPointCol = ipRingInn;
 					ipPointCol->get_PointCount(&lCount);
 
 					for (int i = 0; i < lCount - 1; i++)
 					{
 						ipPointCol->get_Point(i, &iptempPoint);
 						iptempPoint->get_X(&dX_Src);
 						iptempPoint->get_Y(&dY_Src);
 						//iptempPoint->get_Z(&dZ_Src);
 
 						//�˴���Ҫ��ת�� ����
 						m_Trans.TransSDEVector(dY_Src, dX_Src, dZ_Src, dY_Des, dX_Des, dZ_Des);
 					
 						iptempPoint->put_X(dX_Des);
 						iptempPoint->put_Y(dY_Des);
 						//iptempPoint->put_Z(dZ_Des);
 
 						ipPointCol->UpdatePoint(i, iptempPoint);	
 					}
 
 					ipEnumGeometryInn->Next(&ipGeometryInn);
 				}

				//2. deal with external rings
 				ipPointCol = ipRingExt;
 				ipPointCol->get_PointCount(&lCount);
 
 				for (int i = 0; i < lCount - 1; i++)
 				{
 					ipPointCol->get_Point(i, &iptempPoint);
 					iptempPoint->get_X(&dX_Src);
 					iptempPoint->get_Y(&dY_Src);
 					//iptempPoint->get_Z(&dZ_Src);
 
 					//�˴���Ҫ��ת�� ����
 					m_Trans.TransSDEVector(dY_Src, dX_Src, dZ_Src, dY_Des, dX_Des, dZ_Des);
					
 					iptempPoint->put_X(dX_Des);
 					iptempPoint->put_Y(dY_Des);
 					//iptempPoint->put_Z(dZ_Des);
 
 					ipPointCol->UpdatePoint(i, iptempPoint);
	
 				}

				ipEnumGeometryExt->Next(&ipGeometryExt);
			}	
			
			break;

		}
	
		//hRe = ipGeometry->SnapToSpatialReference();
		ipGeometry->putref_SpatialReference(ipSpatial);

		//alter by chenyong 2013-12-26
		InsertFeature(ipFeatureCursorDes, ipFeatureBufferDes, ipFeature, ipGeometry);

  		if (lFeatureDones % 100 == 0)
		{		
			hRe = ipFeatureCursorDes->Flush();
			if (FAILED(hRe))
			{
				sprintf(szLog, "����Ҫ��ʧ��,���ش����룺%ld", (long)hRe);
				LOGSTR(szLog);
				return S_FALSE;
			}
		}
		
		//������ add by chenyong 2013-12-4
		++lFeatureDones;

		if (lFeatureDones % 10 == 0)
		{
			Percent = (unsigned int)(lFeatureDones*100 / lFeatureCount);
			::SendMessage(m_hWnd, WM_PROGRESS, 0, Percent);
		}

		ipFeatureSor->NextFeature(&ipFeature);

	}

	ipFeatureCursorDes->Flush();

	::SendMessage(m_hWnd, WM_PROGRESS, 0, (unsigned int)(100));

	ipWorkspaceEdit->StopEditOperation();
	ipWorkspaceEdit->StopEditing(VARIANT_TRUE);

	sprintf(szLog, "���ת��Ҫ����%s", CString(strFeatureName.c_str()));
	LOGSTR(szLog);

	return S_OK;
 }

 HRESULT CArcSDEVector::TransFeatureDataset(const string& strDatasetName)
 {
	IFeatureWorkspacePtr							ipFeatureWS_Src = m_WorkspaceSrc;
	IFeatureWorkspacePtr							ipFeatureWS_Des = m_WorkspaceDes;
	IFeatureDatasetPtr								ipFeatureDS_Src;
	IFeatureDatasetPtr								ipFeatureDS_Des;
	HRESULT											hr;
	string											strMsg = "";
	IWorkspaceEditPtr								ipWorkspaceEdit = m_WorkspaceDes;

	char									szLog[128] = {0};
	sprintf(szLog, "��ʼת��Ҫ�ؼ�%s", CString(strDatasetName.c_str()));
	LOGSTR(szLog);

	IWorkspaceEdit2Ptr								ipWorkspaceEdit2 = ipWorkspaceEdit;
	VARIANT_BOOL									IsActive = VARIANT_FALSE;

	ipWorkspaceEdit2->get_IsInEditOperation(&IsActive);
	if (IsActive == VARIANT_TRUE)
	{
		AfxMessageBox(_T("�������ڱ�����һ���Ự���̱༭....."));
		return S_FALSE;
	}

	//����Ƿ������ͬ���ֵ����� add by chenyong 2014-2-11
	IWorkspace2Ptr					ipWorkspace2 = m_WorkspaceDes;
	VARIANT_BOOL					varExist = VARIANT_FALSE;

	ipWorkspace2->get_NameExists(esriDTFeatureClass, _bstr_t(strDatasetName.c_str()), &varExist);
	if (varExist)
	{
		sprintf(szLog, _T("Ŀ����д���Ҫ�ؼ�%s"), strDatasetName.c_str());
		LOGSTR(szLog);
		return S_FALSE;
	}

	//ipWorkspaceEdit->StartEditing(VARIANT_TRUE);
	//ipWorkspaceEdit->StartEditOperation();

	//1.��Դʼ���ݼ�
	hr = ipFeatureWS_Src->OpenFeatureDataset(_bstr_t(strDatasetName.c_str()), &ipFeatureDS_Src);
	if (FAILED(hr))
	{
		sprintf(szLog, "��Ҫ�ؼ�%sʧ��,���ش�����:%ld", strDatasetName.c_str(), (long)hr);
		LOGSTR(szLog);
		return hr;
	}

	//2.���������ݼ�
	ISpatialReferenceFactoryPtr							ipSpatialFac(CLSID_SpatialReferenceEnvironment);
	ISpatialReferencePtr								ipSpatial;

	hr = ipSpatialFac->CreateESRISpatialReferenceFromPRJFile(_bstr_t(m_strPrjFullPath.c_str()), &ipSpatial);
	if (FAILED(hr))
	{
		sprintf(szLog, "�����ռ�����ϵʧ��,���ش�����:%ld", (long)hr);
		LOGSTR(szLog);
		return hr;
	}

	hr = ipFeatureWS_Des->CreateFeatureDataset(_bstr_t(strDatasetName.c_str()), ipSpatial, &ipFeatureDS_Des);
	if (FAILED(hr))
	{
		sprintf(szLog, "����Ҫ�ؼ�%sʧ��,���ش�����:%ld", strDatasetName.c_str(), (long)hr);
		LOGSTR(szLog);
		return hr;
	}

	//3.��ȡҪ������
	IEnumDatasetPtr									ipEnumDS;
	esriFeatureType									featureType = esriFTSimple;
	IDatasetPtr										ipDS;
	BSTR											name;
	esriDatasetType									esriDSType = esriDTAny;

	//4.����Դʼ���ݼ�
	ipFeatureDS_Src->get_Subsets(&ipEnumDS);
	ipEnumDS->Reset();

	hr = ipEnumDS->Next(&ipDS);
	if (FAILED(hr))
	{
		return hr;
	}

	while (ipDS != NULL)
	{
		ipDS->get_Name(&name);
		ipDS->get_Type(&esriDSType);
		switch (esriDSType)
		{
		case esriDTFeatureDataset:
			//TransFeatureDataset(_com_util::ConvertBSTRToString(name));
			break;

		case esriDTFeatureClass:
			hr = TransFeatureClass(ipFeatureDS_Des, _com_util::ConvertBSTRToString(name));
			if(hr == S_FALSE)
			{
				ipWorkspaceEdit->StopEditOperation();
				ipWorkspaceEdit->StopEditing(VARIANT_FALSE);
			}

			break;

		default:
			break;
		}

		ipEnumDS->Next(&ipDS);

	}


// 	ipWorkspaceEdit->StopEditOperation();
// 	ipWorkspaceEdit->StopEditing(VARIANT_TRUE);
	
	sprintf(szLog, "���ת��Ҫ�ؼ�%s", CString(strDatasetName.c_str()));
	LOGSTR(szLog);
		
	return S_OK;
 }

 HRESULT CArcSDEVector::TransFeatureClass(IFeatureDatasetPtr pFeatureDS_Des, const string& strFeatureName)
 {
	 IFeatureWorkspacePtr					ipFeatureWorkspace = m_WorkspaceSrc;
	 IFeatureClassPtr						ipFeatureCls;
	 IFeatureClassPtr						ipFeatureCls_Des;
	 IFieldsPtr								ipFlds;
	 esriFeatureType						FeatureType;
	 CComBSTR								strShapeName;
	 IUIDPtr								uid;
	 IUIDPtr								uid2;
	 HRESULT								hRe;
	 IFeatureCursorPtr						ipFeatureSor;
	 IFeaturePtr							ipFeature;
	 IGeometryPtr							ipGeometry;
	 esriGeometryType						GeometryType = esriGeometryNull;
	 IFeaturePtr							ipFeature_Des;
	 IPointCollectionPtr					ipPointCol;
	 long									lCount = 0;
	 IPointPtr								iptempPoint;
	 double									dX_Src = 0;
	 double									dY_Src = 0;
	 double									dZ_Src = 0;
	 double									dX_Des = 0;
	 double									dY_Des = 0;
	 double									dZ_Des = 0;
	 IPointPtr								ipPoint;
//	 VARIANT								varValue;
	 long									lCountVal = 0;

	 IFieldsPtr								ipFieldS_Des;
	 IFieldPtr								ipField_Des;
	 VARIANT_BOOL							varIsEdit = VARIANT_TRUE;
	 VARIANT_BOOL							varIsExist = VARIANT_TRUE;

	 IPolygon4Ptr							ipPolygon4;
	 IGeometryBagPtr							ipGeometryBagExt;
	 IGeometryBagPtr							ipGeometryBagInn;
	 IEnumGeometryPtr						ipEnumGeometryExt;
	 IEnumGeometryPtr						ipEnumGeometryInn;

	 IRingPtr								ipRingExt;
	 IRingPtr								ipRingInn;
	 IGeometryPtr							ipGeometryExt;
	 IGeometryPtr							ipGeometryInn;

	 IFeatureCursorPtr						ipFeatureCursorDes;
	 IFeatureBufferPtr						ipFeatureBufferDes;
	 
	 char									szLog[128] = {0};
	 sprintf(szLog, "��ʼת��Ҫ����%s", CString(strFeatureName.c_str()));
	 LOGSTR(szLog);

	 hRe = ipFeatureWorkspace->OpenFeatureClass(_bstr_t(strFeatureName.c_str()), &ipFeatureCls);
	 if (FAILED(hRe))
	 {
		 sprintf(szLog, "��Ҫ����%sʧ��,���ش�����Ϊ:%ld", strFeatureName.c_str(), (long)hRe);
		 LOGSTR(szLog);
		 return S_FALSE;
	 }

	 IWorkspaceEditPtr			ipWorkspaceEdit = m_WorkspaceDes;

	 ipWorkspaceEdit->StartEditing(VARIANT_TRUE);
	 ipWorkspaceEdit->StartEditOperation();

	 ipFeatureCls->get_Fields(&ipFlds);
	 ipFeatureCls->get_FeatureType(&FeatureType);
	 ipFeatureCls->get_ShapeFieldName(&strShapeName);
	 ipFeatureCls->get_CLSID(&uid);
	 ipFeatureCls->get_EXTCLSID(&uid2);

	 IFieldCheckerPtr	ipFieldChecker(CLSID_FieldChecker);

	 IFieldPtr		ipField;
	 IFieldsPtr		ipValidateFields;
	 IEnumFieldErrorPtr		ipFieldError;
	 IFieldErrorPtr		FError;
	 esriFieldNameErrorType		errType;

	 ipFieldChecker->putref_ValidateWorkspace(m_WorkspaceSrc);
	 ipFieldChecker->Validate(ipFlds, &ipFieldError, &ipValidateFields);

	 ipValidateFields->get_FieldCount(&lCountVal);

	 if (ipFieldError != NULL)
	 {
		 ipFieldError->Next(&FError);
		 FError->get_FieldError(&errType);
	 }

	 //��������domain��Χ add by chenyong 2013-12-2
	 long									lindex(0);
	 IFieldPtr								ipFieldShape;
	 IGeometryDefPtr						ipGeometryDef;
	 IGeometryDefEditPtr					ipGeometryDefEdit;


	 ipValidateFields->FindFieldByAliasName(_bstr_t("shape"), &lindex);
	 ipValidateFields->get_Field(lindex, &ipFieldShape);
	 ipFieldShape->get_GeometryDef(&ipGeometryDef);

	 ISpatialReferencePtr				ipSpatialSrc;
	 double								dXmin(0);
	 double								dYmin(0);
	 double								dXmax(0);
	 double								dYmax(0);

	 ipGeometryDef->get_SpatialReference(&ipSpatialSrc);
	 ipSpatialSrc->GetDomain(&dXmin, &dXmax, &dYmin, &dYmax);

	 //����ת�����domain��Χ
	 double								dXSrc[4] = {0};
	 double								dYSrc[4] = {0};
	 double								dXDes[4] = {0};
	 double								dYDes[4] = {0};
	 double								dZSrc[4] = {0};
	 double								dZDes[4] = {0};

	 dXSrc[0] = dXSrc[3] = dXmin;
	 dXSrc[1] = dXSrc[2] = dXmax;
	 dYSrc[0] = dYSrc[1] = dYmin;
	 dYSrc[2] = dYSrc[3] = dYmax;

	 for (int i = 0; i < 4; ++i)
	 {
		 m_Trans.TransSDEVector(dYSrc[i], dXSrc[i], dZSrc[i], dYDes[i], dXDes[i], dZDes[i]);
	 }


	 dXmin = dXmax = dXDes[0];
	 dYmin = dYmax = dYDes[0];

	 for (int i = 1; i < 4; ++i)
	 {
		 dXmax = (dXDes[i] > dXmax) ? dXDes[i] : dXmax;
		 dXmin = (dXDes[i] < dXmin) ? dXDes[i] : dXmin;
		 dYmax = (dYDes[i] > dYmax) ? dYDes[i] : dYmax;
		 dYmin = (dYDes[i] < dYmin) ? dYDes[i] : dYmin;
	 }

	 //ipSpatialSrc->SetDomain(dXmin, dXmax, dYmin, dYmax);

	 ISpatialReferenceFactoryPtr							ipSpatialFac(CLSID_SpatialReferenceEnvironment);
	 ISpatialReferencePtr								ipSpatial;

	 hRe = ipSpatialFac->CreateESRISpatialReferenceFromPRJFile(_bstr_t(m_strPrjFullPath.c_str()), &ipSpatial);
	 if (FAILED(hRe))
	 {
		 sprintf(szLog, "�����ռ�����ϵʧ��,���ش�����:%ld", (long)hRe);
		 LOGSTR(szLog);
		 return hRe;
	 }

	 ipSpatial->SetDomain(dXmin, dXmax, dYmin, dYmax);

	 ipGeometryDefEdit = ipGeometryDef;

	 ipGeometryDefEdit->putref_SpatialReference(/*ipSpatialSrc*/ipSpatial);

	 IFieldEditPtr			ipFieldEdit = ipFieldShape;
	 ipFieldEdit->putref_GeometryDef(ipGeometryDef);

	 hRe = pFeatureDS_Des->CreateFeatureClass(_bstr_t(strFeatureName.c_str()), /*ipFlds*/ipValidateFields, uid, uid2, FeatureType, strShapeName, _bstr_t(""), &ipFeatureCls_Des);
	 if (FAILED(hRe))
	 {
		 sprintf(szLog, "����Ҫ����%sʧ��,���ش�����Ϊ:%ld", strFeatureName.c_str(), (long)hRe);
		 LOGSTR(szLog);
		 return S_FALSE;
	 }

	// IQueryFilterPtr							ipQueryFilter(CLSID_QueryFilter);

	 //ipQueryFilter->AddField(_bstr_t("SHAPE"));

	 hRe = ipFeatureCls->Search(NULL, VARIANT_TRUE, &ipFeatureSor);
	 if (FAILED(hRe))
	 {
		 return S_FALSE;
	 }
	 ipFeatureSor->NextFeature(&ipFeature);


	 //���ӽ����� add by chenyong 2013-12-4
	 long					lFeatureCount(0);		//Ҫ���ܸ���
	 long					lFeatureDones(0);		//��ת��Ҫ�ظ���

	 ipFeatureCls->FeatureCount(NULL, &lFeatureCount);

	 unsigned int  Percent = (unsigned int)((lFeatureDones / lFeatureCount)*100);
	 ::SendMessage(m_hWnd, WM_PROGRESS, 0, Percent);


	 ipFeatureCls_Des->Insert(VARIANT_TRUE, &ipFeatureCursorDes);
	 ipFeatureCls_Des->CreateFeatureBuffer(&ipFeatureBufferDes);

	 while (NULL != ipFeature)
	 {
		 ipFeature->get_Shape(&ipGeometry);
		 ipGeometry->get_IsEmpty(&varIsExist);
		 if (varIsExist == VARIANT_TRUE)
		 {
			 continue;
		 }

		 ipGeometry->get_GeometryType(&GeometryType);

		 switch (GeometryType)
		 {
		 case esriGeometryPoint:

			 ipPoint = ipGeometry;

			 ipPoint->get_X(&dX_Src);
			 ipPoint->get_Y(&dY_Src);
			 //ipPoint->get_Z(&dZ_Src);

			 //�˴���Ҫ��ת������
			 m_Trans.TransSDEVector(dY_Src, dX_Src, dZ_Src, dY_Des, dX_Des, dZ_Des);

			 ipPoint->put_X(dX_Des);
			 ipPoint->put_Y(dY_Des);
			 ipPoint->put_Z(dZ_Des);

			 break;

		 case esriGeometryMultipoint:
		 case esriGeometryLine:
		 case esriGeometryPolyline:

			 ipPointCol = ipGeometry;
			 ipPointCol->get_PointCount(&lCount);

			 for (int i = 0; i < lCount; i++)
			 {
				 ipPointCol->get_Point(i, &iptempPoint);
				 iptempPoint->get_X(&dX_Src);
				 iptempPoint->get_Y(&dY_Src);
				 //iptempPoint->get_Z(&dZ_Src);

				 //�˴���Ҫ��ת�� ����
				 m_Trans.TransSDEVector(dY_Src, dX_Src, dZ_Src, dY_Des, dX_Des, dZ_Des);

				 iptempPoint->put_X(dX_Des);
				 iptempPoint->put_Y(dY_Des);
				 iptempPoint->put_Z(dZ_Des);

				 ipPointCol->UpdatePoint(i, iptempPoint);
			 }

			 break;

 		 case esriGeometryPolygon:

			
 			 /*
 				1.�ֳ����⻷����
 				2.������һ���㼯��������ʼ��������Σ���������ת��ʱ�����һ���㲻����
 			 */

 			 ipPolygon4 = ipGeometry;
 			 ipPolygon4->get_ExteriorRingBag(&ipGeometryBagExt);
 			 ipEnumGeometryExt = ipGeometryBagExt;
 			 ipEnumGeometryExt->Reset();
 			 ipEnumGeometryExt->Next(&ipGeometryExt);
 
 			 while(NULL != ipGeometryExt)
 			 {
 				 //1. deal with inner rings
 				 ipRingExt = ipGeometryExt;

				 hRe = ipPolygon4->get_InteriorRingBag(ipRingExt, &ipGeometryBagInn);
				 if (FAILED(hRe))
				 {
					 continue;
				 }
				 ipEnumGeometryInn = ipGeometryBagInn;
				 ipEnumGeometryInn->Reset();
				 ipEnumGeometryInn->Next(&ipGeometryInn);

				 while (NULL != ipGeometryInn)
				 {
					 ipRingInn = ipGeometryInn;
					 ipPointCol = ipRingInn;
					 ipPointCol->get_PointCount(&lCount);

					 for (int i = 0; i < lCount - 1; i++)
					 {
						 ipPointCol->get_Point(i, &iptempPoint);
						 iptempPoint->get_X(&dX_Src);
						 iptempPoint->get_Y(&dY_Src);
						 //iptempPoint->get_Z(&dZ_Src);

						 //�˴���Ҫ��ת�� ����
						 m_Trans.TransSDEVector(dY_Src, dX_Src, dZ_Src, dY_Des, dX_Des, dZ_Des);

						 iptempPoint->put_X(dX_Des);
						 iptempPoint->put_Y(dY_Des);
						 iptempPoint->put_Z(dZ_Des);

						 ipPointCol->UpdatePoint(i, iptempPoint);
					 }

					 ipEnumGeometryInn->Next(&ipGeometryInn);
				 }

				  //2. deal with external rings
 				 ipPointCol = ipRingExt;
 				 ipPointCol->get_PointCount(&lCount);
 
 				 for (int i = 0; i < lCount - 1; i++)
 				 {
 					 ipPointCol->get_Point(i, &iptempPoint);
 					 iptempPoint->get_X(&dX_Src);
 					 iptempPoint->get_Y(&dY_Src);
 					 //iptempPoint->get_Z(&dZ_Src);
 
 					 m_Trans.TransSDEVector(dY_Src, dX_Src, dZ_Src, dY_Des, dX_Des, dZ_Des);
 
 					 iptempPoint->put_X(dX_Des);
 					 iptempPoint->put_Y(dY_Des);
 					 iptempPoint->put_Z(dZ_Des);
 
 					 ipPointCol->UpdatePoint(i, iptempPoint);
 				 }
 				 
 
 				 ipEnumGeometryExt->Next(&ipGeometryExt);
 			 }	
 
 			 break;
		 }

		 //ipGeometry->SnapToSpatialReference();
		 ipGeometry->putref_SpatialReference(ipSpatial);

		 //alter by chenyong 2013-12-26
		 InsertFeature(ipFeatureCursorDes, ipFeatureBufferDes, ipFeature, ipGeometry);
		
		if (lFeatureDones % 100 == 0)
		{
			ipFeatureCursorDes->Flush();
		}
		
		 //������ add by chenyong 2013-12-4
		 ++lFeatureDones;

		 if (lFeatureDones % 10 == 0)
		 {
			 Percent = (unsigned int)(lFeatureDones*100 / lFeatureCount);
			 ::SendMessage(m_hWnd, WM_PROGRESS, 0, Percent);
		 }

		 ipFeatureSor->NextFeature(&ipFeature);
	 }

	 ipFeatureCursorDes->Flush();


	 ipWorkspaceEdit->StopEditOperation();
	 ipWorkspaceEdit->StopEditing(VARIANT_TRUE);

	::SendMessage(m_hWnd, WM_PROGRESS, 0, 100);

	sprintf(szLog, "���ת��Ҫ����%s", CString(strFeatureName.c_str()));
	LOGSTR(szLog);
	
	return S_OK;
 }

 HRESULT CArcSDEVector::InsertFeature(IFeatureCursorPtr ipInsertCur, IFeatureBufferPtr ipFeatureBuf, IFeaturePtr ipFeature, IGeometryPtr ipGeom)
 {
	 IFieldsPtr			ipFields;
	 ipFeature->get_Fields(&ipFields);

	 long		fieldCount = 0;
	 ipFields->get_FieldCount(&fieldCount);

	 IFieldPtr			ipField;

	 //skip OID and geometry fields
	 for (long i = 0; i < fieldCount; ++i)
	 {
		 ipFields->get_Field(i, &ipField);

		 esriFieldType	esriField;
		 ipField->get_Type(&esriField);

		 VARIANT_BOOL	varboolEdit;
		 ipField->get_Editable(&varboolEdit);

		 //skip OID and geometry fields;
		 if ((esriField != esriFieldTypeGeometry) && (esriFieldTypeGeometry != esriFieldTypeOID) && (varboolEdit))
		 {
			 CComVariant		origValue;
			 ipFeature->get_Value(i, &origValue);
			 ipFeatureBuf->put_Value(i, origValue);
		 }
	 }

	 ipFeatureBuf->putref_Shape(ipGeom);

	 CComVariant varID;

	 HRESULT hr = ipInsertCur->InsertFeature(ipFeatureBuf, &varID);
	 
	 return hr;
 }
