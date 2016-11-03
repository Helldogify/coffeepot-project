#include <blackfin.h>
.section data1;
.var _temperature = 0x0000;
.section program;
	.global _HeaterControlCode_ASM;
	
_HeaterControlCode_ASM: //
[--SP] = R4; 
R4 = R0; // pointer to coffeepot base address saved in R4
[--SP] = R5;
R5 =R1; //water temperature required saved in R5
LINK 20;

	.extern __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE;
	CALL __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE;
 
	R1 =R0; // store current temperature in R1
WHILE_WCC:

CC = R1 <= R5;  // check current water temperature

If !CC JUMP END_WHILE_CC; // run loop till watertemperature is at required temperature
P0 = R4; // base register value to P0
R2 = 80; // temperature register value = 80 (experimental)
R3 = 12; // heater booster register value 12 (experimental)
       B[P0 + 0x06] = R2; // set temperature reg value
       B[P0 + 0x08] = R3; // set heater booster value
       .extern __Z31My_SimulateOneSecondPassing_CPPv;
       CALL __Z31My_SimulateOneSecondPassing_CPPv; 
       
       R0 = R4; // put base register value into first argument register
       
       .extern __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE; 
       CALL __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE;  // find current temperature
       R1 = R0; // update current temperature value
       JUMP WHILE_WCC;
END_WHILE_CC:
_HeaterControlCode_ASM.END:
       UNLINK; 
   R4 = [SP++]; 
   R5 = [SP++];
       RTS;
 
