#pragma once


// PowerDLG 对话框

class PowerDLG : public CDialog
{
	DECLARE_DYNAMIC(PowerDLG)

public:
	PowerDLG(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PowerDLG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POWER_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
