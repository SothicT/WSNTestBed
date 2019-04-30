#if !defined(AFX_EVLUATORMANAGEDLG_H__4BB3D157_AEB0_4B63_A1A9_0F89B322B977__INCLUDED_)
#define AFX_EVLUATORMANAGEDLG_H__4BB3D157_AEB0_4B63_A1A9_0F89B322B977__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EvluatorManageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEvluatorManageDlg dialog

class CEvluatorManageDlg : public CDialog
{
// Construction
public:
	CEvluatorManageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEvluatorManageDlg)
	enum { IDD = IDD_EVALUATORMANAGE_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEvluatorManageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEvluatorManageDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVLUATORMANAGEDLG_H__4BB3D157_AEB0_4B63_A1A9_0F89B322B977__INCLUDED_)
