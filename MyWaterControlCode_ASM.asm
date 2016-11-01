#include <blackfin.h>
.section data1;
.var _dummy = 0x0000;
.var _waterlevel = 0x0000;


//#define INPAR1_R0 R0
//#define INPAR2_R1 R1
#define INPAR1_R4 R4
#define INPAR2_R5 R5
#define returnValue_R0 R0
#define baseAddress_P0 P0
#define waterlevel_R1 R1
#define temp_R2 R2


.section program;
	.global _WaterControlCode_ASM;
	
_WaterControlCode_ASM: //
[--SP] = R4; // pointer to coffeepot base address
R4 = R0;
[--SP] = R5;
R5 =R1;
LINK 20;

	.extern __Z21CurrentWaterLevel_CPPP16COFFEEPOT_DEVICE;
	CALL __Z21CurrentWaterLevel_CPPP16COFFEEPOT_DEVICE;

	R1 =R0;
WHILE_WCC:

CC = R1 <= R5;

If !CC JUMP END_WHILE_CC;
P0 = P4;
 temp_R2 = 200; 
       B[P0 + 0x7] = R2;
       .extern __Z31My_SimulateOneSecondPassing_CPPv;
       CALL __Z31My_SimulateOneSecondPassing_CPPv; 
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
 
