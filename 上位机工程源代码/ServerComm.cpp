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

BOOL CServerComm::Open(CWnd* pNotifyWnd,		//通知窗口句柄
					   UINT  nPort,				//串口号
					   UINT  nBaud,				//波特率
					   char  chParity,			// parity 
					   UINT  nDataBits,			//数据位 
					   UINT  nStopBits,			//停止位
					   DWORD dwCommEvents,		//串口事件如EV_RXCHAR,EV_CTS等
					   UINT  nWriteBufferMaxSize)	//写缓存大小
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

//串口事件的消息响应函数
void CServerComm::OnRxCharEvent(BYTE bytData)
{
	
	//对串口接收到的数据包进行解包处理,并将已处理的数据交给上层应用作进一步处理
	int n;
	CString strSQL;
	
	static BYTE pRxData[MAX_COMM_BUFFER_LEN];//串口接收数据
	static int nRxSize=0;//用于记录总共收到了多少字节
	static int nRxState=RXSTATE_NOSYNC;//用于状态转换
	static unsigned short nRxRunningCRC=0;//用于计算数据CRC值
	static unsigned short nRxReceiveCRC=0;//用于存放数据包中的CRC值
	
	switch (nRxState)
	{
	case RXSTATE_NOSYNC: 
		if(bytData==HDLC_FLAG_BYTE)//剔除7E，且未放入PRxData[]中
		{
			nRxSize=0;
			nRxRunningCRC=0;
			nRxState=RXSTATE_PROTO;//将状态转换至协议帧类型
		}
		break;
		
	case RXSTATE_PROTO://协议帧处理过程
		if(bytData==HDLC_FLAG_BYTE)
		{
			break;
		}
		nRxRunningCRC=CRC(nRxRunningCRC,bytData);//开始计算CRC
		nRxState=RXSTATE_INFO;//串口帧内容
		break;
		
	case RXSTATE_INFO:
		if(bytData==HDLC_CTLESC_BYTE) //接收的字节为7D，转向转义字节处理状态
		{
			nRxState=RXSTATE_ESC;
		}
		else if(bytData==HDLC_FLAG_BYTE)//帧末同步字
		{
			if(nRxSize>=2) 
			{
				//如果不是第一个7e
				nRxReceiveCRC=(pRxData[(nRxSize-1)]&0xFF);//计算接收到的数据的CRC
				nRxReceiveCRC=(nRxReceiveCRC<<8)|(pRxData[(nRxSize-2)]&0xFF);
				if(nRxReceiveCRC==nRxRunningCRC)
				{
					//CRC校验正确,解包完成,交给上层应用作进一步处理
					//去掉包头的8个字节和CRC的2个字节,共10个字节.
					//例如:(7E 45 -不计)(00 FF FF FF FF 04 00 02 -8个字节) 00 0D 24 6B 00 00 (98 06 -2个字节的CRC校验值)(7E -不计)
					if(nRxSize-10>=0)//完整数据帧 //上行包中最短的payload长度为9个字节
					{
						
						/* 消息分发 */
						BYTE bytOneByte;
						
						CAMMessage Msg;
						//截取消息字段字节
						
						//消息类型和子类型
						//消息类型 0X0002，00表示上行；子类型02状态数据包
						Msg.m_bytType=pRxData[8]; 
						Msg.m_bytSubType=pRxData[9];
						
						CString strMsgBodyItem="";
						CString strMsgBody="";
						
						for(n=0;n<nRxSize-10;n++)
						{
							bytOneByte=pRxData[10+n]; 
							Msg.m_arryBody.Add(bytOneByte);//存储至Msg结构体中
							
							strMsgBodyItem="";
							::ByteToHex(strMsgBodyItem,bytOneByte);
							strMsgBody+=strMsgBodyItem;
						}					
						//消息分发，由于在链路质量中只考虑单跳的链路质量，且类型比较单一，只需解析即可
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
		//转义字节或结束帧同步字
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
			bytData=bytData^0x20; // 7D->7D5D的还原,7D跳过,5D->7D
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

//数据解析
BOOL CServerComm::WSNDataMessageParser(CAMMessage Msg)
{
	
	CString strSQL;
	_variant_t vSQLTemp;
	CString  strSQLTemp;
	
	int nOffset=0;//偏移量	
	unsigned short nNodeID;	//节点ID
	unsigned short nMsgID;	//发送序列
	short nRSSIUpValue, nLQIUpValue, nSNRUpValue;
	short nRSSIDownValue, nLQIDownValue, nSNRDownValue;	
	short nMsgSum;			
	CString strTime;		//reportTime
	
	if(Msg.m_bytType == UP_MSG_TYPE && Msg.m_bytSubType == UP_CONFIG_SUBTYPE ) //配置命令反馈包
	{
		if(!::ReadUnsignedShortFromByteArrayR(Msg.m_arryBody,nOffset,nNodeID))
		{
			return FALSE;
		}
		CString str;
		str.Format("收到%d号节点配置反馈，命令下发成功!",nNodeID);
		((CLQ_TestbedApp*)AfxGetApp())->pdlg->AddLogText(str);
		
	}
	if(Msg.m_bytType == UP_MSG_TYPE && Msg.m_bytSubType == UP_CAMMAND_SUBTYPE ) //控制命令反馈包
	{
		if(!::ReadUnsignedShortFromByteArrayR(Msg.m_arryBody,nOffset,nNodeID))
		{
			return FALSE;
		}
		CString str;
		str.Format("收到%d号节点命令反馈，命令下发成功!",nNodeID);
	    ((CLQ_TestbedApp*)AfxGetApp())->pdlg->AddLogText(str);
		
	}
		
	if(Msg.m_bytType == UP_MSG_TYPE && Msg.m_bytSubType == LINK_MSG_SUBTYPE ) // 链路测试包
    {	
		if(!::ReadUnsignedShortFromByteArrayR(Msg.m_arryBody,nOffset,nNodeID))//引用调用，可作为返回值
		{
			return FALSE;
		}
		
		if(!::ReadUnsignedShortFromByteArrayR(Msg.m_arryBody,nOffset,nMsgID))//引用调用，可作为返回值
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
		//更新实时数据
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
		
		//向数据表中添加数据
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
		
		/* 向包信息表中添加信息*/
		
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
/* 控制命令，cmdType：0 停止测试，1 开始测试，2重新测试                 */
/************************************************************************/
BOOL CServerComm::ControlCmdToWSN(short sNodeID,BYTE cmdType)
{
	
	CAMMessage Msg;	
    Msg.m_bytType= DOWN_MSG_TYPE;
	Msg.m_bytSubType = DOWN_CAMMAND_SUBTYPE;
	
	//节点0xFFFF表示所有节点
	WriteShortToByteArrayR(Msg.m_arryBody,sNodeID);
	//数据包总数
    WriteByteToByteArray(Msg.m_arryBody,cmdType);
	
	return MessageSender(Msg);
}

/************************************************************************/
/* 发送配置命令给节点                                                   */
/************************************************************************/
BOOL CServerComm::ConfigCmdToWSN(short sNodeID, short pktSum, short sendPeriod,BYTE testModel)
{
	CAMMessage Msg;
	Msg.m_bytType= DOWN_MSG_TYPE;
	Msg.m_bytSubType = DOWN_CONFIG_SUBTYPE;
    
	//节点0xFFFF表示所有节点
	WriteShortToByteArrayR(Msg.m_arryBody,sNodeID);
	//数据包总数
    WriteShortToByteArrayR(Msg.m_arryBody,pktSum);
	//发送周期
    WriteShortToByteArrayR(Msg.m_arryBody,sendPeriod);
	//探测模式
    WriteByteToByteArray(Msg.m_arryBody,testModel);

	return MessageSender(Msg);
}

/************************************************************************/
/* 向WSN发送链路质量主动探测包                                          */
/************************************************************************/
BOOL CServerComm::ActiveTestToWSN(short sNodeID,short sMsgID,short sMsgSum)
{
	CAMMessage Msg;
	Msg.m_bytType= DOWN_MSG_TYPE;
	Msg.m_bytSubType = DOWN_ACTIVETEST_SUBTYPE;
    
	//节点0xFFFF表示所有节点
	WriteShortToByteArrayR(Msg.m_arryBody,sNodeID);
	//消息序列
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
	//消息总数
	WriteShortToByteArrayR(Msg.m_arryBody,sMsgSum);

	return MessageSender(Msg);

}


//********************************************************************
// 方法名称:MessageSender
//
// 方法说明:向串口发送消息.
//
// 参数说明:
// Msg:CAMMessage结构数据包内容
//
// 返回值:TRUE发送成功;FALSE发送失败
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
	
	bytOneByte=0x44;//需要接收方发送ACK确认帧的数据帧类型44
	pBuffer[1]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=0x00;//前缀字，将前缀字作为内容发发送给发送方
	pBuffer[2]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=0x00; //分发类型
	pBuffer[3]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=0xFF;//目的地址
	pBuffer[4]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=0xFF;
	pBuffer[5]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=0x00;//源地址
	pBuffer[6]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=0x00;
	pBuffer[7]=bytOneByte;
	nCRC=CRC(nCRC,bytOneByte);
	
	bytOneByte=(BYTE)nMsgLen;//消息长度
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
		pBuffer[13+n]=bytOneByte; //修改
		nCRC=CRC(nCRC,bytOneByte);
	}
	
	pBuffer[nBufferLen-3]=(BYTE)(nCRC & 0x00FF);
	pBuffer[nBufferLen-2]=(BYTE)((nCRC & 0xFF00)>>8);
	pBuffer[nBufferLen-1]=0x7E;
	
	Write(pBuffer,nBufferLen);
	
	delete pBuffer;
	
	return TRUE;
}


