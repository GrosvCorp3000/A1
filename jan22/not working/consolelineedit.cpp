#include <cstring>
#include "keys.h"
#include "console.h"
#include "consoleplus.h"
#include <cstdio>
//

void display(const char *str, int row, int col, int fieldLen)
{
	if (str==NULL) return;

	int numCharsToPrint = 0;
	int startRow = row, startCol = col, i=0;
	int strLen = std::strlen(str);
	
	//if field length is zero, the number of characters
	//to print on screen is the length of the string
	if (fieldLen==0)
		numCharsToPrint = strLen;
	
	//if the string is shorter than the field length
	//the number of characters to print is the length of the string, as well
	else if (strLen <= fieldLen) 
		numCharsToPrint = strLen;			
		

	//otherwise, the number of characters is the the same as the field length
	else 
		numCharsToPrint = fieldLen;
	
	for (i = 0; i <= numCharsToPrint; i++) 
	{
		if(columnCheck()!=1)
		{
			cio::console.setPosition(row, col + i);
			cio::console.setCharacter(str[i]);
			cio::console.setPosition(row, col + i);
			cio::console.drawCharacter();
		}
	}

	if(i<=fieldLen)
	{
		for(i; i <= fieldLen; i++)
		  {
				cio::console.setPosition(row,col+i);
				cio::console.setCharacter('\0');
				cio::console.setPosition(row, col + i);
				cio::console.drawCharacter();
		  } 
	}

	//Move the cursor back to its original position, and then set the cursor to after the last displayed character
	cio::console.setPosition(row, col + numCharsToPrint-1);
	

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
	int i=0, userKey=0, strLen = strlen(str), flag = 0;
	int totalColumns=0;

	char* tempStr;
	tempStr = new char[strLen+1];
	strcpy(tempStr,str);
	
	//if(fieldLength+col > cio::console.getCols())
	//	fieldLength=cio::console.getCols()-(col+1);

	display(str + *strOffset, row, col, fieldLength);
	
	//if the string offset is greater than the maximum length of the string,
	//set it to that that max length
	if(*strOffset > strLen - fieldLength)
		*strOffset = strLen - fieldLength;

	//if cursors position is greater than or equal to the field length, set it to field length minus 1
	if(*curPosition+col >= fieldLength+col)
		*curPosition = fieldLength+col-1;

	if(fieldLength> totalColumns)
		fieldLength=totalColumns-col;
		
	cio::console.setPosition(row, col + *curPosition);	
	//get the key pressed by the user, using the overloaded input operator
	
	do
		{

			display(str + *strOffset, row, col, fieldLength);
			cio::console.setPosition(row, col + *curPosition);
			//call display function to print out the next editable string line
			cio::console>> userKey;

	//check the key pressed by the user is usable ascii
	//Check that insert mode is true and your string length is less than the maximum,
	//If so, add the character to the string

	if(userKey >= ' ' && userKey <= '~')
			{		
			if(*insertMode==true && strLen < maxStrLength)
				{
					for(i = strLen+1; i > (*curPosition+*strOffset); i--)
						str[i] = str[i-1];
						str[*curPosition + *strOffset]=userKey;
				}
				
			else if(insertMode==false)
				{
					str[*curPosition+*strOffset]=userKey;
							
					if(*curPosition < fieldLength)
							*curPosition+=1;
					else if(strLen <=maxStrLength)
							*strOffset+=1;
				}

			//if insertMode is off, check the string is still not full,
			//overwrite the character at the current position and every other character until the user stops
			//entering ascii keys
			if(*insertMode==false && strLen+2 < maxStrLength)
				{
					str[*curPosition + *strOffset] = userKey;
					*curPosition+=1;
				}
			}
	
			//check to see if the user pressed a non-ascii usable key
			if(userKey==LEFT)
					//if you're not off the left edge of the screen and
					//if the col isn't zero, move curPosition left by one until it is THEN move offset.
					//if col = 0, and stroffset greater than 0, move the stringoffset left 1
					if(*curPosition+col > col)
						{
							*curPosition-=1; 
							cio::console.setPosition(row, *curPosition+col);
						}

					else if(*strOffset > 0)
						*strOffset-=1;
											
			//if you're not off the right edge of the screen
			//and the cursor position is not at the end of the field
			if(userKey==RIGHT)
				if(*curPosition < fieldLength)		
						{
							*curPosition+=1;
							cio::console.setPosition(row, *curPosition+col);
						}

					else if(*strOffset < strLen+1)
						*strOffset+= 1;
						
			//move cursor position to beginning of field
			// or the string offset back to zero, aka the 
			//beginning of the string if curPos is already there
			if(userKey==HOME)
				{
					*curPosition=0;
					*strOffset=0;
				}
				
			//The reverse of HOME,
			//Move to space after last character in the string
			//and/or the last space in the field
			if(userKey==END)
				{
					if((strLen - *strOffset) > fieldLength)
					{
					*curPosition=fieldLength;
					*strOffset=strLen-fieldLength;		
					}
					else
						*curPosition=strLen - *strOffset;
				}
							

			//remove the character at cursor position, shift string left
			if(userKey==DEL)
				{
					i = *strOffset + *curPosition;
					while(str[i]!='\0')
					{
						str[i] = str[i+1];
						i++;
					}
				
				}
		
			//remove character behind cursor position, shift string left
			if(userKey==BACKSPACE)
				{
					i = (*strOffset + *curPosition)-1;
					while(str[i] != '\0')
					{
						str[i] = str[i+1];
						i++;												
					}
					if(*curPosition>0)
						*curPosition-=1;
				}
				

			//turn Insert Mode on or off
			if(userKey==INSERT)
			{
				if(*insertMode==true)
					*insertMode=false;

				else if(*insertMode==false)
					*insertMode=true;
			}
			
		//If the user pushes any of the following keys (as defined by keys.h), editing function ends.
		switch(userKey)
		{
			case ENTER:
					flag=1;
					break;
			case TAB:
					flag=1;
					break;
			case UP:
					flag=1;
					break;
			case DOWN:
					flag=1;
					break;
			case PGUP:
					flag=1;
					break;
			case PGDN:
					flag=1;
					break;
			case F(1):
					flag=1;
					break;
			case F(2):
					flag=1;
					break;
			case F(3):
					flag=1;
					break;
			case F(4):
					flag=1;
					break;
			case F(5):
					flag=1;
					break;
			case F(6):
					flag=1;
					break;
			case F(7):		
					flag=1;
					break;
			case F(8):
					flag=1;
					break;
			case F(9):
					flag=1;
					break;
			case F(10):
					flag=1;
					break;
			case F(11):
					flag=1;
					break;
			case F(12):
					flag=1;
					break;

			case ESCAPE:
					strcpy(str,tempStr);
					flag=1;
					break;
				}
	}
	while(flag!=1);
	delete [] tempStr;

return userKey;
}