
// LQ_TestbedDlg.h : header file
//
//{{AFX_INCLUDES()
#include "iplotx.h"
//}}AFX_INCLUDES

#if !defined(AFX_LQ_TESTBEDDLG_H__300155E7_8D79_4E96_B424_E5FCB051C52C__INCLUDED_)
#define AFX_LQ_TESTBEDDLG_H__300155E7_8D79_4E96_B424_E5FCB051C52C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include  "HighResolutionTimer.h"
/////////////////////////////////////////////////////////////////////////////
// CLQ_TestbedDlg dialog
#define  ALLOW_ACCESS_NODES 20
struct BasicConfig
{	
	int m_nSerialPort;
	int m_nSerialPortBaud;
};

class CLQ_TestbedDlg : public CDialog
{
public:
	CString   m_strStartTime;

//添加工具栏
	CToolBarCtrl	m_ToolBar;		
	CImageList		m_ImageList;
    bool            m_bOpenUart; //开启串口标志

	bool			m_bStartTest;//开启测试标志	
	bool			m_bStartTestSchedule; //开始测试计划

	int  NodeList[ALLOW_ACCESS_NODES]; //记录节点号与对应的channel
//	bool		    m_bSendCmd;//发送命令
//	int				isSendSuccess[ALLOW_ACCESS_NODES]; //确保成功

	CHighResolutionTimer mm_Timer; //毫秒计时器
//状态栏
	CStatusBarCtrl		m_wndStatusBar;
// Construction
public:
	void PreProcessing();
	void NewTest();

	CLQ_TestbedDlg(CWnd* pParent = NULL);	// standard constructor
  
	void InitPacketInfo();
	void InitLogListInfo();
	void InitRealTimePlots();
	void AddLogText(CString strMsg);
static	void TimerCallback(DWORD dwUser);
// Dialog Data
	//{{AFX_DATA(CLQ_TestbedDlg)
	enum { IDD = IDD_LQ_TESTBED_DIALOG };
	CListCtrl	m_ctrlLogList;
	CListCtrl	m_ctrlListPacketInfo;
	CiPlotX	m_ctrlPlotx;
	int		m_iSelection;
	int		m_nPktSum; //包总数
	CTime	m_EDate;
	CTime	m_ETime;
	int		m_IntervalTime;
	CTime	m_SDate;
	CTime	m_STime;
	int		m_nSendPeriod;
	int		m_nTestModel;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLQ_TestbedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	afx_msg LRESULT OnCmdFeedbackMsg(WPARAM wParam,LPARAM lParam);
	// Generated message map functions
	//{{AFX_MSG(CLQ_TestbedDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnMenuBaseSet();
	afx_msg void OnMenuStart();
	afx_msg void OnMenuClose();
	afx_msg void OnMenuExit();
	afx_msg void OnClose();
	afx_msg void OnMenuSceneConfig();
	afx_msg void OnMenuTestCustom();
	afx_msg void OnRadioRSSIRealTime();
	afx_msg void OnRadioLQIRealTime();
	afx_msg void OnRadioSNRRealTime();
	afx_msg void OnBtnConfigCmd();
	afx_msg void OnBtnSubmitSchedule();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMenuExportdata();
	afx_msg void OnChangeEditMsgSum();
	afx_msg void OnBtnWithdrawSchedule();
	afx_msg void OnAboutbox();
	afx_msg void OnChangeEditSendperiod();
	afx_msg void OnMenuCurResultShow();
	afx_msg void OnMenuOldresult();
	afx_msg void OnMenuLQP();
	afx_msg void OnMenuDatamanage();
	afx_msg void OnMenuDisplayTopology();
	afx_msg void OnMenuPower();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditT();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LQ_TESTBEDDLG_H__300155E7_8D79_4E96_B424_E5FCB051C52C__INCLUDED_)
