#if !defined(AFX_NODEMANAGEDLG_H__4EECCA82_595E_4C39_90DD_B6297F294AC0__INCLUDED_)
#define AFX_NODEMANAGEDLG_H__4EECCA82_595E_4C39_90DD_B6297F294AC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NodeManageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNodeManageDlg dialog

class CNodeManageDlg : public CDialog
{
// Construction
public:
	CNodeManageDlg(CWnd* pParent = NULL);   // standard constructor
	void InitNodeInfo();
// Dialog Data
	//{{AFX_DATA(CNodeManageDlg)
	enum { IDD = IDD_NODEMANAGE_DLG };
	CListCtrl	m_ctrlListNodeInfo;
	CString	m_strLocation;
	CString	m_strSendPower;
	CString	m_strChain;
	CString	m_strDistance;
	CString	m_strNodelD;
	CString	m_strScence;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNodeManageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNodeManageDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnBack();
	afx_msg void OnClickListNodeinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDelte();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnOk();
	afx_msg void OnBtnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NODEMANAGEDLG_H__4EECCA82_595E_4C39_90DD_B6297F294AC0__INCLUDED_)
