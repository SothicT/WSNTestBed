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
		m_ctrlComboSceneName.SetWindowText("��");
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
	
	if(nSearchSceneID!=-1) //��ǰ����
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
		m_ctrlComboSceneName.SetWindowText("��ѡ��Ҫ�鿴����ʷ����");
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
		if (!m_pRecordSet->adoEOF)
		{
			strScheduleTime = VariantToCString(m_pRecordSet->GetCollect("StartTime"));
			m_ctrlComboTestTime.SetWindowText(VariantToCString(m_pRecordSet->GetCollect("StartTime")));

		}
	}
	else
	{
		m_ctrlComboTestTime.SetWindowText("��ѡ��ʼʱ��");
	}
	
	UpdateData(FALSE);
}


void CDataManageDlg::OnBtnExporttestinfo() 
{

	CString Field[12]={"�ƻ����","���Ա��","�ڵ���","RSSI��ֵ(����)","LQI��ֵ(����)","SNR��ֵ(����)","RSSI��ֵ(����)","LQI��ֵ(����)","SNR��ֵ(����)","PRR","��ʼʱ��","����ʱ��",};//�еı���
	_Application exApp;//Ӧ�ó������
	_Workbook exBook;//����������
	Workbooks exBooks;//���������϶���
	Worksheets exSheets;//��������
	_Worksheet exSheet;//���������
	Range exRange;
	myexcel::Font exFont;//����
	
	if(!exApp.CreateDispatch(_T("Excel.Application"))) 
	{
		AfxMessageBox(_T(" Excel failed to start!"));
		return;
	}
	VARIANT varOptional;//��ѡ��������
	VariantInit(&varOptional);
	varOptional.vt=VT_ERROR;
	varOptional.scode=DISP_E_PARAMNOTFOUND;
	
	//��ӹ��鲾�͹�����
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
	int count = atoi(VariantToCString(m_pTestRecordSet->GetCollect("TestCount")));//��¼����
	
	strSQL.Format("SELECT * FROM tb_TestInfo WHERE ScheduleID=%d",nSearchScheduleID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	
	long nRows,nCols;//�������к���
	nCols=12;
	nRows=count+1;
	
	long nstrLen;
	CString strField;
	VARIANT varCol;//���������п�
	VariantInit(&varCol);
	varCol.vt=VT_R4;
	char cCol='A';//A��V
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
		cCol=cCol++;//��A�п�ʼ��ÿ��
	}
	//��ȡ��Ԫ������

	char chr;
	chr='A'+nCols-1;
	CString strCh=chr;
	strCh=strCh+"2";
	VARIANT varUnit;
	VariantInit(&varUnit);
	varUnit.vt=VT_I4;
	varUnit.lVal=15;
		
	exRange=exSheet.GetRange(COleVariant("A1"),COleVariant(strCh));
	exRange.Merge(varOptional);//�ϲ���Ԫ��
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("����"));
	exFont.SetSize(varUnit);
	CString m_strTitle;
	m_strTitle.Format("WSN��·�������Խ��(%s/%s)",strSceneName,strScheduleTime);
	exRange.SetValue2(COleVariant(m_strTitle));//���ñ���

	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//ˮƽ����
	exRange.SetVerticalAlignment(varUnit);//��ֱ����
	
	//������ȫ���ݣ���¼��ر������
	COleSafeArray sarry;
	DWORD ElementsNum[2];
	ElementsNum[0]=nRows;//����
	ElementsNum[1]=nCols;//����
	sarry.Create(VT_BSTR,2,ElementsNum);
	VARIANT varVal;//��ֵ����
	long Index[2];
	CString strvalue;
	
	
	
	int k,l;
	for( k=0;k<nRows;k++)
	{
		if(k==0)//��һ��
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;
				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=Field[l].AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//��ӵ�������
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
				sarry.PutElement(Index,varVal.bstrVal);//��ӵ�������
				SysFreeString(varVal.bstrVal);//��ձ���
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
	exFont.SetName(COleVariant("����"));
	varUnit.lVal=12;
	exFont.SetSize(varUnit);
	exRange.SetValue2(COleVariant(sarry));
	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//ˮƽ����
	exRange.SetVerticalAlignment(varUnit);//��ֱ����
//	exApp.SetVisible(true);//��ʾ�ĵ�

	CString strFilePath;
	CString strFileName = "��·�������Խ��";
	CFileDialog FileDlg(false,NULL,strFileName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
		_T("Excel FILE(*.xls)|*.xls|*.xlsx||"),NULL);//��3��������ָ���ļ�������5���������ļ����������б�
    if(FileDlg.DoModal()==IDOK)
    {
        strFilePath = FileDlg.GetPathName();//�õ��ļ���ȫ·���������ļ�������չ��
		COleVariant varFilePath(strFilePath);		
		exBook.SaveAs(varFilePath,varOptional,varOptional,varOptional,varOptional,varOptional,0,varOptional,varOptional,varOptional,varOptional,varOptional);
		AfxMessageBox("���ݵ����ɹ�!");
	}
	
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	exBook.SetSaved(TRUE);     // ��Workbook�ı���״̬����Ϊ�ѱ��棬������ϵͳ��ʾ�Ƿ��˹�����
	exRange.ReleaseDispatch();    // �ͷ�Range����
	exSheet.ReleaseDispatch();    // �ͷ�Sheet����
	exSheets.ReleaseDispatch();    // �ͷ�Sheets����
	
	exBook.ReleaseDispatch();     // �ͷ�Workbook����
	exBooks.ReleaseDispatch();    // �ͷ�Workbooks����
	exBook.Close (covOptional, covOptional,covOptional);// �ر�Workbook����
	exBooks.Close();           // �ر�Workbooks����
	
	exApp.Quit();          // �˳�_Application
	exApp.ReleaseDispatch ();       // �ͷ�_Application
	
}


void CDataManageDlg::OnBtnDeleteData() 
{
	if(!m_bBackUp)
	{
		AfxMessageBox("����ǰ�����ȱ������ݿ�!");
		return;
	}

	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();	
    CString strSQL;
	
	try
	{
		//�¼�start
		m_AdoConn.m_pConnection->BeginTrans(); 
		
		//������ݰ����
		strSQL="DELETE From tb_PacketInfo";
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);		
		strSQL ="ALTER TABLE[tb_PacketInfo] ALTER COLUMN [PacketID] counter(1,1)"; 
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
		
		//��ղ��Խ����
		strSQL="DELETE From tb_TestInfo";
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);	
		
		//��ղ��Լƻ���
		strSQL="DELETE From tb_TestSchedule";
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);		
		strSQL ="ALTER TABLE[tb_TestSchedule] ALTER COLUMN [ScheduleID] counter(1,1)"; 
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
		
		//���Խڵ��
		strSQL="DELETE From tb_NodeInfo";
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
		
		//��ճ�����
		strSQL="DELETE From tb_SceneInfo";
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);		
		strSQL ="ALTER TABLE[tb_SceneInfo] ALTER COLUMN [SceneID] counter(1,1)"; 
		m_AdoConn.ExecuteSQL((_bstr_t)strSQL);
		
		m_AdoConn.m_pConnection->CommitTrans(); //�¼�end	
		
		AfxMessageBox("���ݿ���������գ�");
	}
	catch (_com_error e)
	{
		m_AdoConn.m_pConnection->RollbackTrans();//�ع�����
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
	m_strDatabaseFile.Format("%s",lpPath);//��ǰ�ļ�ȫ·������   
	m_strDatabaseFile= m_strDatabaseFile.Left( m_strDatabaseFile.ReverseFind('\\'));//ȥ���ļ�������	
	m_strDatabaseFile+="\\LQ_Testbed.mdb";

	CString strfileName;
	CTime	nowtime = CTime::GetCurrentTime(); //��ǰʱ��		
    strfileName.Format("\\BackUp\\LQ_Testbed_%s%s.mdb",nowtime.Format(_T("%Y%m%d")), nowtime.Format(_T("%H%M%S")));
	
	m_strDstFile.Format("%s",lpPath);//��ǰ�ļ�ȫ·������   
	m_strDstFile= m_strDstFile.Left( m_strDstFile.ReverseFind('\\'));//ȥ���ļ�������	
	m_strDstFile+=strfileName;
	
	if (CopyFile(m_strDatabaseFile,m_strDstFile,FALSE))
    {
		AfxMessageBox("���ݳɹ�");
		m_bBackUp = TRUE;
    }
	else
	{
		AfxMessageBox("����ʧ��");
	}
	
}

void CDataManageDlg::OnBtnRestore() 
{
	if(!m_bBackUp)
	{
		AfxMessageBox("����ǰ�����ȱ������ݿ�!");
		return;
	}

	CString strFilePath;

	char   lpPath[_MAX_PATH];   
	if(   GetModuleFileName(NULL,lpPath,_MAX_PATH)==0)   
	{  
		return ;   
	}
	
	CString m_strDatabaseFile;
	m_strDatabaseFile.Format("%s",lpPath);//��ǰ�ļ�ȫ·������   
	m_strDatabaseFile= m_strDatabaseFile.Left( m_strDatabaseFile.ReverseFind('\\'));//ȥ���ļ�������	
	m_strDatabaseFile+="\\LQ_Testbed.mdb";


	CFileDialog FileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
		_T("ACCESS���ݿ��ļ�(*.mdb)|*.mdb||"),NULL);//��3��������ָ���ļ�������5���������ļ����������б�

	if(FileDlg.DoModal()==IDOK)
	{
		strFilePath = FileDlg.GetPathName();//�õ��ļ���ȫ·���������ļ�������չ��
		
		if (CopyFile(strFilePath ,m_strDatabaseFile,FALSE))
		{
			AfxMessageBox("���ݿ⻹ԭ�ɹ�");
			m_bBackUp = TRUE;
		}
		else
		{
			AfxMessageBox("���ݿ⻹ԭʧ��");
		}		
	}
}

/************************************************************************/
/* ����������Ϣ                                                         */
/************************************************************************/
void CDataManageDlg::OnBtnExportSceneinfo() 
{

	CString Field[4]={"�������","��������","��������","����ʱ��"};//�еı���
	_Application exApp;//Ӧ�ó������
	_Workbook exBook;//����������
	Workbooks exBooks;//���������϶���
	Worksheets exSheets;//��������
	_Worksheet exSheet;//���������
	Range exRange;
	myexcel::Font exFont;//����
	
	if(!exApp.CreateDispatch(_T("Excel.Application"))) 
	{
		AfxMessageBox(_T(" Excel failed to start!"));
		return;
	}
	VARIANT varOptional;//��ѡ��������
	VariantInit(&varOptional);
	varOptional.vt=VT_ERROR;
	varOptional.scode=DISP_E_PARAMNOTFOUND;
	
	//��ӹ��鲾�͹�����
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
	int count = atoi(VariantToCString(m_pTestRecordSet->GetCollect("SceneCount")));//��¼����
	
	strSQL.Format("SELECT * FROM tb_SceneInfo  WHERE SceneID=%d",nSearchSceneID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	
	long nRows,nCols;//�������к���
	nCols=4;
	nRows=count+1;
	
	long nstrLen;
	CString strField;
	VARIANT varCol;//���������п�
	VariantInit(&varCol);
	varCol.vt=VT_R4;
	char cCol='A';//A��V
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
		cCol=cCol++;//��A�п�ʼ��ÿ��
	}
	//��ȡ��Ԫ������

	char chr;
	chr='A'+nCols-1;
	CString strCh=chr;
	strCh=strCh+"2";
	VARIANT varUnit;
	VariantInit(&varUnit);
	varUnit.vt=VT_I4;
	varUnit.lVal=15;
		
	exRange=exSheet.GetRange(COleVariant("A1"),COleVariant(strCh));
	exRange.Merge(varOptional);//�ϲ���Ԫ��
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("����"));
	exFont.SetSize(varUnit);
	CString m_strTitle;
	m_strTitle.Format("WSN��·�������Գ�������(%s/%s)",strSceneName,strScheduleTime);

	exRange.SetValue2(COleVariant(m_strTitle));//���ñ���

	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//ˮƽ����
	exRange.SetVerticalAlignment(varUnit);//��ֱ����
	
	//������ȫ���ݣ���¼��ر������
	COleSafeArray sarry;
	DWORD ElementsNum[2];
	ElementsNum[0]=nRows;//����
	ElementsNum[1]=nCols;//����
	sarry.Create(VT_BSTR,2,ElementsNum);
	VARIANT varVal;//��ֵ����
	long Index[2];
	CString strvalue;
	
	
	
	int k,l;
	for( k=0;k<nRows;k++)
	{
		if(k==0)//��һ��
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;
				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=Field[l].AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//��ӵ�������
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
				sarry.PutElement(Index,varVal.bstrVal);//��ӵ�������
				SysFreeString(varVal.bstrVal);//��ձ���
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
	exFont.SetName(COleVariant("����"));
	varUnit.lVal=12;
	exFont.SetSize(varUnit);
	exRange.SetValue2(COleVariant(sarry));
	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//ˮƽ����
	exRange.SetVerticalAlignment(varUnit);//��ֱ����

	CString strFilePath;
	CString strFileName = "��·�������Գ�������";
	CFileDialog FileDlg(false,NULL,strFileName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
		_T("Excel FILE(*.xls)|*.xls|*.xlsx||"),NULL);//��3��������ָ���ļ�������5���������ļ����������б�
    if(FileDlg.DoModal()==IDOK)
    {
        strFilePath = FileDlg.GetPathName();//�õ��ļ���ȫ·���������ļ�������չ��
		COleVariant varFilePath(strFilePath);		
		exBook.SaveAs(varFilePath,varOptional,varOptional,varOptional,varOptional,varOptional,0,varOptional,varOptional,varOptional,varOptional,varOptional);
		AfxMessageBox("���ݵ����ɹ�!");
	}
	
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	exBook.SetSaved(TRUE);     // ��Workbook�ı���״̬����Ϊ�ѱ��棬������ϵͳ��ʾ�Ƿ��˹�����
	exRange.ReleaseDispatch();    // �ͷ�Range����
	exSheet.ReleaseDispatch();    // �ͷ�Sheet����
	exSheets.ReleaseDispatch();    // �ͷ�Sheets����
	
	exBook.ReleaseDispatch();     // �ͷ�Workbook����
	exBooks.ReleaseDispatch();    // �ͷ�Workbooks����
	exBook.Close (covOptional, covOptional,covOptional);// �ر�Workbook����
	exBooks.Close();           // �ر�Workbooks����
	
	exApp.Quit();          // �˳�_Application
	exApp.ReleaseDispatch ();       // �ͷ�_Application
	
}

/************************************************************************/
/* �ڵ���Ϣ                                                             */
/************************************************************************/
void CDataManageDlg::OnBtnExportNodeinfo() 
{

	CString Field[6]={"�������","�ڵ��","����","�ŵ�","����","����"};//�еı���
	_Application exApp;//Ӧ�ó������
	_Workbook exBook;//����������
	Workbooks exBooks;//���������϶���
	Worksheets exSheets;//��������
	_Worksheet exSheet;//���������
	Range exRange;
	myexcel::Font exFont;//����
	
	if(!exApp.CreateDispatch(_T("Excel.Application"))) 
	{
		AfxMessageBox(_T(" Excel failed to start!"));
		return;
	}
	VARIANT varOptional;//��ѡ��������
	VariantInit(&varOptional);
	varOptional.vt=VT_ERROR;
	varOptional.scode=DISP_E_PARAMNOTFOUND;
	
	//��ӹ��鲾�͹�����
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
	int count = atoi(VariantToCString(m_pTestRecordSet->GetCollect("NodeCount")));//��¼����
	
	strSQL.Format("SELECT * FROM tb_NodeInfo WHERE SceneID=%d",nSearchSceneID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	
	long nRows,nCols;//�������к���
	nCols=6;
	nRows=count+1;
	
	long nstrLen;
	CString strField;
	VARIANT varCol;//���������п�
	VariantInit(&varCol);
	varCol.vt=VT_R4;
	char cCol='A';//A��V
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
		cCol=cCol++;//��A�п�ʼ��ÿ��
	}
	//��ȡ��Ԫ������

	char chr;
	chr='A'+nCols-1;
	CString strCh=chr;
	strCh=strCh+"2";
	VARIANT varUnit;
	VariantInit(&varUnit);
	varUnit.vt=VT_I4;
	varUnit.lVal=15;
		
	exRange=exSheet.GetRange(COleVariant("A1"),COleVariant(strCh));
	exRange.Merge(varOptional);//�ϲ���Ԫ��
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("����"));
	exFont.SetSize(varUnit);
	CString m_strTitle;
	m_strTitle.Format("WSN��·�����ڵ���Ϣ(%s/%s)",strSceneName,strScheduleTime);
	exRange.SetValue2(COleVariant(m_strTitle));//���ñ���

	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//ˮƽ����
	exRange.SetVerticalAlignment(varUnit);//��ֱ����
	
	//������ȫ���ݣ���¼��ر������
	COleSafeArray sarry;
	DWORD ElementsNum[2];
	ElementsNum[0]=nRows;//����
	ElementsNum[1]=nCols;//����
	sarry.Create(VT_BSTR,2,ElementsNum);
	VARIANT varVal;//��ֵ����
	long Index[2];
	CString strvalue;
	
	
	
	int k,l;
	for( k=0;k<nRows;k++)
	{
		if(k==0)//��һ��
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;
				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=Field[l].AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//��ӵ�������
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
				sarry.PutElement(Index,varVal.bstrVal);//��ӵ�������
				SysFreeString(varVal.bstrVal);//��ձ���
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
	exFont.SetName(COleVariant("����"));
	varUnit.lVal=12;
	exFont.SetSize(varUnit);
	exRange.SetValue2(COleVariant(sarry));
	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//ˮƽ����
	exRange.SetVerticalAlignment(varUnit);//��ֱ����

	CString strFilePath;
	CString strFileName="��·�������Խڵ���Ϣ";
	CFileDialog FileDlg(false,NULL,strFileName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
		_T("Excel FILE(*.xls)|*.xls|*.xlsx||"),NULL);//��3��������ָ���ļ�������5���������ļ����������б�
    if(FileDlg.DoModal()==IDOK)
    {
        strFilePath = FileDlg.GetPathName();//�õ��ļ���ȫ·���������ļ�������չ��
		COleVariant varFilePath(strFilePath);		
		exBook.SaveAs(varFilePath,varOptional,varOptional,varOptional,varOptional,varOptional,0,varOptional,varOptional,varOptional,varOptional,varOptional);
		AfxMessageBox("���ݵ����ɹ�!");
	}
	
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	exBook.SetSaved(TRUE);     // ��Workbook�ı���״̬����Ϊ�ѱ��棬������ϵͳ��ʾ�Ƿ��˹�����
	exRange.ReleaseDispatch();    // �ͷ�Range����
	exSheet.ReleaseDispatch();    // �ͷ�Sheet����
	exSheets.ReleaseDispatch();    // �ͷ�Sheets����
	
	exBook.ReleaseDispatch();     // �ͷ�Workbook����
	exBooks.ReleaseDispatch();    // �ͷ�Workbooks����
	exBook.Close (covOptional, covOptional,covOptional);// �ر�Workbook����
	exBooks.Close();           // �ر�Workbooks����
	
	exApp.Quit();          // �˳�_Application
	exApp.ReleaseDispatch ();       // �ͷ�_Application
}


/************************************************************************/
/* �������Լƻ�                                                         */
/************************************************************************/
void CDataManageDlg::OnBtnExportSchedule() 
{
 	CString Field[8]={"�ƻ����","�����任","��ʼʱ��","����ʱ��","̽�����","��������","��������","̽�ⷽʽ"}; //�еı���
	_Application exApp;//Ӧ�ó������
	_Workbook exBook;//����������
	Workbooks exBooks;//���������϶���
	Worksheets exSheets;//��������
	_Worksheet exSheet;//���������
	Range exRange;
	myexcel::Font exFont;//����
	
	if(!exApp.CreateDispatch(_T("Excel.Application"))) 
	{
		AfxMessageBox(_T(" Excel failed to start!"));
		return;
	}
	VARIANT varOptional;//��ѡ��������
	VariantInit(&varOptional);
	varOptional.vt=VT_ERROR;
	varOptional.scode=DISP_E_PARAMNOTFOUND;
	
	//��ӹ��鲾�͹�����
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
	int count = atoi(VariantToCString(m_pTestRecordSet->GetCollect("ScheduleCount")));//��¼����
	
	strSQL.Format("SELECT * FROM tb_TestSchedule WHERE ScheduleID=%d", nSearchScheduleID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	
	long nRows,nCols;//�������к���
	nCols=8;
	nRows=count+1;
	
	long nstrLen;
	CString strField;
	VARIANT varCol;//���������п�
	VariantInit(&varCol);
	varCol.vt=VT_R4;
	char cCol='A';//A��V
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
		cCol=cCol++;//��A�п�ʼ��ÿ��
	}
	//��ȡ��Ԫ������

	char chr;
	chr='A'+nCols-1;
	CString strCh=chr;
	strCh=strCh+"2";
	VARIANT varUnit;
	VariantInit(&varUnit);
	varUnit.vt=VT_I4;
	varUnit.lVal=15;
		
	exRange=exSheet.GetRange(COleVariant("A1"),COleVariant(strCh));
	exRange.Merge(varOptional);//�ϲ���Ԫ��
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("����"));
	exFont.SetSize(varUnit);
	CString m_strTitle;
	m_strTitle.Format("WSN��·�������Լƻ���(%s/%s)",strSceneName,strScheduleTime);
	exRange.SetValue2(COleVariant(m_strTitle));//���ñ���

	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//ˮƽ����
	exRange.SetVerticalAlignment(varUnit);//��ֱ����
	
	//������ȫ���ݣ���¼��ر������
	COleSafeArray sarry;
	DWORD ElementsNum[2];
	ElementsNum[0]=nRows;//����
	ElementsNum[1]=nCols;//����
	sarry.Create(VT_BSTR,2,ElementsNum);
	VARIANT varVal;//��ֵ����
	long Index[2];
	CString strvalue;
	
	
	
	int k,l;
	for( k=0;k<nRows;k++)
	{
		if(k==0)//��һ��
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;
				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=Field[l].AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//��ӵ�������
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
				sarry.PutElement(Index,varVal.bstrVal);//��ӵ�������
				SysFreeString(varVal.bstrVal);//��ձ���
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
	exFont.SetName(COleVariant("����"));
	varUnit.lVal=12;
	exFont.SetSize(varUnit);
	exRange.SetValue2(COleVariant(sarry));
	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//ˮƽ����
	exRange.SetVerticalAlignment(varUnit);//��ֱ����

	CString strFilePath;
	CString strFileName = "��·�������Բ��Լƻ�";
	CFileDialog FileDlg(false,NULL,strFileName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
		_T("Excel FILE(*.xls)|*.xls|*.xlsx||"),NULL);//��3��������ָ���ļ�������5���������ļ����������б�
    if(FileDlg.DoModal()==IDOK)
    {
        strFilePath = FileDlg.GetPathName();//�õ��ļ���ȫ·���������ļ�������չ��
		COleVariant varFilePath(strFilePath);		
		exBook.SaveAs(varFilePath,varOptional,varOptional,varOptional,varOptional,varOptional,0,varOptional,varOptional,varOptional,varOptional,varOptional);
		AfxMessageBox("���ݵ����ɹ�!");
	}
	
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	exBook.SetSaved(TRUE);     // ��Workbook�ı���״̬����Ϊ�ѱ��棬������ϵͳ��ʾ�Ƿ��˹�����
	exRange.ReleaseDispatch();    // �ͷ�Range����
	exSheet.ReleaseDispatch();    // �ͷ�Sheet����
	exSheets.ReleaseDispatch();    // �ͷ�Sheets����
	
	exBook.ReleaseDispatch();     // �ͷ�Workbook����
	exBooks.ReleaseDispatch();    // �ͷ�Workbooks����
	exBook.Close (covOptional, covOptional,covOptional);// �ر�Workbook����
	exBooks.Close();           // �ر�Workbooks����
	
	exApp.Quit();          // �˳�_Application
	exApp.ReleaseDispatch ();       // �ͷ�_Application
}

/************************************************************************/
/* �������ݰ���Ϣ                                                       */
/************************************************************************/
void CDataManageDlg::OnBtnPacketinfo() 
{
	CString Field[12]={"���Լƻ�","���Ա��","�ڵ��","��Ϣ����","RSSI(��)","LQI(��)","SNR(��)","RSSI(��)","LQI(��)","SNR(��)","��Ϣ����","�ϱ�ʱ��"};//�еı���
	_Application exApp;//Ӧ�ó������
	_Workbook exBook;//����������
	Workbooks exBooks;//���������϶���
	Worksheets exSheets;//��������
	_Worksheet exSheet;//���������
	Range exRange;
	myexcel::Font exFont;//����
	
	if(!exApp.CreateDispatch(_T("Excel.Application"))) 
	{
		AfxMessageBox(_T(" Excel failed to start!"));
		return;
	}
	VARIANT varOptional;//��ѡ��������
	VariantInit(&varOptional);
	varOptional.vt=VT_ERROR;
	varOptional.scode=DISP_E_PARAMNOTFOUND;
	
	//��ӹ��鲾�͹�����
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
	int count = atoi(VariantToCString(m_pTestRecordSet->GetCollect("PacketCount")));//��¼����
	
	strSQL.Format("SELECT * FROM tb_PacketInfo WHERE ScheduleID=%d", nSearchScheduleID);
    m_pTestRecordSet = m_AdoConn.GetRecordSet((_bstr_t)strSQL);
	
	long nRows,nCols;//�������к���
	nCols=12;
	nRows=count+1;
	
	long nstrLen;
	CString strField;
	VARIANT varCol;//���������п�
	VariantInit(&varCol);
	varCol.vt=VT_R4;
	char cCol='A';//A��V
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
		cCol=cCol++;//��A�п�ʼ��ÿ��
	}
	//��ȡ��Ԫ������

	char chr;
	chr='A'+nCols-1;
	CString strCh=chr;
	strCh=strCh+"2";
	VARIANT varUnit;
	VariantInit(&varUnit);
	varUnit.vt=VT_I4;
	varUnit.lVal=15;
		
	exRange=exSheet.GetRange(COleVariant("A1"),COleVariant(strCh));
	exRange.Merge(varOptional);//�ϲ���Ԫ��
	exFont=exRange.GetFont();
	exFont.SetName(COleVariant("����"));
	exFont.SetSize(varUnit);
	CString m_strTitle;
	m_strTitle.Format("WSN��·�������ݰ�(%s/%s)",strSceneName,strScheduleTime);

	exRange.SetValue2(COleVariant(m_strTitle));//���ñ���

	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//ˮƽ����
	exRange.SetVerticalAlignment(varUnit);//��ֱ����
	
	//������ȫ���ݣ���¼��ر������
	COleSafeArray sarry;
	DWORD ElementsNum[2];
	ElementsNum[0]=nRows;//����
	ElementsNum[1]=nCols;//����
	sarry.Create(VT_BSTR,2,ElementsNum);
	VARIANT varVal;//��ֵ����
	long Index[2];
	CString strvalue;
	
	int k,l;
	for( k=0;k<nRows;k++)
	{
		if(k==0)//��һ��
		{
			for(l=0;l<nCols;l++)
			{
				Index[0]=k;
				Index[1]=l;
				VariantInit(&varVal);
				varVal.vt=VT_BSTR;
				varVal.bstrVal=Field[l].AllocSysString();
				sarry.PutElement(Index,varVal.bstrVal);//��ӵ�������
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
				sarry.PutElement(Index,varVal.bstrVal);//��ӵ�������
				SysFreeString(varVal.bstrVal);//��ձ���
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
	exFont.SetName(COleVariant("����"));
	varUnit.lVal=12;
	exFont.SetSize(varUnit);
	exRange.SetValue2(COleVariant(sarry));
	varUnit.lVal=-4108;
	exRange.SetHorizontalAlignment(varUnit);//ˮƽ����
	exRange.SetVerticalAlignment(varUnit);//��ֱ����

	CString strFilePath;
	CString strFileName = "��·�����������ݰ�������Ϣ";
	CFileDialog FileDlg(false,NULL,strFileName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
		_T("Excel FILE(*.xls)|*.xls|*.xlsx||"),NULL);//��3��������ָ���ļ�������5���������ļ����������б�
    if(FileDlg.DoModal()==IDOK)
    {
        strFilePath = FileDlg.GetPathName();//�õ��ļ���ȫ·���������ļ�������չ��
		COleVariant varFilePath(strFilePath);		
		exBook.SaveAs(varFilePath,varOptional,varOptional,varOptional,varOptional,varOptional,0,varOptional,varOptional,varOptional,varOptional,varOptional);
		AfxMessageBox("���ݵ����ɹ�!");
	}
	
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	exBook.SetSaved(TRUE);     // ��Workbook�ı���״̬����Ϊ�ѱ��棬������ϵͳ��ʾ�Ƿ��˹�����
	exRange.ReleaseDispatch();    // �ͷ�Range����
	exSheet.ReleaseDispatch();    // �ͷ�Sheet����
	exSheets.ReleaseDispatch();    // �ͷ�Sheets����
	
	exBook.ReleaseDispatch();     // �ͷ�Workbook����
	exBooks.ReleaseDispatch();    // �ͷ�Workbooks����
	exBook.Close (covOptional, covOptional,covOptional);// �ر�Workbook����
	exBooks.Close();           // �ر�Workbooks����
	
	exApp.Quit();          // �˳�_Application
	exApp.ReleaseDispatch ();       // �ͷ�_Application
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
