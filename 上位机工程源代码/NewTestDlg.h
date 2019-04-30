#if !defined(AFX_NEWTESTDLG_H__EE020C5A_EFA2_4884_A20D_F39DD9E38BA0__INCLUDED_)
#define AFX_NEWTESTDLG_H__EE020C5A_EFA2_4884_A20D_F39DD9E38BA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewTestDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewTestDlg dialog

class CNewTestDlg : public CDialog
{
// Construction
public:
	CNewTestDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewTestDlg)
	enum { IDD = IDD_NEWTEST_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewTestDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWTESTDLG_H__EE020C5A_EFA2_4884_A20D_F39DD9E38BA0__INCLUDED_)
