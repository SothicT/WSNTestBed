/****************************************************************
*文 件 名:SensorStationAppC.nc
*功能描述:感知节点的组件配置文件
*日    期:20150316
*作    者:liusong
*****************************************************************/

#include "LQTestbedMessages.h"  

configuration SensorStationAppC{
}
implementation{
    components MainC,LedsC;
    components SensorStationC as App;
    components new TimerMilliC() as MsgTimer;

    components ActiveMessageC;
    components new AMSenderC(AM_LQT_MSG_TYPE);
    components new AMReceiverC(AM_LQT_MSG_TYPE);
    components CC2420ActiveMessageC; 
    components CC2420ControlC;
    
    App.Packet->AMSenderC;
    App.AMPacket->AMSenderC;
    App.AMSend->AMSenderC;
    App.Receive->AMReceiverC;
    App.AMControl->ActiveMessageC;
    App.Boot->MainC;
    App.Leds->LedsC;
    App.MsgTimer->MsgTimer;

    App.CC2420Packet -> CC2420ActiveMessageC;
    App.CC2420Config -> CC2420ControlC;
	App.ReadNoiseFloor->CC2420ControlC.ReadRssi;
}