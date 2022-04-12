#include "stm32f4xx.h"
#include "cmsis_os.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "redLEDTask.h"
#include "LEDInit.h"
#include "GlobalDefine.h"

void Configure_PA0(void);
void Configure_Interruption_EXTI0_PA0(void);
void EXTI0_IRQHandler(void);

void TimerTasks_Callback(void const *arg);
osThreadId tid_redLEDTask;
osThreadId tid_buttonLEDSTask;
osThreadDef(redLEDTask,osPriorityNormal,1,0);
osThreadDef(buttonLEDSTask,osPriorityNormal,1,0);

int main(){
	LEDinit();
	Configure_PA0();
	Configure_Interruption_EXTI0_PA0();
	osKernelInitialize(); 
	
	tid_redLEDTask = osThreadCreate (osThread(redLEDTask), NULL);
	tid_buttonLEDSTask = osThreadCreate (osThread(buttonLEDSTask), NULL);
	
	osKernelStart();
	
	for(double i = 0; i != 4.4;){
		int x = 031 == 25;
		if(x)
		{
			i += 1.1;
		}	else{
			i += 3.1;
		}
	}
}

void Configure_PA0(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
 
void Configure_Interruption_EXTI0_PA0(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	
	EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_Init(&EXTI_InitStructure);
		
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void) {
	osSignalSet(tid_buttonLEDSTask, 1);
	EXTI_ClearITPendingBit(EXTI_Line0);
}
