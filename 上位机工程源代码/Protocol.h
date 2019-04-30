#ifndef INFINITY
#define INFINITY -65535.0
#endif
#define MAX_COMM_BUFFER_LEN				1024*2
#define MAX_SOCKET_BUFFER_LEN			1024*1024

#include <afxtempl.h>
  
//////////////////////////////////////////////////////////////////////
//
// AMЭ��
//
//////////////////////////////////////////////////////////////////////

class CAMMessage
{
public:
	BYTE m_bytType;				 //������
	BYTE m_bytSubType;			 //������
	CArray<BYTE,BYTE> m_arryBody;//������ݵ��ֽ�����
	
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
{  //����
	UP_MSG_TYPE = 0x00,
		
	LINK_MSG_SUBTYPE = 0x01,      //������·��
	NODESTAT_MSG_SUBTYPE = 0x02,  //���нڵ�״̬�� 
	UP_CONFIG_SUBTYPE = 0x11,  	 //���ýڵ��������
	UP_CAMMAND_SUBTYPE= 0x12,     //�������ݰ������������		
	
	//����
	DOWN_MSG_TYPE = 0x01,		
	
	DOWN_CONFIG_SUBTYPE = 0x01,   //��������
	DOWN_CAMMAND_SUBTYPE = 0x02,  //�ڵ��������
	DOWN_ACTIVETEST_SUBTYPE = 0x03 //��·����̽������
};