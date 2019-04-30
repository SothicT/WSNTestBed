/****************************************************************
*�� �� ��:LQTestbedMessage.h
*��������:��·��������ƽ̨�Ľڵ���Ϣ��ʽ����
*��    ��:20150316
*��    ��:liusong
*****************************************************************/
#ifndef LQT_MSG_H__
#define LQT_MSG_H__

enum 
{	
   AM_LQT_MSG_TYPE = 0x10, 		 //AM Type
   MESSAGES_SUM = 1000, 	 	 //��Ϣ����
   SEND_INTERVAL_MS = 200, 	     //��������Ϊ200ms,����Ƶ��5/s 
   CC2420CHANNEL=26,			 //�ŵ�11-26��Ч��Ĭ���ŵ��趨Ϊ26
   CC2420RFPOWER=31,			 //���͹���0-31��Ч��Ĭ���趨ΪMAX=31��   
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
   
   DOWN_CONFIG_SUBTYPE = 0x01, 	  //�ڵ���������
   DOWN_CAMMAND_SUBTYPE = 0x02,   //�ڵ��������
   DOWN_ACTIVETEST_SUBTYPE = 0x03 //��·����̽������
   
};

//--------------------------���в������ݣ�״̬��Ϣ--------------------------//
//��·�����������ݰ���Ϣ��ʽ����(20byte),����̽���/����̽���
typedef nx_struct LQTMessage 
{
  nx_int8_t   msgtype;		//����  
  nx_int8_t   msgsubtype;	//������ 
  nx_int16_t  nodeid;       //�ڵ�id
  nx_int16_t  msgid; 	 	//��Ϣ�����
  nx_int16_t  rssi_down;    //�����źŽ���ǿ��
  nx_int16_t  lqi_down;		//������·����ָʾֵ
  nx_int16_t  snr_down;		//���������
  nx_int16_t  rssi_up;    	//�����źŽ���ǿ��
  nx_int16_t  lqi_up;		//������·����ָʾֵ
  nx_int16_t  snr_up;		//���������
  
  nx_int16_t  msgsum;  		//��Ϣ����
}LQTMessage;


//���нڵ�״̬��Ϣ��ʽ���� (9byte)
/*
typedef  nx_struct NodeStateInfo
{
	nx_int8_t   msgtype;		      	//����   
	nx_int8_t   msgsubtype;				//������
	nx_int16_t  nodeid;   				//�ڵ�id
	nx_int16_t  power;    				//����
	nx_int16_t  channel;  				//�ŵ�
	nx_int8_t   state;    				//״̬ 
	
}NodeStateInfo;
*/
//----------------------------------- ���з�������-------------------------------//
//���ýڵ������·��ɹ��������з�����   (3byte)
typedef  nx_struct BACK_LQT_CONFIG_SUSCESS_MSG
{
	nx_int8_t   msgtype;		      //����
	nx_int8_t   msgsubtype;			  //������
	nx_int16_t  nodeid;   			  //�ڵ�id
	
}BACK_LQT_CONFIG_SUSCESS_MSG;

//�������ݰ�����������Ϣ�ɹ��������з�����   (3byte)
typedef  nx_struct BACK_LQT_CAMMAND_SUSCESS_MSG
{
	nx_int8_t   msgtype;		      //����	
	nx_int8_t   msgsubtype;			  //������
	nx_int16_t  nodeid;   			  //�ڵ�id
	
}BACK_LQT_CAMMAND_SUSCESS_MSG;


//--------------------------------- ��������-----------------------------------------//
//�ڵ�״̬��������(5byte)
typedef nx_struct LQT_CAMMAND_MSG  
{
	nx_int8_t   msgtype;		      //���� 
	nx_int8_t   msgsubtype;		      //������  
	nx_int16_t  nodeid;			      //�ڵ�ID
	nx_int8_t   nodestate;            //�ڵ�״̬ 00 ֹͣ���ԣ�01��ʼ����; 02���²���
   
}LQT_CAMMAND_MSG;

//�ڵ������������(9byte)
typedef nx_struct LQT_CONFIG_MSG 
{
	nx_int8_t   msgtype;		    //����
	nx_int8_t   msgsubtype;			//������ 02
	nx_int16_t  nodeid;				//�ڵ�ID 
    nx_int16_t  msgsum;				//��Ϣ����	
	nx_int16_t  sendperiod;			//��������
	nx_int8_t   testmode;           //���Է�ʽ

}LQT_CONFIG_MSG;
 
#endif
