// ADOConn.cpp: implementation of the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "ADOConn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADOConn::ADOConn()
{

}

ADOConn::~ADOConn()
{

}

void  ADOConn::OnInitADOConn()
{
	
	::CoInitialize(NULL);

	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");

		char   lpPath[_MAX_PATH];   
		if(GetModuleFileName(NULL,lpPath,_MAX_PATH)==0)   
		{  
			return;   
		}   
		
		m_strDatabaseFile.Format("%s",lpPath);//��ǰ�ļ�ȫ·������   
		m_strDatabaseFile= m_strDatabaseFile.Left( m_strDatabaseFile.ReverseFind('\\'));//ȥ���ļ�������	
		m_strDatabaseFile+="\\LQ_Testbed.mdb";

		CString	strConnect ;	//ACCESS �����ַ���		
		strConnect.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;", m_strDatabaseFile) ;
		m_pConnection->Open((_bstr_t)strConnect,"","",adModeUnknown);

	
	}	
	catch(_com_error e)
	{
		AfxMessageBox("�������ݿ�ʧ��!\r\n������Ϣ:"+e.Description());	
		exit(0);//exit: 0�����˳�;1�쳣�˳�
	}
}

_RecordsetPtr&  ADOConn::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{
		if(m_pConnection==NULL)	// �������ݿ⣬���Connection����Ϊ�գ��������������ݿ�
			OnInitADOConn();
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)	// ��ʾ������Ϣ
	{		
		AfxMessageBox("��ȡ��¼��ʧ��!\r\n������Ϣ:"+e.Description());
		exit(0);
	}
	return m_pRecordset;
}


BOOL ADOConn::ExecuteSQL(_bstr_t bstrSQL)
{

	try
	{
		if(m_pConnection == NULL)
		{
			OnInitADOConn();
		}
		
		m_pConnection->Execute(bstrSQL,NULL,adCmdText);
		return true;
	}
	catch(_com_error e)
	{
		AfxMessageBox("ִ��SQL������!\r\n������Ϣ:"+e.Description());
		return false;
	}

}


void ADOConn::ExitConnect()
{
	if (m_pRecordset != NULL)
	{
			m_pRecordset->Close();
	}
	m_pConnection->Close();
	::CoUninitialize();   //�ͷ�OLE����
}

CString VariantToCString(VARIANT var)
{
   	CString strValue;
	_variant_t var_t;
	_bstr_t bst_t;
	time_t cur_time;
	CTime time_value;
	COleCurrency var_currency;
	switch(var.vt){
	case VT_EMPTY:strValue=_T("");break;
	case VT_UI1:strValue.Format ("%d",var.bVal);break;
	case VT_I2:strValue.Format ("%d",var.iVal );break;
	case VT_I4:strValue.Format ("%d",var.lVal);break;
	case VT_R4:strValue.Format ("%.3f",var.fltVal);break;
	case VT_R8:strValue.Format ("%.3f",var.dblVal);break;
	case VT_CY:
		var_currency=var;
		strValue=var_currency.Format(0);
		break;
	case VT_BSTR:
		var_t=var;
		bst_t=var_t;
		strValue.Format ("%s",(const char*)bst_t);
		break;
	case VT_NULL:strValue=_T("");break;
	case VT_DATE:
		cur_time=(long)var.date;
		time_value=cur_time;
        strValue=time_value.Format("%Y-%m-%d");
		break;
	case VT_BOOL:strValue.Format ("%d",var.boolVal );break;
	default:strValue=_T("");break;
	}
	return strValue;
}

CTime StringToTime(CString str)
{
	if(str.IsEmpty())
		str="1990-1-1";
	int   y,m,d;
	y=atoi(str);
	int   i,j;   
	i=str.Find('-',0);
	j=str.Find('-',i+1);
	CString   temp;   
	while(i<j-1)   
		temp+=str.GetAt(++i);   
	m=atoi(temp);
	temp.Empty();   
	i=str.GetLength();    
	while(j<i-1)   
		temp+=str.GetAt(++j);   
	d=atoi(temp);
	CTime   tmp(y,m,d,0,0,0);
	return tmp;
}
