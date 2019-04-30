// OptionDlg.cpp : implementation file
//  

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "OptionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionDlg dialog


COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
: CDialog(COptionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionDlg)
	//}}AFX_DATA_INIT
}


void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionDlg)
	DDX_Control(pDX, IDC_COMBO_SERIALBAUD, m_ctrlSerialBaud);
	DDX_Control(pDX, IDC_COMBO_SERIALPORT, m_ctrlSerialPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialog)
//{{AFX_MSG_MAP(COptionDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionDlg message handlers

BOOL COptionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	//串口
	m_ctrlSerialPort.AddString("1");
	m_ctrlSerialPort.AddString("2");
	m_ctrlSerialPort.AddString("3");
	m_ctrlSerialPort.AddString("4");
	m_ctrlSerialPort.AddString("5");
	m_ctrlSerialPort.AddString("6");
	m_ctrlSerialPort.AddString("7");
	m_ctrlSerialPort.AddString("8");
	m_ctrlSerialPort.AddString("9");
	m_ctrlSerialPort.AddString("10");
	m_ctrlSerialPort.AddString("11");
	m_ctrlSerialPort.AddString("12");
	m_ctrlSerialPort.AddString("13");
	m_ctrlSerialPort.AddString("14");
	m_ctrlSerialPort.AddString("15");
	m_ctrlSerialPort.AddString("16");
	m_ctrlSerialPort.AddString("17");
	m_ctrlSerialPort.AddString("18");
	m_ctrlSerialPort.AddString("19");
	m_ctrlSerialPort.AddString("20");
	
	//波特率
	m_ctrlSerialBaud.AddString("300");
	m_ctrlSerialBaud.AddString("600");
	m_ctrlSerialBaud.AddString("1200");
	m_ctrlSerialBaud.AddString("2400");
	m_ctrlSerialBaud.AddString("4800");
	m_ctrlSerialBaud.AddString("9600");
	m_ctrlSerialBaud.AddString("19200");
	m_ctrlSerialBaud.AddString("38400");
	m_ctrlSerialBaud.AddString("57600");
	m_ctrlSerialBaud.AddString("115200");
	m_ctrlSerialBaud.AddString("230400");
	m_ctrlSerialBaud.AddString("460800");
	m_ctrlSerialBaud.AddString("921600");
	
	CString  strTemp;
	//读取配置文件
	::GetPrivateProfileString("BaseSet","SerialPort","",strTemp.GetBuffer(100),100,".\\Config\\LQ_TestbedConfig.ini");
    m_ctrlSerialPort.SetWindowText(strTemp);

	::GetPrivateProfileString("BaseSet","BaudRate","",strTemp.GetBuffer(100),100,".\\Config\\LQ_TestbedConfig.ini");
	m_ctrlSerialBaud.SetWindowText(strTemp);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void COptionDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	
	CString strText;

	int nIndex;
	nIndex=m_ctrlSerialPort.GetCurSel();
	if(-1!=nIndex)
	{
		m_ctrlSerialPort.GetLBText(nIndex,strText);
		::WritePrivateProfileString("BaseSet","SerialPort", strText ,".\\Config\\LQ_TestbedConfig.ini");
	}

	
	nIndex=m_ctrlSerialBaud.GetCurSel();
	if(-1!=nIndex)
	{
		m_ctrlSerialBaud.GetLBText(nIndex,strText);
		::WritePrivateProfileString("BaseSet","BaudRate", strText,".\\Config\\LQ_TestbedConfig.ini");
	}

	CDialog::OnOK();
}

void COptionDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
