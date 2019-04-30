// DataManageDlg.cpp : implementation file
//
#include "stdafx.h"
#include "LQ_Testbed.h"
#include "DataManageDlg.h"
#include "Excel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace myexcel;
/////////////////////////////////////////////////////////////////////////////
// CDataManageDlg dialog


CDataManageDlg::CDataManageDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDataManageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataManageDlg)
	m_bBackUp = FALSE;
	m_strSceneDescrible = _T("");
	nSearchSceneID= -1;
	nSearchScheduleID = -1;
	//}}AFX_DATA_INIT
}


void CDataManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataManageDlg)
	DDX_Control(pDX, IDC_COMBO_SCHEDULE, m_ctrlComboTestTime);
	DDX_Control(pDX, IDC_COMBO_SCENE, m_ctrlComboSceneName);
	DDX_Text(pDX, IDC_EDIT_SCENEDESCRIBLE, m_strSceneDescrible);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataManageDlg, CDialog)
//{{AFX_MSG_MAP(CDataManageDlg)
ON_BN_CLICKED(IDC_BTN_EXPORTTESTINFO, OnBtnExporttestinfo)
ON_BN_CLICKED(IDC_BTN_DELETEDATA, OnBtnDeleteData)
ON_BN_CLICKED(IDC_BTN_BACKUP, OnBtnBackUp)
ON_BN_CLICKED(IDC_BTN_RESTORE, OnBtnRestore)
	ON_BN_CLICKED(IDC_BTN_EXPORTSCENEINFO, OnBtnExportSceneinfo)
	ON_BN_CLICKED(IDC_BTN_EXPORTNODEINFO, OnBtnExportNodeinfo)
	ON_BN_CLICKED(IDC_BTN_EXPORTSCHEDULE, OnBtnExportSchedule)
	ON_BN_CLICKED(IDC_BTN_PACKETINFO, OnBtnPacketinfo)
	ON_CBN_SELCHANGE(IDC_COMBO_SCENE, OnSelchangeComboScene)
	ON_CBN_SELCHANGE(IDC_COMBO_SCHEDULE, OnSelchangeComboSchedule)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataManageDlg message handlers

void CDataManageDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CDataManageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    InitSceneNameCombo();
	InitScheduleTimeCombo();
	
	
	
	//////////////////////////////////////////////////////////////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDataManageDlg::InitSceneNameCombo()
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
		m_ctrlComboSceneName.SetWindowText("无");
	}
	else
	{
		while(!m_pRecordSet->adoEOF)
		{
	    	CString	str_SceneName = VariantToCString(m_pRecordSet->GetCollect("SceneName"));
			m_ctrlComboSceneName.AddString(str_SceneName);	
			
			m_pRecordSet->MoveNext();	
		}
	}
	
	if(nSearchSceneID!=-1) //当前场景
	{
		strSQL.Format("SELECT * FROM tb_SceneInfo WHERE SceneID=%d",nSearchSceneID);
		m_pRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
		if (!m_pRecordSet->adoEOF)
		{
			strSceneName = VariantToCString(m_pRecordSet->GetCollect("SceneName"));
			CString StrSceneDescribe = VariantToCString(m_pRecordSet->GetCollect("SceneDescribe"));
			m_ctrlComboSceneName.SetWindowText(strSceneName);
			InitScheduleTimeCombo();
		}
	}
	else
	{
		m_ctrlComboSceneName.SetWindowText("请选择要查看的历史场景");
	}
	UpdateData(FALSE);
}

void CDataManageDlg::InitScheduleTimeCombo()
{
	m_ctrlComboTestTime.ResetContent();
	
	ADOConn m_AdoConn;
	_RecordsetPtr m_pRecordSet;
	m_AdoConn.OnInitADOConn();
	
	CString strSQL;
	strSQL.Format("SELECT * FROM tb_TestSchedule WHERE SceneID=%d",nSearchSceneID);
	m_pRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
   	
	if (m_pRecordSet->adoEOF)
	{
		m_ctrlComboTestTime.SetWindowText("暂无测试数据");
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
	
	if(nSearchScheduleID!=-1) //当前测试
	{
		strSQL.Format("SELECT * FROM tb_TestSchedule WHERE ScheduleID=%d",nSearchScheduleID);
		m_pRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
		if (!m_pRecordSet->adoEOF)
		{
			strScheduleTime = VariantToCString(m_pRecordSet->GetCollect("StartTime"));
			m_ctrlComboTestTime.SetWindowText(VariantToCString(m_pRecordSet->GetCollect("StartTime")));

		}
	}
	else
	{
		m_ctrlComboTestTime.SetWindowText("请选择开始时间");
	}
	
	UpdateData(FALSE);
}


void CDataManageDlg::OnBtnExporttestinfo() 
{

	CString Field[12]={"计划编号","测试编号","节点编号","RSSI均值(下行)","LQI均值(下行)","SNR均值(下行)","RSSI均值(上行)","LQI均值(上行)","SNR均值(上行)","PRR","开始时间","结束时间",};//列的标题
	_Application exApp;//应用程序对象
	_Workbook exBook;//工作簿对象
	Workbooks exBooks;//工作簿集合对象
	Worksheets exSheets;//工作表集合
	_Worksheet exSheet;//工作表对象
	Range exRange;
	myexcel::Font exFont;//字体
	
	if(!exApp.CreateDispatch(_T("Excel.Application"))) 
	{
		AfxMessageBox(_T(" Excel failed to start!"));
		return;
	}
	VARIANT varOptional;//可选参数变量
	VariantInit(&varOptional);
	varOptional.vt=VT_ERROR;
	varOptional.scode=DISP_E_PARAMNOTFOUND;
	
	//添加工组簿和工作表
	exBooks=exApp.GetWorkbooks();
	exBook=exBooks.Add(varOptional);
	exSheets=exBook.GetWorksheets();
	exSheet=exSheets.Add(varOptional,varOptional,varOptional,varOptional);
	
	ADOConn m_AdoConn;
	_RecordsetPtr m_pTestRecordSet;
	m_AdoConn.OnInitADOConn();	

	CString strSQL;
	strSQL.Format("SELECT COUNT(*) AS TestCount FROM tb_TestInfo WHERE ScheduleID=%d",nSearchScheduleID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	int count = atoi(VariantToCString(m_pTestRecordSet->GetCollect("TestCount")));//记录总数
	
	strSQL.Format("SELECT * FROM tb_TestInfo WHERE ScheduleID=%d",nSearchScheduleID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	
	long nRows,nCols;//定义表的行和列
	nCols=12;
	nRows=count+1;
	
	long nstrLen;
	CString strField;
	VARIANT varCol;//用于设置列宽
	VariantInit(&varCol);
	varCol.vt=VT_R4;
	char cCol='A';//A列V
	CString strCol;
	for(int i=0;i<nCols;i++)
	{
		CString str=Field[i];
		nstrLen=str.GetLength();
		strCol=cCol;
		strCol=strCol+"1";
		exRange=exSheet.GetRange(COleVariant(strCol),varOptional);
		varCol.fltVal=(float)nstrLen+10;
		exRange.SetColumnWidth(varCol);
		cCol=cCol++;//从A列开始的每列
	}
	//获取单元格区间

	char chr;
	chr='A'+nCols-1;
	CString strCh=chr;
	strCh=strCh+"2";
	VARIANT varUnit;
	VariantInit(&varUnit);
	varUnit.vt=VT_I4;
	varUnit.lVal=15;
		
	exRange=exSheet.GetRange(COleVariant("A1"),COleVariant(strCh));
	exRange.Merge(varOptional);//合并单元格
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("黑体"));
	exFont.SetSize(varUnit);
	CString m_strTitle;
	m_strTitle.Format("WSN链路质量测试结果(%s/%s)",strSceneName,strScheduleTime);
	exRange.SetValue2(COleVariant(m_strTitle));//设置标题

	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//水平居中
	exRange.SetVerticalAlignment(varUnit);//垂直居中
	
	//创建安全数据，记录相关表格数据
	COleSafeArray sarry;
	DWORD ElementsNum[2];
	ElementsNum[0]=nRows;//行数
	ElementsNum[1]=nCols;//列数
	sarry.Create(VT_BSTR,2,ElementsNum);
	VARIANT varVal;//赋值变量
	long Index[2];
	CString strvalue;
	
	
	
	int k,l;
	for( k=0;k<nRows;k++)
	{
		if(k==0)//第一行
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;
				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=Field[l].AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//添加到数组中
				SysFreeString(varVal.bstrVal);
				VariantClear(&varVal);
			}
		}
		else
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;	
				switch (l)
				{
				case 0:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("ScheduleID")); 	break;
				case 1:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("TestID")); 	break;
				case 2:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("NodeID")); 	break;
				case 3:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("MeanRSSI_Down")); 	break;
				case 4:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("MeanLQI_Down")); 	break;
				case 5:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("MeanSNR_Down")); 	break;
				case 6:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("MeanRSSI_Up")); 	break;
				case 7:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("MeanLQI_Up")); 	break;
				case 8:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("MeanSNR_Up")); 	break;
				case 9:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("PRR")); 	break;
				case 10:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("StartTestTime")); 	break;
				case 11:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("EndTestTime")); 	break;
				}
				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=strvalue.AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//添加到数组中
				SysFreeString(varVal.bstrVal);//清空变量
				VariantClear(&varVal);
			}
			m_pTestRecordSet->MoveNext();
		}
	}
	strCh=chr;
	CString temp;
	temp.Format("%d",nRows+2);
	strCh=strCh+temp;
	
	exRange=exSheet.GetRange(COleVariant("A3"),COleVariant(strCh));
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("宋体"));
	varUnit.lVal=12;
	exFont.SetSize(varUnit);
	exRange.SetValue2(COleVariant(sarry));
	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//水平居中
	exRange.SetVerticalAlignment(varUnit);//垂直居中
//	exApp.SetVisible(true);//显示文档

	CString strFilePath;
	CString strFileName = "链路质量测试结果";
	CFileDialog FileDlg(false,NULL,strFileName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
		_T("Excel FILE(*.xls)|*.xls|*.xlsx||"),NULL);//第3个参数是指定文件名，第5个参数是文件类型下拉列表
    if(FileDlg.DoModal()==IDOK)
    {
        strFilePath = FileDlg.GetPathName();//得到文件完全路径，包括文件名和扩展名
		COleVariant varFilePath(strFilePath);		
		exBook.SaveAs(varFilePath,varOptional,varOptional,varOptional,varOptional,varOptional,0,varOptional,varOptional,varOptional,varOptional,varOptional);
		AfxMessageBox("数据导出成功!");
	}
	
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	exBook.SetSaved(TRUE);     // 将Workbook的保存状态设置为已保存，即不让系统提示是否人工保存
	exRange.ReleaseDispatch();    // 释放Range对象
	exSheet.ReleaseDispatch();    // 释放Sheet对象
	exSheets.ReleaseDispatch();    // 释放Sheets对象
	
	exBook.ReleaseDispatch();     // 释放Workbook对象
	exBooks.ReleaseDispatch();    // 释放Workbooks对象
	exBook.Close (covOptional, covOptional,covOptional);// 关闭Workbook对象
	exBooks.Close();           // 关闭Workbooks对象
	
	exApp.Quit();          // 退出_Application
	exApp.ReleaseDispatch ();       // 释放_Application
	
}


void CDataManageDlg::OnBtnDeleteData() 
{
	if(!m_bBackUp)
	{
		AfxMessageBox("操作前，请先备份数据库!");
		return;
	}

	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();	
    CString strSQL;
	
	try
	{
		//事件start
		m_AdoConn.m_pConnection->BeginTrans(); 
		
		//清空数据包表格
		strSQL="DELETE From tb_PacketInfo";
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);		
		strSQL ="ALTER TABLE[tb_PacketInfo] ALTER COLUMN [PacketID] counter(1,1)"; 
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
		
		//清空测试结果表
		strSQL="DELETE From tb_TestInfo";
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);	
		
		//清空测试计划表
		strSQL="DELETE From tb_TestSchedule";
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);		
		strSQL ="ALTER TABLE[tb_TestSchedule] ALTER COLUMN [ScheduleID] counter(1,1)"; 
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
		
		//测试节点表
		strSQL="DELETE From tb_NodeInfo";
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
		
		//清空场景表
		strSQL="DELETE From tb_SceneInfo";
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);		
		strSQL ="ALTER TABLE[tb_SceneInfo] ALTER COLUMN [SceneID] counter(1,1)"; 
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
		
		m_AdoConn.m_pConnection->CommitTrans(); //事件end	
		
		AfxMessageBox("数据库数据已清空！");
	}
	catch (_com_error e)
	{
		m_AdoConn.m_pConnection->RollbackTrans();//回滚事务
		AfxMessageBox(e.ErrorMessage());						
	}
	
}

void CDataManageDlg::OnBtnBackUp() 
{
	CString	m_strDstFile;
	
	char   lpPath[_MAX_PATH];   
	if(   GetModuleFileName(NULL,lpPath,_MAX_PATH)==0)   
	{  
		return ;   
	}

	CString m_strDatabaseFile;
	m_strDatabaseFile.Format("%s",lpPath);//当前文件全路径名。   
	m_strDatabaseFile= m_strDatabaseFile.Left( m_strDatabaseFile.ReverseFind('\\'));//去除文件名部分	
	m_strDatabaseFile+="\\LQ_Testbed.mdb";

	CString strfileName;
	CTime	nowtime = CTime::GetCurrentTime(); //当前时间		
    strfileName.Format("\\BackUp\\LQ_Testbed_%s%s.mdb",nowtime.Format(_T("%Y%m%d")), nowtime.Format(_T("%H%M%S")));
	
	m_strDstFile.Format("%s",lpPath);//当前文件全路径名。   
	m_strDstFile= m_strDstFile.Left( m_strDstFile.ReverseFind('\\'));//去除文件名部分	
	m_strDstFile+=strfileName;
	
	if (CopyFile(m_strDatabaseFile,m_strDstFile,FALSE))
    {
		AfxMessageBox("备份成功");
		m_bBackUp = TRUE;
    }
	else
	{
		AfxMessageBox("备份失败");
	}
	
}

void CDataManageDlg::OnBtnRestore() 
{
	if(!m_bBackUp)
	{
		AfxMessageBox("操作前，请先备份数据库!");
		return;
	}

	CString strFilePath;

	char   lpPath[_MAX_PATH];   
	if(   GetModuleFileName(NULL,lpPath,_MAX_PATH)==0)   
	{  
		return ;   
	}
	
	CString m_strDatabaseFile;
	m_strDatabaseFile.Format("%s",lpPath);//当前文件全路径名。   
	m_strDatabaseFile= m_strDatabaseFile.Left( m_strDatabaseFile.ReverseFind('\\'));//去除文件名部分	
	m_strDatabaseFile+="\\LQ_Testbed.mdb";


	CFileDialog FileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
		_T("ACCESS数据库文件(*.mdb)|*.mdb||"),NULL);//第3个参数是指定文件名，第5个参数是文件类型下拉列表

	if(FileDlg.DoModal()==IDOK)
	{
		strFilePath = FileDlg.GetPathName();//得到文件完全路径，包括文件名和扩展名
		
		if (CopyFile(strFilePath ,m_strDatabaseFile,FALSE))
		{
			AfxMessageBox("数据库还原成功");
			m_bBackUp = TRUE;
		}
		else
		{
			AfxMessageBox("数据库还原失败");
		}		
	}
}

/************************************************************************/
/* 导出场景信息                                                         */
/************************************************************************/
void CDataManageDlg::OnBtnExportSceneinfo() 
{

	CString Field[4]={"场景编号","场景名称","场景描述","部署时间"};//列的标题
	_Application exApp;//应用程序对象
	_Workbook exBook;//工作簿对象
	Workbooks exBooks;//工作簿集合对象
	Worksheets exSheets;//工作表集合
	_Worksheet exSheet;//工作表对象
	Range exRange;
	myexcel::Font exFont;//字体
	
	if(!exApp.CreateDispatch(_T("Excel.Application"))) 
	{
		AfxMessageBox(_T(" Excel failed to start!"));
		return;
	}
	VARIANT varOptional;//可选参数变量
	VariantInit(&varOptional);
	varOptional.vt=VT_ERROR;
	varOptional.scode=DISP_E_PARAMNOTFOUND;
	
	//添加工组簿和工作表
	exBooks=exApp.GetWorkbooks();
	exBook=exBooks.Add(varOptional);
	exSheets=exBook.GetWorksheets();
	exSheet=exSheets.Add(varOptional,varOptional,varOptional,varOptional);
	
	ADOConn m_AdoConn;
	_RecordsetPtr m_pTestRecordSet;
	m_AdoConn.OnInitADOConn();	

	CString strSQL;
	strSQL.Format("SELECT COUNT(*) AS SceneCount FROM tb_SceneInfo WHERE SceneID=%d",nSearchSceneID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	int count = atoi(VariantToCString(m_pTestRecordSet->GetCollect("SceneCount")));//记录总数
	
	strSQL.Format("SELECT * FROM tb_SceneInfo  WHERE SceneID=%d",nSearchSceneID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	
	long nRows,nCols;//定义表的行和列
	nCols=4;
	nRows=count+1;
	
	long nstrLen;
	CString strField;
	VARIANT varCol;//用于设置列宽
	VariantInit(&varCol);
	varCol.vt=VT_R4;
	char cCol='A';//A列V
	CString strCol;
	for(int i=0;i<nCols;i++)
	{
		CString str=Field[i];
		nstrLen=str.GetLength();
		strCol=cCol;
		strCol=strCol+"1";
		exRange=exSheet.GetRange(COleVariant(strCol),varOptional);
		varCol.fltVal=(float)nstrLen+10;
		exRange.SetColumnWidth(varCol);
		cCol=cCol++;//从A列开始的每列
	}
	//获取单元格区间

	char chr;
	chr='A'+nCols-1;
	CString strCh=chr;
	strCh=strCh+"2";
	VARIANT varUnit;
	VariantInit(&varUnit);
	varUnit.vt=VT_I4;
	varUnit.lVal=15;
		
	exRange=exSheet.GetRange(COleVariant("A1"),COleVariant(strCh));
	exRange.Merge(varOptional);//合并单元格
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("黑体"));
	exFont.SetSize(varUnit);
	CString m_strTitle;
	m_strTitle.Format("WSN链路质量测试场景设置(%s/%s)",strSceneName,strScheduleTime);

	exRange.SetValue2(COleVariant(m_strTitle));//设置标题

	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//水平居中
	exRange.SetVerticalAlignment(varUnit);//垂直居中
	
	//创建安全数据，记录相关表格数据
	COleSafeArray sarry;
	DWORD ElementsNum[2];
	ElementsNum[0]=nRows;//行数
	ElementsNum[1]=nCols;//列数
	sarry.Create(VT_BSTR,2,ElementsNum);
	VARIANT varVal;//赋值变量
	long Index[2];
	CString strvalue;
	
	
	
	int k,l;
	for( k=0;k<nRows;k++)
	{
		if(k==0)//第一行
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;
				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=Field[l].AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//添加到数组中
				SysFreeString(varVal.bstrVal);
				VariantClear(&varVal);
			}
		}
		else
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;	
				switch (l)
				{
				case 0:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("SceneID")); 	break;
				case 1:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("SceneName")); 	  break;
				case 2:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("SceneDescribe")); 	break;
				case 3:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("DeploymentTime")); 	break;			
				}
				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=strvalue.AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//添加到数组中
				SysFreeString(varVal.bstrVal);//清空变量
				VariantClear(&varVal);
			}
			m_pTestRecordSet->MoveNext();
		}
	}
	strCh=chr;
	CString temp;
	temp.Format("%d",nRows+2);
	strCh=strCh+temp;
	
	exRange=exSheet.GetRange(COleVariant("A3"),COleVariant(strCh));
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("宋体"));
	varUnit.lVal=12;
	exFont.SetSize(varUnit);
	exRange.SetValue2(COleVariant(sarry));
	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//水平居中
	exRange.SetVerticalAlignment(varUnit);//垂直居中

	CString strFilePath;
	CString strFileName = "链路质量测试场景设置";
	CFileDialog FileDlg(false,NULL,strFileName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
		_T("Excel FILE(*.xls)|*.xls|*.xlsx||"),NULL);//第3个参数是指定文件名，第5个参数是文件类型下拉列表
    if(FileDlg.DoModal()==IDOK)
    {
        strFilePath = FileDlg.GetPathName();//得到文件完全路径，包括文件名和扩展名
		COleVariant varFilePath(strFilePath);		
		exBook.SaveAs(varFilePath,varOptional,varOptional,varOptional,varOptional,varOptional,0,varOptional,varOptional,varOptional,varOptional,varOptional);
		AfxMessageBox("数据导出成功!");
	}
	
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	exBook.SetSaved(TRUE);     // 将Workbook的保存状态设置为已保存，即不让系统提示是否人工保存
	exRange.ReleaseDispatch();    // 释放Range对象
	exSheet.ReleaseDispatch();    // 释放Sheet对象
	exSheets.ReleaseDispatch();    // 释放Sheets对象
	
	exBook.ReleaseDispatch();     // 释放Workbook对象
	exBooks.ReleaseDispatch();    // 释放Workbooks对象
	exBook.Close (covOptional, covOptional,covOptional);// 关闭Workbook对象
	exBooks.Close();           // 关闭Workbooks对象
	
	exApp.Quit();          // 退出_Application
	exApp.ReleaseDispatch ();       // 释放_Application
	
}

/************************************************************************/
/* 节点信息                                                             */
/************************************************************************/
void CDataManageDlg::OnBtnExportNodeinfo() 
{

	CString Field[6]={"场景编号","节点号","功率","信道","方向","距离"};//列的标题
	_Application exApp;//应用程序对象
	_Workbook exBook;//工作簿对象
	Workbooks exBooks;//工作簿集合对象
	Worksheets exSheets;//工作表集合
	_Worksheet exSheet;//工作表对象
	Range exRange;
	myexcel::Font exFont;//字体
	
	if(!exApp.CreateDispatch(_T("Excel.Application"))) 
	{
		AfxMessageBox(_T(" Excel failed to start!"));
		return;
	}
	VARIANT varOptional;//可选参数变量
	VariantInit(&varOptional);
	varOptional.vt=VT_ERROR;
	varOptional.scode=DISP_E_PARAMNOTFOUND;
	
	//添加工组簿和工作表
	exBooks=exApp.GetWorkbooks();
	exBook=exBooks.Add(varOptional);
	exSheets=exBook.GetWorksheets();
	exSheet=exSheets.Add(varOptional,varOptional,varOptional,varOptional);
	
	ADOConn m_AdoConn;
	_RecordsetPtr m_pTestRecordSet;
	m_AdoConn.OnInitADOConn();	

	CString strSQL;
	strSQL.Format("SELECT COUNT(*) AS NodeCount FROM tb_NodeInfo WHERE SceneID=%d",nSearchSceneID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	int count = atoi(VariantToCString(m_pTestRecordSet->GetCollect("NodeCount")));//记录总数
	
	strSQL.Format("SELECT * FROM tb_NodeInfo WHERE SceneID=%d",nSearchSceneID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	
	long nRows,nCols;//定义表的行和列
	nCols=6;
	nRows=count+1;
	
	long nstrLen;
	CString strField;
	VARIANT varCol;//用于设置列宽
	VariantInit(&varCol);
	varCol.vt=VT_R4;
	char cCol='A';//A列V
	CString strCol;
	for(int i=0;i<nCols;i++)
	{
		CString str=Field[i];
		nstrLen=str.GetLength();
		strCol=cCol;
		strCol=strCol+"1";
		exRange=exSheet.GetRange(COleVariant(strCol),varOptional);
		varCol.fltVal=(float)nstrLen+10;
		exRange.SetColumnWidth(varCol);
		cCol=cCol++;//从A列开始的每列
	}
	//获取单元格区间

	char chr;
	chr='A'+nCols-1;
	CString strCh=chr;
	strCh=strCh+"2";
	VARIANT varUnit;
	VariantInit(&varUnit);
	varUnit.vt=VT_I4;
	varUnit.lVal=15;
		
	exRange=exSheet.GetRange(COleVariant("A1"),COleVariant(strCh));
	exRange.Merge(varOptional);//合并单元格
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("黑体"));
	exFont.SetSize(varUnit);
	CString m_strTitle;
	m_strTitle.Format("WSN链路质量节点信息(%s/%s)",strSceneName,strScheduleTime);
	exRange.SetValue2(COleVariant(m_strTitle));//设置标题

	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//水平居中
	exRange.SetVerticalAlignment(varUnit);//垂直居中
	
	//创建安全数据，记录相关表格数据
	COleSafeArray sarry;
	DWORD ElementsNum[2];
	ElementsNum[0]=nRows;//行数
	ElementsNum[1]=nCols;//列数
	sarry.Create(VT_BSTR,2,ElementsNum);
	VARIANT varVal;//赋值变量
	long Index[2];
	CString strvalue;
	
	
	
	int k,l;
	for( k=0;k<nRows;k++)
	{
		if(k==0)//第一行
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;
				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=Field[l].AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//添加到数组中
				SysFreeString(varVal.bstrVal);
				VariantClear(&varVal);
			}
		}
		else
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;	
				switch (l)
				{
				case 0:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("SceneID")); 	break;
				case 1:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("NodeID")); 	  break;
				case 2:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("Power")); 	break;
				case 3:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("Channel")); 	break;	
				case 4:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("Direction")); 	break;
				case 5:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("Distance")); 	break;
				}

				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=strvalue.AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//添加到数组中
				SysFreeString(varVal.bstrVal);//清空变量
				VariantClear(&varVal);
			}
			m_pTestRecordSet->MoveNext();
		}
	}
	strCh=chr;
	CString temp;
	temp.Format("%d",nRows+2);
	strCh=strCh+temp;
	
	exRange=exSheet.GetRange(COleVariant("A3"),COleVariant(strCh));
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("宋体"));
	varUnit.lVal=12;
	exFont.SetSize(varUnit);
	exRange.SetValue2(COleVariant(sarry));
	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//水平居中
	exRange.SetVerticalAlignment(varUnit);//垂直居中

	CString strFilePath;
	CString strFileName="链路质量测试节点信息";
	CFileDialog FileDlg(false,NULL,strFileName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
		_T("Excel FILE(*.xls)|*.xls|*.xlsx||"),NULL);//第3个参数是指定文件名，第5个参数是文件类型下拉列表
    if(FileDlg.DoModal()==IDOK)
    {
        strFilePath = FileDlg.GetPathName();//得到文件完全路径，包括文件名和扩展名
		COleVariant varFilePath(strFilePath);		
		exBook.SaveAs(varFilePath,varOptional,varOptional,varOptional,varOptional,varOptional,0,varOptional,varOptional,varOptional,varOptional,varOptional);
		AfxMessageBox("数据导出成功!");
	}
	
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	exBook.SetSaved(TRUE);     // 将Workbook的保存状态设置为已保存，即不让系统提示是否人工保存
	exRange.ReleaseDispatch();    // 释放Range对象
	exSheet.ReleaseDispatch();    // 释放Sheet对象
	exSheets.ReleaseDispatch();    // 释放Sheets对象
	
	exBook.ReleaseDispatch();     // 释放Workbook对象
	exBooks.ReleaseDispatch();    // 释放Workbooks对象
	exBook.Close (covOptional, covOptional,covOptional);// 关闭Workbook对象
	exBooks.Close();           // 关闭Workbooks对象
	
	exApp.Quit();          // 退出_Application
	exApp.ReleaseDispatch ();       // 释放_Application
}


/************************************************************************/
/* 导出测试计划                                                         */
/************************************************************************/
void CDataManageDlg::OnBtnExportSchedule() 
{
 	CString Field[8]={"计划编号","场景变换","开始时间","结束时间","探测包数","发送周期","测试周期","探测方式"}; //列的标题
	_Application exApp;//应用程序对象
	_Workbook exBook;//工作簿对象
	Workbooks exBooks;//工作簿集合对象
	Worksheets exSheets;//工作表集合
	_Worksheet exSheet;//工作表对象
	Range exRange;
	myexcel::Font exFont;//字体
	
	if(!exApp.CreateDispatch(_T("Excel.Application"))) 
	{
		AfxMessageBox(_T(" Excel failed to start!"));
		return;
	}
	VARIANT varOptional;//可选参数变量
	VariantInit(&varOptional);
	varOptional.vt=VT_ERROR;
	varOptional.scode=DISP_E_PARAMNOTFOUND;
	
	//添加工组簿和工作表
	exBooks=exApp.GetWorkbooks();
	exBook=exBooks.Add(varOptional);
	exSheets=exBook.GetWorksheets();
	exSheet=exSheets.Add(varOptional,varOptional,varOptional,varOptional);
	
	ADOConn m_AdoConn;
	_RecordsetPtr m_pTestRecordSet;
	m_AdoConn.OnInitADOConn();	

	CString strSQL;
	strSQL.Format("SELECT COUNT(*) AS ScheduleCount FROM tb_TestSchedule WHERE ScheduleID=%d", nSearchScheduleID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	int count = atoi(VariantToCString(m_pTestRecordSet->GetCollect("ScheduleCount")));//记录总数
	
	strSQL.Format("SELECT * FROM tb_TestSchedule WHERE ScheduleID=%d", nSearchScheduleID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	
	long nRows,nCols;//定义表的行和列
	nCols=8;
	nRows=count+1;
	
	long nstrLen;
	CString strField;
	VARIANT varCol;//用于设置列宽
	VariantInit(&varCol);
	varCol.vt=VT_R4;
	char cCol='A';//A列V
	CString strCol;
	for(int i=0;i<nCols;i++)
	{
		CString str=Field[i];
		nstrLen=str.GetLength();
		strCol=cCol;
		strCol=strCol+"1";
		exRange=exSheet.GetRange(COleVariant(strCol),varOptional);
		varCol.fltVal=(float)nstrLen+10;
		exRange.SetColumnWidth(varCol);
		cCol=cCol++;//从A列开始的每列
	}
	//获取单元格区间

	char chr;
	chr='A'+nCols-1;
	CString strCh=chr;
	strCh=strCh+"2";
	VARIANT varUnit;
	VariantInit(&varUnit);
	varUnit.vt=VT_I4;
	varUnit.lVal=15;
		
	exRange=exSheet.GetRange(COleVariant("A1"),COleVariant(strCh));
	exRange.Merge(varOptional);//合并单元格
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("黑体"));
	exFont.SetSize(varUnit);
	CString m_strTitle;
	m_strTitle.Format("WSN链路质量测试计划表(%s/%s)",strSceneName,strScheduleTime);
	exRange.SetValue2(COleVariant(m_strTitle));//设置标题

	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//水平居中
	exRange.SetVerticalAlignment(varUnit);//垂直居中
	
	//创建安全数据，记录相关表格数据
	COleSafeArray sarry;
	DWORD ElementsNum[2];
	ElementsNum[0]=nRows;//行数
	ElementsNum[1]=nCols;//列数
	sarry.Create(VT_BSTR,2,ElementsNum);
	VARIANT varVal;//赋值变量
	long Index[2];
	CString strvalue;
	
	
	
	int k,l;
	for( k=0;k<nRows;k++)
	{
		if(k==0)//第一行
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;
				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=Field[l].AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//添加到数组中
				SysFreeString(varVal.bstrVal);
				VariantClear(&varVal);
			}
		}
		else
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;	
				switch (l)
				{
				case 0:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("ScheduleID")); 	  break;
				case 1:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("SceneID")); 	break;
				case 2:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("StartTime")); 	break;
				case 3:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("EndTime")); 	break;	
				case 4:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("TestPackets")); 	break;
				case 5:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("SendPeriod")); 	break;
				case 6:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("TestPeriod"));     break;			
				case 7:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("TestMode")); 	break;	
				}

				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=strvalue.AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//添加到数组中
				SysFreeString(varVal.bstrVal);//清空变量
				VariantClear(&varVal);
			}
			m_pTestRecordSet->MoveNext();
		}
	}
	strCh=chr;
	CString temp;
	temp.Format("%d",nRows+2);
	strCh=strCh+temp;
	
	exRange=exSheet.GetRange(COleVariant("A3"),COleVariant(strCh));
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("宋体"));
	varUnit.lVal=12;
	exFont.SetSize(varUnit);
	exRange.SetValue2(COleVariant(sarry));
	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//水平居中
	exRange.SetVerticalAlignment(varUnit);//垂直居中

	CString strFilePath;
	CString strFileName = "链路质量测试测试计划";
	CFileDialog FileDlg(false,NULL,strFileName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
		_T("Excel FILE(*.xls)|*.xls|*.xlsx||"),NULL);//第3个参数是指定文件名，第5个参数是文件类型下拉列表
    if(FileDlg.DoModal()==IDOK)
    {
        strFilePath = FileDlg.GetPathName();//得到文件完全路径，包括文件名和扩展名
		COleVariant varFilePath(strFilePath);		
		exBook.SaveAs(varFilePath,varOptional,varOptional,varOptional,varOptional,varOptional,0,varOptional,varOptional,varOptional,varOptional,varOptional);
		AfxMessageBox("数据导出成功!");
	}
	
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	exBook.SetSaved(TRUE);     // 将Workbook的保存状态设置为已保存，即不让系统提示是否人工保存
	exRange.ReleaseDispatch();    // 释放Range对象
	exSheet.ReleaseDispatch();    // 释放Sheet对象
	exSheets.ReleaseDispatch();    // 释放Sheets对象
	
	exBook.ReleaseDispatch();     // 释放Workbook对象
	exBooks.ReleaseDispatch();    // 释放Workbooks对象
	exBook.Close (covOptional, covOptional,covOptional);// 关闭Workbook对象
	exBooks.Close();           // 关闭Workbooks对象
	
	exApp.Quit();          // 退出_Application
	exApp.ReleaseDispatch ();       // 释放_Application
}

/************************************************************************/
/* 导出数据包信息                                                       */
/************************************************************************/
void CDataManageDlg::OnBtnPacketinfo() 
{
	CString Field[12]={"测试计划","测试编号","节点号","消息序列","RSSI(下)","LQI(下)","SNR(下)","RSSI(上)","LQI(上)","SNR(上)","消息总数","上报时间"};//列的标题
	_Application exApp;//应用程序对象
	_Workbook exBook;//工作簿对象
	Workbooks exBooks;//工作簿集合对象
	Worksheets exSheets;//工作表集合
	_Worksheet exSheet;//工作表对象
	Range exRange;
	myexcel::Font exFont;//字体
	
	if(!exApp.CreateDispatch(_T("Excel.Application"))) 
	{
		AfxMessageBox(_T(" Excel failed to start!"));
		return;
	}
	VARIANT varOptional;//可选参数变量
	VariantInit(&varOptional);
	varOptional.vt=VT_ERROR;
	varOptional.scode=DISP_E_PARAMNOTFOUND;
	
	//添加工组簿和工作表
	exBooks=exApp.GetWorkbooks();
	exBook=exBooks.Add(varOptional);
	exSheets=exBook.GetWorksheets();
	exSheet=exSheets.Add(varOptional,varOptional,varOptional,varOptional);
	
	ADOConn m_AdoConn;
	_RecordsetPtr m_pTestRecordSet;
	m_AdoConn.OnInitADOConn();	

	CString strSQL;
	strSQL.Format("SELECT COUNT(*) AS PacketCount FROM tb_PacketInfo WHERE ScheduleID=%d",nSearchScheduleID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	int count = atoi(VariantToCString(m_pTestRecordSet->GetCollect("PacketCount")));//记录总数
	
	strSQL.Format("SELECT * FROM tb_PacketInfo WHERE ScheduleID=%d", nSearchScheduleID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	
	long nRows,nCols;//定义表的行和列
	nCols=12;
	nRows=count+1;
	
	long nstrLen;
	CString strField;
	VARIANT varCol;//用于设置列宽
	VariantInit(&varCol);
	varCol.vt=VT_R4;
	char cCol='A';//A列V
	CString strCol;
	for(int i=0;i<nCols;i++)
	{
		CString str=Field[i];
		nstrLen=str.GetLength();
		strCol=cCol;
		strCol=strCol+"1";
		exRange=exSheet.GetRange(COleVariant(strCol),varOptional);
		varCol.fltVal=(float)nstrLen+10;
		exRange.SetColumnWidth(varCol);
		cCol=cCol++;//从A列开始的每列
	}
	//获取单元格区间

	char chr;
	chr='A'+nCols-1;
	CString strCh=chr;
	strCh=strCh+"2";
	VARIANT varUnit;
	VariantInit(&varUnit);
	varUnit.vt=VT_I4;
	varUnit.lVal=15;
		
	exRange=exSheet.GetRange(COleVariant("A1"),COleVariant(strCh));
	exRange.Merge(varOptional);//合并单元格
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("黑体"));
	exFont.SetSize(varUnit);
	CString m_strTitle;
	m_strTitle.Format("WSN链路质量数据包(%s/%s)",strSceneName,strScheduleTime);

	exRange.SetValue2(COleVariant(m_strTitle));//设置标题

	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//水平居中
	exRange.SetVerticalAlignment(varUnit);//垂直居中
	
	//创建安全数据，记录相关表格数据
	COleSafeArray sarry;
	DWORD ElementsNum[2];
	ElementsNum[0]=nRows;//行数
	ElementsNum[1]=nCols;//列数
	sarry.Create(VT_BSTR,2,ElementsNum);
	VARIANT varVal;//赋值变量
	long Index[2];
	CString strvalue;
	
	int k,l;
	for( k=0;k<nRows;k++)
	{
		if(k==0)//第一行
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;
				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=Field[l].AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//添加到数组中
				SysFreeString(varVal.bstrVal);
				VariantClear(&varVal);
			}
		}
		else
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;	
				switch (l)
				{
				case 0:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("ScheduleID")); 	break;
				case 1:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("TestID")); 	break;
				case 2:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("NodeID")); 	  break;
				case 3:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("MsgSeq")); 	break;	
				case 4:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("RSSI_Down")); 	break;
				case 5:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("LQI_Down")); 	break;
				case 6:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("SNR_Down")); 	break;
				case 7:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("RSSI_Up")); 	break;
				case 8:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("LQI_Up")); 	break;
				case 9:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("SNR_Up")); 	break;
				case 10:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("MsgSum")); 	break;
				case 11:
					strvalue= VariantToCString(m_pTestRecordSet->GetCollect("ReportTime")); 	break;
				
				}

				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=strvalue.AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//添加到数组中
				SysFreeString(varVal.bstrVal);//清空变量
				VariantClear(&varVal);
			}
			m_pTestRecordSet->MoveNext();
		}
	}
	strCh=chr;
	CString temp;
	temp.Format("%d",nRows+2);
	strCh=strCh+temp;
	
	exRange=exSheet.GetRange(COleVariant("A3"),COleVariant(strCh));
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("宋体"));
	varUnit.lVal=12;
	exFont.SetSize(varUnit);
	exRange.SetValue2(COleVariant(sarry));
	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//水平居中
	exRange.SetVerticalAlignment(varUnit);//垂直居中

	CString strFilePath;
	CString strFileName = "链路质量测试数据包详情信息";
	CFileDialog FileDlg(false,NULL,strFileName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
		_T("Excel FILE(*.xls)|*.xls|*.xlsx||"),NULL);//第3个参数是指定文件名，第5个参数是文件类型下拉列表
    if(FileDlg.DoModal()==IDOK)
    {
        strFilePath = FileDlg.GetPathName();//得到文件完全路径，包括文件名和扩展名
		COleVariant varFilePath(strFilePath);		
		exBook.SaveAs(varFilePath,varOptional,varOptional,varOptional,varOptional,varOptional,0,varOptional,varOptional,varOptional,varOptional,varOptional);
		AfxMessageBox("数据导出成功!");
	}
	
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	exBook.SetSaved(TRUE);     // 将Workbook的保存状态设置为已保存，即不让系统提示是否人工保存
	exRange.ReleaseDispatch();    // 释放Range对象
	exSheet.ReleaseDispatch();    // 释放Sheet对象
	exSheets.ReleaseDispatch();    // 释放Sheets对象
	
	exBook.ReleaseDispatch();     // 释放Workbook对象
	exBooks.ReleaseDispatch();    // 释放Workbooks对象
	exBook.Close (covOptional, covOptional,covOptional);// 关闭Workbook对象
	exBooks.Close();           // 关闭Workbooks对象
	
	exApp.Quit();          // 退出_Application
	exApp.ReleaseDispatch ();       // 释放_Application
}

void CDataManageDlg::OnSelchangeComboScene() 
{
	UpdateData(TRUE);

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
		m_strSceneDescrible = VariantToCString(m_pRecordSet->GetCollect("SceneDescribe"));
		
		InitScheduleTimeCombo();
	}
	
    UpdateData(FALSE);
}

void CDataManageDlg::OnSelchangeComboSchedule() 
{
	UpdateData(TRUE);
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
		
	}

    UpdateData(FALSE);
}
