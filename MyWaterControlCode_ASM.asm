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

CC = R1 <= R5;

If !CC JUMP END_WHILE_CC;
P0 = R4;
R2 = 20; 
       B[P0 + 0x7] = R2;
       
       .extern __Z31My_SimulateOneSecondPassing_CPPv;
       CALL __Z31My_SimulateOneSecondPassing_CPPv; 
       
       R0 = R4;
       .extern __Z21CurrentWaterLevel_CPPP16COFFEEPOT_DEVICE; 
       CALL __Z21CurrentWaterLevel_CPPP16COFFEEPOT_DEVICE; 
       R1 = R0; 
       JUMP WHILE_WCC;
END_WHILE_CC:
_WaterControlCode_ASM.END:
       UNLINK; 
   R4 = [SP++]; 
   R5 = [SP++];
       RTS;
 
