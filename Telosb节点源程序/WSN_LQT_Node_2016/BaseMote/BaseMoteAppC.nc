
#include "LQTestbedMessages.h"  
#include "message.h"

configuration BaseMoteAppC {
} 
implementation {

  components BaseStationC; 
  components BaseMoteC as App;
  components CC2420ActiveMessageC;
  components CC2420ControlC;
  
  App -> CC2420ActiveMessageC.CC2420Packet;
  
  App.ReadNoiseFloor->CC2420ControlC.ReadRssi;
  
  App.RadioIntercept -> BaseStationC.RadioIntercept[AM_LQT_MSG_TYPE];
  
  
}
