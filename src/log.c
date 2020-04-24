#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "flags.h"
#include "getHex.h"

void WriteI32BHCode(FILE* f, Intel32BitHex code) {
	fprintf(f, "\nRecordLength: %u \nLoadOffset: %#X \nRecordType: %#X \nData: ", code.recordLength, code.loadOffset, code.recordType);
	for (int i = 0; i < code.recordLength; ++i) {
		fprintf(f, "%#02X ", code.data[i]);
	}
	fprintf(f, "\nCheckSum: %#X\n", code.checkSum);
}

void DisplayASMCode(Intel32BitHex code) {
	for (int i = 0; i < code.recordLength; ++i) {
		switch (code.data[i]) {
		case 0x00: printf("NOP "); break;
		case 0x01: printf("AJMP "); break;
		case 0x02: printf("LJMP "); break;
		case 0x03: printf("RR "); break;
		default: 
			break;
		}
	}
}

int main(int argc, char* argv[]) {
	FILE *fp = fopen("hextest.hex", "r");
	FILE* fw = fopen("C:\\Users\\mmurrell\\Desktop\\log.txt", "w");

	if (fp == NULL) {
		printf("ERROR! FILE NOT FOUND");
		exit(1);
	}

	Intel32BitHex code;

	char buff[255];
	while (fgets(buff, 255, fp)) {

		//Get the record length
		char rl[2];
		rl[0] = buff[1];
		rl[1] = buff[2];
		code.recordLength = charToHex8(rl);

		//Get the Load offset
		char lo[4];
		lo[0] = buff[3];
		lo[1] = buff[4];
		lo[2] = buff[5];
		lo[3] = buff[6];
		code.loadOffset = charToHex16(lo);

		//Get the record Type
		char rt[2];
		rt[0] = buff[7];
		rt[1] = buff[8];
		code.recordType = charToHex8(rt);

		//Get the data
		int start = 9;
		int end = code.recordLength * 2 + 9;

		for (int i = start, j = 0; i < end; i += 2, j++) {
			char d[2];
			d[0] = buff[i];
			d[1] = buff[i + 1];
			code.data[j] = charToHex8(d);
		}

		//Finally the checksum
		char cs[2];
		cs[0] = buff[end];
		cs[1] = buff[end + 1];
		code.checkSum = charToHex8(cs);

		//DisplayI32BHCode(code);
		WriteI32BHCode(fw, code);
		//DisplayASMCode(code);
	}

	fclose(fp);
	fclose(fw);
   	return 0;
}