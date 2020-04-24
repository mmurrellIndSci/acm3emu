#pragma once
#include "branch-instructions.h"

//16bit
extern void CBZ_T1(const Instruction* ins, StateARMCortexM3* m3);

extern void CMN_REG_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void CMP_IMM_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void CMP_REG_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void CMP_REG_T2(const Instruction* ins, StateARMCortexM3* m3);

extern void IT_T1(const Instruction* ins, StateARMCortexM3* m3);

//32-bit
extern void CMN_IMM_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void CMN_REG_T2(const Instruction* ins, StateARMCortexM3* m3);
extern void CMP_IMM_T2(const Instruction* ins, StateARMCortexM3* m3);
extern void CMP_REG_T3(const Instruction* ins, StateARMCortexM3* m3);