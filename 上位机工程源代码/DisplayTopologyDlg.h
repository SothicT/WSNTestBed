#pragma once


// DisplayTopologyDlg 对话框

class DisplayTopologyDlg : public CDialog
{
	DECLARE_DYNAMIC(DisplayTopologyDlg)

public:
	DisplayTopologyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DisplayTopologyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DISPLAYTOPOLOGY_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
