#if !defined(AFX_SCENECONFIGDLG_H__81C7C429_B634_45FC_873A_0DEC31927E97__INCLUDED_)
#define AFX_SCENECONFIGDLG_H__81C7C429_B634_45FC_873A_0DEC31927E97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SceneConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSceneConfigDlg dialog

class CSceneConfigDlg : public CDialog
{
// Construction
public:
	CSceneConfigDlg(CWnd* pParent = NULL);   // standard constructor
	int  nCurItem;
	void InitSceneCombo();
	void FromScenceNameToSceneInfo(CString strSceneName);
	void FromScenceIDToSceneInfo(int nSceneID);
// Dialog Data
	//{{AFX_DATA(CSceneConfigDlg)
	enum { IDD = IDD_SCENECONFIG_DLG };
	CComboBox	m_ctrlComboOldScene;
	CComboBox	m_ctrlComboPower;
	CComboBox	m_ctrlComboLocation;
	CComboBox	m_ctrlComboChannel;
	CListCtrl	m_ctrlListNodeInfo;
	CString	m_strSceneDescribe;
	CString	m_strNodeID;
	double	m_dDistance;
	int		m_nFunction;
	CString	m_strSceneName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSceneConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSceneConfigDlg)
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnOk();
	afx_msg void OnBtnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListNodeinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioReConfig();
	afx_msg void OnRadioUseOldConfig();
	afx_msg void OnSelchangeComboOld();
	afx_msg void OnBtnDeleteScene();
	afx_msg void OnRadioShowCurInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCENECONFIGDLG_H__81C7C429_B634_45FC_873A_0DEC31927E97__INCLUDED_)
