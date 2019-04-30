// ServerComm.h: interface for the CServerComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERCOMM_H__238E92E4_ECD1_4183_A2CC_193FC9751540__INCLUDED_)
#define AFX_SERVERCOMM_H__238E92E4_ECD1_4183_A2CC_193FC9751540__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Comm.h"
#include "Protocol.h"
#include <afxtempl.h>

class CServerComm : public CComm  
{
public:
	CServerComm();
	virtual ~CServerComm();

// Attributes
	CWnd* m_pNotifyWnd;
  
// Operations
BOOL Open(CWnd* pNotifyWnd,UINT nPort=1,UINT nBaud=19200,char chParity='N',UINT nDataBits=8,UINT nStopBits=1,DWORD dwCommEvents=EV_RXCHAR, UINT nWriteBufferSize=1024);

/* 消息发送和分发处理 */
BOOL MessageSender(CAMMessage Msg);
//void MessageDispatcher(CAMMessage Msg,CArray<int,int>& arryRouteArray);

/* 命令 */
BOOL ControlCmdToWSN(short sNodeID, BYTE cmdType);
BOOL ConfigCmdToWSN(short sNodeID, short pktSum, short sendPeriod,BYTE testModel);
BOOL ActiveTestToWSN(short sNodeID,short sMsgID,short sMsgSum);


/* 解析消息 */
BOOL WSNDataMessageParser(CAMMessage Msg);

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerComm)
public:
	/* 串口消息事件捕获 */
	virtual void OnCstDetectedEvent(); 
	virtual void OnBreakDetectedEvent();
	virtual void OnErrDetectedEvent();
	virtual void OnRingDetectedEvent();
	virtual void OnRxFlagDetectedEvent();
	virtual void OnTxEmptyDetectedEvent();
	virtual void OnRxCharEvent(BYTE bytData);
	//}}AFX_VIRTUAL
		
	// Generated message map functions
	//{{AFX_MSG(CServerComm)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
		
// Implementation
	protected:

};

#endif // !defined(AFX_SERVERCOMM_H__238E92E4_ECD1_4183_A2CC_193FC9751540__INCLUDED_)
