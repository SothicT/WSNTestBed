#if !defined(AFX_LINKESTIMATEDLG_H__EE6AA982_6A08_4F83_BDBE_0052A1448E9B__INCLUDED_)
#define AFX_LINKESTIMATEDLG_H__EE6AA982_6A08_4F83_BDBE_0052A1448E9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LinkEstimateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLinkEstimateDlg dialog

class CLinkEstimateDlg : public CDialog
{
// Construction
public:
	CLinkEstimateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLinkEstimateDlg)
	enum { IDD = IDD_LINKESTIMATE_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinkEstimateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLinkEstimateDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINKESTIMATEDLG_H__EE6AA982_6A08_4F83_BDBE_0052A1448E9B__INCLUDED_)
