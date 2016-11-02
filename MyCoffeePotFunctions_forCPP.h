#ifndef CoffeePot_SimulatorFunctions_h
#define CoffeePot_SimulatorFunctions_h

#include <MockDevices2016\CoffeePot_SimulatorFunctions2016.h>

// General Control(Bits 4 to 0)

#define INITandSTAYPOWERED (1<<0) // 0x1 -- cause device to initialize (2  seconds ) and stay powerd up
#define LEDPOWER (1<<1) // 0x2 -- LED Power on
#define WATERPOWER (1<<2) // 0x4 -- water control power on
#define HEATERPOWER  (1<<3) // 0x8 -- heater power on
#define DEVICE_READY_RO ((0x10))  // 0x10 - DEVICE is ready after initialization  -- RO
#define CoffeeBit	(1<<11) //coffebit?

//LED CONTROL (Bits 15 to 12) -- W1S
#define LED_CONTROL_OFFSET 12
#define LED1 (0x1<< (LED_CONTROL_OFFSET +0))  // 0x1 LED -- 1
#define LED2 (0x1<< (LED_CONTROL_OFFSET +1))
#define LED3 (0x1<< (LED_CONTROL_OFFSET +2))
#define LED4 (0x1<< (LED_CONTROL_OFFSET +3))
#define LED5 (0x1<< (LED_CONTROL_OFFSET +4))

// function stubs


void My_DemonstrateCoffeePotAction_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[],
  unsigned short int waterLevelRequired, unsigned short int waterTemperatureRequired);

void My_DemonstrateCoffeePotAction_CPP(bool Hardwarecontrol ,COFFEEPOT_DEVICE *coffeePot_BaseAddress1,
  char uniqueCoffeePotName1[],unsigned short int waterLevelRequired1, unsigned short int waterTemperatureRequired1,
  COFFEEPOT_DEVICE *coffeePot_BaseAddress2,char uniqueCoffeePotName2[],unsigned short int waterLevelRequired2,
  unsigned short int waterTemperatureRequired2,
  COFFEEPOT_DEVICE *coffeePot_BaseAddress3,char uniqueCoffeePotName3[],unsigned short int waterLevelRequired3,
  unsigned short int waterTemperatureRequired3);



void My_MakeCoffeePot_ReadyForAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[]);

void My_WaterControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterLevelRequired);
void My_SimulateOneSecondPassing_CPP(void);
void My_HeatControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterTemperatureRequired);
void My_HeatDoubleCode_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress1, unsigned short int waterTemperatureRequired1,
		COFFEEPOT_DEVICE *coffeePot_BaseAddress2, unsigned short int waterTemperatureRequired2);


extern "C" void WaterControlCode_ASM(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterLevelRequired);
extern "C" void HeaterControlCode_ASM(COFFEEPOT_DEVICE *coffeePot_BaseAddress , unsigned short int watertemperatureRequired);


#endif
