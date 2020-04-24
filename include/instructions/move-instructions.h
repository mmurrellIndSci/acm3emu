#ifndef MOVE_INSTRUCTIONS_H_
#define MOVE_INSTRUCTIONS_H_

#include "../structs.h"


/*Move (immediate) writes an immediate value to the destination register. 
It can optionally update the condition flags based on the value.*/

//16bit intructions
extern void MOV_Imm_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void MOV_Reg_T2(const Instruction* ins, StateARMCortexM3* m3);

//32bit instructions
extern void MOV_Imm_T2(const Instruction* ins, StateARMCortexM3* m3);
extern void MOV_Imm_T3(const Instruction* ins, StateARMCortexM3* m3);

extern void MOVT(const Instruction* ins, StateARMCortexM3* m3);

extern void MVN_Imm_T1(const Instruction* ins, StateARMCortexM3* m3);

#endif // !MOVE_INSTRUCTIONS_H_
