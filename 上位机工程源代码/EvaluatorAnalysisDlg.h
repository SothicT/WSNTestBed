#if !defined(AFX_EVALUATORANALYSISDLG_H__5C34A5F5_8079_4632_90FA_8412A4B84CD4__INCLUDED_)
#define AFX_EVALUATORANALYSISDLG_H__5C34A5F5_8079_4632_90FA_8412A4B84CD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EvaluatorAnalysisDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEvaluatorAnalysisDlg dialog

class CEvaluatorAnalysisDlg : public CDialog
{
// Construction
public:
	CEvaluatorAnalysisDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEvaluatorAnalysisDlg)
	enum { IDD = IDD_EVALUATORANALYSIS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEvaluatorAnalysisDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEvaluatorAnalysisDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVALUATORANALYSISDLG_H__5C34A5F5_8079_4632_90FA_8412A4B84CD4__INCLUDED_)
