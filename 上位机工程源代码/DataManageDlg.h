
#if !defined(AFX_DATAMANAGEDLG_H__010CDF72_EAEE_435A_A3C7_C3B0063597DD__INCLUDED_)
#define AFX_DATAMANAGEDLG_H__010CDF72_EAEE_435A_A3C7_C3B0063597DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataManageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataManageDlg dialog

class CDataManageDlg : public CDialog
{
// Construction
public:
	BOOL m_bBackUp;
	
	int  nSearchSceneID;
	int  nSearchScheduleID;

	CString  strSceneName;
	CString  strScheduleTime;

	void InitSceneNameCombo();
	void InitScheduleTimeCombo();

	CDataManageDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CDataManageDlg)
	enum { IDD = IDD_DATAMANAGE_DLG };
	CComboBox	m_ctrlComboTestTime;
	CComboBox	m_ctrlComboSceneName;
	CString	m_strSceneDescrible;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataManageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataManageDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnExporttestinfo();
	afx_msg void OnBtnDeleteData();
	afx_msg void OnBtnBackUp();
	afx_msg void OnBtnRestore();
	afx_msg void OnBtnExportSceneinfo();
	afx_msg void OnBtnExportNodeinfo();
	afx_msg void OnBtnExportSchedule();
	afx_msg void OnBtnPacketinfo();
	afx_msg void OnSelchangeComboScene();
	afx_msg void OnSelchangeComboSchedule();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAMANAGEDLG_H__010CDF72_EAEE_435A_A3C7_C3B0063597DD__INCLUDED_)
