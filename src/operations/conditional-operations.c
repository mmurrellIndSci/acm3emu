#include "../../include/operations/conditional-operations.h"

bool InITBlock(const StateARMCortexM3* m3)
{
	return m3->psr.it2 != 0;
}

bool LastInITBlock(const StateARMCortexM3* m3)
{
	return (m3->psr.it2 >> 2) == 8;
}

bool ConditionsPassed(const StateARMCortexM3* m3, uint_fast8_t conditional)
{
	uint_fast8_t cond = conditional >> 1;
	uint_fast8_t c0 = conditional & 1;
	bool result = false;
	switch (cond){
	case 0: result = (m3->psr.z == 1); break;
	case 1: result = (m3->psr.c == 1); break;
	case 2: result = (m3->psr.n == 1); break;
	case 3:	result = (m3->psr.v == 1); break;
	case 4: result = ((m3->psr.c == 1) && (m3->psr.z == 0)); break;
	case 5: result = (m3->psr.n == m3->psr.v); break;
	case 6: result = ((m3->psr.n == m3->psr.v) && (m3->psr.z == 0)); break;
	case 7: result = true;
	default: break;}

	if ((c0 == 1) && (conditional != 15))
		result = !result;
	return result;
}

void DisplayConditional(uint_fast8_t c) {
	switch (c)
	{
	case EQ:printf("EQ"); break;
	case NE:printf("NE"); break;
	case CS:printf("CS"); break;
	case CC:printf("CC"); break;
	case MI:printf("MI"); break;
	case PL:printf("PL"); break;
	case VS:printf("VS"); break;
	case VC:printf("VC"); break;
	case HI:printf("HI"); break;
	case LS:printf("LS"); break;
	case GE:printf("GE"); break;
	case LT:printf("LT"); break;
	case GT:printf("GT"); break;
	case LE:printf("LE"); break;
	case AL:printf("AL"); break;
	default:break;
	}
}