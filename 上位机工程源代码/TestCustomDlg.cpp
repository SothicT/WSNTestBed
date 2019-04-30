// TestCustomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "TestCustomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestCustomDlg dialog


CTestCustomDlg::CTestCustomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestCustomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestCustomDlg)
	m_strNodeID = _T("");
	m_strTestModel = _T("");
	m_iPackets = 0;
	m_strSendRate = _T("");
	m_iTestTime = 0;
	//}}AFX_DATA_INIT
}


void CTestCustomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestCustomDlg)
	DDX_Control(pDX, IDC_LIST_CUSTOMINFO, m_ctrlListCustomInfo);
	DDX_CBString(pDX, IDC_COMBO_NODEID, m_strNodeID);
	DDX_CBString(pDX, IDC_COMBO_TESTMODEL, m_strTestModel);
	DDX_Text(pDX, IDC_EDIT_PACKETS, m_iPackets);
	DDX_Text(pDX, IDC_EDIT_SENDRATE, m_strSendRate);
	DDX_Text(pDX, IDC_EDIT_TESTTIME, m_iTestTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestCustomDlg, CDialog)
	//{{AFX_MSG_MAP(CTestCustomDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestCustomDlg message handlers

void CTestCustomDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

BOOL CTestCustomDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int nCount=0;
	CHeaderCtrl *pHeaderCtrl=m_ctrlListCustomInfo.GetHeaderCtrl();
	if(pHeaderCtrl!=NULL)
		nCount=pHeaderCtrl->GetItemCount();
	for(int i=0;i<nCount;i++)
	  m_ctrlListCustomInfo.DeleteColumn(0);
	m_ctrlListCustomInfo.DeleteAllItems();
	
	//设置风格,列名,列宽
	m_ctrlListCustomInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrlListCustomInfo.InsertColumn(0,"节点ID",LVCFMT_CENTER,60); 
	m_ctrlListCustomInfo.InsertColumn(1,"探测包总数",LVCFMT_CENTER,80); 
	m_ctrlListCustomInfo.InsertColumn(2,"测试次数",LVCFMT_CENTER,70); 
	m_ctrlListCustomInfo.InsertColumn(3,"探测方式",LVCFMT_CENTER,70); 
	m_ctrlListCustomInfo.InsertColumn(4,"发送频率",LVCFMT_CENTER,70); 

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


