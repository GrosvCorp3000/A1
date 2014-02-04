#include <cstring>
#include "keys.h"
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
	int userKey=0;
	int returnValue = 0;
	int strLen = strlen(str);

	//get the key pressed by the user, using the overloaded input operator
	cio::console>> userKey;

	//if the string offset is greater than the maximum length of the string,
	//set it to that that max length
	if(*strOffset > strLen)
		*strOffset = strLen;


	//if string offset is NULL, set it to zero
	if(*strOffset==NULL)
		*strOffset = 0;

	//
	if(*curPosition > fieldLength)
		*curPosition = fieldLength;
	
	if(*curPosition==NULL)
		*curPosition;

	char* tempStr = NULL;
		char* tempStr = new char[strLen+1];
		strcpy(tempStr,str);
	
	//If the user pushes any of the following keys (as defined by keys.h), editing ends.
	switch(userKey)
	{
		case ENTER:
			returnValue=ENTER;
			break;

		case TAB:
			returnValue=TAB;
			break;

		case UP:
			returnValue=UP;
			break;

		case DOWN:
			returnValue=DOWN;
			break;

		case PGUP:
			returnValue=PGUP;
			break;				

		case PGDN:
			returnValue=PGDN;
			break;

		case F(1):
			returnValue=F(1);
			break;

		case F(2):
			returnValue=F(2);
			break;

		case F(3):
			returnValue=F(3);
			break;

		case F(4):
			returnValue=F(4);
			break;

		case F(5):
			returnValue=F(5);
			break;

		case F(6):
			returnValue=F(6);
			break;

		case F(7):
			returnValue=F(7);
			break;

		case F(8):
			returnValue=F(8);
			break;

		case F(9):
			returnValue=F(9);
			break;

		case F(10):
			returnValue=F(10);
			break;

		case F(11):
			returnValue=F(11);
			break;

		case F(12):
			returnValue=F(12);
			break;
	}
	
	if(userKey==ESCAPE)
		returnValue = ESCAPE;
		strcpy(str,tempStr);

	return returnValue;
}