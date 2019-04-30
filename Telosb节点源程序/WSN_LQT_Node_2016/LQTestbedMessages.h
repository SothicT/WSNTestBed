/****************************************************************
*文 件 名:LQTestbedMessage.h
*功能描述:链路质量测试平台的节点消息格式定义
*日    期:20150316
*作    者:liusong
*****************************************************************/
#ifndef LQT_MSG_H__
#define LQT_MSG_H__

enum 
{	
   AM_LQT_MSG_TYPE = 0x10, 		 //AM Type
   MESSAGES_SUM = 1000, 	 	 //消息总数
   SEND_INTERVAL_MS = 200, 	     //发送周期为200ms,发包频率5/s 
   CC2420CHANNEL=26,			 //信道11-26有效，默认信道设定为26
   CC2420RFPOWER=31,			 //发送功率0-31有效，默认设定为MAX=31，   
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
   
   DOWN_CONFIG_SUBTYPE = 0x01, 	  //节点配置命令
   DOWN_CAMMAND_SUBTYPE = 0x02,   //节点控制命令
   DOWN_ACTIVETEST_SUBTYPE = 0x03 //链路主动探测命令
   
};

//--------------------------上行测试数据，状态信息--------------------------//
//链路质量测试数据包消息格式定义(20byte),主动探测包/被动探测包
typedef nx_struct LQTMessage 
{
  nx_int8_t   msgtype;		//类型  
  nx_int8_t   msgsubtype;	//子类型 
  nx_int16_t  nodeid;       //节点id
  nx_int16_t  msgid; 	 	//消息包序号
  nx_int16_t  rssi_down;    //下行信号接收强度
  nx_int16_t  lqi_down;		//下行链路质量指示值
  nx_int16_t  snr_down;		//下行信噪比
  nx_int16_t  rssi_up;    	//上行信号接收强度
  nx_int16_t  lqi_up;		//上行链路质量指示值
  nx_int16_t  snr_up;		//上行信噪比
  
  nx_int16_t  msgsum;  		//消息总数
}LQTMessage;


//上行节点状态消息格式定义 (9byte)
/*
typedef  nx_struct NodeStateInfo
{
	nx_int8_t   msgtype;		      	//类型   
	nx_int8_t   msgsubtype;				//子类型
	nx_int16_t  nodeid;   				//节点id
	nx_int16_t  power;    				//功率
	nx_int16_t  channel;  				//信道
	nx_int8_t   state;    				//状态 
	
}NodeStateInfo;
*/
//----------------------------------- 上行反馈数据-------------------------------//
//配置节点命令下发成功接收上行反馈包   (3byte)
typedef  nx_struct BACK_LQT_CONFIG_SUSCESS_MSG
{
	nx_int8_t   msgtype;		      //类型
	nx_int8_t   msgsubtype;			  //子类型
	nx_int16_t  nodeid;   			  //节点id
	
}BACK_LQT_CONFIG_SUSCESS_MSG;

//测试数据包下行命令消息成功接收上行反馈包   (3byte)
typedef  nx_struct BACK_LQT_CAMMAND_SUSCESS_MSG
{
	nx_int8_t   msgtype;		      //类型	
	nx_int8_t   msgsubtype;			  //子类型
	nx_int16_t  nodeid;   			  //节点id
	
}BACK_LQT_CAMMAND_SUSCESS_MSG;


//--------------------------------- 下行命令-----------------------------------------//
//节点状态设置命令(5byte)
typedef nx_struct LQT_CAMMAND_MSG  
{
	nx_int8_t   msgtype;		      //类型 
	nx_int8_t   msgsubtype;		      //子类型  
	nx_int16_t  nodeid;			      //节点ID
	nx_int8_t   nodestate;            //节点状态 00 停止测试；01开始测试; 02重新测试
   
}LQT_CAMMAND_MSG;

//节点测试配置命令(9byte)
typedef nx_struct LQT_CONFIG_MSG 
{
	nx_int8_t   msgtype;		    //类型
	nx_int8_t   msgsubtype;			//子类型 02
	nx_int16_t  nodeid;				//节点ID 
    nx_int16_t  msgsum;				//消息总数	
	nx_int16_t  sendperiod;			//发送周期
	nx_int8_t   testmode;           //测试方式

}LQT_CONFIG_MSG;
 
#endif
