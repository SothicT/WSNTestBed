// Comm.cpp : implementation file
//

#include "stdafx.h"
#include "LQ_Testbed.h"
#include "Comm.h"

//#include "Matrix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <assert.h>

/////////////////////////////////////////////////////////////////////////////
// CComm implementation

CComm::CComm()
{
	m_hWnd=NULL;

	m_hComm=NULL;
	
	/* ��ʼ��overlapped�ṹ */
	m_Ov.Offset=0;
	m_Ov.OffsetHigh=0;
	
	/* ��ʼ���¼���� */
	m_Ov.hEvent=NULL;
	m_hWriteEvent=NULL;
	m_hShutdownEvent=NULL;
	
	m_pWriteBuffer=NULL;
	m_nWriteBufferSize=1;
	
	m_bThreadAlive=FALSE;
}

CComm::~CComm()
{
	/* �ͷ�д���� */
	do
	{
		SetEvent(m_hShutdownEvent);
	}while(m_bThreadAlive);
	
	TRACE("Thread ended\n");
	
	delete [] m_pWriteBuffer;
}

BEGIN_MESSAGE_MAP(CComm, CWnd)
//{{AFX_MSG_MAP(CComm)
ON_MESSAGE(WM_COMM_NOTIFY, OnCommNotify) //������Ϣ
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CComm message handlers

afx_msg LRESULT CComm::OnCommNotify(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
	case EV_CTS:
		OnCstDetectedEvent();
		break;
	case EV_BREAK:
		OnBreakDetectedEvent();
		break;
	case EV_ERR:
		OnErrDetectedEvent();
		break;
	case EV_RING:
		OnRingDetectedEvent();
		break;
	case EV_TXEMPTY:
		OnTxEmptyDetectedEvent();
		break;
	case EV_RXCHAR:
		OnRxCharEvent((BYTE)lParam);
		break;
	default:break;
	}
	
	return 1;
}


/* �򿪴��� */
BOOL CComm::Open(UINT  nPort,				//���ں�
					UINT  nBaud,				//������
					char  chParity,			// parity 
					UINT  nDataBits,			//����λ 
					UINT  nStopBits,			//ֹͣλ
					DWORD dwCommEvents,		//�����¼���EV_RXCHAR,EV_CTS��
					UINT  nWriteBufferMaxSize)	//д�����С
{
	/* �������ͨ���߳���������,������ֹͣ */
	
	if (m_bThreadAlive)
	{
		do
		{
			SetEvent(m_hShutdownEvent);
		}
		while (m_bThreadAlive);
		
		TRACE("Thread ended\n");
	}

	if(m_hWnd==NULL)
	{
		/* �������ڴ��ڶ��� */
		if (!CreateEx(0,AfxRegisterWndClass(0),"SerialPort Notification Sink",WS_OVERLAPPED, 0, 0, 0, 0, NULL, NULL))
		{
			TRACE("Warning: unable to create serialport notify window!\n");
			return FALSE;
		}
	}

	/* �����¼����� */
	if (m_Ov.hEvent!=NULL)
		ResetEvent(m_Ov.hEvent);
	m_Ov.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	
	if (m_hWriteEvent!=NULL)
		ResetEvent(m_hWriteEvent);
	m_hWriteEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	
	if (m_hShutdownEvent!=NULL)
		ResetEvent(m_hShutdownEvent);
	m_hShutdownEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	
	/* ��ʼ���¼����� */
	m_hEventArray[0]=m_hShutdownEvent;//�����ȼ�
	m_hEventArray[1]=m_Ov.hEvent;
	m_hEventArray[2]=m_hWriteEvent;
	
	/* ��ʼ���ؼ������� */
	InitializeCriticalSection(&m_csCommunicationSync);

	if (m_pWriteBuffer!=NULL)
		delete [] m_pWriteBuffer;
	m_pWriteBuffer=new BYTE[nWriteBufferMaxSize];
	
	m_nPort=nPort;
	
	m_nWriteBufferMaxSize=nWriteBufferMaxSize;
	m_dwCommEvents=dwCommEvents;
	
	BOOL bResult=FALSE;
	char *szPort=new char[50];
	char *szBaud=new char[50];
	
	/* ����ؼ������ */
	EnterCriticalSection(&m_csCommunicationSync);
	
	/* ��������Ѵ�,��ر� */
	if (m_hComm!=NULL)
	{
		CloseHandle(m_hComm);
		m_hComm=NULL;
	}
	
	sprintf(szPort,"COM%d",nPort);
	sprintf(szBaud,"baud=%d parity=%c data=%d stop=%d",nBaud,chParity,nDataBits,nStopBits);
	
	/* ��ô��ھ�� */
	m_hComm=CreateFile(szPort,			//���ں�:COMX
		GENERIC_READ | GENERIC_WRITE,	//���ڶ�/д
		0,								//������ʴ����豸
		NULL,							//��ȫ����
		OPEN_EXISTING,					//OPEN_EXISTING
		FILE_FLAG_OVERLAPPED,			//�첽I/O
		0);								//0
	

	if (m_hComm==INVALID_HANDLE_VALUE)
	{
		/* ����δ�ҵ� */
		delete [] szPort;
		delete [] szBaud;
		
		return FALSE;
	}
	
	/* ���ô��ڳ�ʱʱ�� */
	m_CommTimeouts.ReadIntervalTimeout = 1000;
	m_CommTimeouts.ReadTotalTimeoutMultiplier = 1000;
	m_CommTimeouts.ReadTotalTimeoutConstant = 1000;
	m_CommTimeouts.WriteTotalTimeoutMultiplier = 1000;
	m_CommTimeouts.WriteTotalTimeoutConstant = 1000;
	
	/* ���ô��� */
	if(SetCommTimeouts(m_hComm,&m_CommTimeouts))
	{						   
		if(SetCommMask(m_hComm,dwCommEvents))
		{
			if(GetCommState(m_hComm,&m_Dcb))
			{
				m_Dcb.EvtChar='q';
				m_Dcb.fRtsControl=RTS_CONTROL_ENABLE;	// set RTS bit high!
				if(BuildCommDCB(szBaud,&m_Dcb))
				{
					if(SetCommState(m_hComm,&m_Dcb))
					{
						;
					}
					else
					{
						ProcessErrorMessage("SetCommState()");
					}
				}
				else
				{
					ProcessErrorMessage("BuildCommDCB()");
				}
			}
			else
			{
				ProcessErrorMessage("GetCommState()");
			}
		}
		else
		{
			ProcessErrorMessage("SetCommMask()");
		}
	}
	else
	{
		ProcessErrorMessage("SetCommTimeouts()");
	}
	
	delete [] szPort;
	delete [] szBaud;
	
	/* ˢ�´��� */
	PurgeComm(m_hComm,PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	
	/* �뿪�ؼ������� */
	LeaveCriticalSection(&m_csCommunicationSync);
	
	TRACE("Initialisation for communicationport %d completed.\nUse Startmonitor to communicate.\n",nPort);
	
	/* ��������ͨ���߳� */
	if(!(m_Thread=AfxBeginThread(CommThread,this)))
	{
		return FALSE;
	}
	TRACE("Thread started\n");

	return TRUE;
}

/* ����ͨ���߳� */
UINT CComm::CommThread(LPVOID pParam)
{
	CComm *pComm=(CComm*)pParam;
	
	pComm->m_bThreadAlive=TRUE;	
	
	// Misc. variables
	DWORD dwBytesTransfered=0; 
	DWORD dwEvent=0;
	DWORD dwCommEvent=0;
	DWORD dwError=0;
	COMSTAT Comstat;
	BOOL bResult=TRUE;
	
	if(pComm->m_hComm) //��鴮���Ƿ��Ѵ�
	{
		PurgeComm(pComm->m_hComm,PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	}

	for(;;) 
	{ 
		
		// Make a call to WaitCommEvent().  This call will return immediatly
		// because our port was created as an async port (FILE_FLAG_OVERLAPPED
		// and an m_OverlappedStructerlapped structure specified).  This call will cause the 
		// m_OverlappedStructerlapped element m_OverlappedStruct.hEvent, which is part of the m_hEventArray to 
		// be placed in a non-signeled state if there are no bytes available to be read,
		// or to a signeled state if there are bytes available.  If this event handle 
		// is set to the non-signeled state, it will be set to signeled when a 
		// character arrives at the port.
		
		// we do this for each port!
		
		bResult=WaitCommEvent(pComm->m_hComm,&dwEvent,&pComm->m_Ov);
		
		if(!bResult)  
		{ 
			// If WaitCommEvent() returns FALSE, process the last error to determin
			// the reason..
			switch(dwError=GetLastError()) 
			{ 
			case ERROR_IO_PENDING: 	
				{ 
					// This is a normal return value if there are no bytes
					// to read at the port.
					// Do nothing and continue
					break;
				}
			case 87:
				{
					// Under Windows NT, this value is returned for some reason.
					// I have not investigated why, but it is also a valid reply
					// Also do nothing and continue.
					break;
				}
			default:
				{
					// All other error codes indicate a serious error has
					// occured.  Process this error.
					pComm->ProcessErrorMessage("WaitCommEvent()");
					break;
				}
			}
		}
		else
		{
			// If WaitCommEvent() returns TRUE, check to be sure there are
			// actually bytes in the buffer to read.  
			//
			// If you are reading more than one byte at a time from the buffer 
			// (which this program does not do) you will have the situation occur 
			// where the first byte to arrive will cause the WaitForMultipleObjects() 
			// function to stop waiting.  The WaitForMultipleObjects() function 
			// resets the event handle in m_OverlappedStruct.hEvent to the non-signelead state
			// as it returns.  
			//
			// If in the time between the reset of this event and the call to 
			// ReadFile() more bytes arrive, the m_OverlappedStruct.hEvent handle will be set again
			// to the signeled state. When the call to ReadFile() occurs, it will 
			// read all of the bytes from the buffer, and the program will
			// loop back around to WaitCommEvent().
			// 
			// At this point you will be in the situation where m_OverlappedStruct.hEvent is set,
			// but there are no bytes available to read.  If you proceed and call
			// ReadFile(), it will return immediatly due to the async port setup, but
			// GetOverlappedResults() will not return until the next character arrives.
			//
			// It is not desirable for the GetOverlappedResults() function to be in 
			// this state.  The thread shutdown event (event 0) and the WriteFile()
			// event (Event2) will not work if the thread is blocked by GetOverlappedResults().
			//
			// The solution to this is to check the buffer with a call to ClearCommError().
			// This call will reset the event handle, and if there are no bytes to read
			// we can loop back through WaitCommEvent() again, then proceed.
			// If there are really bytes to read, do nothing and proceed.
			
			bResult=ClearCommError(pComm->m_hComm,&dwError,&Comstat);
			
			if(Comstat.cbInQue==0)
			{
				continue;
			}
		}
		
		// Main wait function.  This function will normally block the thread
		// until one of nine events occur that require action.
		dwEvent=WaitForMultipleObjects(3,pComm->m_hEventArray,FALSE,INFINITE);
		
		switch (dwEvent)
		{
		case 0:
			{
				// Shutdown event.  This is event zero so it will be
				// the higest priority and be serviced first.
				CloseHandle(pComm->m_hComm);
				pComm->m_hComm=NULL;
				pComm->m_bThreadAlive=FALSE;
				
				// Kill this thread.  break is not needed, but makes me feel better.
				AfxEndThread(100);
				
				break;
			}
		case 1:	// read event
			{
				GetCommMask(pComm->m_hComm,&dwCommEvent);
				if(dwCommEvent & EV_RXCHAR)
				{
					ReadChar(pComm,Comstat);
				}
				if(dwCommEvent & EV_CTS)
				{
					pComm->PostMessage((WPARAM)WM_COMM_NOTIFY,(WPARAM)EV_CTS,(LPARAM)0);
				}
				if(dwCommEvent & EV_BREAK)
				{
					pComm->PostMessage((WPARAM)WM_COMM_NOTIFY,(WPARAM)EV_BREAK,(LPARAM)0);
				}
				if(dwCommEvent & EV_ERR)
				{
					pComm->PostMessage((WPARAM)WM_COMM_NOTIFY,(WPARAM)EV_ERR,(LPARAM)0);
				}
				if(dwCommEvent & EV_RING)
				{
					pComm->PostMessage((WPARAM)WM_COMM_NOTIFY,(WPARAM)EV_RING,(LPARAM)0);
				}
				if(dwCommEvent & EV_RXFLAG)
				{
					pComm->PostMessage((WPARAM)WM_COMM_NOTIFY,(WPARAM)EV_RXFLAG,(LPARAM)0);
				}
				break;
			}  
		case 2: // write event
			{
				// Write character event from port
				WriteChar(pComm);
				break;
			}
		}
	}
	
	return 0;
}

/* ������Ϣ���� */
void CComm::ProcessErrorMessage(char* lpszErrorText)
{
	char *Temp=new char[200];
	
	LPVOID lpMsgBuf;
	
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),//Ĭ������
		(LPTSTR) &lpMsgBuf,
		0,
		NULL
		);
	
	sprintf(Temp,"WARNING:  %s Failed with the following error: \n%s\nPort: %d\n",lpszErrorText,lpMsgBuf,m_nPort); 
	MessageBox(Temp,"Application Error",MB_ICONSTOP);
	
	LocalFree(lpMsgBuf);
	delete [] Temp;
}

/* �򴮿�д��һ���ֽ� */
void CComm::WriteChar(CComm* pComm)
{
	BOOL bWrite=TRUE;
	BOOL bResult=TRUE;
	
	DWORD dwBytesSend=0;
	
	ResetEvent(pComm->m_hWriteEvent);
	
	EnterCriticalSection(&pComm->m_csCommunicationSync);
	
	if (bWrite)
	{
		/* ��ʼ��overlapped�ṹ */
		pComm->m_Ov.Offset=0;
		pComm->m_Ov.OffsetHigh=0;
		
		PurgeComm(pComm->m_hComm,PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
		
		bResult=WriteFile(pComm->m_hComm,			//���ھ��
			pComm->m_pWriteBuffer,				//д������ָ��
			pComm->m_nWriteBufferSize,					//д���С
			&dwBytesSend,								//Where to store the number of bytes sent
			&pComm->m_Ov);						//Overlapped�ṹ
		
		/* ������� */
		if (!bResult)  
		{
			DWORD dwError=GetLastError();
			switch(dwError)
			{
			case ERROR_IO_PENDING:
				{
					/* ���� GetOverlappedResults() */
					dwBytesSend=0;
					bWrite=FALSE;
					break;
				}
			default:
				{
					/* ��������������Ϣ */
					pComm->ProcessErrorMessage("WriteFile()");
				}
			}
		} 
		else
		{
			LeaveCriticalSection(&pComm->m_csCommunicationSync);
		}
	}
	
	if(!bWrite)
	{
		bWrite=TRUE;
		
		bResult=GetOverlappedResult(pComm->m_hComm,		//���ھ��
			&pComm->m_Ov,									//Overlapped�ṹ
			&dwBytesSend,										//Stores number of bytes sent
			TRUE); 												//�ȴ���־
		
		LeaveCriticalSection(&pComm->m_csCommunicationSync);	
	}
	
	pComm->PostMessage((WPARAM)WM_COMM_NOTIFY,(WPARAM)EV_TXEMPTY,0);
}

/* �����յ�һ���ֽ� */
void CComm::ReadChar(CComm* pComm, COMSTAT Comstat)
{

	BOOL  bRead=TRUE; 
	BOOL  bResult=TRUE;
	DWORD dwError=0;
	DWORD dwBytesRead=0;
	BYTE RxChar;
	
	for(;;) 
	{ 
		// Gain ownership of the comm port critical section.
		// This process guarantees no other part of this program 
		// is using the port object. 
		
		EnterCriticalSection(&pComm->m_csCommunicationSync);
		
		// ClearCommError() will update the COMSTAT structure and
		// clear any other errors.
		
		bResult=ClearCommError(pComm->m_hComm,&dwError,&Comstat);
		
		LeaveCriticalSection(&pComm->m_csCommunicationSync);
		
		// start forever loop.  I use this type of loop because I
		// do not know at runtime how many loops this will have to
		// run. My solution is to start a forever loop and to
		// break out of it when I have processed all of the
		// data available.  Be careful with this approach and
		// be sure your loop will exit.
		// My reasons for this are not as clear in this sample 
		// as it is in my production code, but I have found this 
		// solutiion to be the most efficient way to do this.
		
		if(Comstat.cbInQue==0)
		{
			// break out when all bytes have been read
			break;
		}
		
		EnterCriticalSection(&pComm->m_csCommunicationSync);
		
		if(bRead)
		{
			bResult=ReadFile(pComm->m_hComm,	//���ھ��
				&RxChar,							//���ջ���ָ��
				1,									//1���ֽ�
				&dwBytesRead,						//�Ѷ�ȡ���ֽ���
				&pComm->m_Ov);				//Overlapped�ṹ
			
			/* ���������Ϣ */
			if(!bResult)  
			{ 
				switch(dwError=GetLastError()) 
				{ 
				case ERROR_IO_PENDING: 	
					{ 
						// asynchronous i/o is still in progress 
						// Proceed on to GetOverlappedResults();
						bRead=FALSE;
						break;
					}
				default:
					{
						/* ��������������Ϣ */
						pComm->ProcessErrorMessage("ReadFile()");
						break;
					} 
				}
			}
			else
			{
				// ReadFile() returned complete. It is not necessary to call GetOverlappedResults()
				bRead=TRUE;
			}
		}
		
		if (!bRead)
		{
			bRead=TRUE;
			bResult=GetOverlappedResult(pComm->m_hComm,	//���ھ�� 
				&pComm->m_Ov,								//Overlapped�ṹ
				&dwBytesRead,									//�Ѷ�ȡ���ֽ���
				TRUE); 											//�ȴ���־
			
			/* ���������Ϣ */
			if (!bResult)  
			{
				pComm->ProcessErrorMessage("GetOverlappedResults() in ReadFile()");
			}	
		}
		
		LeaveCriticalSection(&pComm->m_csCommunicationSync);
		
		/* ֪ͨ���������� */
		pComm->PostMessage((WPARAM)WM_COMM_NOTIFY,(WPARAM)EV_RXCHAR,(LPARAM)RxChar);
	}
}

/* �򴮿�д��һ������ */
void CComm::Write(BYTE* pBuffer,int nBufferSize)
{		
	assert(m_hComm != 0);
	
	memset(m_pWriteBuffer,0,sizeof(m_pWriteBuffer));
	
	m_nWriteBufferSize=nBufferSize;
	memcpy(m_pWriteBuffer,pBuffer,nBufferSize*sizeof(BYTE));
	
	SetEvent(m_hWriteEvent);//����д�¼�
}

/* �����豸���ƿ� */
DCB CComm::GetDCB()
{
	return m_Dcb;
}

/* ����ͨ���¼�Mask */
DWORD CComm::GetCommEvents()
{
	return m_dwCommEvents;
}

void CComm::Close()
{
	SetEvent(m_hShutdownEvent);
}
