// LQ_TestbedDlg.cpp : implementation file
//
#include "stdafx.h"
#include "LQ_Testbed.h"
#include "LQ_TestbedDlg.h"
#include "OptionDlg.h" 
#include "SceneConfigDlg.h"
#include "TestCustomDlg.h"
#include "DataManageDlg.h"
#include "TestResultDisplayDlg.h"
#include "DataManageDlg.h"
#include "DisplayTopologyDlg.h"
#include "PowerDLG.h"

#include "iPlotChannelX.h"
#include "iPlotAxisX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLQ_TestbedDlg dialog

CLQ_TestbedDlg::CLQ_TestbedDlg(CWnd* pParent /*=NULL*/)
: CDialog(CLQ_TestbedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLQ_TestbedDlg)
	m_iSelection = 0;
	m_nPktSum = 0;
	m_EDate = 0;
	m_ETime = 0;
	m_IntervalTime = 0;
	m_SDate = 0;
	m_STime = 0;
	m_nSendPeriod = 0;
	m_nTestModel = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_bOpenUart = false;
	m_bStartTest = false;
	m_bStartTestSchedule = false;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLQ_TestbedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLQ_TestbedDlg)
	DDX_Control(pDX, IDC_LIST_LOG, m_ctrlLogList);
	DDX_Control(pDX, IDC_LIST_PACKETINFO, m_ctrlListPacketInfo);
	DDX_Control(pDX, IDC_IPLOTX, m_ctrlPlotx);
	DDX_Radio(pDX, IDC_RADIO1, m_iSelection);
	DDX_Text(pDX, IDC_EDIT_MSGSUM, m_nPktSum);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_EDATE, m_EDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ETIME, m_ETime);
	DDX_Text(pDX, IDC_EDIT_T, m_IntervalTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_SDATE, m_SDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STIME, m_STime);
	DDX_Text(pDX, IDC_EDIT_SENDPERIOD, m_nSendPeriod);
	DDX_Radio(pDX, IDC_RADIO_ACTIVE, m_nTestModel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLQ_TestbedDlg, CDialog)
//{{AFX_MSG_MAP(CLQ_TestbedDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_COMMAND(ID_MENU_BASESET, OnMenuBaseSet)
ON_COMMAND(ID_MENU_START, OnMenuStart)
ON_COMMAND(ID_MENU_CLOSE, OnMenuClose)
ON_COMMAND(ID_MENU_EXIT, OnMenuExit)
ON_WM_CLOSE()
ON_COMMAND(ID_MENU_NODEMANAGE, OnMenuSceneConfig)
ON_COMMAND(ID_MENU_TESTCUSTOM, OnMenuTestCustom)
ON_BN_CLICKED(IDC_RADIO1, OnRadioRSSIRealTime)
ON_BN_CLICKED(IDC_RADIO2, OnRadioLQIRealTime)
ON_BN_CLICKED(IDC_RADIO3, OnRadioSNRRealTime)
ON_BN_CLICKED(IDC_BTN_CONFIG, OnBtnConfigCmd)
ON_BN_CLICKED(IDC_BTN_SUBMIT, OnBtnSubmitSchedule)
ON_WM_TIMER()
ON_COMMAND(ID_MENU_EXPORTDATA, OnMenuExportdata)
ON_EN_CHANGE(IDC_EDIT_MSGSUM, OnChangeEditMsgSum)
ON_BN_CLICKED(IDC_BTN_WITHDRAW, OnBtnWithdrawSchedule)
ON_COMMAND(IDD_ABOUTBOX, OnAboutbox)
ON_EN_CHANGE(IDC_EDIT_SENDPERIOD, OnChangeEditSendperiod)
ON_COMMAND(ID_MENU_CURRESULT, OnMenuCurResultShow)
ON_COMMAND(ID_MENU_OLDRESULT, OnMenuOldresult)
ON_COMMAND(ID_MENU_LQP, OnMenuLQP)
ON_COMMAND(ID_MENU_DATAMANAGE, OnMenuDatamanage)
ON_COMMAND(ID_MENU_TOPOLOGY, OnMenuDisplayTopology)
ON_COMMAND(ID_MENU_POWER,OnMenuPower)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT_T, &CLQ_TestbedDlg::OnEnChangeEditT)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLQ_TestbedDlg message handlers

BOOL CLQ_TestbedDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	//��ӹ�����
	TBBUTTON button[9];
	int i=0,nStringLength;
	CString string;
	TCHAR * pString;
	
	m_ImageList.Create(42,42,ILC_COLOR32|ILC_MASK,0,0);	//����ͼ���б��,32ɫ,48X48����	
	
	m_ToolBar.EnableAutomation();
	m_ToolBar.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDR_TOOLBAR);
	//��IMAGELIST���������Դͼ��
	
	for(i=IDI_ICON1;i<=IDI_ICON9;i++)
	{		
		m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(i)));		
	}	
	m_ToolBar.SetImageList(&m_ImageList);	
	//Ϊͼ���������˵��
	for(i=0;i<9;i++)//����
	{	//if (i==3) continue;
		button[i].dwData=0;
		button[i].fsState=TBSTATE_ENABLED;
		button[i].fsStyle=TBSTYLE_BUTTON;
		button[i].iBitmap=i;
		string.LoadString(i+IDS_STRING102);		
		nStringLength=string.GetLength()+1;
		pString=string.GetBufferSetLength(nStringLength);
		button[i].iString=m_ToolBar.AddStrings(pString);
		string.ReleaseBuffer();
	}
	//��������������ID��˵���
	button[0].idCommand=ID_MENU_NODEMANAGE;//�ڵ����
	button[1].idCommand=ID_MENU_TESTCUSTOM;//���Զ���
	button[2].idCommand=ID_MENU_START;//��ʼ����
 	button[3].idCommand=ID_MENU_CURRESULT;//��ǰ���
	// 	button[4].idCommand=ID_MENU_PRINT;//��ӡ����
	// 	button[5].idCommand=ID_MENU_SYSTEMMANAGE;//ϵͳ����
	button[6].idCommand=ID_MENU_OLDRESULT;//
 	button[7].idCommand=ID_MENU_DATAMANAGE;//��������
	button[8].idCommand=ID_MENU_EXIT;//�˳�ϵͳ
	
	
	m_ToolBar.AddButtons(9,button);
	
	button[0].fsStyle=TBSTYLE_SEP;
	
	//��ӷָ���,Ӧ�ôӺ���ǰ���,�������ÿ�����Ӻ����ŵ�Ӱ��
	// 	m_ToolBar.InsertButton(10,&button[0]);
	m_ToolBar.InsertButton(6,&button[0]);
	m_ToolBar.InsertButton(3,&button[0]);
	m_ToolBar.InsertButton(1,&button[0]);
	
	m_ToolBar.AutoSize();
	m_ToolBar.SetStyle(TBSTYLE_FLAT|CCS_TOP);	//���ķ��
	
	InitPacketInfo();//��ʼ����Ϣ����Ϣ��
	InitLogListInfo();
	//Ĭ����ʾRSSIֵ
	m_iSelection=0;
	OnRadioRSSIRealTime();
	
	//Ĭ����ʾ��ǰʱ��
	CTime	nowtime = CTime::GetCurrentTime();
	m_EDate = nowtime;
	m_ETime = nowtime;
	m_SDate = nowtime;
	m_STime = nowtime;
	GetDlgItem(IDC_BTN_WITHDRAW)->EnableWindow(FALSE);
	
	//����״̬��
	m_wndStatusBar.Create(WS_CHILD|WS_VISIBLE|CCS_BOTTOM,  CRect(0,0,0,0),  this,  102);	
    m_wndStatusBar.SetText("\t�ϲ����մ�ѧ�����������о�����Ȩ����(C)2014  All Rights Reserved",0,0 );
	
	
	//��ʼ����ʱ��
	SetTimer(1,1,NULL); 
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLQ_TestbedDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLQ_TestbedDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLQ_TestbedDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLQ_TestbedDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

//��������
void CLQ_TestbedDlg::OnMenuBaseSet() 
{
	COptionDlg dlg;
	dlg.DoModal();
}

//�������񣬽�������
void CLQ_TestbedDlg::OnMenuStart() 
{
	// TODO: Add your command handler code here

	CString  strTemp;
	int nSerialPort,nSerialBaud;
	//��ȡ�����ļ�
	::GetPrivateProfileString("BaseSet","SerialPort","",strTemp.GetBuffer(100),100,".\\Config\\LQ_TestbedConfig.ini");
	nSerialPort=atoi(strTemp);
	::GetPrivateProfileString("BaseSet","BaudRate","",strTemp.GetBuffer(100),100,".\\Config\\LQ_TestbedConfig.ini");
	nSerialBaud=atoi(strTemp);
	
	if(!(m_bOpenUart))
	{
		BeginWaitCursor();				
		//��������
		if (!((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm.Open(this,nSerialPort,nSerialBaud,'N',8,1,EV_RXFLAG | EV_RXCHAR,512))
		{
			EndWaitCursor();
			AfxMessageBox("��������ʧ��:���ڴ�ʧ��!",MB_OK|MB_ICONEXCLAMATION);
			return;
		}	
		//�������̼߳�������
		
		m_bOpenUart=TRUE;
		AddLogText("��������!");
		EndWaitCursor();
	}
	else
	{
		AfxMessageBox("�ѿ��������������ظ�����!");
	}
}

//�رշ��񣬶Ͽ�����
void CLQ_TestbedDlg::OnMenuClose() 
{	
	if(m_bOpenUart)
	{
		BeginWaitCursor();
		//�رմ��ڼ���		
		((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm.Close();	
		m_bOpenUart=FALSE;
		EndWaitCursor();
		AfxMessageBox("�Ͽ�����!");
	}
	else
	{
		AfxMessageBox("��δ��������!");
	}
	
}

//ͨ���˵����˳�ƽ̨
void CLQ_TestbedDlg::OnMenuExit() 
{
	if(AfxMessageBox("ȷ��Ҫ�˳�ƽ̨��?",4+32+256)==IDYES)
	{
		CDialog::OnOK();
	}
}

//�˳�ƽ̨
void CLQ_TestbedDlg::OnClose() 
{
	if(AfxMessageBox("ȷ��Ҫ�˳�ƽ̨��?",4+32+256)==IDYES)
	{
		CDialog::OnClose();
	}
}

//���粿��
void CLQ_TestbedDlg::OnMenuSceneConfig() 
{
	CSceneConfigDlg dlg;
	if (dlg.DoModal()==IDOK)
	{
		InitRealTimePlots();
	}	
}

void CLQ_TestbedDlg::OnMenuTestCustom() 
{
	// TODO: Add your command handler code here
	CTestCustomDlg dlg;
	dlg.DoModal();
}
//��ʼ�����ݰ���Ϣ

void CLQ_TestbedDlg::InitPacketInfo()
{
	int nCount=0;
	CHeaderCtrl *pHeaderCtrl=m_ctrlListPacketInfo.GetHeaderCtrl();
	if(pHeaderCtrl!=NULL)
		nCount=pHeaderCtrl->GetItemCount();
	for(int i=0;i<nCount;i++)
		m_ctrlListPacketInfo.DeleteColumn(0);
	m_ctrlListPacketInfo.DeleteAllItems();
	
	//���÷��,����,�п�
	m_ctrlListPacketInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrlListPacketInfo.InsertColumn(0,"�ڵ�ID",LVCFMT_CENTER,60); 
	m_ctrlListPacketInfo.InsertColumn(1,"��Ϣ����",LVCFMT_CENTER,60); 
	m_ctrlListPacketInfo.InsertColumn(2,"RSSI(dBm)",LVCFMT_CENTER,80); 
	m_ctrlListPacketInfo.InsertColumn(3,"LQI",LVCFMT_CENTER,60); 
	m_ctrlListPacketInfo.InsertColumn(4,"SNR(dBm)",LVCFMT_CENTER,80); 
	m_ctrlListPacketInfo.InsertColumn(5,"��Ϣ����",LVCFMT_CENTER,80); 
	m_ctrlListPacketInfo.InsertColumn(6,"����ʱ��",LVCFMT_CENTER,150); 	
}
//��ʼ����־�б�

void CLQ_TestbedDlg::InitLogListInfo()
{
	int nCount=0;
	CHeaderCtrl *pHeaderCtrl=m_ctrlLogList.GetHeaderCtrl();
	if(pHeaderCtrl!=NULL)
		nCount=pHeaderCtrl->GetItemCount();
	for(int i=0;i<nCount;i++)
		m_ctrlLogList.DeleteColumn(0);
	m_ctrlLogList.DeleteAllItems();
	
	//���÷��,����,�п�
	m_ctrlLogList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrlLogList.InsertColumn(0,"ʱ��",LVCFMT_LEFT,120); 
	m_ctrlLogList.InsertColumn(1,"�¼�",LVCFMT_LEFT,240); 
	
}

//���¼�б�ͼ�¼�ļ�����¼���Ϣ                                  
void CLQ_TestbedDlg::AddLogText(CString strMsg) 
{
	
	static int nItem=0;
	
	CTime nTime=CTime::GetCurrentTime();
	CString strDate=nTime.Format("%Y-%m-%d ");
	CString strTime=nTime.Format("%H:%M:%S");
	strTime =strDate+strTime;
	
	m_ctrlLogList.InsertItem(nItem,strTime);
	m_ctrlLogList.SetItemText(nItem,1,strMsg);
	
	m_ctrlLogList.SendMessage(WM_VSCROLL,SB_LINERIGHT,0);
	
	if (nItem<1000)
	{
		nItem++;
	}
	else
	{
		m_ctrlLogList.DeleteAllItems();
		nItem=0;
	}
}

//��ʼ��ʵʱ��·���ݱ��
void CLQ_TestbedDlg::InitRealTimePlots()
{	
	memset(NodeList,-1,ALLOW_ACCESS_NODES);	
	m_ctrlPlotx.RemoveAllChannels();
	
	int nNodeID;
	CString strChannelName;
	
	ADOConn m_AdoConn;
	_RecordsetPtr m_pRecordSet;
	m_AdoConn.OnInitADOConn();	
	
	CString strSQL;
	strSQL.Format("SELECT * FROM tb_Nodeinfo WHERE SceneID=%d",m_curSceneID);
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
		m_ctrlPlotx.GetChannel(i).SetMarkersStyle(1);

		m_ctrlPlotx.GetChannel(i).SetTraceVisible(TRUE);
		m_ctrlPlotx.GetChannel(i).SetTraceLineWidth(2);
		i++;
		m_pRecordSet->MoveNext();
	}
	
	
	
}

//��ʼ��ʵʱ�źŽ���ǿ�ȱ��
void CLQ_TestbedDlg::OnRadioRSSIRealTime() 
{
	// TODO: Add your control notification handler code here
	m_iSelection = 0;
	
	m_ctrlPlotx.SetTitleText("RSSI(�źŽ���ǿ��/dBm)");
	
	m_ctrlPlotx.RemoveAllChannels();
	m_ctrlPlotx.AddChannel();
	
	m_ctrlPlotx.GetYAxis(0).SetMin(-100);
	m_ctrlPlotx.GetYAxis(0).SetSpan(100);
	InitRealTimePlots();
}

//��ʼ��ʵʱ��·ָʾ���
void CLQ_TestbedDlg::OnRadioLQIRealTime() 
{
	// TODO: Add your control notification handler code here
	m_iSelection = 1;
	
	m_ctrlPlotx.SetTitleText("LQI(��·����ָʾֵ)");
	m_ctrlPlotx.GetYAxis(0).SetMin(0);
	m_ctrlPlotx.GetYAxis(0).SetSpan(150);
	InitRealTimePlots();
	
}

//��ʼ��ʵʱ����ȱ��
void CLQ_TestbedDlg::OnRadioSNRRealTime() 
{
	m_iSelection = 2;
	
	m_ctrlPlotx.SetTitleText("SNR(�����/dBm)");
	
	m_ctrlPlotx.GetYAxis(0).SetMin(0);
	m_ctrlPlotx.GetYAxis(0).SetDesiredIncrement(5);
	m_ctrlPlotx.GetYAxis(0).SetSpan(100);
	InitRealTimePlots();
}

//���·���
/*
void CLQ_TestbedDlg::OnBtnCommandtest() 
{
if (!m_bOpenUart)
{
AfxMessageBox("�뿪������");
return;
}
if (!m_bStartTest )
{
AfxMessageBox("���½�����");
return;
}

  ((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm.RebootNodesCmdToWSN();
  
	}
*/

//������������
void CLQ_TestbedDlg::OnBtnConfigCmd() 
{
	UpdateData(TRUE);
	if (!m_bOpenUart)
	{
		AfxMessageBox("�뿪������");
		return;
	}
	if (m_nPktSum <=0)
	{
		AfxMessageBox("�����÷���������");
		return;
	}
	if (m_nSendPeriod <=0)
	{
		AfxMessageBox("�����÷������ڣ�");
		return;
	}
	((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm.ConfigCmdToWSN(-1,m_nPktSum,m_nSendPeriod,m_nTestModel);	
	AddLogText("�������·������������");
	
}

/************************************************************************/
/* �ύ���Լƻ�                                                         */
/************************************************************************/
void CLQ_TestbedDlg::OnBtnSubmitSchedule() 
{
	UpdateData(TRUE);
	if (!m_bOpenUart)
	{
		AfxMessageBox("�뿪�����ڼ�����");
		return;
	}
	if (m_curSceneID ==-1)
	{
		AfxMessageBox("���Ȳ���ڵ㣬�ٽ��в���!");
		return;
	}
	if (m_nPktSum <=0)
	{
		AfxMessageBox("����д̽�������");
		return;
	}
	if (m_IntervalTime <=(m_nPktSum/5) )//1s��5�����ݰ�
	{
		AfxMessageBox("�������ڹ��̣����������һ����������!");
		return;
	}
	
	CString  m_strTestMode;
	if (m_nTestModel == 0)
	{
		m_strTestMode="����̽��";
	}
	else
	{
		m_strTestMode="����̽��";
	}
	
	CString strCurDate,strCurTime,strStartDate,strStartTime,strEndDate,strEndTime;
	
	CTime	nowtime = CTime::GetCurrentTime(); //��ǰʱ��
	strCurDate = nowtime.Format(_T("%Y-%m-%d "));
	strCurTime = nowtime.Format(_T("%H:%M:%S"));
	strCurTime =strCurDate+strCurTime;
	
	strStartDate =  m_SDate.Format(_T("%Y-%m-%d "));
	strStartTime = m_STime.Format(_T("%H:%M:%S"));
	strStartTime = strStartDate + strStartTime;
	
	strEndDate = m_EDate.Format(_T("%Y-%m-%d "));
	strEndTime = m_ETime.Format(_T("%H:%M:%S"));
	strEndTime = strEndDate + strEndTime;
	
	if (strStartTime < strCurTime || strEndTime < strCurTime )
	{
		AfxMessageBox("ʱ�䲻��С�ڵ�ǰʱ��");
		return;
		if (strStartTime < strEndTime)
		{
			AfxMessageBox("����ʱ�䲻��С�ڿ�ʼʱ��");
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//ʱ��֮��
	CTimeSpan c_date = m_EDate-m_SDate;
	CTimeSpan c_time = m_ETime-m_STime;
    //ת��Ϊs;
	int nSumtime=c_date.GetTotalSeconds()+c_time.GetTotalSeconds();
	
	if (nSumtime <= m_IntervalTime)
	{
		AfxMessageBox("����ʱ����̲������һ�β��ԣ����������ò���ʱ��!");
		return;
	}
	
	m_curPackets = m_nPktSum;
	
	ADOConn m_AdoConn;
	_RecordsetPtr m_pRecordSet;
	m_AdoConn.OnInitADOConn();	
				
	CString strSQL;
	strSQL.Format("INSERT INTO tb_TestSchedule(SceneID,StartTime,EndTime,TestPackets,SendPeriod,TestPeriod,TestMode) VALUES(%d,'%s','%s',%d,%d,%d,'%s')",m_curSceneID,
		strStartTime,strEndTime,m_nPktSum,m_nSendPeriod,m_IntervalTime,m_strTestMode);	
	
	m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
				
	strSQL.Format("SELECT * FROM tb_TestSchedule WHERE ScheduleID=(SELECT MAX(ScheduleID) FROM tb_TestSchedule)");
	m_pRecordSet=m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	if(!m_pRecordSet->adoEOF)
	{
		m_curTestScheduleID = atoi(VariantToCString(m_pRecordSet->GetCollect("ScheduleID")));						 
	}
	m_bStartTestSchedule = true;
	
	//�ѽڵ�������������·����ڵ�
	(((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm).ConfigCmdToWSN(-1,m_nPktSum,m_nSendPeriod,m_nTestModel);
	
	AddLogText("���Լƻ����ύ!");
	//AfxMessageBox("���Լƻ����ύ!");
	
	GetDlgItem(IDC_BTN_SUBMIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_WITHDRAW)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_DATETIMEPICKER_SDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATETIMEPICKER_STIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATETIMEPICKER_EDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATETIMEPICKER_ETIME)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_EDIT_SENDPERIOD)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MSGSUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_T)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_ACTIVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);
}

void  CLQ_TestbedDlg::TimerCallback(DWORD dwUser)
{
	CLQ_TestbedDlg *pThis = (CLQ_TestbedDlg *)dwUser;
	static short sMsgID=1;
	if (sMsgID<=pThis->m_nPktSum)
	{
		(((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm).ActiveTestToWSN(-1,sMsgID,pThis->m_nPktSum);
		sMsgID++;
	}
	else
	{
		pThis->mm_Timer.KillTimer(); 
		sMsgID=1;
	}
	
}


void CLQ_TestbedDlg::OnTimer(UINT nIDEvent) 
{

	if (nIDEvent==1) 
	{	
		
		CString strCurDate,strCurTime,strStartDate,strStartTime,strEndDate,strEndTime;
		
		CTime	nowtime = CTime::GetCurrentTime(); //��ǰʱ��
		strCurDate = nowtime.Format(_T("%Y-%m-%d"));
		strCurTime = nowtime.Format(_T("%H:%M:%S"));
		
		strStartDate = m_SDate.Format(_T("%Y-%m-%d"));
		strStartTime = m_STime.Format(_T("%H:%M:%S"));
		
		strEndDate = m_EDate.Format(_T("%Y-%m-%d"));
		strEndTime = m_ETime.Format(_T("%H:%M:%S"));
		
		CString strCurTimeShow;
		strCurTimeShow.Format("%s %s",strCurDate,strCurTime);
	

		GetDlgItem(IDC_STATIC_CURTIME)->SetWindowText(strCurTimeShow);
		
		if(	m_bStartTestSchedule )//�ύ�˲�������
		{
			if((strCurDate == strStartDate) && (strCurTime == strStartTime) )//��ʼ��������
			{	
				
				NewTest();//�½�����
				SetTimer(2,m_IntervalTime*1000,NULL);		
				
			}
			
			
			if((strCurDate == strEndDate) && (strCurTime == strEndTime) )//������������
			{
				
				m_bStartTestSchedule = false;				
				m_curTestID = 0;
				KillTimer(2);
				
				GetDlgItem(IDC_BTN_WITHDRAW)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_SUBMIT)->EnableWindow(TRUE);
				
				GetDlgItem(IDC_DATETIMEPICKER_SDATE)->EnableWindow(TRUE);
				GetDlgItem(IDC_DATETIMEPICKER_STIME)->EnableWindow(TRUE);
				GetDlgItem(IDC_DATETIMEPICKER_EDATE)->EnableWindow(TRUE);
				GetDlgItem(IDC_DATETIMEPICKER_ETIME)->EnableWindow(TRUE);
				
				GetDlgItem(IDC_EDIT_MSGSUM)->EnableWindow(TRUE);
				GetDlgItem(IDC_EDIT_T)->EnableWindow(TRUE);	
				
				AfxMessageBox("����������ɣ�");
			}
		}	
	}
				
	if(nIDEvent == 2) //��������
	{	
		if (m_bStartTestSchedule)
		{		
			NewTest();//�½�����
			
		}
	}
	
	if (nIDEvent == 3)
	{	
		if (m_bStartTestSchedule&&m_bStartTest)
		{	
			PreProcessing();//����Ԥ����
			KillTimer(3);
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

//��������
void CLQ_TestbedDlg::OnMenuExportdata() 
{
	// TODO: Add your command handler code here
	CDataManageDlg  dlg;
	dlg.DoModal();
}


/************************************************************************/
/* �������Լƻ�                                                         */
/************************************************************************/
void CLQ_TestbedDlg::OnBtnWithdrawSchedule() 
{
	UpdateData(TRUE);
	m_bStartTestSchedule = false;
	
	if(m_nTestModel ==0)
	{
		mm_Timer.KillTimer();
	}
	else
	{
		(((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm).ControlCmdToWSN(-1,0);		//�ڵ�ֹͣ��������	
	}
	
	//ɾ����ʱ��
	KillTimer(2);
	
	//���ԭ�ƻ��ͼƻ��µ����в�������
	ADOConn m_AdoConn;
	_RecordsetPtr m_pRecordSet;
	m_AdoConn.OnInitADOConn();	
				
	CString strSQL;
	strSQL.Format("SELECT * FROM tb_TestInfo WHERE ScheduleID=%d",m_curTestScheduleID);	
	m_pRecordSet=m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	
	try
	{
		//�¼�start
		m_AdoConn.m_pConnection->BeginTrans(); 
		
		while (!m_pRecordSet->adoEOF)
		{
			int nTestID = atoi(VariantToCString(m_pRecordSet->GetCollect("TestID")));	
			
			//ɾ�����ݰ���Ϣ���еĲ�����Ϣ
			strSQL.Format("DELETE FROM tb_PacketInfo WHERE TestID=%d",nTestID);
			m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
			
			strSQL.Format("DELETE FROM tb_TestInfo WHERE TestID=%d",nTestID);
			m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
			
			m_pRecordSet->MoveNext();
		}
		
		strSQL.Format("DELETE FROM tb_TestSchedule WHERE ScheduleID=%d",m_curTestScheduleID);	
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
		
		m_AdoConn.m_pConnection->CommitTrans(); //�¼�end	

		AfxMessageBox("���Լƻ���ȡ��");
		GetDlgItem(IDC_BTN_WITHDRAW)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SUBMIT)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_DATETIMEPICKER_SDATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_STIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_EDATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_ETIME)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_EDIT_MSGSUM)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SENDPERIOD)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_ACTIVE)->EnableWindow(TRUE);	
		GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_T)->EnableWindow(TRUE);	
		m_curTestScheduleID = -1; //��λ
	}
	catch (_com_error e)
	{
		m_AdoConn.m_pConnection->RollbackTrans();//�ع�����
		AfxMessageBox(e.ErrorMessage());						
	}	
}


/************************************************************************/
/* �½�����                                                             */
/************************************************************************/
void CLQ_TestbedDlg::NewTest()
{	
	UpdateData(TRUE);
	
	CTime curTime=CTime::GetCurrentTime();
	CString strDate=curTime.Format("%Y-%m-%d ");
	CString m_strTime=curTime.Format("%H:%M:%S");
	
	CTimeSpan cTimespan = m_ETime - curTime;//��Ԥ����ʱ��
    int nTime = cTimespan.GetTotalSeconds();
	
	if (!m_bStartTest && nTime>=m_IntervalTime)
	{
		m_bStartTest = true;
		//��ǰ����id
		m_curTestID++; 
		
		//��¼��ʼ����ʱ��
		m_strStartTime =strDate+m_strTime;
		
		if (m_nTestModel==0)
		{
			mm_Timer.CreateTimer((DWORD)this,m_nSendPeriod,TimerCallback);  
		}
		else
		{
			//���²��������·����ڵ�
			(((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm).ControlCmdToWSN(-1,2);	
		}
		
		
		//��ʱ��ʼԤ���� 
		int prePTime = m_nPktSum/5+(m_IntervalTime-m_nPktSum/5)/2;
		SetTimer(3,prePTime*1000,NULL);	
	}	
}

/************************************************************************/
/* Ԥ����ͳ��PRR���ó����                                            */
/************************************************************************/
void CLQ_TestbedDlg::PreProcessing()
{
	m_bStartTest = false;	
	
	int  nRSSIUp=0, nLQIUp=0, nSNRUp=0;
	int  nRSSIDown=0, nLQIDown=0, nSNRDown=0;
	
	double  fMeanRSSIUp=0, fMeanLQIUp=0, fMeanSNRUp=0;
	double  fMeanRSSIDown=0, fMeanLQIDown=0, fMeanSNRDown=0;
	
	double  fDetRSSIUp=0, fDetLQIUp=0, fDetSNRUp=0;
	double  fDetRSSIDown=0, fDetLQIDown=0, fDetSNRDown=0;
	
	int	 nNodeID, nReceivedPkts=0;
	
	double fPRR=0;
	
	ADOConn m_AdoConn;
	_RecordsetPtr m_pNodeRecordSet,m_pTestRecordSet,m_pPRRRecordSet,m_pDetRecordSet;
	m_AdoConn.OnInitADOConn();	
	
	CString strSQL;
	
	strSQL.Format("SELECT * FROM tb_NodeInfo WHERE SceneID=%d",m_curSceneID);         
	m_pNodeRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	
	while(!m_pNodeRecordSet->adoEOF) //�������е�ÿ���ڵ���ͳ��
	{
		
		nNodeID = atoi(VariantToCString(m_pNodeRecordSet->GetCollect("NodeID")));
		
		//��PRR
		strSQL.Format("SELECT COUNT(*) AS RPackets FROM tb_PacketInfo WHERE ScheduleID= %d AND TestID=%d AND NodeID=%d",m_curTestScheduleID,m_curTestID,nNodeID);
		m_pPRRRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
		
		if(!m_pPRRRecordSet->adoEOF)
		{
			nReceivedPkts = atoi(VariantToCString(m_pPRRRecordSet->GetCollect("RPackets")));
			if (nReceivedPkts <= m_curPackets)
			{
				fPRR = 100*(double)nReceivedPkts/m_curPackets;
			}
			else
			{
				fPRR =100;
			}
		}

		//���ֵ
		strSQL.Format("SELECT AVG(RSSI_Down) AS MeanRSSIDown,AVG(LQI_Down) AS MeanLQIDown,AVG(SNR_Down) AS MeanSNRDown, \
			 AVG(RSSI_Up) AS MeanRSSIUp,AVG(LQI_Up) AS MeanLQIUp,AVG(SNR_Up) AS MeanSNRUp FROM tb_PacketInfo \
			WHERE ScheduleID= %d AND TestID=%d AND NodeID=%d",m_curTestScheduleID,m_curTestID,nNodeID);
		
		m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
		
		if (!m_pTestRecordSet->adoEOF) //������ڵ�����������ʱ
		{
			fMeanRSSIUp = atof(VariantToCString(m_pTestRecordSet->GetCollect("MeanRSSIUp")));
			fMeanLQIUp = atof(VariantToCString(m_pTestRecordSet->GetCollect("MeanLQIUp")));
			fMeanSNRUp = atof(VariantToCString(m_pTestRecordSet->GetCollect("MeanSNRUp")));
			
			fMeanRSSIDown = atof(VariantToCString(m_pTestRecordSet->GetCollect("MeanRSSIDown")));
			fMeanLQIDown = atof(VariantToCString(m_pTestRecordSet->GetCollect("MeanLQIDown")));
			fMeanSNRDown = atof(VariantToCString(m_pTestRecordSet->GetCollect("MeanSNRDown")));
			
		}
					
		//�󷽲�
		strSQL.Format("SELECT * FROM tb_PacketInfo WHERE ScheduleID= %d AND TestID=%d AND NodeID=%d",m_curTestScheduleID,m_curTestID,nNodeID);
		m_pDetRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
			
			double fSumRSSIUp = 0, fSumLQIUp = 0, fSumSNRUp = 0;
			double fSumRSSIDown = 0, fSumLQIDown = 0, fSumSNRDown = 0;
			
			while(!m_pDetRecordSet->adoEOF)
			{
				nRSSIUp = atoi(VariantToCString(m_pDetRecordSet->GetCollect("RSSI_Up")));
				nLQIUp = atoi(VariantToCString(m_pDetRecordSet->GetCollect("LQI_Up")));
				nSNRUp = atoi(VariantToCString(m_pDetRecordSet->GetCollect("SNR_Up")));
				
				fDetRSSIUp = (float)(nRSSIUp-fMeanRSSIUp)*(nRSSIUp-fMeanRSSIUp);
				fSumRSSIUp += fDetRSSIUp;	
				
				fDetLQIUp = (float)(nLQIUp-fMeanLQIUp)*(nLQIUp-fMeanLQIUp);
				fSumLQIUp += fDetLQIUp;
				
				fDetSNRUp = (float)(nSNRUp-fMeanSNRUp)*(nSNRUp-fMeanSNRUp);
				fSumSNRUp += fDetSNRUp;
				
				
				nRSSIDown = atoi(VariantToCString(m_pDetRecordSet->GetCollect("RSSI_Down")));
				nLQIDown = atoi(VariantToCString(m_pDetRecordSet->GetCollect("LQI_Down")));
				nSNRDown = atoi(VariantToCString(m_pDetRecordSet->GetCollect("SNR_Down")));
				
				fDetRSSIDown = (float)(nRSSIDown-fMeanRSSIDown)*(nRSSIDown-fMeanRSSIDown);
				fSumRSSIDown += fDetRSSIDown;	
				
				fDetLQIDown = (float)(nLQIDown-fMeanLQIDown)*(nLQIDown-fMeanLQIDown);
				fSumLQIDown += fDetLQIDown;
				
				fDetSNRDown = (float)(nSNRDown-fMeanSNRDown)*(nSNRDown-fMeanSNRDown);
				fSumSNRDown += fDetSNRDown;
				
				m_pDetRecordSet->MoveNext();
			}
			
			if (nReceivedPkts>0)
			{	
			fSumRSSIUp = fSumRSSIUp/nReceivedPkts;
			fSumLQIUp = fSumLQIUp/nReceivedPkts;
			fSumSNRUp = fSumSNRUp/nReceivedPkts;
			
			fSumRSSIDown = fSumRSSIDown/nReceivedPkts;
			fSumLQIDown = fSumLQIDown/nReceivedPkts;
			fSumSNRDown = fSumSNRDown/nReceivedPkts;
			}
			else
			{
				fSumRSSIUp=fSumRSSIDown=0;
				fSumLQIUp=fSumLQIDown=0;
				fSumSNRUp=fSumSNRDown=0;
			}
			
			CTime nTime=CTime::GetCurrentTime();
			CString strEndDate=nTime.Format("%Y-%m-%d ");
			CString strEndTime=nTime.Format("%H:%M:%S");
			strEndTime =strEndDate+strEndTime;
			
			//������Խ��
			strSQL.Format("INSERT INTO tb_TestInfo(ScheduleID,TestID,NodeID,MeanRSSI_Down,MeanRSSI_Up,MeanLQI_Down,MeanLQI_Up,MeanSNR_Down,MeanSNR_Up,VarRSSI_Down,VarRSSI_Up,VarLQI_Down,VarLQI_Up,VarSNR_Down,VarSNR_Up,PRR,StartTestTime,EndTestTime) VALUES(%d,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,'%s','%s')",m_curTestScheduleID,m_curTestID,nNodeID,fMeanRSSIDown,fMeanRSSIUp,fMeanLQIDown,fMeanLQIUp,fMeanSNRDown,fMeanSNRUp,fSumRSSIDown,fSumRSSIUp,fSumLQIDown,fSumLQIUp,fSumSNRDown,fSumSNRUp,fPRR,m_strStartTime,strEndTime);
			m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
	
		m_pNodeRecordSet->MoveNext();
	}
	
}

LRESULT CLQ_TestbedDlg::OnCmdFeedbackMsg(WPARAM wParam,LPARAM lparam)
{	  
	
	static int nItem=0;
	CTime nTime=CTime::GetCurrentTime();
	CString strDate=nTime.Format("%Y-%m-%d ");
	CString strTime=nTime.Format("%H:%M:%S");
	strTime = strDate+strTime;
	
	CString strMsg = (char *)lparam;
	
	m_ctrlLogList.InsertItem(nItem,strTime);
	m_ctrlLogList.SetItemText(nItem,1,strMsg);
	
	m_ctrlLogList.SendMessage(WM_VSCROLL,SB_LINERIGHT,0);
	
	if (nItem<1000)
	{
		nItem++;
	}
	else
	{
		m_ctrlLogList.DeleteAllItems();
		nItem=0;
	}
	return 1;
}

void CLQ_TestbedDlg::OnAboutbox() 
{
	CAboutDlg dlg;

	dlg.DoModal();
}

void CLQ_TestbedDlg::OnChangeEditMsgSum() 
{
	UpdateData(TRUE);
	if (m_nPktSum>0 && m_nSendPeriod>0)
	{
		int	nIntervalTime = m_nPktSum*m_nSendPeriod/1000; //(����Ƶ��Ϊ5/s)
		CString str;
		str.Format("(T>%d)",nIntervalTime);
		GetDlgItem(IDC_STATIC_TIME)->SetWindowText(str);
		UpdateData(FALSE);
	}
}

void CLQ_TestbedDlg::OnChangeEditSendperiod() 
{
	OnChangeEditMsgSum();	
}

void CLQ_TestbedDlg::OnMenuCurResultShow() 
{
	CTestResultDisplayDlg  dlg;
	dlg.nSearchSceneID = m_curSceneID;
	dlg.nSearchScheduleID = m_curTestScheduleID;
	dlg.DoModal();
}


void CLQ_TestbedDlg::OnMenuOldresult() 
{
	CTestResultDisplayDlg  dlg;
	dlg.DoModal();
}

void CLQ_TestbedDlg::OnMenuLQP() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("���ڿ�����");\

	
}

void CLQ_TestbedDlg::OnMenuDatamanage() 
{
	CDataManageDlg dlg;
	dlg.DoModal();
}

void CLQ_TestbedDlg::OnMenuDisplayTopology()
{
	DisplayTopologyDlg dlg;
	dlg.DoModal();
}

void CLQ_TestbedDlg::OnMenuPower()
{
	PowerDLG dlg;
	dlg.DoModal();
}



void CLQ_TestbedDlg::OnEnChangeEditT()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
