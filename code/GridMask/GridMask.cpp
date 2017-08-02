/*
*Copyright (C) 2012 ,Juno 
*All	rights	reserved.
*
*File Name:	GridMask.cpp
*
*Function:	Interface of  base class
*
*Author:	Juno
*
*E-mail:	http://lyflxr@yahoo.cn
*
*Version:	0.1
*/
#include "stdafx.h"
/**
 * ����������ʸ��������Ӹ���
 * @param pszDSName: ʸ�����ݵ�·����������
 * @param pszGridDSName: ���ɵĸ����ļ�����·��
 * @param step: �����������������ľ���
 * @return :�ɹ��򷵻�1��ʧ�ܷ���-1
 **/
GRID_MASK_API int GeneralGridForShp(const char *pszDSName, const char *pszGridDSName, /*const*/ double step)
{
	if(pszDSName == NULL || pszGridDSName == NULL || step <= 0)
	{
		return -1;
	}

	OGRRegisterAll();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");
	CPLSetConfigOption("SHAPE_ENCODING","");

	OGRDataSource *poDS = OGRSFDriverRegistrar::Open(pszDSName);
	if(poDS == NULL)
	{
		//�жϣ��������Դ��ʧ�ܣ����˳�
		::MessageBox(NULL, TEXT("������Դʧ��"), TEXT("��ʾ��Ϣ"), MB_OK);
		return -1;
	}

	OGRLayer *poLayer = poDS->GetLayer(0);
	OGREnvelope oEnvelope;
	poLayer->GetExtent(&oEnvelope);

	const char *pszDriverName = "ESRI Shapefile";
	OGRSFDriver *poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(pszDriverName);
	if(poDriver == NULL)
	{
		::MessageBox ( NULL,NULL, NULL, MB_OK ); 
		return -1;
	}

	BOOL ret= DeleteFileA(pszGridDSName);	

	OGRDataSource *poGridDS = poDriver->CreateDataSource(pszGridDSName,NULL);
	if(poGridDS == NULL)
	{
		::MessageBox ( NULL,NULL, NULL, MB_OK ); 
		return -1;
	}

	OGRLayer *poGridLayer = poGridDS->CreateLayer("gridlayer", poLayer->GetSpatialRef(), wkbLineString,NULL);
	if(poGridLayer == NULL)
	{
		::MessageBox ( NULL,NULL, NULL, MB_OK ); 
		return -1;
	}

	OGRFieldDefn oField("GRID", OFTInteger);
	poGridLayer->CreateField(&oField);

	int count = 1;
	double currentX = oEnvelope.MinX + step;
	while(currentX < oEnvelope.MaxX)
	{
		OGRLineString oLine;
		oLine.addPoint(currentX, oEnvelope.MinY);
		oLine.addPoint(currentX, oEnvelope.MaxY);
		oLine.addPoint(oEnvelope.MinX, oEnvelope.MaxY);
		oLine.addPoint(oEnvelope.MinX, oEnvelope.MinY);
		
		OGRFeature *poFeature = OGRFeature::CreateFeature(poGridLayer->GetLayerDefn());
		poFeature->SetGeometry(&oLine);
		poFeature->SetField("GRID", count);

		poGridLayer->CreateFeature(poFeature);
		OGRFeature::DestroyFeature(poFeature);

		currentX += step;
		count++;
	}

	double currentY = oEnvelope.MaxY - step;
	while(currentY > oEnvelope.MinY)
	{
		OGRLineString oLine;
		oLine.addPoint(oEnvelope.MinX, currentY);
		oLine.addPoint(oEnvelope.MaxX, currentY);
		oLine.addPoint(oEnvelope.MaxX,oEnvelope.MaxY);
		oLine.addPoint(oEnvelope.MinX, oEnvelope.MaxY);		
		
		OGRFeature *poFeature = OGRFeature::CreateFeature(poGridLayer->GetLayerDefn());
		poFeature->SetGeometry(&oLine);
		poFeature->SetField("GRID", count);

		poGridLayer->CreateFeature(poFeature);
		OGRFeature::DestroyFeature(poFeature);

		currentY -= step;
		count++;
	}

	OGRDataSource::DestroyDataSource(poGridDS);
	OGRDataSource::DestroyDataSource(poDS);

	return 1;
}
