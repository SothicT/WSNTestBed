// NodeManageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "NodeManageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeManageDlg dialog


CNodeManageDlg::CNodeManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNodeManageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNodeManageDlg)
	m_strLocation = _T("");
	m_strSendPower = _T("");
	m_strChain = _T("");
	m_strDistance = _T("");
	m_strNodelD = _T("");
	m_strScence = _T("");
	//}}AFX_DATA_INIT
}


void CNodeManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeManageDlg)
	DDX_Control(pDX, IDC_LIST_NODEINFO, m_ctrlListNodeInfo);
	DDX_CBString(pDX, IDC_COMBO_LOCATION, m_strLocation);
	DDX_CBString(pDX, IDC_COMBO_SENDPOWER, m_strSendPower);
	DDX_Text(pDX, IDC_EDIT_CHAIN, m_strChain);
	DDX_Text(pDX, IDC_EDIT_DISTANCE, m_strDistance);
	DDX_Text(pDX, IDC_EDIT_NODEID, m_strNodelD);
	DDX_Text(pDX, IDC_EDIT_SCENEDISCRIBE, m_strScence);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeManageDlg, CDialog)
	//{{AFX_MSG_MAP(CNodeManageDlg)
	ON_BN_CLICKED(IDC_BTN_BACK, OnBtnBack)
	ON_NOTIFY(NM_CLICK, IDC_LIST_NODEINFO, OnClickListNodeinfo)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELTE, OnBtnDelte)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeManageDlg message handlers

void CNodeManageDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

BOOL CNodeManageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitNodeInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//�ڵ���Ϣ���ʼ��
void CNodeManageDlg::InitNodeInfo()
{
	int nCount=0;
	CHeaderCtrl *pHeaderCtrl=m_ctrlListNodeInfo.GetHeaderCtrl();
	if(pHeaderCtrl!=NULL)
		nCount=pHeaderCtrl->GetItemCount();
	for(int i=0;i<nCount;i++)
		m_ctrlListNodeInfo.DeleteColumn(0);
	m_ctrlListNodeInfo.DeleteAllItems();
	
	//���÷��,����,�п�
	m_ctrlListNodeInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrlListNodeInfo.InsertColumn(0,"�ڵ�ID",LVCFMT_CENTER,70); 
	m_ctrlListNodeInfo.InsertColumn(1,"����(m)",LVCFMT_CENTER,70); 
	m_ctrlListNodeInfo.InsertColumn(2,"����",LVCFMT_CENTER,70); 
	m_ctrlListNodeInfo.InsertColumn(3,"����(dBm)",LVCFMT_CENTER,70);  
	m_ctrlListNodeInfo.InsertColumn(4,"�����ŵ�",LVCFMT_CENTER,70);  

}

//����
void CNodeManageDlg::OnBtnBack() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CNodeManageDlg::OnClickListNodeinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int	n_item=m_ctrlListNodeInfo.GetSelectionMark();		
	m_strNodelD=m_ctrlListNodeInfo.GetItemText(n_item,0);
	m_strSendPower=m_ctrlListNodeInfo.GetItemText(n_item,1);
	m_strChain=m_ctrlListNodeInfo.GetItemText(n_item,2);
	m_strLocation=m_ctrlListNodeInfo.GetItemText(n_item,3);
	m_strDistance=m_ctrlListNodeInfo.GetItemText(n_item,4);

	UpdateData(FALSE);
	*pResult = 0;
}

void CNodeManageDlg::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
/*
	UpdateData(TRUE);	
	if (!m_strNodelD.IsEmpty())
	{		
		ADOConn m_AdoConn;
		_RecordsetPtr m_pRecordSet;
		m_AdoConn.OnInitADOConn();	
		
		CString strSQL;
		strSQL.Format("SELECT * FROM tb_NodeInfo WHERE NodeID='%s'",m_strNodelD);6+
		
		m_pRecordSet=m_AdoConn.GetRecordSet((_bstr_t)strSQL);
		
		if (!m_pRecordSet->adoEOF)
		{
			AfxMessageBox("����ʽ�Ѵ��ڣ�����������!");
			m_strModelName="";
			m_fModelWeight=0;
			m_strModelDescription="";
			UpdateData(FALSE);
			operatestate=0;
			return;
		}
		else
		{
			if (!IsModelCheckOK(m_fModelWeight))
			{
				operatestate=0;
				return;
			}		
			strSQL="";
			strSQL.Format("INSERT INTO tbModel(ModelName,ModelWeight,ModelDescription) VALUES('%s',%f,'%s')",m_strModelName,m_fModelWeight,m_strModelDescription);
			if (m_AdoConn.ExecuteSQL((_bstr_t)strSQL))
			{
				AfxMessageBox("���Ӽ�¼�ɹ�!");
			}		
			RefreshModelList();
		}
	}
	else
	{
		AfxMessageBox("��ʽ���Ʋ���Ϊ��!");
		operatestate=0;
		return;
	}
	*/
}

void CNodeManageDlg::OnBtnDelte() 
{
	// TODO: Add your control notification handler code here
	
}

void CNodeManageDlg::OnBtnDelete() 
{
	// TODO: Add your control notification handler code here
	
}

void CNodeManageDlg::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	
}

void CNodeManageDlg::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	
}
