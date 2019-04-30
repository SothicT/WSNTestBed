/****************************************************************
*文 件 名:SensorStationC.nc
*功能描述:感知节点的组件文件
*日    期:20150316
*作    者:liusong
*****************************************************************/
#include <Timer.h>
#include "LQTestbedMessages.h"

module SensorStationC
{
    uses interface Boot;
    uses interface Leds;  
    uses interface Timer<TMilli> as MsgTimer; //消息包时钟
 
    uses interface Packet;
    uses interface AMPacket;
    uses interface AMSend;
    uses interface Receive;
    uses interface SplitControl as AMControl;
    uses interface CC2420Packet;
    uses interface CC2420Config;
	uses interface Read<uint16_t> as ReadNoiseFloor; //用于读取背景噪声/本底噪声
}

implementation
{
    bool busy = FALSE;
	message_t pkt;
	
 	int16_t  msgSum = MESSAGES_SUM; 			//发送的消息总数，默认值为MESSAGES_SUM
 	int16_t  sendPeriod= SEND_INTERVAL_MS;    //发送周期，默认值为SEND_INTERVAL_MS
	int16_t  msgcounter = 1; 				    //消息计数器
 	bool 	 sendingflag = FALSE;				//发送标识，默认不发送
	int8_t   nodestate = 0x00;        			//节点状态,00暂停测试
    int8_t   testmode = 0x00;                   //链路探测方式,00主动探测，01被动探测
	
	
	uint16_t getRSSI(message_t *msg);
	uint16_t getLQI(message_t *msg);
	
	uint16_t noiseFloor = 0; 	
		
    event void Boot.booted()
	{
		call Leds.led0On();						
		call Leds.led1Off();
		call Leds.led2Off();    
		
        call AMControl.start();  
		
    }    
    

    event void AMSend.sendDone(message_t *msg, error_t error)
	{
		    if (&pkt == msg) 
			{
		       busy = FALSE;	//发送成功，节点空闲		     
		    }		 
    }

    event void CC2420Config.syncDone(error_t error)
	{
    }

    event void AMControl.startDone(error_t error)
	{
        if (error == SUCCESS)
		{
          call CC2420Config.setChannel(CC2420CHANNEL);  	//设置通信信道
          call CC2420Config.sync();	  
    	}
    }

    event void AMControl.stopDone(error_t error)
	{
        call Leds.led0Toggle();		//发送完毕后，LED0闪烁
    }

    event void MsgTimer.fired() 
	{       
		if( msgcounter <= msgSum && sendingflag)
		{
			LQTMessage *tempmsg = (LQTMessage *)call AMSend.getPayload(&pkt,sizeof(LQTMessage)); 	
			tempmsg->msgtype = UP_MSG_TYPE;
			tempmsg->msgsubtype = LINK_MSG_SUBTYPE;		
			tempmsg->nodeid = TOS_NODE_ID;  
			tempmsg->msgid = msgcounter;
			tempmsg->msgsum = msgSum; 			
			tempmsg->rssi_down = 0;
			tempmsg->lqi_down = 0;
			tempmsg->rssi_down = 0;
			
			if(!busy)
		   	{
		   		call CC2420Packet.setPower(&pkt,CC2420RFPOWER);				//设置发送功率 
				if(call AMSend.send(AM_BROADCAST_ADDR, &pkt, sizeof(LQTMessage))==SUCCESS)
				{ 
				    busy = TRUE;
				    call Leds.led1Toggle();  
				    if( msgcounter == msgSum) 
		            {
						sendingflag = FALSE;

		            }		       
				        msgcounter++; 
				}
		    }		     
		} 	 	  	
    }

  
 event  message_t* Receive.receive(message_t* msg, void* payload, uint8_t len)
 {
 		LQT_CAMMAND_MSG*  cammandpkt = (LQT_CAMMAND_MSG*)payload;
 		LQT_CONFIG_MSG*   configpkt = (LQT_CONFIG_MSG*)payload;	
		LQTMessage* 	  testpkt = (LQTMessage*)payload;
			
		//收到的是节点控制命令并反馈			
        if (( TOS_NODE_ID == cammandpkt->nodeid || 0xFFFF == cammandpkt->nodeid )&& len == sizeof(LQT_CAMMAND_MSG)) 
        {	
			BACK_LQT_CAMMAND_SUSCESS_MSG* backCammandPkt = (BACK_LQT_CAMMAND_SUSCESS_MSG *)call AMSend.getPayload(&pkt,sizeof(BACK_LQT_CAMMAND_SUSCESS_MSG)); 	
            backCammandPkt->msgtype = UP_MSG_TYPE;
			backCammandPkt->msgsubtype = UP_CAMMAND_SUBTYPE;
			backCammandPkt->nodeid = TOS_NODE_ID; 
			call AMSend.send(AM_BROADCAST_ADDR, &pkt, sizeof(BACK_LQT_CAMMAND_SUSCESS_MSG));
			
			call Leds.led2Toggle(); //蓝光闪烁，表示收到下发命令  
            nodestate= cammandpkt->nodestate;        
			
        	if(nodestate == 0x00) 	  	
       	    {
       	 		sendingflag = FALSE;  	//暂停测试  
       	    }
       	    else if(nodestate == 0x01)
       	    {
       	    	sendingflag = TRUE;  	//开始测试
       	    }
			else					  	
			{
				sendingflag = TRUE; 
				msgcounter = 1; 		//重新测试				
			}		
		}  
		//收到的是测试配置命令并反馈
        if( ( TOS_NODE_ID == configpkt->nodeid || 0xFFFF == configpkt->nodeid )&& len == sizeof(LQT_CONFIG_MSG)) 
        {
			//反馈配置节点命令接受成功
			BACK_LQT_CONFIG_SUSCESS_MSG* backConfigPkt = (BACK_LQT_CONFIG_SUSCESS_MSG *)call AMSend.getPayload(&pkt,sizeof(BACK_LQT_CONFIG_SUSCESS_MSG)); 
            backConfigPkt->msgtype = UP_MSG_TYPE;
			backConfigPkt->msgsubtype = UP_CONFIG_SUBTYPE;
			backConfigPkt->nodeid = TOS_NODE_ID;  
			call AMSend.send(AM_BROADCAST_ADDR, &pkt, sizeof(BACK_LQT_CONFIG_SUSCESS_MSG));
				
			call Leds.led2Toggle();  //蓝光闪烁，表示收到下发命令  
			msgSum = configpkt->msgsum; 
			testmode = configpkt->testmode;
			sendPeriod = configpkt->sendperiod;
			call MsgTimer.stop();
			if(testmode == 0x01)//被动探测
			{
				//根据配置发包频率设定时钟								
				call MsgTimer.startPeriodic(sendPeriod); 
			}		
        }  
        
		//收到的是主动链路质量探测包
		if( ( TOS_NODE_ID == testpkt->nodeid || 0xFFFF == testpkt->nodeid )&& len == sizeof(LQTMessage)) 
		{	
			LQTMessage* uptestpkt = (LQTMessage*)call AMSend.getPayload(&pkt,sizeof(LQTMessage)); 
			call Leds.led1Toggle();   //绿光闪烁，表示发送链路探测包
			uptestpkt->msgtype = UP_MSG_TYPE;
			uptestpkt->msgsubtype = LINK_MSG_SUBTYPE;
			uptestpkt->nodeid = TOS_NODE_ID; 
			uptestpkt->msgid = testpkt->msgid;
			uptestpkt->msgsum = testpkt->msgsum;
			
			uptestpkt->rssi_down = getRSSI(msg);
			uptestpkt->lqi_down = getLQI(msg);
			call ReadNoiseFloor.read();	
			uptestpkt->snr_down = uptestpkt->rssi_down - noiseFloor;		
			uptestpkt->rssi_up = 0;
			uptestpkt->lqi_up = 0;
			uptestpkt->snr_up = 0;
			
			call AMSend.send(AM_BROADCAST_ADDR, &pkt, sizeof(LQTMessage));
		}
					
        return msg;
  }
  
  uint16_t getRSSI(message_t *msg)
  {
       return (uint16_t) (call CC2420Packet.getRssi(msg))-45;//类型uint8_t转换为uint16_t
  }
  
  uint16_t getLQI(message_t *msg)
  {
	   return (uint16_t) call CC2420Packet.getLqi(msg);
  }
	
	//求noise floor
  event void ReadNoiseFloor.readDone(error_t error, uint16_t data) 
  {
  	 int8_t noise_val=(int8_t)(((data-0x7F)&0xFF)-45);
  	 noiseFloor = noise_val;
  }
  
}

 