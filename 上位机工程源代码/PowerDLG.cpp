// PowerDLG.cpp: 实现文件
//

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "PowerDLG.h"
#include "afxdialogex.h"


// PowerDLG 对话框

IMPLEMENT_DYNAMIC(PowerDLG, CDialog)

PowerDLG::PowerDLG(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_POWER_DLG, pParent)
{

}

PowerDLG::~PowerDLG()
{
}

void PowerDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PowerDLG, CDialog)
END_MESSAGE_MAP()


// PowerDLG 消息处理程序
