// DisplayTopologyDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "DisplayTopologyDlg.h"
#include "afxdialogex.h"


// DisplayTopologyDlg 对话框

IMPLEMENT_DYNAMIC(DisplayTopologyDlg, CDialog)

DisplayTopologyDlg::DisplayTopologyDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DISPLAYTOPOLOGY_DLG, pParent)
{

}

DisplayTopologyDlg::~DisplayTopologyDlg()
{
}

void DisplayTopologyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(DisplayTopologyDlg, CDialog)
END_MESSAGE_MAP()


// DisplayTopologyDlg 消息处理程序
