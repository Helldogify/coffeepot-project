#include <stdio.h>
#include <MockDevices2016\CoffeePot_SimulatorFunctions2016.h>
#include "CoffeePot_2016Main.h"
#include "MyCoffeePotFunctions_forCPP.h"
void NetworkTimingFudge_USE_CCES_GUI_Delay(void){
// check the lecutres for this
}

#define DO_SECOND_POT false
#define CONTROL_TWO_POTS_AT_ONE_TIME false

#include "My_CoffeePotFunctions.h"

int main(void) {

  printf("Blackfin\n\n");
  printf("This computer is starting my coffee pot simulator \n");

  int numCoffeePots = 2;

  WHICHDISPLAY whichDisplay = USE_TEXT_GUI; // use this display mode at beginning
  //WHICHDISPLAY whichDisplay= USE_CCES_GUI;
  //WHICHDISPLAY whichDisplay= (WHICHDISPLAY) (USE_TEXT_GUI | USE_CCES_GUI);
  //WHICHDISPLAY whichDisplay= (WHICHDISPLAY) (USE_TEXT_GUI | USE_SPI_GUI);
  Init_CoffeePotSimulation(numCoffeePots, whichDisplay);

  char uniqueCoffeePotName1[] = "nixian";
  char uniqueCoffeePotName2[] = "dracaena";

//  Simulate plugging in new plug and play coffeepot controller devices into USE ports
  COFFEEPOTDEVICE *coffeePot1_BaseAddress = (COFFEEPOT_DEVICE *) NULL;
  coffeePot1_BaseAddress = Add_CoffeePotToSystem_PlgAndPlay(COFFEEPOT1, uniqueCoffeePotName1);
  MY_SIMULATEONESECONDPASSING();
  //GOING TO CALL THE CODE TO FILL A COFFEEPOT TO A DESIRED WATER LEVEL BUT NOT DO ANY HEATING
  unsigned short int waterlevelrequired1 = 200; unsigned short int watertemperaturerequired1 = 0;
  My_DemonstrateCoffeePotAction(coffeePot1_BaseAddress, uniqueCoffeePotName1, waterlevelrequired1, watertemperaturerequired1);
#if DO_SECOND_POT // leave till first one works
//fix as well since changes were done
  COFFEEPOT_DEVICE *coffeePot2_BaseAddress = (COFFEEPOT_DEVICE *) NULL;
  coffeePot2_BaseAddress = Add_CoffeePotToSystem_PlgAndPlay(COFFEEPOT2, uniqueCoffeePotName2);
  MY_SIMULATEONESECONDPASSING();

  unsigned short int WATERLEVELREQUIRED2 = 400; unsigned short in WATERTEMPERATUREREQUIRED2 = 80;
  My_DemonstrateCoffeePotAction(coffeePot2_BaseAddress, uniqueCoffeePotName2, WATERLEVELREQUIRED2, WATERTEMPERATUREREQUIRED2);
#endif
#if CONTROL_TWO_POTS_AT_ONE_TIME
//Example call to control 2 coffeepots at the same time
//question to be answered during Individual Assignemnt 1
//How does the overloaded call(not the code) get handled when c++ becomes assembly code becomes machine code
//answered
//it get name mangled

  bool hardwareControl = false;

#endif
return 0;
}
