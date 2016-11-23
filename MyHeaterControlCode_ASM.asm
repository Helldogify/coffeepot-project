#include <blackfin.h>
.section data1;
.var _dummy = 0x0000;
.var _temperature = 0x0000;


//#define INPAR1_R0 R0
//#define INPAR2_R1 R1
#define INPAR1_R4 R4
#define INPAR2_R5 R5
#define returnValue_R0 R0
#define baseAddress_P0 P0
#define waterlevel_R1 R1
#define temp_R2 R2


.section program;
	.global _HeaterControlCode_ASM;
	
_HeaterControlCode_ASM: //
[--SP] = R4; // pointer to coffeepot base address
R4 = R0;
[--SP] = R5;
R5 =R1;
LINK 20;

	.extern __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE;
	CALL __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE;

	R1 =R0;
WHILE_WCC:

CC = R1 <= R5;

If !CC JUMP END_WHILE_CC;
P0 = R4;
R2 = 80; 
R3 = 12;
       B[P0 + 0x06] = R2;
       B[P0 + 0x08] = R3;
       R0 = P0;
       .extern __Z31My_SimulateOneSecondPassing_CPPP16COFFEEPOT_DEVICE;
       CALL __Z31My_SimulateOneSecondPassing_CPPP16COFFEEPOT_DEVICE; 
       
       R0 = R4;
       
       .extern __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE; 
       CALL __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE; 
       R1 = R0; 
       JUMP WHILE_WCC;
END_WHILE_CC:
 R2 = 0;
 R3 = 0;
 B[P0 + 0x6] = R2;
 B[P0 + 0x8] = R3;
_HeaterControlCode_ASM.END:
       UNLINK; 
   R4 = [SP++]; 
   R5 = [SP++];
       RTS;
 
