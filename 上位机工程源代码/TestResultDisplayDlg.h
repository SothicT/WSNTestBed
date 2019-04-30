//{{AFX_INCLUDES()
#include "iplotx.h"
//}}AFX_INCLUDES
#if !defined(AFX_TESTRESULTDISPLAYDLG_H__3309FFFA_0760_4093_A936_CFFF961DF73E__INCLUDED_)
#define AFX_TESTRESULTDISPLAYDLG_H__3309FFFA_0760_4093_A936_CFFF961DF73E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestResultDisplayDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestResultDisplayDlg dialog

class CTestResultDisplayDlg : public CDialog
{
// Construction
public:
	void RefreshPlotShow();
	void InitPlotDisplay();
	void InitTestResultInfoList();
	void InitSceneNameCombo();
	void InitScheduleTimeCombo();
	void FromScenceIDToSceneInfo(int nSceneID);
	CTestResultDisplayDlg(CWnd* pParent = NULL);   // standard constructor
	int  NodeList[ALLOW_ACCESS_NODES]; //记录节点号与对应的channel

	int  nSearchSceneID;
	int  nSearchScheduleID;
    
// Dialog Data
	//{{AFX_DATA(CTestResultDisplayDlg)
	enum { IDD = IDD_TESTRESULTDISPLAY_DLG };
	CComboBox	m_ctrlComboTestTime;
	CComboBox	m_ctrlComboSceneName;
	CListCtrl	m_ctrlResultInfoList;
	CiPlotX	m_ctrlPlotx;
	CString	m_strEndTime;
	CString	m_strSceneDescribe;
	CString	m_strTestPackets;
	CString	m_strSendPeriod;
	CString	m_strTestMode;
	CString	m_strTestPeriod;
	int		m_nSelectNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestResultDisplayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestResultDisplayDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSelChangeComboSceneName();
	afx_msg void OnSelChangeComboScheduleTime();
	afx_msg void OnBtnDataView();
	afx_msg void OnRadioTime2PRR();
	afx_msg void OnRadioTime2RssiDown();
	afx_msg void OnRadioTime2rssiup();
	afx_msg void OnRadioTime2lqidown();
	afx_msg void OnRadioTime2lqiup();
	afx_msg void OnRadioTime2snrdown();
	afx_msg void OnRadioTime2snrup();
	afx_msg void OnBtnExport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTRESULTDISPLAYDLG_H__3309FFFA_0760_4093_A936_CFFF961DF73E__INCLUDED_)
