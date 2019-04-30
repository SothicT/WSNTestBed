
#include "LQTestbedMessages.h"  

module BaseMoteC {

  uses interface Intercept as RadioIntercept;
  uses interface CC2420Packet;  
  uses interface Read<uint16_t> as ReadNoiseFloor; //���ڶ�ȡ��������/��������
  
} 

implementation 
{

  uint16_t getRSSI(message_t *msg);
  uint16_t getLQI(message_t *msg);
  uint16_t noiseFloor; 

  event bool RadioIntercept.forward(message_t *msg, void *payload,uint8_t len)
  {
       
      LQTMessage *LQTMsg = (LQTMessage*) payload;
     	if (len == sizeof(LQTMessage)&& (LQTMsg->msgtype == UP_MSG_TYPE && LQTMsg->msgsubtype == LINK_MSG_SUBTYPE ))//�жϳ��Ⱥ���Ϣ�����Ƿ�Ϊ��·����������Ϣ
     	{	   
			    LQTMsg->rssi_up = getRSSI(msg);  
			    LQTMsg->lqi_up =  getLQI(msg);  
			    call ReadNoiseFloor.read();
				LQTMsg->snr_up =LQTMsg->rssi_up - noiseFloor;
		}  
       return TRUE;
  }

  uint16_t getRSSI(message_t *msg)
  {
    return (uint16_t) (call CC2420Packet.getRssi(msg))-45;//����uint8_tת��Ϊuint16_t
  }
  
	uint16_t getLQI(message_t *msg)
	{
		return (uint16_t) call CC2420Packet.getLqi(msg);
	}
	
	//��noise floor
  event void ReadNoiseFloor.readDone(error_t error, uint16_t data) 
  {
  
  	int8_t noise_val=(int8_t)(((data-0x7F)&0xFF)-45);
  	noiseFloor = noise_val;
  
  }
}
