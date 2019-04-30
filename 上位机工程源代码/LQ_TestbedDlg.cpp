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
	
	//添加工具栏
	TBBUTTON button[9];
	int i=0,nStringLength;
	CString string;
	TCHAR * pString;
	
	m_ImageList.Create(42,42,ILC_COLOR32|ILC_MASK,0,0);	//创建图像列表框,32色,48X48象素	
	
	m_ToolBar.EnableAutomation();
	m_ToolBar.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDR_TOOLBAR);
	//向IMAGELIST对象添加资源图标
	
	for(i=IDI_ICON1;i<=IDI_ICON9;i++)
	{		
		m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(i)));		
	}	
	m_ToolBar.SetImageList(&m_ImageList);	
	//为图标添加文字说明
	for(i=0;i<9;i++)//改了
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
	//将工具栏的命令ID与菜单绑定
	button[0].idCommand=ID_MENU_NODEMANAGE;//节点管理
	button[1].idCommand=ID_MENU_TESTCUSTOM;//测试定制
	button[2].idCommand=ID_MENU_START;//开始测试
 	button[3].idCommand=ID_MENU_CURRESULT;//当前结果
	// 	button[4].idCommand=ID_MENU_PRINT;//打印评估
	// 	button[5].idCommand=ID_MENU_SYSTEMMANAGE;//系统管理
	button[6].idCommand=ID_MENU_OLDRESULT;//
 	button[7].idCommand=ID_MENU_DATAMANAGE;//导出数据
	button[8].idCommand=ID_MENU_EXIT;//退出系统
	
	
	m_ToolBar.AddButtons(9,button);
	
	button[0].fsStyle=TBSTYLE_SEP;
	
	//添加分隔条,应该从后向前添加,这样不用考虑添加后对序号的影响
	// 	m_ToolBar.InsertButton(10,&button[0]);
	m_ToolBar.InsertButton(6,&button[0]);
	m_ToolBar.InsertButton(3,&button[0]);
	m_ToolBar.InsertButton(1,&button[0]);
	
	m_ToolBar.AutoSize();
	m_ToolBar.SetStyle(TBSTYLE_FLAT|CCS_TOP);	//更改风格
	
	InitPacketInfo();//初始化消息包信息表
	InitLogListInfo();
	//默认显示RSSI值
	m_iSelection=0;
	OnRadioRSSIRealTime();
	
	//默认显示当前时间
	CTime	nowtime = CTime::GetCurrentTime();
	m_EDate = nowtime;
	m_ETime = nowtime;
	m_SDate = nowtime;
	m_STime = nowtime;
	GetDlgItem(IDC_BTN_WITHDRAW)->EnableWindow(FALSE);
	
	//定义状态栏
	m_wndStatusBar.Create(WS_CHILD|WS_VISIBLE|CCS_BOTTOM,  CRect(0,0,0,0),  this,  102);	
    m_wndStatusBar.SetText("\t南昌航空大学物联网技术研究所版权所有(C)2014  All Rights Reserved",0,0 );
	
	
	//初始化定时器
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

//基本设置
void CLQ_TestbedDlg::OnMenuBaseSet() 
{
	COptionDlg dlg;
	dlg.DoModal();
}

//开启服务，建立连接
void CLQ_TestbedDlg::OnMenuStart() 
{
	// TODO: Add your command handler code here

	CString  strTemp;
	int nSerialPort,nSerialBaud;
	//读取配置文件
	::GetPrivateProfileString("BaseSet","SerialPort","",strTemp.GetBuffer(100),100,".\\Config\\LQ_TestbedConfig.ini");
	nSerialPort=atoi(strTemp);
	::GetPrivateProfileString("BaseSet","BaudRate","",strTemp.GetBuffer(100),100,".\\Config\\LQ_TestbedConfig.ini");
	nSerialBaud=atoi(strTemp);
	
	if(!(m_bOpenUart))
	{
		BeginWaitCursor();				
		//开启串口
		if (!((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm.Open(this,nSerialPort,nSerialBaud,'N',8,1,EV_RXFLAG | EV_RXCHAR,512))
		{
			EndWaitCursor();
			AfxMessageBox("服务启动失败:串口打开失败!",MB_OK|MB_ICONEXCLAMATION);
			return;
		}	
		//创建多线程监听串口
		
		m_bOpenUart=TRUE;
		AddLogText("监听开启!");
		EndWaitCursor();
	}
	else
	{
		AfxMessageBox("已开启监听，无需重复操作!");
	}
}

//关闭服务，断开连接
void CLQ_TestbedDlg::OnMenuClose() 
{	
	if(m_bOpenUart)
	{
		BeginWaitCursor();
		//关闭串口监听		
		((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm.Close();	
		m_bOpenUart=FALSE;
		EndWaitCursor();
		AfxMessageBox("断开连接!");
	}
	else
	{
		AfxMessageBox("尚未开启连接!");
	}
	
}

//通过菜单栏退出平台
void CLQ_TestbedDlg::OnMenuExit() 
{
	if(AfxMessageBox("确定要退出平台吗?",4+32+256)==IDYES)
	{
		CDialog::OnOK();
	}
}

//退出平台
void CLQ_TestbedDlg::OnClose() 
{
	if(AfxMessageBox("确定要退出平台吗?",4+32+256)==IDYES)
	{
		CDialog::OnClose();
	}
}

//网络部署
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
//初始化数据包信息

void CLQ_TestbedDlg::InitPacketInfo()
{
	int nCount=0;
	CHeaderCtrl *pHeaderCtrl=m_ctrlListPacketInfo.GetHeaderCtrl();
	if(pHeaderCtrl!=NULL)
		nCount=pHeaderCtrl->GetItemCount();
	for(int i=0;i<nCount;i++)
		m_ctrlListPacketInfo.DeleteColumn(0);
	m_ctrlListPacketInfo.DeleteAllItems();
	
	//设置风格,列名,列宽
	m_ctrlListPacketInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrlListPacketInfo.InsertColumn(0,"节点ID",LVCFMT_CENTER,60); 
	m_ctrlListPacketInfo.InsertColumn(1,"消息序列",LVCFMT_CENTER,60); 
	m_ctrlListPacketInfo.InsertColumn(2,"RSSI(dBm)",LVCFMT_CENTER,80); 
	m_ctrlListPacketInfo.InsertColumn(3,"LQI",LVCFMT_CENTER,60); 
	m_ctrlListPacketInfo.InsertColumn(4,"SNR(dBm)",LVCFMT_CENTER,80); 
	m_ctrlListPacketInfo.InsertColumn(5,"消息总数",LVCFMT_CENTER,80); 
	m_ctrlListPacketInfo.InsertColumn(6,"接收时间",LVCFMT_CENTER,150); 	
}
//初始化日志列表

void CLQ_TestbedDlg::InitLogListInfo()
{
	int nCount=0;
	CHeaderCtrl *pHeaderCtrl=m_ctrlLogList.GetHeaderCtrl();
	if(pHeaderCtrl!=NULL)
		nCount=pHeaderCtrl->GetItemCount();
	for(int i=0;i<nCount;i++)
		m_ctrlLogList.DeleteColumn(0);
	m_ctrlLogList.DeleteAllItems();
	
	//设置风格,列名,列宽
	m_ctrlLogList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrlLogList.InsertColumn(0,"时间",LVCFMT_LEFT,120); 
	m_ctrlLogList.InsertColumn(1,"事件",LVCFMT_LEFT,240); 
	
}

//向记录列表和记录文件添加事件信息                                  
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

//初始化实时链路数据表格
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
		strChannelName.Format("%d号节点",nNodeID);
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

//初始化实时信号接收强度表格
void CLQ_TestbedDlg::OnRadioRSSIRealTime() 
{
	// TODO: Add your control notification handler code here
	m_iSelection = 0;
	
	m_ctrlPlotx.SetTitleText("RSSI(信号接收强度/dBm)");
	
	m_ctrlPlotx.RemoveAllChannels();
	m_ctrlPlotx.AddChannel();
	
	m_ctrlPlotx.GetYAxis(0).SetMin(-100);
	m_ctrlPlotx.GetYAxis(0).SetSpan(100);
	InitRealTimePlots();
}

//初始化实时链路指示表格
void CLQ_TestbedDlg::OnRadioLQIRealTime() 
{
	// TODO: Add your control notification handler code here
	m_iSelection = 1;
	
	m_ctrlPlotx.SetTitleText("LQI(链路质量指示值)");
	m_ctrlPlotx.GetYAxis(0).SetMin(0);
	m_ctrlPlotx.GetYAxis(0).SetSpan(150);
	InitRealTimePlots();
	
}

//初始化实时信噪比表格
void CLQ_TestbedDlg::OnRadioSNRRealTime() 
{
	m_iSelection = 2;
	
	m_ctrlPlotx.SetTitleText("SNR(信噪比/dBm)");
	
	m_ctrlPlotx.GetYAxis(0).SetMin(0);
	m_ctrlPlotx.GetYAxis(0).SetDesiredIncrement(5);
	m_ctrlPlotx.GetYAxis(0).SetSpan(100);
	InitRealTimePlots();
}

//重新发送
/*
void CLQ_TestbedDlg::OnBtnCommandtest() 
{
if (!m_bOpenUart)
{
AfxMessageBox("请开启服务！");
return;
}
if (!m_bStartTest )
{
AfxMessageBox("请新建测试");
return;
}

  ((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm.RebootNodesCmdToWSN();
  
	}
*/

//发送配置命令
void CLQ_TestbedDlg::OnBtnConfigCmd() 
{
	UpdateData(TRUE);
	if (!m_bOpenUart)
	{
		AfxMessageBox("请开启服务！");
		return;
	}
	if (m_nPktSum <=0)
	{
		AfxMessageBox("请设置发包数量！");
		return;
	}
	if (m_nSendPeriod <=0)
	{
		AfxMessageBox("请设置发送周期！");
		return;
	}
	((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm.ConfigCmdToWSN(-1,m_nPktSum,m_nSendPeriod,m_nTestModel);	
	AddLogText("向网络下发测试配置命令！");
	
}

/************************************************************************/
/* 提交测试计划                                                         */
/************************************************************************/
void CLQ_TestbedDlg::OnBtnSubmitSchedule() 
{
	UpdateData(TRUE);
	if (!m_bOpenUart)
	{
		AfxMessageBox("请开启串口监听！");
		return;
	}
	if (m_curSceneID ==-1)
	{
		AfxMessageBox("请先部署节点，再进行测试!");
		return;
	}
	if (m_nPktSum <=0)
	{
		AfxMessageBox("请填写探测包总数");
		return;
	}
	if (m_IntervalTime <=(m_nPktSum/5) )//1s，5个数据包
	{
		AfxMessageBox("测试周期过短，不足于完成一次完整测试!");
		return;
	}
	
	CString  m_strTestMode;
	if (m_nTestModel == 0)
	{
		m_strTestMode="主动探测";
	}
	else
	{
		m_strTestMode="被动探测";
	}
	
	CString strCurDate,strCurTime,strStartDate,strStartTime,strEndDate,strEndTime;
	
	CTime	nowtime = CTime::GetCurrentTime(); //当前时间
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
		AfxMessageBox("时间不能小于当前时间");
		return;
		if (strStartTime < strEndTime)
		{
			AfxMessageBox("结束时间不能小于开始时间");
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//时间之差
	CTimeSpan c_date = m_EDate-m_SDate;
	CTimeSpan c_time = m_ETime-m_STime;
    //转换为s;
	int nSumtime=c_date.GetTotalSeconds()+c_time.GetTotalSeconds();
	
	if (nSumtime <= m_IntervalTime)
	{
		AfxMessageBox("结束时间过短不足完成一次测试，请重新设置测试时间!");
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
	
	//把节点测试配置命令下发给节点
	(((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm).ConfigCmdToWSN(-1,m_nPktSum,m_nSendPeriod,m_nTestModel);
	
	AddLogText("测试计划已提交!");
	//AfxMessageBox("测试计划已提交!");
	
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
		
		CTime	nowtime = CTime::GetCurrentTime(); //当前时间
		strCurDate = nowtime.Format(_T("%Y-%m-%d"));
		strCurTime = nowtime.Format(_T("%H:%M:%S"));
		
		strStartDate = m_SDate.Format(_T("%Y-%m-%d"));
		strStartTime = m_STime.Format(_T("%H:%M:%S"));
		
		strEndDate = m_EDate.Format(_T("%Y-%m-%d"));
		strEndTime = m_ETime.Format(_T("%H:%M:%S"));
		
		CString strCurTimeShow;
		strCurTimeShow.Format("%s %s",strCurDate,strCurTime);
	

		GetDlgItem(IDC_STATIC_CURTIME)->SetWindowText(strCurTimeShow);
		
		if(	m_bStartTestSchedule )//提交了测试任务
		{
			if((strCurDate == strStartDate) && (strCurTime == strStartTime) )//开始测试任务
			{	
				
				NewTest();//新建测试
				SetTimer(2,m_IntervalTime*1000,NULL);		
				
			}
			
			
			if((strCurDate == strEndDate) && (strCurTime == strEndTime) )//结束测试任务
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
				
				AfxMessageBox("测试任务完成！");
			}
		}	
	}
				
	if(nIDEvent == 2) //测试周期
	{	
		if (m_bStartTestSchedule)
		{		
			NewTest();//新建测试
			
		}
	}
	
	if (nIDEvent == 3)
	{	
		if (m_bStartTestSchedule&&m_bStartTest)
		{	
			PreProcessing();//数据预处理
			KillTimer(3);
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

//导出数据
void CLQ_TestbedDlg::OnMenuExportdata() 
{
	// TODO: Add your command handler code here
	CDataManageDlg  dlg;
	dlg.DoModal();
}


/************************************************************************/
/* 撤销测试计划                                                         */
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
		(((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm).ControlCmdToWSN(-1,0);		//节点停止发包命令	
	}
	
	//删除定时器
	KillTimer(2);
	
	//清空原计划和计划下的所有测试数据
	ADOConn m_AdoConn;
	_RecordsetPtr m_pRecordSet;
	m_AdoConn.OnInitADOConn();	
				
	CString strSQL;
	strSQL.Format("SELECT * FROM tb_TestInfo WHERE ScheduleID=%d",m_curTestScheduleID);	
	m_pRecordSet=m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	
	try
	{
		//事件start
		m_AdoConn.m_pConnection->BeginTrans(); 
		
		while (!m_pRecordSet->adoEOF)
		{
			int nTestID = atoi(VariantToCString(m_pRecordSet->GetCollect("TestID")));	
			
			//删除数据包信息表中的测试信息
			strSQL.Format("DELETE FROM tb_PacketInfo WHERE TestID=%d",nTestID);
			m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
			
			strSQL.Format("DELETE FROM tb_TestInfo WHERE TestID=%d",nTestID);
			m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
			
			m_pRecordSet->MoveNext();
		}
		
		strSQL.Format("DELETE FROM tb_TestSchedule WHERE ScheduleID=%d",m_curTestScheduleID);	
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
		
		m_AdoConn.m_pConnection->CommitTrans(); //事件end	

		AfxMessageBox("测试计划已取消");
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
		m_curTestScheduleID = -1; //复位
	}
	catch (_com_error e)
	{
		m_AdoConn.m_pConnection->RollbackTrans();//回滚事务
		AfxMessageBox(e.ErrorMessage());						
	}	
}


/************************************************************************/
/* 新建测试                                                             */
/************************************************************************/
void CLQ_TestbedDlg::NewTest()
{	
	UpdateData(TRUE);
	
	CTime curTime=CTime::GetCurrentTime();
	CString strDate=curTime.Format("%Y-%m-%d ");
	CString m_strTime=curTime.Format("%H:%M:%S");
	
	CTimeSpan cTimespan = m_ETime - curTime;//的预处理时间
    int nTime = cTimespan.GetTotalSeconds();
	
	if (!m_bStartTest && nTime>=m_IntervalTime)
	{
		m_bStartTest = true;
		//当前测试id
		m_curTestID++; 
		
		//记录开始测试时间
		m_strStartTime =strDate+m_strTime;
		
		if (m_nTestModel==0)
		{
			mm_Timer.CreateTimer((DWORD)this,m_nSendPeriod,TimerCallback);  
		}
		else
		{
			//重新测试命令下发给节点
			(((CLQ_TestbedApp*)AfxGetApp())->m_ServerComm).ControlCmdToWSN(-1,2);	
		}
		
		
		//计时开始预处理 
		int prePTime = m_nPktSum/5+(m_IntervalTime-m_nPktSum/5)/2;
		SetTimer(3,prePTime*1000,NULL);	
	}	
}

/************************************************************************/
/* 预处理，统计PRR，得出结果                                            */
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
	
	while(!m_pNodeRecordSet->adoEOF) //按测试中的每个节点来统计
	{
		
		nNodeID = atoi(VariantToCString(m_pNodeRecordSet->GetCollect("NodeID")));
		
		//求PRR
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

		//求均值
		strSQL.Format("SELECT AVG(RSSI_Down) AS MeanRSSIDown,AVG(LQI_Down) AS MeanLQIDown,AVG(SNR_Down) AS MeanSNRDown, \
			 AVG(RSSI_Up) AS MeanRSSIUp,AVG(LQI_Up) AS MeanLQIUp,AVG(SNR_Up) AS MeanSNRUp FROM tb_PacketInfo \
			WHERE ScheduleID= %d AND TestID=%d AND NodeID=%d",m_curTestScheduleID,m_curTestID,nNodeID);
		
		m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
		
		if (!m_pTestRecordSet->adoEOF) //当这个节点有数据上来时
		{
			fMeanRSSIUp = atof(VariantToCString(m_pTestRecordSet->GetCollect("MeanRSSIUp")));
			fMeanLQIUp = atof(VariantToCString(m_pTestRecordSet->GetCollect("MeanLQIUp")));
			fMeanSNRUp = atof(VariantToCString(m_pTestRecordSet->GetCollect("MeanSNRUp")));
			
			fMeanRSSIDown = atof(VariantToCString(m_pTestRecordSet->GetCollect("MeanRSSIDown")));
			fMeanLQIDown = atof(VariantToCString(m_pTestRecordSet->GetCollect("MeanLQIDown")));
			fMeanSNRDown = atof(VariantToCString(m_pTestRecordSet->GetCollect("MeanSNRDown")));
			
		}
					
		//求方差
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
			
			//插入测试结果
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
		int	nIntervalTime = m_nPktSum*m_nSendPeriod/1000; //(发包频率为5/s)
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
	AfxMessageBox("正在开发中");\

	
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
