// ServerComm.cpp: implementation of the CServerComm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServerComm.h"
#include "LQ_Testbed.h"

#include "Global.h"
#include "Common.h"
#include  "LQ_TestbedDlg.h"

#include "iPlotChannelX.h"
#include "iPlotAxisX.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServerComm::CServerComm()
{
	m_pNotifyWnd=NULL;
}

CServerComm::~CServerComm()
{
	
}

BOOL CServerComm::Open(CWnd* pNotifyWnd,		//֪ͨ���ھ��
					   UINT  nPort,				//���ں�
					   UINT  nBaud,				//������
					   char  chParity,			// parity 
					   UINT  nDataBits,			//����λ 
					   UINT  nStopBits,			//ֹͣλ
					   DWORD dwCommEvents,		//�����¼���EV_RXCHAR,EV_CTS��
					   UINT  nWriteBufferMaxSize)	//д�����С
{
	m_pNotifyWnd=pNotifyWnd;
	
	return CComm::Open(nPort,nBaud,chParity,nDataBits,nStopBits,dwCommEvents,nWriteBufferMaxSize);
}

void CServerComm::OnCstDetectedEvent()
{
	
}

void CServerComm::OnBreakDetectedEvent()
{
	
}

void CServerComm::OnErrDetectedEvent()
{
	
}

void CServerComm::OnRingDetectedEvent()
{
	
}

void CServerComm::OnRxFlagDetectedEvent()
{
	
}

void CServerComm::OnTxEmptyDetectedEvent()
{
	
}

//�����¼�����Ϣ��Ӧ����
void CServerComm::OnRxCharEvent(BYTE bytData)
{
	
	//�Դ��ڽ��յ������ݰ����н������,�����Ѵ�������ݽ����ϲ�Ӧ������һ������
	int n;
	CString strSQL;
	
	static BYTE pRxData[MAX_COMM_BUFFER_LEN];//���ڽ�������
	static int nRxSize=0;//���ڼ�¼�ܹ��յ��˶����ֽ�
	static int nRxState=RXSTATE_NOSYNC;//����״̬ת��
	static unsigned short nRxRunningCRC=0;//���ڼ�������CRCֵ
	static unsigned short nRxReceiveCRC=0;//���ڴ�����ݰ��е�CRCֵ
	
	switch (nRxState)
	{
	case RXSTATE_NOSYNC: 
		if(bytData==HDLC_FLAG_BYTE)//�޳�7E����δ����PRxData[]��
		{
			nRxSize=0;
			nRxRunningCRC=0;
			nRxState=RXSTATE_PROTO;//��״̬ת����Э��֡����
		}
		break;
		
	case RXSTATE_PROTO://Э��֡�������
		if(bytData==HDLC_FLAG_BYTE)
		{
			break;
		}
		nRxRunningCRC=CRC(nRxRunningCRC,bytData);//��ʼ����CRC
		nRxState=RXSTATE_INFO;//����֡����
		break;
		
	case RXSTATE_INFO:
		if(bytData==HDLC_CTLESC_BYTE) //���յ��ֽ�Ϊ7D��ת��ת���ֽڴ���״̬
		{
			nRxState=RXSTATE_ESC;
		}
		else if(bytData==HDLC_FLAG_BYTE)//֡ĩͬ����
		{
			if(nRxSize>=2) 
			{
				//������ǵ�һ��7e
				nRxReceiveCRC=(pRxData[(nRxSize-1)]&0xFF);//������յ������ݵ�CRC
				nRxReceiveCRC=(nRxReceiveCRC<<8)|(pRxData[(nRxSize-2)]&0xFF);
				if(nRxReceiveCRC==nRxRunningCRC)
				{
					//CRCУ����ȷ,������,�����ϲ�Ӧ������һ������
					//ȥ����ͷ��8���ֽں�CRC��2���ֽ�,��10���ֽ�.
					//����:(7E 45 -����)(00 FF FF FF FF 04 00 02 -8���ֽ�) 00 0D 24 6B 00 00 (98 06 -2���ֽڵ�CRCУ��ֵ)(7E -����)
					if(nRxSize-10>=0)//��������֡ //���а�����̵�payload����Ϊ9���ֽ�
					{
						
						/* ��Ϣ�ַ� */
						BYTE bytOneByte;
						
						CAMMessage Msg;
						//��ȡ��Ϣ�ֶ��ֽ�
						
						//��Ϣ���ͺ�������
						//��Ϣ���� 0X0002��00��ʾ���У�������02״̬���ݰ�
						Msg.m_bytType=pRxData[8]; 
						Msg.m_bytSubType=pRxData[9];
						
						CString strMsgBodyItem="";
						CString strMsgBody="";
						
						for(n=0;n<nRxSize-10;n++)
						{
							bytOneByte=pRxData[10+n]; 
							Msg.m_arryBody.Add(bytOneByte);//�洢��Msg�ṹ����
							
							strMsgBodyItem="";
							::ByteToHex(strMsgBodyItem,bytOneByte);
							strMsgBody+=strMsgBodyItem;
						}					
						//��Ϣ�ַ�����������·������ֻ���ǵ�������·�����������ͱȽϵ�һ��ֻ���������
						WSNDataMessageParser(Msg);	 									
					}
				}
				
				nRxState=RXSTATE_NOSYNC;
			}
			else 
			{
				nRxSize=0;
				nRxRunningCRC=0;
				nRxState=RXSTATE_NOSYNC;
			}
		}
		else 
		{
			pRxData[nRxSize]=bytData;
			if (nRxSize>=2) 
			{
				nRxRunningCRC=CRC(nRxRunningCRC,pRxData[(nRxSize-2)]);
			}
			nRxSize++;
		}
		break;
		//ת���ֽڻ����֡ͬ����
	case RXSTATE_ESC:
		if (bytData==HDLC_FLAG_BYTE)
		{
			//Error case,fail and resync
			nRxSize=0;
			nRxRunningCRC=0;
			nRxState=RXSTATE_NOSYNC;
		}
		else
		{
			bytData=bytData^0x20; // 7D->7D5D�Ļ�ԭ,7D����,5D->7D
			pRxData[nRxSize]=bytData;//7D
			if(nRxSize>=2)
			{
				nRxRunningCRC=CRC(nRxRunningCRC,pRxData[(nRxSize-2)]);
			}
			nRxSize++;
			nRxState=RXSTATE_INFO;
		}
		break;
	default:
		nRxState=RXSTATE_NOSYNC;
		break;
	}
}

//���ݽ���
BOOL CServerComm::WSNDataMessageParser(CAMMessage Msg)
{
	
	CString strSQL;
	_variant_t vSQLTemp;
	CString  strSQLTemp;
	
	int nOffset=0;//ƫ����	
	unsigned short nNodeID;	//�ڵ�ID
	unsigned short nMsgID;	//��������
	short nRSSIUpValue, nLQIUpValue, nSNRUpValue;
	short nRSSIDownValue, nLQIDownValue, nSNRDownValue;	
	short nMsgSum;			
	CString strTime;		//reportTime
	
	if(Msg.m_bytType == UP_MSG_TYPE && Msg.m_bytSubType == UP_CONFIG_SUBTYPE ) //�����������
	{
		if(!::ReadUnsignedShortFromByteArrayR(Msg.m_arryBody,nOffset,nNodeID))
		{
			return FALSE;
		}
		CString str;
		str.Format("�յ�%d�Žڵ����÷����������·��ɹ�!",nNodeID);
		((CLQ_TestbedApp*)AfxGetApp())->pdlg->AddLogText(str);
		
	}
	if(Msg.m_bytType == UP_MSG_TYPE && Msg.m_bytSubType == UP_CAMMAND_SUBTYPE ) //�����������
	{
		if(!::ReadUnsignedShortFromByteArrayR(Msg.m_arryBody,nOffset,nNodeID))
		{
			return FALSE;
		}
		CString str;
		str.Format("�յ�%d�Žڵ�������������·��ɹ�!",nNodeID);
	    ((CLQ_TestbedApp*)AfxGetApp())->pdlg->AddLogText(str);
		
	}
		
	if(Msg.m_bytType == UP_MSG_TYPE && Msg.m_bytSubType == LINK_MSG_SUBTYPE ) // ��·���԰�
    {	
		if(!::ReadUnsignedShortFromByteArrayR(Msg.m_arryBody,nOffset,nNodeID))//���õ��ã�����Ϊ����ֵ
		{
			return FALSE;
		}
		
		if(!::ReadUnsignedShortFromByteArrayR(Msg.m_arryBody,nOffset,nMsgID))//���õ��ã�����Ϊ����ֵ
		{
			return FALSE;
		}
		
		if(!::ReadShortFromByteArrayR(Msg.m_arryBody,nOffset,nRSSIDownValue))
		{
			return FALSE;
		}
		
		if(!::ReadShortFromByteArrayR(Msg.m_arryBody,nOffset,nLQIDownValue))
		{
			return FALSE;
		}
		
		if(!::ReadShortFromByteArrayR(Msg.m_arryBody,nOffset,nSNRDownValue))
		{
			return FALSE;
		}

		if(!::ReadShortFromByteArrayR(Msg.m_arryBody,nOffset,nRSSIUpValue))
		{
			return FALSE;
		}
		
		if(!::ReadShortFromByteArrayR(Msg.m_arryBody,nOffset,nLQIUpValue))
		{
			return FALSE;
		}
		
		if(!::ReadShortFromByteArrayR(Msg.m_arryBody,nOffset,nSNRUpValue))
		{
			return FALSE;
		}
		if(!::ReadShortFromByteArrayR(Msg.m_arryBody,nOffset,nMsgSum))
		{
			return FALSE;
		}		
		m_curPackets = nMsgSum;
		
		int nChannelNum = ((CLQ_TestbedApp*)AfxGetApp())->pdlg->NodeList[nNodeID];
		if (nChannelNum == -1)
		{
			return FALSE;
		}
		//����ʵʱ����
		if (((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_iSelection==0)
		{	
			((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_ctrlPlotx.GetChannel(nChannelNum).AddYNow(nRSSIUpValue);
		}
		else if (((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_iSelection==1)
		{
			((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_ctrlPlotx.GetChannel(nChannelNum).AddYNow(nLQIUpValue);
		}
		else if (((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_iSelection==2)
		{
			((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_ctrlPlotx.GetChannel(nChannelNum).AddYNow(nSNRUpValue);
		}		
		
		//�����ݱ����������
		CString  strNodeID,strMsgID,strRSSI,strLQI,strSNR,strMsgSum;
		strNodeID.Format("%d",nNodeID);
		strMsgID.Format("%d",nMsgID);
		strRSSI.Format("%d",nRSSIUpValue);
		strLQI.Format("%d",nLQIUpValue);
		strSNR.Format("%d",nSNRUpValue);
		strMsgSum.Format("%d",nMsgSum);
		
		CTime nTime=CTime::GetCurrentTime();
		CString strDate=nTime.Format("%Y-%m-%d ");
		strTime=nTime.Format("%H:%M:%S");
		strTime =strDate+strTime;
		
		
		static int nItem =0;
		((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_ctrlListPacketInfo.InsertItem(nItem,strNodeID);
		((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_ctrlListPacketInfo.SetItemText(nItem,1,strMsgID);
		((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_ctrlListPacketInfo.SetItemText(nItem,2,strRSSI);
		((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_ctrlListPacketInfo.SetItemText(nItem,3,strLQI);
		((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_ctrlListPacketInfo.SetItemText(nItem,4,strSNR);
		((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_ctrlListPacketInfo.SetItemText(nItem,5,strMsgSum);
		((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_ctrlListPacketInfo.SetItemText(nItem,6,strTime);
		((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_ctrlListPacketInfo.SendMessage(WM_VSCROLL,SB_LINERIGHT,0);
		
		if (nItem<1000)
		{
			nItem++;
		}
		else
		{
			((CLQ_TestbedApp*)AfxGetApp())->pdlg->m_ctrlListPacketInfo.DeleteAllItems();
			nItem=0;
		}
		
		UpdateData(FALSE);
		
		ADOConn m_AdoConn;
		m_AdoConn.OnInitADOConn();	
		
		/* �����Ϣ���������Ϣ*/
		
		strSQL.Format("INSERT INTO tb_PacketInfo(NodeID,MsgSeq,RSSI_Down,LQI_Down,SNR_Down,RSSI_Up,LQI_Up,SNR_Up,MsgSum,ReportTime,TestID,ScheduleID) VALUES(%d,%d,%d,%d,%d,%d,%d,%d,%d,'%s',%d,%d)",nNodeID,nMsgID,nRSSIDownValue,nLQIDownValue,nSNRDownValue,nRSSIUpValue,nLQIUpValue,nSNRUpValue,nMsgSum,strTime,m_curTestID,m_curTestScheduleID);
		try
		{			
			m_AdoConn.ExecuteSQL((_bstr_t)strSQL);			
		}
		catch (_com_error &e)
		{
			AfxMessageBox(e.Description());
			return FALSE;
		}

	}	
	return TRUE;
}

/************************************************************************/
/* �������cmdType��0 ֹͣ���ԣ�1 ��ʼ���ԣ�2���²���                 */
/************************************************************************/
BOOL CServerComm::ControlCmdToWSN(short sNodeID,BYTE cmdType)
{
	
	CAMMessage Msg;	
    Msg.m_bytType= DOWN_MSG_TYPE;
	Msg.m_bytSubType = DOWN_CAMMAND_SUBTYPE;
	
	//�ڵ�0xFFFF��ʾ���нڵ�
	WriteShortToByteArrayR(Msg.m_arryBody,sNodeID);
	//���ݰ�����
    WriteByteToByteArray(Msg.m_arryBody,cmdType);
	
	return MessageSender(Msg);
}

/************************************************************************/
/* ��������������ڵ�                                                   */
/************************************************************************/
BOOL CServerComm::ConfigCmdToWSN(short sNodeID, short pktSum, short sendPeriod,BYTE testModel)
{
	CAMMessage Msg;
	Msg.m_bytType= DOWN_MSG_TYPE;
	Msg.m_bytSubType = DOWN_CONFIG_SUBTYPE;
    
	//�ڵ�0xFFFF��ʾ���нڵ�
	WriteShortToByteArrayR(Msg.m_arryBody,sNodeID);
	//���ݰ�����
    WriteShortToByteArrayR(Msg.m_arryBody,pktSum);
	//��������
    WriteShortToByteArrayR(Msg.m_arryBody,sendPeriod);
	//̽��ģʽ
    WriteByteToByteArray(Msg.m_arryBody,testModel);

	return MessageSender(Msg);
}

/************************************************************************/
/* ��WSN������·��������̽���                                          */
/************************************************************************/
BOOL CServerComm::ActiveTestToWSN(short sNodeID,short sMsgID,short sMsgSum)
{
	CAMMessage Msg;
	Msg.m_bytType= DOWN_MSG_TYPE;
	Msg.m_bytSubType = DOWN_ACTIVETEST_SUBTYPE;
    
	//�ڵ�0xFFFF��ʾ���нڵ�
	WriteShortToByteArrayR(Msg.m_arryBody,sNodeID);
	//��Ϣ����
    WriteShortToByteArrayR(Msg.m_arryBody,sMsgID);
	//RSSI_Down
    WriteShortToByteArrayR(Msg.m_arryBody,0);
	//LQI_Down
    WriteShortToByteArrayR(Msg.m_arryBody,0);
	//SNR_Down
	WriteShortToByteArrayR(Msg.m_arryBody,0);
	//RSSI_UP
	WriteShortToByteArrayR(Msg.m_arryBody,0);
	//LQI_UP
	WriteShortToByteArrayR(Msg.m_arryBody,0);
	//SNR_UP
	WriteShortToByteArrayR(Msg.m_arryBody,0);
	//��Ϣ����
	WriteShortToByteArrayR(Msg.m_arryBody,sMsgSum);

	return MessageSender(Msg);

}


//********************************************************************
// ��������:MessageSender
//
// ����˵��:�򴮿ڷ�����Ϣ.
//
// ����˵��:
// Msg:CAMMessage�ṹ���ݰ�����
//
// ����ֵ:TRUE���ͳɹ�;FALSE����ʧ��
//********************************************************************
BOOL CServerComm::MessageSender(CAMMessage Msg)
{
	int n;
	BYTE bytOneByte;
	unsigned short nCRC;
	
	BYTE* pBuffer;
	BYTE nMsgLen=sizeof(Msg.m_bytType)+sizeof(Msg.m_bytSubType)+Msg.m_arryBody.GetSize();
	
	int nBufferLen=11+nMsgLen+2+1;
	pBuffer=new BYTE[nBufferLen];
	if(pBuffer==NULL)
	{
		return FALSE;
	}
	
	pBuffer[0]=0x7E;
	
	nCRC=0;
	
	bytOneByte=0x44;//��Ҫ���շ�����ACKȷ��֡������֡����44
	pBuffer[1]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=0x00;//ǰ׺�֣���ǰ׺����Ϊ���ݷ����͸����ͷ�
	pBuffer[2]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=0x00; //�ַ�����
	pBuffer[3]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=0xFF;//Ŀ�ĵ�ַ
	pBuffer[4]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=0xFF;
	pBuffer[5]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=0x00;//Դ��ַ
	pBuffer[6]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=0x00;
	pBuffer[7]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=(BYTE)nMsgLen;//��Ϣ����
	pBuffer[8]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=0x00; //GroupID
	pBuffer[9]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=0x10;//AMTYPE
	pBuffer[10]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=Msg.m_bytType;
	pBuffer[11]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=Msg.m_bytSubType;
	pBuffer[12]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	for(n=0;n<Msg.m_arryBody.GetSize();n++)
	{
		bytOneByte=Msg.m_arryBody[n];
		pBuffer[13+n]=bytOneByte; //�޸�
		nCRC=CRC(nCRC,bytOneByte);
	}
	
	pBuffer[nBufferLen-3]=(BYTE)(nCRC & 0x00FF);
	pBuffer[nBufferLen-2]=(BYTE)((nCRC & 0xFF00)>>8);
	pBuffer[nBufferLen-1]=0x7E;
	
	Write(pBuffer,nBufferLen);
	
	delete pBuffer;
	
	return TRUE;
}


