#ifndef SUB_INSTRUCTIONS_H_
#define SUB_INSTRUCTIONS_H_

#include "../structs.h"

// 16bit
extern void RSB_Imm_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void SBC_Reg_T1(const Instruction* ins, StateARMCortexM3* m3);

extern void SUB_Imm_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void SUB_Imm_T2(const Instruction* ins, StateARMCortexM3* m3);
extern void SUB_Reg_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void SUB_SMI_T1(const Instruction* ins, StateARMCortexM3* m3);

// 32bit
extern void RSB_Imm_T2(const Instruction* ins, StateARMCortexM3* m3);
extern void RSB_Reg_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void SBC_Imm_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void SBC_Reg_T2(const Instruction* ins, StateARMCortexM3* m3);

extern void SUB_Imm_T3(const Instruction* ins, StateARMCortexM3* m3);
extern void SUB_Imm_T4(const Instruction* ins, StateARMCortexM3* m3);
extern void SUB_Reg_T2(const Instruction* ins, StateARMCortexM3* m3);

extern void SUB_SMI_T2(const Instruction* ins, StateARMCortexM3* m3);
extern void SUB_SMI_T3(const Instruction* ins, StateARMCortexM3* m3);
extern void SUB_SMR_T1(const Instruction* ins, StateARMCortexM3* m3);

#endif