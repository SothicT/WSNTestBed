// TestResultDisplayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "TestResultDisplayDlg.h"
#include "DataManageDlg.h"

#include "iPlotChannelX.h"
#include "iPlotAxisX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestResultDisplayDlg dialog


CTestResultDisplayDlg::CTestResultDisplayDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTestResultDisplayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestResultDisplayDlg)
	m_strEndTime = _T("");
	m_strSceneDescribe = _T("");
	m_strTestPackets = _T("");
	m_strSendPeriod = _T("");
	m_strTestMode = _T("");
	m_strTestPeriod = _T("");
	nSearchSceneID= -1;
	nSearchScheduleID = -1;
	m_nSelectNo = 0;
	//}}AFX_DATA_INIT
}


void CTestResultDisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestResultDisplayDlg)
	DDX_Control(pDX, IDC_COMBO_SCHEDULE, m_ctrlComboTestTime);
	DDX_Control(pDX, IDC_COMBO_SCENENAME, m_ctrlComboSceneName);
	DDX_Control(pDX, IDC_LIST_RESULT, m_ctrlResultInfoList);
	DDX_Control(pDX, IDC_IPLOTX_RESULT, m_ctrlPlotx);
	DDX_Text(pDX, IDC_EDIT_ENDTIME, m_strEndTime);
	DDX_Text(pDX, IDC_EDIT_SCENEDESCRIBE, m_strSceneDescribe);
	DDX_Text(pDX, IDC_EDIT_SENDPACKETS, m_strTestPackets);
	DDX_Text(pDX, IDC_EDIT_SENDPERIOD, m_strSendPeriod);
	DDX_Text(pDX, IDC_EDIT_TESTMODE, m_strTestMode);
	DDX_Text(pDX, IDC_EDIT_TESTPERIOD, m_strTestPeriod);
	DDX_Radio(pDX, IDC_RADIO_TIME2PRR, m_nSelectNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestResultDisplayDlg, CDialog)
//{{AFX_MSG_MAP(CTestResultDisplayDlg)
ON_CBN_SELCHANGE(IDC_COMBO_SCENENAME, OnSelChangeComboSceneName)
ON_CBN_SELCHANGE(IDC_COMBO_SCHEDULE, OnSelChangeComboScheduleTime)
ON_BN_CLICKED(IDC_RADIO_TIME2PRR, OnRadioTime2PRR)
ON_BN_CLICKED(IDC_RADIO_TIME2RSSIDOWN, OnRadioTime2RssiDown)
ON_BN_CLICKED(IDC_RADIO_TIME2RSSIUP, OnRadioTime2rssiup)
ON_BN_CLICKED(IDC_RADIO_TIME2LQIDOWN, OnRadioTime2lqidown)
ON_BN_CLICKED(IDC_RADIO_TIME2LQIUP, OnRadioTime2lqiup)
ON_BN_CLICKED(IDC_RADIO_TIME2SNRDOWN, OnRadioTime2snrdown)
ON_BN_CLICKED(IDC_RADIO_TIME2SNRUP, OnRadioTime2snrup)
	ON_BN_CLICKED(IDC_BTN_EXPORT, OnBtnExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestResultDisplayDlg message handlers

BOOL CTestResultDisplayDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int nCount=0;
	CHeaderCtrl *pHeaderCtrl=m_ctrlResultInfoList.GetHeaderCtrl();
	if(pHeaderCtrl!=NULL)
		nCount=pHeaderCtrl->GetItemCount();
	for(int i=0;i<nCount;i++)
		m_ctrlResultInfoList.DeleteColumn(0);
	m_ctrlResultInfoList.DeleteAllItems();
	
	//���÷��,����,�п�
	m_ctrlResultInfoList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrlResultInfoList.InsertColumn(0,"TestID",LVCFMT_CENTER,60); 
	m_ctrlResultInfoList.InsertColumn(1,"NodeID",LVCFMT_CENTER,60);
	m_ctrlResultInfoList.InsertColumn(2,"PRR",LVCFMT_CENTER,60);
	m_ctrlResultInfoList.InsertColumn(3,"��ʼʱ��",LVCFMT_CENTER,140);
	m_ctrlResultInfoList.InsertColumn(4,"����ʱ��",LVCFMT_CENTER,140);
	
	m_ctrlResultInfoList.InsertColumn(5,"����RSSI��ֵ",LVCFMT_CENTER,100);
	m_ctrlResultInfoList.InsertColumn(6,"����RSSI��ֵ",LVCFMT_CENTER,100);
	m_ctrlResultInfoList.InsertColumn(7,"����LQI��ֵ",LVCFMT_CENTER,80);	
	m_ctrlResultInfoList.InsertColumn(8,"����LQI��ֵ",LVCFMT_CENTER,80);
	m_ctrlResultInfoList.InsertColumn(9,"����SNR��ֵ",LVCFMT_CENTER,80);
	m_ctrlResultInfoList.InsertColumn(10,"����SNR��ֵ",LVCFMT_CENTER,80);
	
	m_ctrlResultInfoList.InsertColumn(11,"����RSSI����",LVCFMT_CENTER,100);
	m_ctrlResultInfoList.InsertColumn(12,"����RSSI����",LVCFMT_CENTER,100);
	m_ctrlResultInfoList.InsertColumn(13,"����LQI����",LVCFMT_CENTER,80);	
	m_ctrlResultInfoList.InsertColumn(14,"����LQI����",LVCFMT_CENTER,80);
	m_ctrlResultInfoList.InsertColumn(15,"����SNR����",LVCFMT_CENTER,80);
	m_ctrlResultInfoList.InsertColumn(16,"����SNR����",LVCFMT_CENTER,80);
	
	InitSceneNameCombo();
	InitPlotDisplay();
	
    InitScheduleTimeCombo();
	InitTestResultInfoList();
	OnRadioTime2PRR();
	//RefreshPlotShow();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTestResultDisplayDlg::InitSceneNameCombo()
{
	m_ctrlComboSceneName.ResetContent();
	ADOConn m_AdoConn;
	_RecordsetPtr m_pRecordSet;
	m_AdoConn.OnInitADOConn();
	
	CString strSQL;
	strSQL="SELECT * FROM tb_SceneInfo ORDER BY SceneID ";
	m_pRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	if (m_pRecordSet->adoEOF)
	{
		m_ctrlComboSceneName.SetWindowText("��");
	}
	else
	{
		while(!m_pRecordSet->adoEOF)
		{
			CString strSceneName;
			strSceneName = VariantToCString(m_pRecordSet->GetCollect("SceneName"));
			m_ctrlComboSceneName.AddString(strSceneName);	
			
			m_pRecordSet->MoveNext();	
		}
	}
	
	if(nSearchSceneID!=-1) //��ǰ����
	{
		strSQL.Format("SELECT * FROM tb_SceneInfo WHERE SceneID=%d",nSearchSceneID);
		m_pRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
		if (m_pRecordSet->adoEOF)
		{
			CString strSceneName = VariantToCString(m_pRecordSet->GetCollect("SceneName"));
			CString StrSceneDescribe = VariantToCString(m_pRecordSet->GetCollect("SceneDescribe"));
			m_ctrlComboSceneName.SetWindowText(strSceneName);
			InitScheduleTimeCombo();
		}
	}
	else
	{
		m_ctrlComboSceneName.SetWindowText("��ѡ��Ҫ�鿴����ʷ����");
	}
	UpdateData(FALSE);
}










void CTestResultDisplayDlg::InitScheduleTimeCombo()
{
	m_strEndTime=m_strTestPackets=m_strSendPeriod=m_strTestPeriod=m_strTestMode="";
	m_ctrlComboTestTime.ResetContent();
	
	ADOConn m_AdoConn;
	_RecordsetPtr m_pRecordSet;
	m_AdoConn.OnInitADOConn();
	
	CString strSQL;
	strSQL.Format("SELECT * FROM tb_TestSchedule WHERE SceneID=%d",nSearchSceneID);
	m_pRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
   	
	if (m_pRecordSet->adoEOF)
	{
		m_ctrlComboTestTime.SetWindowText("���޲�������");
	}
	else
	{
		while(!m_pRecordSet->adoEOF)
		{
			CString strStartTime;
			strStartTime = VariantToCString(m_pRecordSet->GetCollect("StartTime"));		
			m_ctrlComboTestTime.AddString(strStartTime);	
			
			m_pRecordSet->MoveNext();	
		}
	}
	
	if(nSearchScheduleID!=-1) //��ǰ����
	{
		strSQL.Format("SELECT * FROM tb_TestSchedule WHERE ScheduleID=%d",nSearchScheduleID);
		m_pRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
		if (m_pRecordSet->adoEOF)
		{
			m_ctrlComboTestTime.SetWindowText(VariantToCString(m_pRecordSet->GetCollect("StartTime")));
			m_strEndTime = VariantToCString(m_pRecordSet->GetCollect("EndTime"));
			m_strTestPackets = VariantToCString(m_pRecordSet->GetCollect("TestPackets"));
			m_strSendPeriod = VariantToCString(m_pRecordSet->GetCollect("SendPeriod"));		
			m_strTestPeriod = VariantToCString(m_pRecordSet->GetCollect("TestPeriod"));
			m_strTestMode = VariantToCString(m_pRecordSet->GetCollect("TestMode"));	
		}
	}
	else
	{
		m_ctrlComboTestTime.SetWindowText("��ѡ��ʼʱ��");
	}
	
	UpdateData(FALSE);
}

void CTestResultDisplayDlg::InitTestResultInfoList()
{
	if(nSearchScheduleID == -1)
	{
		m_ctrlResultInfoList.DeleteAllItems();
		
	}	
	else
	{	
		ADOConn m_AdoConn;
		_RecordsetPtr m_pTestResultRecordSet;
		m_AdoConn.OnInitADOConn();	
		
		CString strSQL;
		strSQL.Format("SELECT * FROM tb_TestInfo WHERE ScheduleID=%d  ORDER BY TestID",nSearchScheduleID);
		m_pTestResultRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
		
		int nItem = 0;
		CString  strTestID,strNodeID,strPRR,strStartTime,strEndTime;
		CString	strMeanRSSIDown,strMeanRSSIUp,strMeanLQIDown,strMeanLQIUp,strMeanSNRDown,strMeanSNRUp,strVarRSSIDown,strVarRSSIUp,strVarLQIDown,strVarLQIUp,strVarSNRDown,strVarSNRUp;
		
		while(!m_pTestResultRecordSet->adoEOF)
		{
			int nTestID= atoi(VariantToCString(m_pTestResultRecordSet->GetCollect("TestID")));
			strTestID.Format("%d",nTestID);
			m_ctrlResultInfoList.InsertItem(nItem,strTestID);
			
			int nNodeID = atoi(VariantToCString(m_pTestResultRecordSet->GetCollect("NodeID")));
			strNodeID.Format("%d",nNodeID);
			m_ctrlResultInfoList.SetItemText(nItem,1,strNodeID);
			
			double dPRR = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("PRR")));
			strPRR.Format("%.3f",dPRR);
			m_ctrlResultInfoList.SetItemText(nItem,2,strPRR);
			
			strStartTime = VariantToCString(m_pTestResultRecordSet->GetCollect("StartTestTime"));
			m_ctrlResultInfoList.SetItemText(nItem,3,strStartTime);
			
			strEndTime = VariantToCString(m_pTestResultRecordSet->GetCollect("EndTestTime"));
			m_ctrlResultInfoList.SetItemText(nItem,4,strEndTime);
			
			double dMeanRSSIDown = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("MeanRSSI_Down")));
			strMeanRSSIDown.Format("%.3f",dMeanRSSIDown);
			m_ctrlResultInfoList.SetItemText(nItem,5,strMeanRSSIDown);
			
			double dMeanRSSIUp = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("MeanRSSI_Up")));
			strMeanRSSIUp.Format("%.3f",dMeanRSSIUp);
			m_ctrlResultInfoList.SetItemText(nItem,6,strMeanRSSIUp);
			
			double dMeanLQIDown = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("MeanLQI_Down")));
			strMeanLQIDown.Format("%.3f",dMeanLQIDown);
			m_ctrlResultInfoList.SetItemText(nItem,7,strMeanLQIDown);
			
			double dMeanLQIUp = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("MeanLQI_Up")));
			strMeanLQIUp.Format("%.3f",dMeanLQIUp);
			m_ctrlResultInfoList.SetItemText(nItem,8,strMeanLQIUp);
			
			double dMeanSNRDown = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("MeanSNR_Down")));
			strMeanSNRDown.Format("%.3f",dMeanSNRDown);
			m_ctrlResultInfoList.SetItemText(nItem,9,strMeanSNRDown);
			
			double dMeanSNRUp = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("MeanSNR_Up")));
			strMeanSNRUp.Format("%.3f",dMeanSNRUp) ;
			m_ctrlResultInfoList.SetItemText(nItem,10,strMeanSNRUp);
			
			double dVarRSSIDown = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("VarRSSI_Down")));
			strVarRSSIDown.Format("%.3f",dVarRSSIDown); 
			m_ctrlResultInfoList.SetItemText(nItem,11,strVarRSSIDown);
			
			double dVarRSSIUp = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("VarRSSI_Up")));
			strVarRSSIUp.Format("%.3f",dVarRSSIUp);
			m_ctrlResultInfoList.SetItemText(nItem,12,strVarRSSIUp);
			
			double dVarLQIDown = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("VarLQI_Down")));
			strVarLQIDown.Format("%.3f",dVarLQIDown);
			m_ctrlResultInfoList.SetItemText(nItem,13,strVarLQIDown);
			
			double dVarLQIUp = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("VarLQI_Up")));
			strVarLQIUp.Format("%.3f",dVarLQIUp);
			m_ctrlResultInfoList.SetItemText(nItem,14,strVarLQIUp);
			
			double dVARSNRDown = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("VarSNR_Down")));
			strVarSNRDown.Format("%.3f",dVARSNRDown);
			m_ctrlResultInfoList.SetItemText(nItem,15,strVarSNRDown);
			
			double dVarSNRUp = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("VarSNR_Up")));
			strVarSNRUp.Format("%.3f",dVarSNRUp);
			m_ctrlResultInfoList.SetItemText(nItem,16,strVarSNRUp);
			
			nItem++;
			m_pTestResultRecordSet->MoveNext();
		}
	}
	UpdateData(FALSE);
}

void CTestResultDisplayDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CTestResultDisplayDlg::InitPlotDisplay()
{
	memset(NodeList,-1,ALLOW_ACCESS_NODES);	
	m_ctrlPlotx.RemoveAllChannels();
	
	if (nSearchSceneID!=-1)
	{
		
		int nNodeID;
		CString strChannelName;
		
		ADOConn m_AdoConn;
		_RecordsetPtr m_pRecordSet;
		m_AdoConn.OnInitADOConn();	
		
		CString strSQL;
		strSQL.Format("SELECT * FROM tb_Nodeinfo WHERE SceneID=%d",nSearchSceneID);
		m_pRecordSet= m_AdoConn.GetRecordSet((_bstr_t)strSQL);
		int i=0;
		while(!m_pRecordSet->adoEOF)
		{
			nNodeID = atoi(VariantToCString(m_pRecordSet->GetCollect("NodeID")));	
			NodeList[nNodeID]=i;
			strChannelName.Format("%d�Žڵ�",nNodeID);
			m_ctrlPlotx.AddChannel();
			m_ctrlPlotx.GetChannel(i).SetTitleText(strChannelName);
			m_ctrlPlotx.GetChannel(i).SetMarkersVisible(TRUE);
			m_ctrlPlotx.GetChannel(i).SetMarkersStyle(0);
			
			m_ctrlPlotx.GetChannel(i).SetTraceVisible(TRUE);
			m_ctrlPlotx.GetChannel(i).SetTraceLineStyle(0);
			m_ctrlPlotx.GetChannel(i).SetTraceLineWidth(2);
			i++;
			m_pRecordSet->MoveNext();
		}	
	}
	
}

/************************************************************************/
/* ���¶�̬ͼ                                                           */
/************************************************************************/
void CTestResultDisplayDlg::RefreshPlotShow()
{
	UpdateData(TRUE);
	ADOConn m_AdoConn;
	_RecordsetPtr m_pTestResultRecordSet;
	m_AdoConn.OnInitADOConn();	
	
	CString strSQL;
	strSQL.Format("SELECT * FROM tb_Testinfo WHERE ScheduleID=%d ORDER BY TestID",nSearchScheduleID);
    m_pTestResultRecordSet= m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	
	while(!m_pTestResultRecordSet->adoEOF)
	{
		int nNodeID = atoi(VariantToCString(m_pTestResultRecordSet->GetCollect("NodeID")));
		
		int nTestID = atoi(VariantToCString(m_pTestResultRecordSet->GetCollect("TestID")));
		
		double dPRR = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("PRR")));
		
		double dMeanRSSIDown = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("MeanRSSI_Down")));
		
		double dMeanRSSIUp = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("MeanRSSI_Up")));
		
		double dMeanLQIDown = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("MeanLQI_Down")));
		
		double dMeanLQIUp = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("MeanLQI_Up")));
		
		double dMeanSNRDown = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("MeanSNR_Down")));
		
		double dMeanSNRUp = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("MeanSNR_Up")));
		
		double dVarRSSIDown = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("VarRSSI_Down")));
		
		double dVarRSSIUp = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("VarRSSI_Up")));
		
		double dVarLQIDown = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("VarLQI_Down")));
		
		double dVarLQIUp = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("VarLQI_Up")));
		
		double dVARSNRDown = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("VarSNR_Down")));
		
		double dVarSNRUp = atof(VariantToCString(m_pTestResultRecordSet->GetCollect("VarSNR_Up")));
		
		double X, Y;
		
		switch(m_nSelectNo)
		{
		case 0: X=nTestID;  Y = dPRR;  break;
		case 1: X=nTestID;  Y = dMeanRSSIDown; break;
		case 2: X=nTestID;  Y = dMeanRSSIUp; break;
		case 3: X=nTestID;  Y = dMeanLQIDown; break;
		case 4: X=nTestID;  Y = dMeanLQIUp; break;
		case 5: X=nTestID;  Y = dMeanSNRDown;  break;
		case 6: X=nTestID;  Y = dMeanSNRUp; break;
		}
		
		m_ctrlPlotx.GetChannel(NodeList[nNodeID]).AddXY(X,Y);
		m_pTestResultRecordSet->MoveNext();
	}
}

void CTestResultDisplayDlg::OnSelChangeComboSceneName() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString  strSceneName;
	int nIndex=m_ctrlComboSceneName.GetCurSel();
	if(-1!=nIndex)
	{
		m_ctrlComboSceneName.GetLBText(nIndex,strSceneName);		
	}
	
	ADOConn m_AdoConn;
	_RecordsetPtr m_pRecordSet;
	m_AdoConn.OnInitADOConn();	
	
	CString strSQL;
	strSQL.Format("SELECT * FROM tb_SceneInfo WHERE SceneName='%s'",strSceneName);
	m_pRecordSet=m_AdoConn.GetRecordSet((_bstr_t)strSQL);		
	if (!m_pRecordSet->adoEOF)
	{
		nSearchSceneID = atoi(VariantToCString(m_pRecordSet->GetCollect("SceneID")));
		nSearchScheduleID = -1;
		m_strSceneDescribe = VariantToCString(m_pRecordSet->GetCollect("SceneDescribe"));
		InitPlotDisplay();		
		InitScheduleTimeCombo();
		InitTestResultInfoList();
	}
	
    UpdateData(FALSE);
}

void CTestResultDisplayDlg::OnSelChangeComboScheduleTime() 
{
	UpdateData(TRUE);
	CString  strScheduleTime;
	int nIndex=m_ctrlComboTestTime.GetCurSel();
	if(-1!=nIndex)
	{
		m_ctrlComboTestTime.GetLBText(nIndex,strScheduleTime);		
	}
	
	ADOConn m_AdoConn;
	_RecordsetPtr m_pRecordSet;
	m_AdoConn.OnInitADOConn();	
	
	CString strSQL;
	strSQL.Format("SELECT * FROM tb_TestSchedule WHERE StartTime='%s'",strScheduleTime);
	m_pRecordSet=m_AdoConn.GetRecordSet((_bstr_t)strSQL);		
	if (!m_pRecordSet->adoEOF)
	{
		nSearchScheduleID = atoi(VariantToCString(m_pRecordSet->GetCollect("ScheduleID")));
		
		m_strEndTime = VariantToCString(m_pRecordSet->GetCollect("EndTime"));
		m_strTestPackets = VariantToCString(m_pRecordSet->GetCollect("TestPackets"));
		m_strSendPeriod = VariantToCString(m_pRecordSet->GetCollect("SendPeriod"));		
		m_strTestPeriod = VariantToCString(m_pRecordSet->GetCollect("TestPeriod"));
		m_strTestMode = VariantToCString(m_pRecordSet->GetCollect("TestMode"));
		InitTestResultInfoList();	
		OnRadioTime2PRR();			
	}
	m_nSelectNo=0;
    UpdateData(FALSE);
}

void CTestResultDisplayDlg::OnRadioTime2PRR() 
{
	InitPlotDisplay();	
	m_ctrlPlotx.SetTitleText("��������ʱ��ͼ");
	m_ctrlPlotx.GetXAxis(0).SetTitleShow(TRUE);
    m_ctrlPlotx.GetXAxis(0).SetTitle("��������");
	m_ctrlPlotx.GetXAxis(0).SetMin(0);
	
	m_ctrlPlotx.GetYAxis(0).SetTitleShow(TRUE);
	m_ctrlPlotx.GetYAxis(0).SetTitle("��������(PRR/%)");
	m_ctrlPlotx.GetYAxis(0).SetMin(0);
	m_ctrlPlotx.GetYAxis(0).SetSpan(100);
	RefreshPlotShow();
}

void CTestResultDisplayDlg::OnRadioTime2RssiDown() 
{
	InitPlotDisplay();	
	m_ctrlPlotx.SetTitleText("RSSI(����)ʱ��ͼ");
	m_ctrlPlotx.GetXAxis(0).SetTitleShow(TRUE);
    m_ctrlPlotx.GetXAxis(0).SetTitle("��������");
	m_ctrlPlotx.GetXAxis(0).SetMin(0);
	
	m_ctrlPlotx.GetYAxis(0).SetTitleShow(TRUE);
	m_ctrlPlotx.GetYAxis(0).SetTitle("�źŽ���ǿ��(����)(RSSI/dBm)");
	m_ctrlPlotx.GetYAxis(0).SetMin(-100);
	m_ctrlPlotx.GetYAxis(0).SetSpan(100);
	
	RefreshPlotShow();
}

void CTestResultDisplayDlg::OnRadioTime2rssiup() 
{
	InitPlotDisplay();	
	m_ctrlPlotx.SetTitleText("RSSI(����)ʱ��ͼ");
	m_ctrlPlotx.GetXAxis(0).SetTitleShow(TRUE);
    m_ctrlPlotx.GetXAxis(0).SetTitle("��������");
	m_ctrlPlotx.GetXAxis(0).SetMin(0);
	
	m_ctrlPlotx.GetYAxis(0).SetTitleShow(TRUE);
	m_ctrlPlotx.GetYAxis(0).SetTitle("�źŽ���ǿ��(����)(RSSI/dBm)");
	m_ctrlPlotx.GetYAxis(0).SetMin(-100);
	m_ctrlPlotx.GetYAxis(0).SetSpan(100);
	
	RefreshPlotShow();
}

void CTestResultDisplayDlg::OnRadioTime2lqidown() 
{
	InitPlotDisplay();	
	m_ctrlPlotx.SetTitleText("LQI(����)ʱ��ͼ");
	m_ctrlPlotx.GetXAxis(0).SetTitleShow(TRUE);
    m_ctrlPlotx.GetXAxis(0).SetTitle("��������");
	m_ctrlPlotx.GetXAxis(0).SetMin(0);
	
	m_ctrlPlotx.GetYAxis(0).SetTitleShow(TRUE);
	m_ctrlPlotx.GetYAxis(0).SetTitle("��·����ָʾֵ(����)(LQI)");
	m_ctrlPlotx.GetYAxis(0).SetMin(0);
	m_ctrlPlotx.GetYAxis(0).SetSpan(150);
	
	RefreshPlotShow();
}

void CTestResultDisplayDlg::OnRadioTime2lqiup() 
{
	InitPlotDisplay();	
	m_ctrlPlotx.SetTitleText("LQI(����)ʱ��ͼ");
	m_ctrlPlotx.GetXAxis(0).SetTitleShow(TRUE);
    m_ctrlPlotx.GetXAxis(0).SetTitle("��������");
	m_ctrlPlotx.GetXAxis(0).SetMin(0);
	
	m_ctrlPlotx.GetYAxis(0).SetTitleShow(TRUE);
	m_ctrlPlotx.GetYAxis(0).SetTitle("��·����ָʾֵ(����)(LQI)");
	m_ctrlPlotx.GetYAxis(0).SetMin(0);
	m_ctrlPlotx.GetYAxis(0).SetSpan(150);
	
	RefreshPlotShow();
}

void CTestResultDisplayDlg::OnRadioTime2snrdown() 
{
	InitPlotDisplay();	
	m_ctrlPlotx.SetTitleText("SNR(����)ʱ��ͼ");
	m_ctrlPlotx.GetXAxis(0).SetTitleShow(TRUE);
    m_ctrlPlotx.GetXAxis(0).SetTitle("��������");
	m_ctrlPlotx.GetXAxis(0).SetMin(0);
	
	m_ctrlPlotx.GetYAxis(0).SetTitleShow(TRUE);
	m_ctrlPlotx.GetYAxis(0).SetTitle("�����(����)(SNR/dBm)");
	m_ctrlPlotx.GetYAxis(0).SetMin(0);
	m_ctrlPlotx.GetYAxis(0).SetSpan(100);
	
	RefreshPlotShow();
}

void CTestResultDisplayDlg::OnRadioTime2snrup() 
{
	InitPlotDisplay();	
	m_ctrlPlotx.SetTitleText("SNR(����)ʱ��ͼ");
	m_ctrlPlotx.GetXAxis(0).SetTitleShow(TRUE);
    m_ctrlPlotx.GetXAxis(0).SetTitle("��������");
	m_ctrlPlotx.GetXAxis(0).SetMin(0);
	
	m_ctrlPlotx.GetYAxis(0).SetTitleShow(TRUE);
	m_ctrlPlotx.GetYAxis(0).SetTitle("�����(����)(SNR/dBm)");
	m_ctrlPlotx.GetYAxis(0).SetMin(0);
	m_ctrlPlotx.GetYAxis(0).SetSpan(100);
	
	RefreshPlotShow();
}

void CTestResultDisplayDlg::OnBtnExport() 
{
	CDataManageDlg dlg;
//	dlg.m_ctrlComboSceneName.SetWindowText();
	dlg.nSearchSceneID = nSearchSceneID;
	dlg.nSearchScheduleID = nSearchScheduleID;
	dlg.m_strSceneDescrible = m_strSceneDescribe;
	dlg.DoModal();
}
