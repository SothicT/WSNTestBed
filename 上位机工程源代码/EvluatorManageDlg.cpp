// EvluatorManageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "EvluatorManageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEvluatorManageDlg dialog


CEvluatorManageDlg::CEvluatorManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEvluatorManageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEvluatorManageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEvluatorManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEvluatorManageDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEvluatorManageDlg, CDialog)
	//{{AFX_MSG_MAP(CEvluatorManageDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEvluatorManageDlg message handlers

void CEvluatorManageDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}
