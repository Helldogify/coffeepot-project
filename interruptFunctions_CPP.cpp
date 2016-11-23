#include <blackfin.h>
#include "MyCoffeePotFunctions_forCPP.h"


void INIT_CoreTimer(void)
{*pTCNTL = 0x1;
ssync();}
void SET_CoreTimer(void){
	*pTCNTL |= 0x7;ssync();
	*pTCOUNT = 0xfff;ssync();
	*pTPERIOD = 0xffffff; ssync();
	*pTSCALE = 0x3; ssync();
}
void SET_IMASK(void){
	*pIMASK = (*pIMASK & 0x001f)|0x0040;
	ssync();}
void SET_EVT_Table(void){
	*pEVT6 = &CoreTimerISRCPP;
	ssync();}

void Wait_Time_USeconds(unsigned long int delayMicroSeconds)
{for (unsigned long int count = 0; count < delayMicroSeconds; count ++ ){}}


