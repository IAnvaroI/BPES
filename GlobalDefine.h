#include "stm32f4xx.h"

typedef enum{
	GREEN = ((uint16_t)0x1000),
	ORANGE = ((uint16_t)0x2000),
	RED = ((uint16_t)0x4000),
	BLUE = ((uint16_t)0x8000)
} LEDCOLOURS;

#define ON 1
#define OFF 0
