#include <cstring>
#include "console.h"
#include "consoleplus.h"

void display(const char *str, int row, int col, int fieldLen)
{
	if (!str) return;

	int fieldGreat = 0;
	int numCharsToPrint = 0;
	int startRow = row, startCol = col;
	int strLen = std::strlen(str);
	
	if (!fieldLen)
		numCharsToPrint = strLen;

	else if (strLen < fieldLen) 
		{
			numCharsToPrint = strLen;
			fieldGreat = 1;
		}
	else numCharsToPrint = fieldLen;
	
	for (int i = 0; i < numCharsToPrint; i++) 
	{
			cio::console.setPosition(row, col + i);
			cio::console.setCharacter(str[i]);
			cio::console.setPosition(row, col + i);
			cio::console.drawCharacter();
	}

	//if fieldLen !=0, blank the rest of the line	
	if(fieldLen=!0)
	{ 
		for(int i = 0; i < fieldLen; i++)
		  {
				cio::console.setCharacter('\0');
				cio::console.setPosition(row, col + i);
				cio::console.drawCharacter();
		  } 
	}

	//Move the cursor back to its original position, and then set the cursor to after the last displayed character
	cio::console.setPosition(row, startCol);
	cio::console.setPosition(row, col + numCharsToPrint);
	

}

//Check to see that the current column is not the final column, and set the return value to 1 if it is.
int columnCheck()
{
	int totCol=0, curCol=0, urRow=0, urCol=0, endOfScreen=0;
		
	totCol=cio::console.getCols();
	cio::console.getPosition(urRow, urCol);
	if(urCol==totCol)
		endOfScreen = 1;

	return endOfScreen;
}

int edit(char *str, int row, int col, int fieldLength, int maxStrLength, bool* insertMode, int* strOffset, int* curPosition)
{
	
	if(*strOffset > maxStrLength)
		*strOffset = maxStrLength;

	if(*strOffset==NULL)
		*strOffset = 0;

	if(*curPosition > fieldLength)
		*curPosition = fieldLength;
	
	if(*curPosition==NULL)
		*curPosition;


	return 0;
}