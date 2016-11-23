#include "MyCoffeePotFunctions_forCPP.h"
#include <MockDevices2016\CoffeePot_SimulatorFunctions2016.h>
#include <GPIO2016/ADSP_GPIO_Interface.h>
#include<stdio.h>



void My_SimulateOneSecondPassing_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress)
{
if (coffeePot_BaseAddress == 0)
{
	UpdateSimulationDisplay();
	}
else
{
	unsigned char current = Read_LED_GPIOInterface();
	if(coffeePot_BaseAddress->waterInFlowRegister != 0) {Write_LED_GPIOInterface(Read_LED_GPIOInterface() | 0x10);}
	else {Write_LED_GPIOInterface(Read_LED_GPIOInterface() & ~(0x10));}
	if(coffeePot_BaseAddress->heaterRegister != 0) {Write_LED_GPIOInterface(Read_LED_GPIOInterface() | (0x20));}
	else {Write_LED_GPIOInterface(Read_LED_GPIOInterface() & ~(0x20));}
	if((CurrentTemperature_CPP(coffeePot_BaseAddress) <= 100)&&(CurrentTemperature_CPP(coffeePot_BaseAddress) >= 80)&&(CurrentWaterLevel_CPP(coffeePot_BaseAddress) >= 80)) {Write_LED_GPIOInterface(Read_LED_GPIOInterface() | 0x08);}
	else{Write_LED_GPIOInterface(Read_LED_GPIOInterface() & ~(0x08));}
//	UpdateSimulationDisplay();
}
}



void My_DemonstrateCoffeePotAction_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[],
  unsigned short int waterLevelRequired, unsigned short int waterTemperatureRequired)
  {

	My_MakeCoffeePot_ReadyForAction(coffeePot_BaseAddress,uniqueCoffeePotName);
	 INIT_CoreTimer();

	SET_CoreTimer();
	SET_IMASK();

	SET_EVT_Table();
	unsigned int waterlevel = CurrentWaterLevel_CPP(coffeePot_BaseAddress);
	unsigned int watertemp = CurrentTemperature_CPP(coffeePot_BaseAddress);
	unsigned short int currentsw = Read_Input_GPIOInterface();
	coffeePot_BaseAddress->heaterBoostRegister = 15;
	while(1)
	{
	 waterlevel = CurrentWaterLevel_CPP(coffeePot_BaseAddress);
	 watertemp = CurrentTemperature_CPP(coffeePot_BaseAddress);
	 currentsw = Read_Input_GPIOInterface()>>8;
	 if(((currentsw & 0x01) == 0x01)){
	 			coffeePot_BaseAddress->waterInFlowRegister = 20;
	 			}
	 if((((currentsw>>1) & 0x01) == 0x01)){
	 					coffeePot_BaseAddress->heaterBoostRegister = 15;
	 					coffeePot_BaseAddress->heaterRegister = (waterTemperatureRequired);
	 					}

	 My_SimulateOneSecondPassing_CPP(coffeePot_BaseAddress);
	}


  }
void My_MakeCoffeePot_ReadyForAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[] )
{

	coffeePot_BaseAddress->controlRegister |= 0x1;
	My_SimulateOneSecondPassing_CPP(0);
	unsigned int regval = coffeePot_BaseAddress->controlRegister&0xff;
	while (regval != 0x11 )
	{
		My_SimulateOneSecondPassing_CPP(0);
		regval = coffeePot_BaseAddress->controlRegister&0xff;
	}

	Init_LED_GPIOInterface();
	Write_LED_GPIOInterface(Read_LED_GPIOInterface()&0x00);
	coffeePot_BaseAddress->controlRegister |= LEDPOWER;
	coffeePot_BaseAddress->controlRegister |= WATERPOWER;
	coffeePot_BaseAddress->controlRegister |= HEATERPOWER;

	My_SimulateOneSecondPassing_CPP(0);
}

void My_DemonstrateCoffeePotAction_CPP(bool Hardwarecontrol ,COFFEEPOT_DEVICE *coffeePot_BaseAddress1,
  char uniqueCoffeePotName1[],unsigned short int waterLevelRequired1, unsigned short int waterTemperatureRequired1,
  COFFEEPOT_DEVICE *coffeePot_BaseAddress2,char uniqueCoffeePotName2[],unsigned short int waterLevelRequired2,
  unsigned short int waterTemperatureRequired2,
  COFFEEPOT_DEVICE *coffeePot_BaseAddress3,char uniqueCoffeePotName3[],unsigned short int waterLevelRequired3,
  unsigned short int waterTemperatureRequired3)
{




	My_MakeCoffeePot_ReadyForAction(coffeePot_BaseAddress1,uniqueCoffeePotName1);
	My_MakeCoffeePot_ReadyForAction(coffeePot_BaseAddress2,uniqueCoffeePotName2);
	My_MakeCoffeePot_ReadyForAction(coffeePot_BaseAddress3,uniqueCoffeePotName3);


	unsigned int waterlevel1 = CurrentWaterLevel_CPP(coffeePot_BaseAddress1);
	unsigned int watertemp1 = CurrentTemperature_CPP(coffeePot_BaseAddress1);


	unsigned int waterlevel2 = CurrentWaterLevel_CPP(coffeePot_BaseAddress2);
	unsigned int watertemp2 = CurrentTemperature_CPP(coffeePot_BaseAddress2);

	unsigned int waterlevel3 = CurrentWaterLevel_CPP(coffeePot_BaseAddress3);
	unsigned int watertemp3 = CurrentTemperature_CPP(coffeePot_BaseAddress3);

	while(1)
	{
		waterlevel1 = CurrentWaterLevel_CPP(coffeePot_BaseAddress1);
		waterlevel2 =CurrentWaterLevel_CPP(coffeePot_BaseAddress2);
		waterlevel3 =CurrentWaterLevel_CPP(coffeePot_BaseAddress3);
		watertemp2 = CurrentTemperature_CPP(coffeePot_BaseAddress2);
		watertemp1 = CurrentTemperature_CPP(coffeePot_BaseAddress1);
		watertemp3 = CurrentTemperature_CPP(coffeePot_BaseAddress3);

		if(waterlevel1<(0.9*waterLevelRequired1)){
			coffeePot_BaseAddress1->waterInFlowRegister = 20;
			}
		if(waterlevel2<(0.9*waterLevelRequired2)){
					coffeePot_BaseAddress2->waterInFlowRegister = 20;
			}
		if(waterlevel3<(0.9*waterLevelRequired3)){
					coffeePot_BaseAddress3->waterInFlowRegister = 20;
			}
		if(watertemp1<(0.9*waterTemperatureRequired1)){
					coffeePot_BaseAddress1->heaterBoostRegister = 15;
					coffeePot_BaseAddress1->heaterRegister = (waterTemperatureRequired1);
					}
		if(watertemp2<(0.9*waterTemperatureRequired2)){
					coffeePot_BaseAddress2->heaterBoostRegister = 15;
					coffeePot_BaseAddress2->heaterRegister = (waterTemperatureRequired2);
					}
		if(watertemp3<(0.9*waterTemperatureRequired3)){
					coffeePot_BaseAddress3->heaterBoostRegister = 15;
					coffeePot_BaseAddress3->heaterRegister = (waterTemperatureRequired2);
					}
		My_SimulateOneSecondPassing_CPP(coffeePot_BaseAddress1);
		My_SimulateOneSecondPassing_CPP(coffeePot_BaseAddress2);
		My_SimulateOneSecondPassing_CPP(coffeePot_BaseAddress3);
	}




}

#pragma interrupt
void CoreTimerISRCPP(void)
{
//	*pTCNTL &= 0xfffffff7;
 UpdateSimulationDisplay();
int x = 10;



}

