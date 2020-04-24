#include "charToHex.h"
#include "../structs.h"

int getHex(FILE* fp, const char* buff, Intel32BitHex* code) {

	if (fgets(buff, 255, fp)) {
		//Get the record length
		char rl[2];
		rl[0] = buff[1];
		rl[1] = buff[2];
		code->recordLength = charToHex8(rl);

		//Get the Load offset
		char lo[4];
		lo[0] = buff[3];
		lo[1] = buff[4];
		lo[2] = buff[5];
		lo[3] = buff[6];
		code->loadOffset = charToHex16(lo);

		//Get the record Type
		char rt[2];
		rt[0] = buff[7];
		rt[1] = buff[8];
		code->recordType = charToHex8(rt);

		//Get the data
		int start = 9;
		int end = code->recordLength * 2 + 9;

		for (int i = start, j = 0; i < end; i += 2, j++) {
			char d[2];
			d[0] = buff[i];
			d[1] = buff[i + 1];
			code->data[j] = charToHex8(d);
		}

		//Finally the checksum
		char cs[2];
		cs[0] = buff[end];
		cs[1] = buff[end + 1];
		code->checkSum = charToHex8(cs);

		return 1;
	}
	else return 0;
}