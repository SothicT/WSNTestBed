// ConnectSQL.h: interface for the CConnectSQL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECTSQL_H__6BA6B383_4A3D_4AE4_9555_0472AD6C7E31__INCLUDED_)
#define AFX_CONNECTSQL_H__6BA6B383_4A3D_4AE4_9555_0472AD6C7E31__INCLUDED_

#import "C:\Program Files\Common Files\System\ado\msado20.tlb" no_namespace rename("EOF","_EOF") rename("BOF","_BOF")

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern CString VariantToCString(VARIANT var);

class CConnectSQL  
{
public:
	CConnectSQL();
	virtual ~CConnectSQL();
public:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
private:
	CString m_strSource;
	BOOL m_bConnected;
public:
	BOOL ConnectSQL(CString strDBName="LQ_Testbed",CString strDBUserID="sa",CString strDBUserPassword="sa",CString strDBIP="(local)");//连接数据库
	void DisconnectSQL();//断开数据库
	BOOL ExecuteSQL(CString sql);//查询数据库

};

#endif // !defined(AFX_CONNECTSQL_H__6BA6B383_4A3D_4AE4_9555_0472AD6C7E31__INCLUDED_)
