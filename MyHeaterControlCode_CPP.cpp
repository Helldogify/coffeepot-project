#include <stdio.h>
#include <MockDevices2016\CoffeePot_SimulatorFunctions2016.h>


#include "MyCoffeePotFunctions_forCPP.h"



void My_HeatControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterTemperatureRequired)
{
	unsigned int Temperature = CurrentTemperature_CPP(coffeePot_BaseAddress);
	while(Temperature < waterTemperatureRequired){
	coffeePot_BaseAddress -> heaterRegister = (waterTemperatureRequired); // increase heat fast
	coffeePot_BaseAddress -> heaterBoostRegister = 12; // experimentally found
	My_SimulateOneSecondPassing_CPP();
	Temperature = CurrentTemperature_CPP(coffeePot_BaseAddress);
	}
}

