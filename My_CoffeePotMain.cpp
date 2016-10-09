#include <stdio.h>
#include <MockDevices2016\CoffeePotSimulatorFunctions2016.h>

void NetworkTimingFudge_USE_CCES_GUI_Delay(void){

}

#define DO_SECOND_POT false
#define CONTROL_TWO_POTS_AT_ONE_TIME false

#include "My_CoffeePotFunctions.h"

int main(void) {

  printf("Blackfin\n\n");
  printf("This dope comunputer is 'bout to start my dope coffee pot simulator \n");

  int numCoffeePots = 2;

  WHICHDISPLAY = USE_TEXT_GUI; // use this display mode at beginning
  //WHICHDISPLAY = USE_CCES_GUI;
  //WHICHDISPLAY = (WHICHDISPLAY) (USE_TEXT_GUI | USE_CCES_GUI);
  //WHICHDISPLAY = (WHICHDISPLAY) (USE_TEXT_GUI | USE_SPI_GUI);
  Init_CoffeePotSimulation(numCoffeePots, whichDisplay);

  char uniqueCoffeePotName1[] = "nixian";
  char uniqueCoffeePotName2[] = "dracaena";

//  Simulate plugging in new plug and play coffeepot controller devices into USE ports
  COFFEEPOTDEVICE *coffeePot1_BaseAddress = (COFFEEPOT_DEVICE *) NULL;
  coffeePot1_BaseAddress = Add_CoffeePotToSystem_PlgAndPlay(COFFEEPOT1, uniqueCoffeePotName1);
  MY_SIMULATEONESECONDPASSING();
  //GOING TO CALL THE CODE TO FILL A COFFEEPOT TO A DESIRED WATER LEVEL BUT NOT DO ANY HEATING
  UNSIGNED SHORT INT WATERLEVELREQUIRED1 = 200; UNSIGNED SHORT INT WATERTEMPERATUREREQUIRED1 = 0;
  MY_DEMONSTRATECOFFEEPOTACTION(coffeePot1_BaseAddress, uniqueCoffeePotName1, WATERLEVELREQUIRED1, WATERTEMPERATUREREQUIRED1);
#if DO_SECOND_POT // leave till first one works
  COFFEEPOTDEVICE *coffeePot2_BaseAddress = (COFFEEPOT_DEVICE *) NULL;
  coffeePot2_BaseAddress = Add_CoffeePotToSystem_PlgAndPlay(COFFEEPOT2, uniqueCoffeePotName2);


#endif



}
