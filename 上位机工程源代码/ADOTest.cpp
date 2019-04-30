#include "stdafx.h"
#include "ADOTest.h"
#include "ADOConn.h"
#include "stdio.h"
#include <iostream>
using namespace std;
ADOTest::ADOTest()
{
}


ADOTest::~ADOTest()
{
}
 
void main()
{
	ADOConn ado; 
	int nSearchScheduleID;
	CString strSQL;
	_RecordsetPtr t_pRecordset;
	//ado.ExecuteSQL((_bstr_t)strSQL);
	ado.OnInitADOConn();
	strSQL.Format("SELECT COUNT(*) AS TestCount FROM tb_TestInfo WHERE ScheduleID=%d", nSearchScheduleID);
	int count = atoi(VariantToCString(t_pRecordset->GetCollect("TestCount")));
	cout << "Test>>>>>>>>>>>>count is :%d" <<count<< endl;
}