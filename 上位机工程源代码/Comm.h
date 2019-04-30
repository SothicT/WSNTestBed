#if !defined(AFX_COMM_H__929424E5_6B12_4E6D_8F73_C77FC67C4452__INCLUDED_)
#define AFX_COMM_H__929424E5_6B12_4E6D_8F73_C77FC67C4452__INCLUDED_

/////////////////////////////////////////////////////////////////////////////
// CComm window

class CComm : public CWnd
{
	// Construction
public:
	CComm();
	
	// Attributes
public:
	HANDLE m_hComm;
	
	// Operations
public:
	BOOL Open(UINT nPort=3,UINT nBaud=115200,char chParity='N',UINT nDataBits=8,UINT nStopBits=1,DWORD dwCommEvents=EV_RXCHAR, UINT nWriteBufferSize=1024);
	void Close();

	void Write(BYTE* pBuffer,int nBufferSize);
	DWORD GetCommEvents();
	DCB	GetDCB();
	
	/* 串口消息事件捕获 */
	virtual void OnCstDetectedEvent()=0;// The CTS (clear-to-send) signal changed state. 
	virtual void OnBreakDetectedEvent()=0;// A break was detected on input.
	virtual void OnErrDetectedEvent()=0;// A line-status error occurred. Line-status errors are CE_FRAME, CE_OVERRUN, and CE_RXPARITY. 
	virtual void OnRingDetectedEvent()=0;// A ring indicator was detected. 
	virtual void OnRxFlagDetectedEvent()=0;// The event character was received and placed in the input buffer.
	virtual void OnTxEmptyDetectedEvent()=0;// The last character in the output buffer was sent.
	virtual void OnRxCharEvent(BYTE bytData)=0;// A character was received and placed in the input buffer. 

protected:
	/* 串口通信线程句柄 */
	CWinThread*	m_Thread;
	
	/* 同步对象 */
	CRITICAL_SECTION m_csCommunicationSync;
	BOOL m_bThreadAlive;
	
	/* 事件句柄 */
	HANDLE m_hWriteEvent;
	HANDLE m_hShutdownEvent;
	
	// Event array. 
	// One element is used for each event. There are two event handles for each port.
	// A Write event and a receive character event which is located in the overlapped structure (m_ov.hEvent).
	// There is a general shutdown when the port is closed. 
	HANDLE m_hEventArray[3];
	
	OVERLAPPED	m_Ov;
	COMMTIMEOUTS m_CommTimeouts;
	DCB	m_Dcb;
	
	UINT m_nPort;
	DWORD m_dwCommEvents;
	BYTE* m_pWriteBuffer;
	DWORD m_nWriteBufferSize;
	DWORD m_nWriteBufferMaxSize;
	
	void ProcessErrorMessage(char* lpszErrorText);
	
	static UINT	CommThread(LPVOID pParam);
	static void	ReadChar(CComm* pComm, COMSTAT Comstat);
	static void	WriteChar(CComm* pComm);
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComm)
	
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CComm();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CComm)
	afx_msg LRESULT OnCommNotify(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif // !defined(AFX_COMM_H__929424E5_6B12_4E6D_8F73_C77FC67C4452__INCLUDED_)
