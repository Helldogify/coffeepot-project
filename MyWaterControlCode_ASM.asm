#include <blackfin.h>
.section data1;
.var _waterlevel = 0x0000;


.section program;
	.global _WaterControlCode_ASM;
	
_WaterControlCode_ASM: //
[--SP] = R4;
R4 = R0;  // pointer to coffeepot base address saved in R4
[--SP] = R5;
R5 =R1; //waterlevel needed stored in R5
LINK 20;


	.extern __Z21CurrentWaterLevel_CPPP16COFFEEPOT_DEVICE;
	CALL __Z21CurrentWaterLevel_CPPP16COFFEEPOT_DEVICE;

	R1 =R0; // R1 = current water level
WHILE_WCC:

CC = R1 <= R5; // Check if waterlevel is at the required amount 

If !CC JUMP END_WHILE_CC; // if it is stop adding water
P0 = R4; //P0 = coffeepot baseregister
R2 = 20; // amount of water to be added per second (determined through experiments)
       B[P0 + 0x7] = R2; // water inflow register = 20
       
       .extern __Z31My_SimulateOneSecondPassing_CPPv;
       CALL __Z31My_SimulateOneSecondPassing_CPPv; //wait a 1 second
       
       R0 = R4; // put base register value in current water level function argument
       .extern __Z21CurrentWaterLevel_CPPP16COFFEEPOT_DEVICE; 
       CALL __Z21CurrentWaterLevel_CPPP16COFFEEPOT_DEVICE; 
       R1 = R0; // update current water level
       JUMP WHILE_WCC;
END_WHILE_CC:
_WaterControlCode_ASM.END:
       UNLINK; 
   R4 = [SP++]; 
   R5 = [SP++];
       RTS;
 
