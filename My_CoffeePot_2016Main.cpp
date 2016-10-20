#include <stdio.h>
#include <MockDevices2016\CoffeePot_SimulatorFunctions2016.h>
#include "CoffeePot_2016Main.h"
#include "MyCoffeePotFunctions_forCPP.h"
void NetworkTimingFudge_USE_CCES_GUI_Delay(void){
// check the lecutres for this
}

#define DO_SECOND_POT true
#define CONTROL_TWO_POTS_AT_ONE_TIME true

#include "MyCoffeePotFunctions_forCPP.h"

int main(void) {

  printf("Blackfin\n\n");
  printf("This computer is starting my coffee pot simulator \n");

  int numCoffeePots = 2;

  //WHICHDISPLAY whichDisplay = USE_TEXT_GUI; // use this display mode at beginning
 // WHICHDISPLAY whichDisplay= USE_CCES_GUI;
  WHICHDISPLAY whichDisplay= (WHICHDISPLAY) (USE_TEXT_GUI | USE_CCES_GUI);
  //WHICHDISPLAY whichDisplay= (WHICHDISPLAY) (USE_TEXT_GUI | USE_SPI_GUI);
  Init_CoffeePotSimulation(numCoffeePots, whichDisplay);

  char uniqueCoffeePotName1[] = "nixian";
  char uniqueCoffeePotName2[] = "dracaena";

//  Simulate plugging in new plug and play coffeepot controller devices into USE ports
  COFFEEPOT_DEVICE *coffeePot1_BaseAddress = (COFFEEPOT_DEVICE *) NULL;
  coffeePot1_BaseAddress = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOT1, uniqueCoffeePotName1);
  My_SimulateOneSecondPassing_CPP();
  //GOING TO CALL THE CODE TO FILL A COFFEEPOT TO A DESIRED WATER LEVEL BUT NOT DO ANY HEATING

 // My_DemonstrateCoffeePotAction_CPP(coffeePot1_BaseAddress, uniqueCoffeePotName1, waterlevelrequired1, watertemperaturerequired1);
#if DO_SECOND_POT // leave till first one works
//fix as well since changes were done
  COFFEEPOT_DEVICE *coffeePot2_BaseAddress = (COFFEEPOT_DEVICE *) NULL;
  coffeePot2_BaseAddress = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOT2, uniqueCoffeePotName2);
  My_SimulateOneSecondPassing_CPP();
  unsigned short int waterlevelrequired1 = 310;
  unsigned short int watertemperaturerequired1 = 100;
  unsigned short int waterlevelrequired2 = 300;
  unsigned short int watertemperaturerequired2 = 100;

 // My_DemonstrateCoffeePotAction_CPP(coffeePot2_BaseAddress, uniqueCoffeePotName2, waterlevelrequired2, watertemperaturerequired2);
#endif
#if CONTROL_TWO_POTS_AT_ONE_TIME

  bool HardwareControl = false;
   My_DemonstrateCoffeePotAction_CPP(HardwareControl , coffeePot1_BaseAddress, uniqueCoffeePotName1, waterlevelrequired1, watertemperaturerequired1,coffeePot2_BaseAddress, uniqueCoffeePotName2, waterlevelrequired2, watertemperaturerequired2);
#endif
return 0;
}
