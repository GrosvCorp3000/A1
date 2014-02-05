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
	if(urCol < 0)
		endOfScreen = -1;

	return endOfScreen;
}

int edit(char *str, int row, int col, int fieldLength, int maxStrLength, bool* insertMode, int* strOffset, int* curPosition)
{
	int userKey=0;
	int returnValue = 0;
	int strLen = strlen(str);
	int flag = 0;
	
	char* tempStr;
	tempStr = new char[strLen+1];
	strcpy(tempStr,str);

	//get the key pressed by the user, using the overloaded input operator
	cio::console>> userKey;

	//if the string offset is greater than the maximum length of the string,
	//set it to that that max length
	if(*strOffset > maxStrLength)
		*strOffset = maxStrLength;
	
	//if string offset is NULL, set it to zero
	if(*strOffset==NULL)
		*strOffset = 0;

	//if cursors position is greater than or equal to the field length, set it to field length minus 1
	if(*curPosition >= fieldLength)
		*curPosition = fieldLength-1;
	
		
	//put loop here
	if(userKey >= ' ' && userKey <= '~')
	{
	}

	else if(userKey==ESCAPE)
	{
		returnValue = ESCAPE;
		strcpy(str,tempStr);
	}

	else
	{
	//If the user pushes any of the following keys (as defined by keys.h), editing ends.
		switch(userKey)
		{
			case ENTER:
				{
					returnValue=ENTER;
					flag = 1;
					break;
				}

			case TAB:
				{
					returnValue=TAB;
					flag=1;
					break;
				}

			case UP:
					returnValue=UP;
					flag=1;
					break;

			case DOWN:
				{	
					returnValue=DOWN;
					flag=1;
					break;
				}

			case PGUP:
				{
					returnValue=PGUP;
					flag=1;
					break;				
				}

			case PGDN:
				{
					returnValue=PGDN;
					flag=1;
					break;
				}

			case F(1):
				{
					returnValue=F(1);
					flag=1;
					break;
				}

			case F(2):
				{
					returnValue=F(2);
					flag=1;
					break;
				}

			case F(3):
				{
					returnValue=F(3);
					flag=1;
					break;
				}

			case F(4):
				{
					returnValue=F(4);
					flag=1;
					break;
				}

			case F(5):
				{
					returnValue=F(5);
					flag=1;
					break;
				}

			case F(6):
				{
					returnValue=F(6);
					flag=1;
					break;
				}
			case F(7):
				{
					returnValue=F(7);
					flag=1;
					break;
				}

			case F(8):
				{
					returnValue=F(8);
					flag=1;
					break;
				}
			case F(9):
				{
					returnValue=F(9);
					flag=1;
					break;
				}

			case F(10):
				{
					returnValue=F(10);	
					flag=1;
					break;
				}

			case F(11):
				{
					returnValue=F(11);
					flag=1;
					break;
				}

			case F(12):
				{
					returnValue=F(12);
					flag=1;
					break;
				}
		}

		if(userKey==LEFT && columnCheck()!=1 && (*curPosition < fieldLength-2))
		{
			cio::console.setPosition(row, col +1);
			if(*strOffset < maxStrLength)
				*strOffset += 1;
		}

		if(userKey==RIGHT && columnCheck()!=-1 && (*curPosition > *str))
		{
			cio::console.setPosition(row, col-1);
			if(*strOffset < 0);
				*strOffset -= 1;
		}

		if(userKey==HOME)
		{
			int startCol = *str-*curPosition;	
			cio::console.setPosition(row, startCol);
			if(*strOffset !=0)
				*strOffset=0;
		}

		if(userKey==END)
		{
			
			cio::console.setPosition(row,);
			if(*strOffset < maxStrLength)
				*strOffset = maxStrLength;
			
		}

	}		

	return returnValue;
}