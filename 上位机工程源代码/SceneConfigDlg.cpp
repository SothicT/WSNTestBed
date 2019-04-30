// SceneConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "SceneConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSceneConfigDlg dialog


CSceneConfigDlg::CSceneConfigDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSceneConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSceneConfigDlg)
	m_strSceneDescribe = _T("");
	m_strNodeID = _T("");
	m_dDistance = 0.0;
	nCurItem = -1;
	m_nFunction = 0;
	m_strSceneName = _T("");
	//}}AFX_DATA_INIT
}


void CSceneConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSceneConfigDlg)
	DDX_Control(pDX, IDC_COMBO_OLD, m_ctrlComboOldScene);
	DDX_Control(pDX, IDC_COMBO_SENDPOWER, m_ctrlComboPower);
	DDX_Control(pDX, IDC_COMBO_LOCATION, m_ctrlComboLocation);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_ctrlComboChannel);
	DDX_Control(pDX, IDC_LIST_NODEINFO, m_ctrlListNodeInfo);
	DDX_Text(pDX, IDC_EDIT_SCENEDISCRIBE, m_strSceneDescribe);
	DDX_Text(pDX, IDC_EDIT_NODEID, m_strNodeID);
	DDX_Text(pDX, IDC_EDIT_DISTANCE, m_dDistance);
	DDX_Radio(pDX, IDC_RADIO_SHOWCURINFO, m_nFunction);
	DDX_Text(pDX, IDC_EDIT_SCENENAME, m_strSceneName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSceneConfigDlg, CDialog)
//{{AFX_MSG_MAP(CSceneConfigDlg)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
ON_NOTIFY(NM_CLICK, IDC_LIST_NODEINFO, OnClickListNodeinfo)
ON_BN_CLICKED(IDC_RADIO_FUNCTION, OnRadioReConfig)
ON_BN_CLICKED(IDC_RADIO2, OnRadioUseOldConfig)
ON_CBN_SELCHANGE(IDC_COMBO_OLD, OnSelchangeComboOld)
ON_BN_CLICKED(IDC_BTN_DELETESCENE, OnBtnDeleteScene)
ON_BN_CLICKED(IDC_RADIO_SHOWCURINFO, OnRadioShowCurInfo)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSceneConfigDlg message handlers

void CSceneConfigDlg::OnBtnAdd() 
{
	UpdateData(TRUE);
	CString strDistance, strLocation, strSendingPower, strChannel;
	if (m_strNodeID.IsEmpty())
	{
		AfxMessageBox("节点id不能为空!");
		return;
	}
	if (m_dDistance<0)
	{
		AfxMessageBox("请填写一个大于等于'0'的数!");
		return;
	}
	strDistance.Format("%f",m_dDistance);
	m_ctrlComboLocation.GetWindowText(strLocation);
	m_ctrlComboPower.GetWindowText(strSendingPower);
	m_ctrlComboChannel.GetWindowText(strChannel);
	
	int nItem=m_ctrlListNodeInfo.GetItemCount();	
	m_ctrlListNodeInfo.InsertItem(nItem,m_strNodeID);
	m_ctrlListNodeInfo.SetItemText(nItem,1,strDistance);	
	m_ctrlListNodeInfo.SetItemText(nItem,2,strLocation);
	m_ctrlListNodeInfo.SetItemText(nItem,3,strSendingPower);
	m_ctrlListNodeInfo.SetItemText(nItem,4,strChannel);
	
	UpdateData(FALSE);
}

void CSceneConfigDlg::OnBtnDelete() 
{
	UpdateData(TRUE);
	if (m_strNodeID != "" && nCurItem != -1)
	{
		m_ctrlListNodeInfo.DeleteItem(nCurItem);
		nCurItem = -1;
		m_strNodeID = "";
		m_dDistance =0.0;
		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox("选择要删除的数据行!");
	}
	
}


void CSceneConfigDlg::OnBtnOk() 
{
	UpdateData(TRUE);
	if (m_nFunction == 1) //重新部署
	{
		if (!m_strSceneName.IsEmpty())
		{		
			ADOConn m_AdoConn;
			_RecordsetPtr m_pRecordSet;
			m_AdoConn.OnInitADOConn();	
			
			CString strSQL;
			strSQL.Format("SELECT * FROM tb_SceneInfo WHERE SceneName='%s'",m_strSceneName);
			
			m_pRecordSet=m_AdoConn.GetRecordSet((_bstr_t)strSQL);
			
			if (!m_pRecordSet->adoEOF)
			{
				AfxMessageBox("该场景名称已存在，请重新输入!");
				m_strSceneName="";
				UpdateData(FALSE);
				return;
			}
			else
			{
				if (m_ctrlListNodeInfo.GetItemCount()<1)
				{
					AfxMessageBox("请登记节点信息");
					return;
				}
				else
				{
					
					CTime nTime=CTime::GetCurrentTime();
					CString strDate=nTime.Format("%Y-%m-%d ");
					CString	strTime=nTime.Format("%H:%M:%S");
					strTime =strDate+strTime;
					
					
					strSQL.Format("INSERT INTO tb_SceneInfo(SceneName,SceneDescribe,DeploymentTime) VALUES('%s','%s','%s')",m_strSceneName,m_strSceneDescribe,strTime);						
					
					try
					{
						//事件start
						m_AdoConn.m_pConnection->BeginTrans(); 
						m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
						
						strSQL.Format("SELECT * FROM tb_SceneInfo WHERE SceneID=(SELECT MAX(SceneID) FROM tb_SceneInfo)");
						m_pRecordSet=m_AdoConn.GetRecordSet((_bstr_t)strSQL);
						if(!m_pRecordSet->adoEOF)
						{
							m_curSceneID = atoi(VariantToCString(m_pRecordSet->GetCollect("SceneID")));						 
						}
						int i=0;
						CString  strNodeID, strSendingPower, strChannel, strLocation, strDistance;
						while (i<m_ctrlListNodeInfo.GetItemCount())
						{	
							strNodeID = m_ctrlListNodeInfo.GetItemText(i,0);
							strDistance =  m_ctrlListNodeInfo.GetItemText(i,1);
							strLocation =  m_ctrlListNodeInfo.GetItemText(i,2);
							strSendingPower =  m_ctrlListNodeInfo.GetItemText(i,3);
							strChannel = m_ctrlListNodeInfo.GetItemText(i,4);
							
							strSQL.Format("INSERT INTO tb_NodeInfo(SceneID,NodeID,Power,Channel,Direction,Distance) VALUES('%d','%s','%s','%s','%s','%s')", m_curSceneID,
								strNodeID,strSendingPower,strChannel,strLocation,strDistance);
							
							m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
							i++;
						}
						m_AdoConn.m_pConnection->CommitTrans(); //事件end	
						
						InitSceneCombo();
						m_nFunction = 0;
						OnRadioShowCurInfo();
						UpdateData(FALSE);

						AfxMessageBox("部署完毕，数据已提交！");
					}
					catch (_com_error e)
					{
						m_AdoConn.m_pConnection->RollbackTrans();//回滚事务
						AfxMessageBox(e.ErrorMessage());						
					}
					
					
				}
			}
		}
		else
		{
			AfxMessageBox("场景名称不能为空!");
			return;
		}	
		
	}
	else if(m_nFunction == 2)
	{
		m_nFunction = 0;
		OnRadioShowCurInfo();
		UpdateData(FALSE);
		AfxMessageBox("已切换到历史场景");
	}
	
	((CLQ_TestbedApp*)AfxGetApp())->pdlg->AddLogText("网络部署完成");
	CDialog::OnOK();
}

void CSceneConfigDlg::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

BOOL CSceneConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here	
	InitSceneCombo();
	m_ctrlComboOldScene.EnableWindow(FALSE);
	
	//初始化节点列表
	int nCount=0;
	CHeaderCtrl *pHeaderCtrl=m_ctrlListNodeInfo.GetHeaderCtrl();
	if(pHeaderCtrl!=NULL)
		nCount=pHeaderCtrl->GetItemCount();
	for(int i=0;i<nCount;i++)
		m_ctrlListNodeInfo.DeleteColumn(0);
	m_ctrlListNodeInfo.DeleteAllItems();
	
	//设置风格,列名,列宽
	m_ctrlListNodeInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrlListNodeInfo.InsertColumn(0,"节点ID",LVCFMT_CENTER,80); 
	m_ctrlListNodeInfo.InsertColumn(1,"距离(m)",LVCFMT_CENTER,80); 
	m_ctrlListNodeInfo.InsertColumn(2,"方向",LVCFMT_CENTER,80); 
	m_ctrlListNodeInfo.InsertColumn(3,"功率(dBm)",LVCFMT_CENTER,80);  
	m_ctrlListNodeInfo.InsertColumn(4,"工作信道",LVCFMT_CENTER,80);  
	
    //方向
	m_ctrlComboLocation.AddString("正北");
	m_ctrlComboLocation.AddString("东北");
	m_ctrlComboLocation.AddString("正东");
	m_ctrlComboLocation.AddString("东南");
	m_ctrlComboLocation.AddString("正南");
	m_ctrlComboLocation.AddString("西南");
	m_ctrlComboLocation.AddString("正西");
	m_ctrlComboLocation.AddString("西北");
	
    m_ctrlComboLocation.SelectString(-1,"正北");
	//发射功率
	for (int i=0;i<8;i++)
	{
		CString strPowerNum;
		strPowerNum.Format("%d",3+4*i);
		m_ctrlComboPower.AddString(strPowerNum);
	}
	
    m_ctrlComboPower.SelectString(-1,"31");
	
	//工作信道
	for(int i=0;i<=26;i++)
	{
		CString strChannelNum;
		strChannelNum.Format("%d",i);
		m_ctrlComboChannel.AddString(strChannelNum);
	}
    m_ctrlComboChannel.SelectString(-1,"26");
	
	//
	if (m_curSceneID != -1) 
	{
		FromScenceIDToSceneInfo(m_curSceneID);		
	}
	OnRadioShowCurInfo();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSceneConfigDlg::InitSceneCombo()
{
	//初始化历史部署
	m_ctrlComboOldScene.ResetContent();
	ADOConn m_AdoConn;
	_RecordsetPtr m_pRecordSet;
	m_AdoConn.OnInitADOConn();
	
	CString strSQL;
	strSQL.Format("SELECT * FROM tb_SceneInfo ");
	m_pRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	if (m_pRecordSet->adoEOF)
	{
		m_ctrlComboOldScene.SetWindowText("无");
	}
	else
	{
		while(!m_pRecordSet->adoEOF)
		{
			CString strSceneName;
			strSceneName = VariantToCString(m_pRecordSet->GetCollect("SceneName"));
			m_ctrlComboOldScene.AddString(strSceneName);	
			
			m_pRecordSet->MoveNext();	
		}
	}
}

void CSceneConfigDlg::FromScenceNameToSceneInfo(CString strSceneName)
{
	ADOConn m_AdoConn;
	_RecordsetPtr m_pRecordSet;
	m_AdoConn.OnInitADOConn();	
	
	CString strSQL;
	strSQL.Format("SELECT * FROM tb_SceneInfo WHERE SceneName='%s'",strSceneName);
	m_pRecordSet=m_AdoConn.GetRecordSet((_bstr_t)strSQL);		
	if (!m_pRecordSet->adoEOF)
	{
		m_curSceneID = atoi(VariantToCString(m_pRecordSet->GetCollect("SceneID")));	
		m_strSceneName = VariantToCString(m_pRecordSet->GetCollect("SceneName"));
		m_strSceneDescribe = VariantToCString(m_pRecordSet->GetCollect("SceneDescribe"));
		
	}
	
	strSQL.Format("SELECT * FROM tb_NodeInfo WHERE SceneID=%d",m_curSceneID);
	m_pRecordSet=m_AdoConn.GetRecordSet((_bstr_t)strSQL);	
	CString  strNodeID, strSendingPower, strChannel, strLocation, strDistance;
	
	m_ctrlListNodeInfo.DeleteAllItems();
	
	int i = 0;	
	while(!m_pRecordSet->adoEOF)
	{
		
		int nodeID =atoi(VariantToCString(m_pRecordSet->GetCollect("NodeID")));
		strNodeID.Format("%d",nodeID);
		
		int nPower=atoi( VariantToCString(m_pRecordSet->GetCollect("Power")));
		strSendingPower.Format("%d",nPower);
		
		int nChannel =atoi(VariantToCString(m_pRecordSet->GetCollect("Channel")));
		strChannel.Format("%d",nChannel);
		
		strLocation = VariantToCString(m_pRecordSet->GetCollect("Direction"));
		
		double nDistance = atof(VariantToCString(m_pRecordSet->GetCollect("Distance")));
		strDistance.Format("%lf",nDistance);
		
		m_ctrlListNodeInfo.InsertItem(i,strNodeID);
		m_ctrlListNodeInfo.SetItemText(i,1,strDistance);
		m_ctrlListNodeInfo.SetItemText(i,2,strLocation);
		m_ctrlListNodeInfo.SetItemText(i,3,strSendingPower);
		m_ctrlListNodeInfo.SetItemText(i,4,strChannel);
		i++;
		
		m_pRecordSet->MoveNext();	
	}
	UpdateData(FALSE);
}

void CSceneConfigDlg::FromScenceIDToSceneInfo(int nSceneID)
{
	ADOConn m_AdoConn;
	_RecordsetPtr m_pRecordSet;
	m_AdoConn.OnInitADOConn();	
	
	CString strSQL;
	strSQL.Format("SELECT * FROM tb_SceneInfo WHERE SceneID=%d",nSceneID);
	m_pRecordSet=m_AdoConn.GetRecordSet((_bstr_t)strSQL);		
	if (!m_pRecordSet->adoEOF)
	{
		m_curSceneID = atoi(VariantToCString(m_pRecordSet->GetCollect("SceneID")));	
		m_strSceneName = VariantToCString(m_pRecordSet->GetCollect("SceneName"));
		m_strSceneDescribe = VariantToCString(m_pRecordSet->GetCollect("SceneDescribe"));
		
	}
	
	strSQL.Format("SELECT * FROM tb_NodeInfo WHERE SceneID=%d",m_curSceneID);
	m_pRecordSet=m_AdoConn.GetRecordSet((_bstr_t)strSQL);	
	CString  strNodeID, strSendingPower, strChannel, strLocation, strDistance;
	int i = m_ctrlListNodeInfo.GetItemCount();	
	while(!m_pRecordSet->adoEOF)
	{
		
		int nodeID =atoi(VariantToCString(m_pRecordSet->GetCollect("NodeID")));
		strNodeID.Format("%d",nodeID);
		
		int nPower=atoi( VariantToCString(m_pRecordSet->GetCollect("Power")));
		strSendingPower.Format("%d",nPower);
		
		int nChannel =atoi(VariantToCString(m_pRecordSet->GetCollect("Channel")));
		strChannel.Format("%d",nChannel);
		
		strLocation = VariantToCString(m_pRecordSet->GetCollect("Direction"));
		
		double nDistance = atof(VariantToCString(m_pRecordSet->GetCollect("Distance")));
		strDistance.Format("%lf",nDistance);
		
		m_ctrlListNodeInfo.InsertItem(i,strNodeID);
		m_ctrlListNodeInfo.SetItemText(i,1,strDistance);
		m_ctrlListNodeInfo.SetItemText(i,2,strLocation);
		m_ctrlListNodeInfo.SetItemText(i,3,strSendingPower);
		m_ctrlListNodeInfo.SetItemText(i,4,strChannel);
		i++;
		
		m_pRecordSet->MoveNext();	
	}
	UpdateData(FALSE);
}


void CSceneConfigDlg::OnClickListNodeinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	nCurItem = m_ctrlListNodeInfo.GetSelectionMark();
	CString strLocation,strSendingPower,strChannel;
	
	m_strNodeID = m_ctrlListNodeInfo.GetItemText(nCurItem,0);
	m_dDistance =atof(m_ctrlListNodeInfo.GetItemText(nCurItem,1));
	strLocation = m_ctrlListNodeInfo.GetItemText(nCurItem,2);
	m_ctrlComboLocation.SetWindowText(strLocation);
    strSendingPower = m_ctrlListNodeInfo.GetItemText(nCurItem,3);
	m_ctrlComboPower.SetWindowText(strSendingPower);
	strChannel = m_ctrlListNodeInfo.GetItemText(nCurItem,4);
	m_ctrlComboChannel.SetWindowText(strChannel);
	
	UpdateData(FALSE);
	*pResult = 0;
}


void CSceneConfigDlg::OnRadioShowCurInfo() 
{
	m_nFunction=0;
	GetDlgItem(IDC_COMBO_OLD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DELETESCENE)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OK)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_EDIT_SCENENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SCENEDISCRIBE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_NODEID)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DISTANCE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_LOCATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_SENDPOWER)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_CHANNEL)->EnableWindow(FALSE);
}

void CSceneConfigDlg::OnRadioReConfig() 
{
	m_nFunction = 1;
	GetDlgItem(IDC_COMBO_OLD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DELETESCENE)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DELETE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_OK)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_EDIT_SCENENAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SCENEDISCRIBE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_NODEID)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DISTANCE)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_LOCATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_SENDPOWER)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_CHANNEL)->EnableWindow(TRUE);
}


void CSceneConfigDlg::OnRadioUseOldConfig() 
{
	m_nFunction = 2;
	GetDlgItem(IDC_COMBO_OLD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DELETESCENE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_OK)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DELETE)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_EDIT_SCENENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SCENEDISCRIBE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_NODEID)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DISTANCE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_LOCATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_SENDPOWER)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_CHANNEL)->EnableWindow(FALSE);
}



void CSceneConfigDlg::OnSelchangeComboOld() 
{
	// TODO: Add your control notification handler code here
	CString strSceneName;
	int nIndex=m_ctrlComboOldScene.GetCurSel();
	if(-1!=nIndex)
	{
		m_ctrlComboOldScene.GetLBText(nIndex,strSceneName);		
		FromScenceNameToSceneInfo(strSceneName);		
	}
}



void CSceneConfigDlg::OnBtnDeleteScene() 
{
	if (m_curSceneID == -1)
	{
		AfxMessageBox("请选择要删除的场景!");
		return;
	}
	if(AfxMessageBox("将删除该场景下的所有测试数据? 请谨慎操作",4+32+256)==IDYES)
	{
		ADOConn m_AdoConn;
		_RecordsetPtr m_pTestScheduleRecordSet;
		m_AdoConn.OnInitADOConn();
		
		CString strSQL;
		strSQL.Format("SELECT * FROM tb_TestSchedule WHERE SceneID=%d",m_curSceneID);
		
		m_pTestScheduleRecordSet=m_AdoConn.GetRecordSet((_bstr_t)strSQL);
		
		try
		{
			//事件start
			m_AdoConn.m_pConnection->BeginTrans(); 
			
			while (!m_pTestScheduleRecordSet->adoEOF)
			{
				int nTestScheduleID = atoi(VariantToCString(m_pTestScheduleRecordSet->GetCollect("ScheduleID")));
				
				strSQL.Format("DELETE FROM tb_PacketInfo WHERE ScheduleID=%d",nTestScheduleID);
				m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
				
				strSQL.Format("DELETE FROM tb_TestInfo WHERE ScheduleID=%d",nTestScheduleID);
				m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
				
				m_pTestScheduleRecordSet->MoveNext();
			}
			
			strSQL.Format("DELETE FROM tb_TestSchedule WHERE SceneID=%d",m_curSceneID);
			m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
			
			strSQL.Format("DELETE FROM tb_NodeInfo WHERE SceneID=%d",m_curSceneID);
			m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
			
			strSQL.Format("DELETE FROM tb_SceneInfo WHERE SceneID=%d",m_curSceneID);
			m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
			
			m_AdoConn.m_pConnection->CommitTrans(); //事件end	
			
			AfxMessageBox("删除成功!");
			InitSceneCombo();
			m_strSceneName = "";
			m_strSceneDescribe = "";
			m_ctrlListNodeInfo.DeleteAllItems();
			
		}
		catch (_com_error e)
		{
			m_AdoConn.m_pConnection->RollbackTrans();//回滚事务
			AfxMessageBox(e.ErrorMessage());						
		}
			
		UpdateData(FALSE);	
	}
	
}
