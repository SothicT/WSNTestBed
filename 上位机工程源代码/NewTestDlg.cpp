// NewTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "NewTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewTestDlg dialog


CNewTestDlg::CNewTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNewTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewTestDlg, CDialog)
	//{{AFX_MSG_MAP(CNewTestDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewTestDlg message handlers

void CNewTestDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}
