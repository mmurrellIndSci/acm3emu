#ifndef BIT_SHIFT_INSTRUCTIONS_H_
#define BIT_SHIFT_INSTRUCTIONS_H_

#include "../structs.h"

//16bit
extern void LSL_Imm_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void LSL_Reg_T1(const Instruction* ins, StateARMCortexM3* m3);

extern void LSR_Imm_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void LSR_Reg_T1(const Instruction* ins, StateARMCortexM3* m3);

extern void ASR_Imm_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void ASR_Reg_T1(const Instruction* ins, StateARMCortexM3* m3);


//32bit
extern void LSL_Imm_T2(const Instruction* ins, StateARMCortexM3* m3);
extern void LSL_Reg_T2(const Instruction* ins, StateARMCortexM3* m3);

extern void LSR_Imm_T2(const Instruction* ins, StateARMCortexM3* m3);
extern void LSR_Reg_T2(const Instruction* ins, StateARMCortexM3* m3);

extern void ASR_Imm_T2(const Instruction* ins, StateARMCortexM3* m3);
extern void ASR_Reg_T2(const Instruction* ins, StateARMCortexM3* m3);

#endif // !BIT_SHIFT_INSTRUCTIONS_H_
