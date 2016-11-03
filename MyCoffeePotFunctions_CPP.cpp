#include "MyCoffeePotFunctions_forCPP.h"
#include <MockDevices2016\CoffeePot_SimulatorFunctions2016.h>
#include<stdio.h>

#define INDIVIDUAL_ASSIGNMENT_MANUAL_UPDATE          1
#define INDIVIDUAL_ASSIGNMENT_TIMER_INTERRUPT_UPDATE 0

void My_SimulateOneSecondPassing_CPP(void)
{
#if INDIVIDUAL_ASSIGNMENT_MANUAL_UPDATE
  UpdateSimulationDisplay();
#elif INDIVIDUAL_ASSIGNMENT_TIMER_INTERRUPT_UPDATE
  //DO via interrupt control+

#else
#error "No assignment type specified"
#endif
}

void My_DemonstrateCoffeePotAction_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[],
  unsigned short int waterLevelRequired, unsigned short int waterTemperatureRequired)
  {

	// start up the pot

	My_MakeCoffeePot_ReadyForAction(coffeePot_BaseAddress,uniqueCoffeePotName);

      // fill with water
      WaterControlCode_ASM(coffeePot_BaseAddress,waterLevelRequired);
	  HeaterControlCode_ASM(coffeePot_BaseAddress,waterTemperatureRequired);
		unsigned int waterlevel = CurrentWaterLevel_CPP(coffeePot_BaseAddress);
		unsigned int temperature = CurrentTemperature_CPP(coffeePot_BaseAddress);


		while(1)
		{
			if(waterlevel> (waterLevelRequired*0.9)){break;}
			coffeePot_BaseAddress-> waterInFlowRegister = 50;
			My_SimulateOneSecondPassing_CPP();
			coffeePot_BaseAddress -> heaterRegister = (waterTemperatureRequired);
			coffeePot_BaseAddress -> heaterBoostRegister = 15;
			temperature = CurrentTemperature_CPP(coffeePot_BaseAddress);

			My_SimulateOneSecondPassing_CPP();

			waterlevel = CurrentWaterLevel_CPP(coffeePot_BaseAddress);
			if(waterlevel> (waterLevelRequired*0.9)){break;}
		}
		coffeePot_BaseAddress -> controlRegister = 0;

  }
void My_MakeCoffeePot_ReadyForAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[] )
{
	coffeePot_BaseAddress->controlRegister |= 0x1;
	My_SimulateOneSecondPassing_CPP();
	unsigned int regval = coffeePot_BaseAddress->controlRegister&0xff;
	while (regval != 0x11 )
	{
		My_SimulateOneSecondPassing_CPP();
		regval = coffeePot_BaseAddress->controlRegister&0xff;
	}


	coffeePot_BaseAddress->controlRegister |= LEDPOWER;
	coffeePot_BaseAddress->controlRegister |= WATERPOWER;
	coffeePot_BaseAddress->controlRegister |= HEATERPOWER;

	My_SimulateOneSecondPassing_CPP();
}

void My_DemonstrateCoffeePotAction_CPP(bool Hardwarecontrol ,COFFEEPOT_DEVICE *coffeePot_BaseAddress1,
  char uniqueCoffeePotName1[],unsigned short int waterLevelRequired1, unsigned short int waterTemperatureRequired1,
  COFFEEPOT_DEVICE *coffeePot_BaseAddress2,char uniqueCoffeePotName2[],unsigned short int waterLevelRequired2,
  unsigned short int waterTemperatureRequired2,
  COFFEEPOT_DEVICE *coffeePot_BaseAddress3,char uniqueCoffeePotName3[],unsigned short int waterLevelRequired3,
  unsigned short int waterTemperatureRequired3)
{
	// start coffee Pots
	My_MakeCoffeePot_ReadyForAction(coffeePot_BaseAddress1,uniqueCoffeePotName1);
	My_MakeCoffeePot_ReadyForAction(coffeePot_BaseAddress2,uniqueCoffeePotName2);
	My_MakeCoffeePot_ReadyForAction(coffeePot_BaseAddress3,uniqueCoffeePotName3);
	
	// find and store current water and temperature values for all pots
	unsigned int waterlevel1 = CurrentWaterLevel_CPP(coffeePot_BaseAddress1);
	unsigned int watertemp1 = CurrentTemperature_CPP(coffeePot_BaseAddress1);
	unsigned int waterlevel2 = CurrentWaterLevel_CPP(coffeePot_BaseAddress2);
	unsigned int watertemp2 = CurrentTemperature_CPP(coffeePot_BaseAddress2);
	unsigned int waterlevel3 = CurrentWaterLevel_CPP(coffeePot_BaseAddress3);
	unsigned int watertemp3 = CurrentTemperature_CPP(coffeePot_BaseAddress3);
	
	// start control Loop
	while(1)
	{	// update status variables for coffepots (1, 2& 3)
		waterlevel1 = CurrentWaterLevel_CPP(coffeePot_BaseAddress1);
		waterlevel2 =CurrentWaterLevel_CPP(coffeePot_BaseAddress2);
		waterlevel3 =CurrentWaterLevel_CPP(coffeePot_BaseAddress3);
		watertemp2 = CurrentTemperature_CPP(coffeePot_BaseAddress2);
		watertemp1 = CurrentTemperature_CPP(coffeePot_BaseAddress1);
		watertemp3 = CurrentTemperature_CPP(coffeePot_BaseAddress3);
		
		// if the water level is below 90% of required amount add in water. 
		//Water amount determined experimentally through many overflows
		if(waterlevel1<(0.9*waterLevelRequired1)){coffeePot_BaseAddress1->waterInFlowRegister = 20;}
		if(waterlevel2<(0.9*waterLevelRequired2)){coffeePot_BaseAddress2->waterInFlowRegister = 20;}
		if(waterlevel3<(0.9*waterLevelRequired3)){coffeePot_BaseAddress3->waterInFlowRegister = 20;}
		
		// If the water temperature falls below 90% of required amount increase heat
		// Heater  and heater boost register values determined experimentally through many melted pots and overflows
		if(watertemp1<(0.9*waterTemperatureRequired1)){
					coffeePot_BaseAddress1->heaterBoostRegister = 15;
					coffeePot_BaseAddress1->heaterRegister = (waterTemperatureRequired1);}
		if(watertemp2<(0.9*waterTemperatureRequired2)){
					coffeePot_BaseAddress2->heaterBoostRegister = 15;
					coffeePot_BaseAddress2->heaterRegister = (waterTemperatureRequired2);}
		if(watertemp3<(0.9*waterTemperatureRequired3)){
					coffeePot_BaseAddress3->heaterBoostRegister = 15;
					coffeePot_BaseAddress3->heaterRegister = (waterTemperatureRequired2);}
		// Update Time to see if coffee is still good physics still in effect
		My_SimulateOneSecondPassing_CPP();}
}


void Moment_Silence_For_All_Lost_Pots(void)
{
	for(int i = 0; i < 60 ; i++)
	{My_SimulateOneSecondPassing_CPP();}
}







