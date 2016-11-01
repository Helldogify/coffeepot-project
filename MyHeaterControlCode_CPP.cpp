#include <stdio.h>
#include <MockDevices2016\CoffeePot_SimulatorFunctions2016.h>


#include "MyCoffeePotFunctions_forCPP.h"



void My_HeatControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterTemperatureRequired)
{

	unsigned int Temperature = CurrentTemperature_CPP(coffeePot_BaseAddress);
	while(Temperature < waterTemperatureRequired)
	{
	coffeePot_BaseAddress -> heaterRegister = (waterTemperatureRequired);
	coffeePot_BaseAddress -> heaterBoostRegister = 12;
	My_SimulateOneSecondPassing_CPP();
	Temperature = CurrentTemperature_CPP(coffeePot_BaseAddress);
	}

	coffeePot_BaseAddress -> heaterRegister = 0;
	coffeePot_BaseAddress -> heaterBoostRegister = 0;

}

void My_HeatDoubleCode_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress1, unsigned short int waterTemperatureRequired1,
		COFFEEPOT_DEVICE *coffeePot_BaseAddress2, unsigned short int waterTemperatureRequired2)
{
	unsigned int Temperature1 = CurrentTemperature_CPP(coffeePot_BaseAddress1);
	unsigned int Temperature2 = CurrentTemperature_CPP(coffeePot_BaseAddress2);
	while((Temperature1 < waterTemperatureRequired1*0.8)&(Temperature1 < waterTemperatureRequired1*0.8))
		{
		coffeePot_BaseAddress1 -> heaterRegister = (waterTemperatureRequired1);
		coffeePot_BaseAddress1 -> heaterBoostRegister = 10;
		coffeePot_BaseAddress2 -> heaterRegister = (waterTemperatureRequired2);
		coffeePot_BaseAddress2 -> heaterBoostRegister = 10;
		My_SimulateOneSecondPassing_CPP();
		Temperature1 = CurrentTemperature_CPP(coffeePot_BaseAddress1);
		Temperature2 = CurrentTemperature_CPP(coffeePot_BaseAddress2);
		}

}
