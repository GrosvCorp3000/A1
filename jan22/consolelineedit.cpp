#include <cstring>
#include "console.h"
#include "consoleplus.h"

void display(const char *str, int row, int col, int fieldLen)
{
	if (!str) return;

	int numCharsToPrint = 0;

	int strLen = std::strlen(str);
	if (!fieldLen) numCharsToPrint = strLen;
	else if (strLen < fieldLen) numCharsToPrint = strLen;
	else numCharsToPrint = fieldLen;

	for (int i = 0; i < numCharsToPrint; i++) {
		cio::console.setPosition(row, col + i);
		cio::console.setCharacter(str[i]);
		cio::console.setPosition(row, col + i);
		cio::console.drawCharacter();
	}
	//if(fieldLen=!0)
	//{ 
	//	for(int i = 0; i < fieldLen; i++)
	//  {
	//		cio::console.setCharacter('\0');
	//		cio::console.setPosition(row, col + i);
	//		cio::console.drawCharacter();
	//	}

	// WARNINGS THIS IMPLEMENTATION IS FAR FROM COMPLETE
	// Some of the things still missing...
	// - Blank out rest of line if fieldLen != 0
	// - Do not write outside screen
	// - Probably other stuff...
	// -H
}

int edit(char *str, int row, int col, int fieldLength, int maxStrLength,
		 bool* insertMode, int* strOffset, int* curPosition)
{
	return 0;
}