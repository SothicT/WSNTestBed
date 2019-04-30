#if !defined(AFX_TESTCUSTOMDLG_H__A980AC37_B35D_48FF_BDA7_F20417AAD040__INCLUDED_)
#define AFX_TESTCUSTOMDLG_H__A980AC37_B35D_48FF_BDA7_F20417AAD040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestCustomDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestCustomDlg dialog

class CTestCustomDlg : public CDialog
{
// Construction
public:
	CTestCustomDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestCustomDlg)
	enum { IDD = IDD_TESTCUSTOM_DLG };
	CListCtrl	m_ctrlListCustomInfo;
	CString	m_strNodeID;
	CString	m_strTestModel;
	int		m_iPackets;
	CString	m_strSendRate;
	int		m_iTestTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCustomDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestCustomDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCUSTOMDLG_H__A980AC37_B35D_48FF_BDA7_F20417AAD040__INCLUDED_)
