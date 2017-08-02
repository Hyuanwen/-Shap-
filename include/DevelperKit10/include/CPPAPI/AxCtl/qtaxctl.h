/*
 COPYRIGHT © 2008 ESRI

 TRADE SECRETS: ESRI PROPRIETARY AND CONFIDENTIAL
 Unpublished material - all rights reserved under the
 Copyright Laws of the United States and applicable international
 laws, treaties, and conventions.

 For additional information, contact:
 Environmental Systems Research Institute, Inc.
 Attn: Contracts and Legal Services Department
 380 New York Street
 Redlands, California, 92373
 USA

 email: contracts@esri.com
*/

#ifndef __ESRI__ARCSDK__QTAXCTL_H__
#define __ESRI__ARCSDK__QTAXCTL_H__

#include <ArcSDK.h>

#if defined(ESRI_UNIX)
typedef WId           ESRIXWindowType;
typedef _XDisplay     ESRIXDisplayType;
typedef long          ESRIXScreenType;
#elif defined(ESRI_WINDOWS)
typedef WId           ESRIXWindowType;
typedef unsigned long ESRIXDisplayType;
typedef unsigned long ESRIXScreenType;
#endif /* ESRI_UNIX|ESRI_WINDOWS */

#include <AxCtl/AxContainer.h>
#include <AxCtl/ControlData.h>

class ESRI_EXT_CLASS QAxCtl
	: public QWidget
{
public:
	QAxCtl(const char *progID = NULL, QWidget *parent = NULL, const char *name = NULL);
	QAxCtl(const ControlDataPtr progID, QWidget *parent = NULL, const char *name = NULL);
	~QAxCtl();
	HRESULT getInterface(IUnknown **ppUnk);
	HRESULT setCursor(HCURSOR cur);
protected:
	bool eventFilter(QObject *qo, QEvent *qe);
#if defined(ESRI_UNIX)
	bool x11Event(XEvent *event);
#endif /* ESRI_UNIX */
private:
	char *m_sProgID;
	AxContainerPtr m_pAxCont;
	void initialize(const char *progID);
};

class ESRI_EXT_CLASS QAxApplication : public QApplication
{
public:
	QAxApplication(int &argc, char **argv);
	QAxApplication(int &argc, char **argv, bool GUIenabled);
	QAxApplication(int &argc, char **argv, Type type);
#ifdef ESRI_UNIX
	QAxApplication(Display *display, Qt::HANDLE visual=0, Qt::HANDLE colormap=0);
	QAxApplication(Display *display, int &argc, char **argv, Qt::HANDLE visual=0, Qt::HANDLE colormap=0);
	bool x11EventFilter(XEvent *event);
	static void printX11EventInfo(XEvent *event);
#endif /* ESRI_UNIX */
};

#endif /* __ESRI__ARCSDK__QTAXCTL_H__ */
