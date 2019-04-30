// LinkEstimateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "LinkEstimateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinkEstimateDlg dialog


CLinkEstimateDlg::CLinkEstimateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLinkEstimateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinkEstimateDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLinkEstimateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinkEstimateDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinkEstimateDlg, CDialog)
	//{{AFX_MSG_MAP(CLinkEstimateDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinkEstimateDlg message handlers

void CLinkEstimateDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}
