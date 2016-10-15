#include "MyCoffeePotFunctions.h"
#include <MockDevices2016\CoffeePot_SimulatorFunctions2016.h>
#include<stdio.h>

#define INDIVIDUAL_ASSIGNMENT_MANUAL_UPDATE          1
#define INDIVIDUAL_ASSIGNMENT_TIMER_INTERRUPT_UPDATE 0

void My_SimulateOneSecondPassing(void)
{
#if INDIVIDUAL_ASSIGNMENT_MANUAL_UPDATE
  UpdateSimulationDisplay();
#elif INDIVIDUAL_ASSIGNMENT_TIMER_INTERRUPT_UPDATE
  //DO via interrup control
#else
#error "No assignment type specified"
#endif
}

void My_DemonstrateCoffeePotAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char uniqueCoffeePotName[],
  unsigned short int waterLevelRequired, unsigned short int waterTemperatureRequired)
  {
      // start up the pot
      My_MakeCoffeePot_ReadyForAction(coffeePot_BaseAddress,uniqueCoffeePotName);

      // enable LED operation

      coffeePot_BaseAddress->controlRegister |= (LED_DISPLAY_ENABLE_BIT | USE_LED1_TO_SHOW_SYSTEM_POWEREDUP);
      My_SimulateOneSecondPassing();

      // Use LEDs to show system powered up and LEDs enabled

      coffeePot_BaseAddress->controlRegister |= (USE_LED4_TO_SHOW_SYSTEM_POWEREDUP | USE_LED1_TO_SHOW_SYSTEM_POWEREDUP);

      // enable water power -- show with LED

      coffeePot_BaseAddress->controlRegister |= WATER_ENABLE_BIT;
      My_SimulateOneSecondPassing();
      coffeePot_BaseAddress->controlRegister |= (USE_LED3_TO_SHOW_WATER_ENABLED);
      My_SimulateOneSecondPassing();

      // set water level flow rate

      coffeePot_BaseAddress-> waterInFlowRegister = waterLevelRequired;
      My_SimulateOneSecondPassing();

      // Simulate water Flowing for 10 seconds
      for (int time = 0; time < 10; time++) {
        My_SimulateOneSecondPassing();
      }
  }
