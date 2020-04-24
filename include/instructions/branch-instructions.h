#ifndef BRANCH_INSTRUCTIONS_H_
#define BRANCH_INSTRUCTIONS_H_

#include "../structs.h"

/* Branch causes a branch to a target address */

//16 bit
extern void B_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void B_T2(const Instruction* ins, StateARMCortexM3* m3);
extern void BLX_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void BX_T1(const Instruction* ins, StateARMCortexM3* m3);


//32 bit
extern void B_T3(const Instruction* ins, StateARMCortexM3* m3);
extern void B_T4(const Instruction* ins, StateARMCortexM3* m3);
extern void BL_T1(const Instruction* ins, StateARMCortexM3* m3);
extern void TBB_T1(const Instruction* ins, StateARMCortexM3* m3);
#endif // !BRANCH_INSTRUCTIONS_H_
