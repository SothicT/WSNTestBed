// ConnectSQL.cpp: implementation of the CConnectSQL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ConnectSQL.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConnectSQL::CConnectSQL()
{
	m_pConnection=NULL;
	m_pRecordset=NULL;
}

CConnectSQL::~CConnectSQL()
{

}
BOOL CConnectSQL::ConnectSQL(CString strDBName,CString strDBUserID,CString strDBUserPassword,CString strDBIP)
{
	if(FAILED(::CoInitialize(NULL)))
        return FALSE;

	HRESULT hr;
	//sqlserver2000
	_bstr_t source("Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;\
					Initial Catalog="+strDBName+";Data Source="+strDBIP+"");//连接数据库

	//sqlserver2005
   //Server=NCHU-ATOM\\SQL2005;


	//////////////////////////////////////////////////////////////////////////
	m_pConnection.CreateInstance("ADODB.Connection");
	//SQL SERVER2000连接字符串
	//_bstr_t  strConnect = "Provider=SQLOLEDB; Server=127.0.0.1;Database=XNPGXT; uid=sa; pwd=sa;";
	

	
	//_bstr_t  	
	CString	strConnect ;
		strConnect.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;",sName) ;
		m_pConnection->Open((_bstr_t)strConnect,"","",adModeUnknown);
	
	//////////////////////////////////////////////////////////////////////////

	_bstr_t user(strDBUserID);//帐号"sa"
	_bstr_t pwd(strDBUserPassword);//密码""
	try
	{
		hr = m_pConnection.CreateInstance(_uuidof(Connection));
		if( SUCCEEDED(hr) )
			hr = m_pConnection->Open(source,user,pwd,adCmdUnspecified);
		if( SUCCEEDED(hr) )
			hr = m_pRecordset.CreateInstance(_uuidof(Recordset));
		if( SUCCEEDED(hr) )
			m_bConnected = TRUE;
		else 
			m_bConnected = FALSE;
	}
	catch (_com_error &e)
	{
	   AfxMessageBox(e.Description());
	   m_bConnected = FALSE;
	}

	if(!m_bConnected) return FALSE;

	m_strSource = (const char * )source;
	return TRUE;	
}

void CConnectSQL::DisconnectSQL()
{
	if(m_bConnected)
	{
		try
		{
			if(adStateOpen==m_pRecordset->State)
				m_pRecordset->Close();
			if(adStateOpen==m_pConnection->State)
				m_pConnection->Close();
		}
		catch (_com_error &e)
		{
			AfxMessageBox(e.Description());
		}

		m_pConnection=NULL;
		m_pRecordset=NULL;

		m_bConnected=FALSE;
	}
	::CoUninitialize();
}

BOOL CConnectSQL::ExecuteSQL(CString sql)
{
	try
	{
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);	
		return TRUE;
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());
		return FALSE; 
	}
	return FALSE; 
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
	case VT_R4:strValue.Format ("%.2f",var.fltVal);break;
	case VT_R8:strValue.Format ("%.2f",var.dblVal);break;
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