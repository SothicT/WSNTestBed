// TestDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "TestDlg.h"
#include "afxdialogex.h"


// TestDlg 对话框

IMPLEMENT_DYNAMIC(TestDlg, CDialog)

TestDlg::TestDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TEST_DLG, pParent)
{

}

TestDlg::~TestDlg()
{
}

void TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TestDlg, CDialog)
END_MESSAGE_MAP()


// TestDlg 消息处理程序
