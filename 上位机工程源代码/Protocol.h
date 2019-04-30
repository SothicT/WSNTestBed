#ifndef INFINITY
#define INFINITY -65535.0
#endif
#define MAX_COMM_BUFFER_LEN				1024*2
#define MAX_SOCKET_BUFFER_LEN			1024*1024

#include <afxtempl.h>
  
//////////////////////////////////////////////////////////////////////
//
// AM协议
//
//////////////////////////////////////////////////////////////////////

class CAMMessage
{
public:
	BYTE m_bytType;				 //主类型
	BYTE m_bytSubType;			 //子类型
	CArray<BYTE,BYTE> m_arryBody;//存放数据的字节数组
	
	CAMMessage()
	{
		Reset();
	}
	
	CAMMessage(const CAMMessage& Msg)
	{
		Copy(Msg);
	}
	
	CAMMessage& operator =(const CAMMessage& Msg)
	{
		Copy(Msg);
		return *this;			
	}
	
	void Copy(const CAMMessage& Msg)
	{
		Reset();
		m_bytType=Msg.m_bytType;
		m_bytSubType=Msg.m_bytSubType;
		
		for(int n=0;n<Msg.m_arryBody.GetSize();n++)
		{
			m_arryBody.Add(Msg.m_arryBody[n]);
		}
	}
	
	void Reset()
	{
		m_bytType=0;
		m_bytSubType=0;
		m_arryBody.RemoveAll();
	}
	
	~CAMMessage()
	{
		Reset();
	}
};



enum 
{  //上行
	UP_MSG_TYPE = 0x00,
		
	LINK_MSG_SUBTYPE = 0x01,      //上行链路包
	NODESTAT_MSG_SUBTYPE = 0x02,  //上行节点状态包 
	UP_CONFIG_SUBTYPE = 0x11,  	 //配置节点命令反馈包
	UP_CAMMAND_SUBTYPE= 0x12,     //测试数据包下行命令反馈包		
	
	//下行
	DOWN_MSG_TYPE = 0x01,		
	
	DOWN_CONFIG_SUBTYPE = 0x01,   //配置命令
	DOWN_CAMMAND_SUBTYPE = 0x02,  //节点控制命令
	DOWN_ACTIVETEST_SUBTYPE = 0x03 //链路主动探测命令
};