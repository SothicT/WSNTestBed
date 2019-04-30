// ADOConn.h: interface for the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOCONN_H__5556CA8A_CB50_411F_A0FC_EB322475EF88__INCLUDED_)
#define AFX_ADOCONN_H__5556CA8A_CB50_411F_A0FC_EB322475EF88__INCLUDED_
//#import "C:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
#import "c:\Program Files\common files\system\ado\msado20.tlb" no_namespace rename("EOF","adoEOF")
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


extern CString VariantToCString(VARIANT var);
extern CTime StringToTime(CString str);

class ADOConn  
{

public:
	_ConnectionPtr m_pConnection;	
	_RecordsetPtr m_pRecordset;
	
	CString   m_strDatabaseFile;   
public:
	ADOConn();
	virtual ~ADOConn();
	void  OnInitADOConn();							// 初始化—连接数据库
	_RecordsetPtr&  GetRecordSet(_bstr_t bstrSQL);	// 执行select语句
	BOOL ExecuteSQL(_bstr_t bstrSQL);				// 执行SQL语句的Insert和 Update
	void ExitConnect();	
};

#endif // !defined(AFX_ADOCONN_H__5556CA8A_CB50_411F_A0FC_EB322475EF88__INCLUDED_)
