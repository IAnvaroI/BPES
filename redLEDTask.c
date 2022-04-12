#include "cmsis_os.h"
#include "GlobalDefine.h"
#include "LEDInit.h"

void redLEDTask(void const *argument){
	while(1){
		LEDSwitchOnOff(RED, ON);
		osDelay(1000);
		LEDSwitchOnOff(RED, OFF);
		osDelay(1000);
	}
}

void buttonLEDSTask(void const *argument){
	osEvent evt;
	while(1){
		evt = osSignalWait(0x0001,osWaitForever);
		if(evt.status == osEventSignal){
			LEDSwitchOnOff(GREEN, ON);
			osDelay(500);
			LEDSwitchOnOff(ORANGE, ON);
			osDelay(500);
			LEDSwitchOnOff(RED, ON);
			osDelay(500);
			LEDSwitchOnOff(BLUE, ON);
			osDelay(500);
					
			LEDSwitchOnOff(GREEN, OFF);
			LEDSwitchOnOff(ORANGE, OFF);
			LEDSwitchOnOff(RED, OFF);
			LEDSwitchOnOff(BLUE, OFF);
			osDelay(500);		
		}
	}
}
