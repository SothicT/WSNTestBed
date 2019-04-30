// EvaluatorAnalysisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "EvaluatorAnalysisDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEvaluatorAnalysisDlg dialog


CEvaluatorAnalysisDlg::CEvaluatorAnalysisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEvaluatorAnalysisDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEvaluatorAnalysisDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEvaluatorAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEvaluatorAnalysisDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEvaluatorAnalysisDlg, CDialog)
	//{{AFX_MSG_MAP(CEvaluatorAnalysisDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEvaluatorAnalysisDlg message handlers

void CEvaluatorAnalysisDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}
