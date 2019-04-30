// LQ_Testbed.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "LQ_TestbedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLQ_TestbedApp

BEGIN_MESSAGE_MAP(CLQ_TestbedApp, CWinApp)
	//{{AFX_MSG_MAP(CLQ_TestbedApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLQ_TestbedApp construction

CLQ_TestbedApp::CLQ_TestbedApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLQ_TestbedApp object

CLQ_TestbedApp theApp;			//1、实例化应用程序类的对象（CWInAPP）
int m_curSceneID = -1;		//当前场景id
int m_curTestScheduleID = -1; //当前测试计划-1
int m_curTestID = 0;		//当前测试id
int m_curPackets = 0; //当前设置探测包总数

/////////////////////////////////////////////////////////////////////////////
// CLQ_TestbedApp initialization

BOOL CLQ_TestbedApp::InitInstance()		//2、调用应用程序类中的initinstance函数
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CLQ_TestbedDlg dlg;
	m_pMainWnd = &dlg;
	pdlg=&dlg;

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
