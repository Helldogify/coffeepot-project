#ifndef CoffeePot_SimulatorFunctions_h
#define CoffeePot_SimulatorFunctions_h

#ifndef _CPP_
  #error("Youcant use this include file inside ASM code - Build an ASM version of the file");
#endif

// General Control(Bits 4 to 0)

#define INITandSTAYPOWERED (1<<0) // 0x1 -- cause device to initialize (2  seconds ) and stay powerd up
#define LEDPOWER (1<<1) // 0x2 -- LED Power on
#define WATERPOWER (1<<2) // 0x4 -- water control power on
#define HEATERPOWER  (1<<3) // 0x8 -- heater power on
#define DEVICE_REQDY_RO ((0x10))  // 0x10 - DEVICE is ready after initialization  -- RO

//LED CONTROL (Bits 15 to 12) -- W1S
#define LED_CONTROL_OFFSET 12
#define LED1 (1<< (1 LED_CONTROL_OFFSET +0))  // 0x1 LED -- 1
#define LED1 (1<< (1 LED_CONTROL_OFFSET +1))
#define LED1 (1<< (1 LED_CONTROL_OFFSET +2))
#define LED1 (1<< (1 LED_CONTROL_OFFSET +3))
#define LED1 (1<< (1 LED_CONTROL_OFFSET +4))

// funciton stubs

void My_SimulateOneSecondPassing();
void My_DemonstrateCoffeePotAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[],
  unsigned short int waterLevelRequired, unsigned short int waterTemperatureRequired);

void MyDemonstrateCoffePotsAction(hardwareControl,
    coffeePot_BaseAddress, uniqueCoffeePotName, WATERLEVELREQUIRED, WATERTEMPERATUREREQUIRED,
    coffeePot_BaseAddress, uniqueCoffeePotName, WATERLEVELREQUIRED, WATERTEMPERATUREREQUIRED);

void My_MakeCoffeePot_ReadyForAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[]);

void My_WaterControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short in waterLevelRequired);
void My_SimulateOneSecondPassing_CPP(void);


#endif
