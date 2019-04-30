// LQ_Testbed.h : main header file for the LQ_TESTBED application
//

#if !defined(AFX_LQ_TESTBED_H__B8611BC0_A151_471C_A301_BAB178C33A72__INCLUDED_)
#define AFX_LQ_TESTBED_H__B8611BC0_A151_471C_A301_BAB178C33A72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "ADOConn.h"
#include "ServerComm.h"
#include "LQ_TestbedDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CLQ_TestbedApp:
// See LQ_Testbed.cpp for the implementation of this class
//

int   extern  m_curSceneID;
int   extern  m_curTestScheduleID;
int   extern  m_curTestID;
int   extern  m_curPackets;

class CLQ_TestbedApp : public CWinApp
{
public:

	BOOL m_bIsRunning;//标识平台是否正在运行	
	CLQ_TestbedDlg *pdlg;
 	CServerComm m_ServerComm;//串口操作对象

public:
	CLQ_TestbedApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLQ_TestbedApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLQ_TestbedApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LQ_TESTBED_H__B8611BC0_A151_471C_A301_BAB178C33A72__INCLUDED_)
