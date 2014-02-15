#include <cstring>
#include "keys.h"
#include "console.h"
#include "consoleplus.h"

void display(const char *str, int row, int col, int fieldLen)
{
	if (str==NULL) return;

	int numCharsToPrint = 0;
	int i=0;
	int strLen = std::strlen(str);
	
	//if field length is zero or string is shorter than the field length, 
	//the number of characters to print on screen is the length of the string
	if (fieldLen==0 || strLen <= fieldLen)
		numCharsToPrint = strLen;
	
	//otherwise, the number of characters is the the same as the field length
	else numCharsToPrint = fieldLen;
	
	for (i = 0; i <= numCharsToPrint; i++) 
	{
			cio::console.setPosition(row, col + i);
			cio::console.setCharacter(str[i]);
			cio::console.setPosition(row, col + i);
			cio::console.drawCharacter();
	}

	if(i<=fieldLen)
	{
		for(; i <= fieldLen; i++)
		  {
				cio::console.setPosition(row,col+i);
				cio::console.setCharacter(' ');
				cio::console.setPosition(row, col + i);
				cio::console.drawCharacter();
		  } 
	}

	//Move the cursor back to its original position, and then set the cursor to after the last displayed character
	cio::console.setPosition(row, col + numCharsToPrint);
}

int edit(char *str, int row, int col, int fieldLength, int maxStrLength, bool* insertMode, int* strOffset, int* curPosition)
{
	int i=0, j=0, k=0, userKey=0, returnValue = 0, strLen = strlen(str), flag = 0;
	int totCol = cio::console.getCols();
			
	char* tempStr;
	tempStr = new char[strLen+1];
	strcpy(tempStr,str);

	if(fieldLength+col >= totCol)
		fieldLength = totCol-(col+1);

	display(str + *strOffset, row, col, fieldLength);	
	
	//if the string offset is greater than the maximum length of the string,
	//set it to that that max length
	//if(*strOffset > strLen - fieldLength)
	//	*strOffset = strLen - fieldLength;

	//if cursors position is greater than or equal to the field length, set it to field length minus 1
	//if(*curPosition+col >= fieldLength+col)
	//	*curPosition = fieldLength+col-1;
	
	//cio::console.setPosition(row, col + *curPosition);	

	//get the key pressed by the user, using the overloaded input operator	
	do
		{
			display(str + *strOffset, row, col, fieldLength);
			cio::console.setPosition(row, col + *curPosition);
			
			cio::console>> userKey;

	//check the key pressed by the user is usable ascii
	//Check that insert mode is true and your string length is less than the maximum,
	//If so, add the character to the string
	if(userKey >= ' ' && userKey <= '~')
			{		
			if(*insertMode==true && strLen < maxStrLength)
				{
					for(i = strLen; i > (*curPosition+*strOffset); i--)
						str[i] = str[i-1];
						str[*curPosition + *strOffset]=userKey;
				}				
			else if(*insertMode==false)
				str[*curPosition + *strOffset]=userKey;
							
					if(*curPosition < fieldLength)
							*curPosition+=1;
					else if(strLen <=maxStrLength)
							*strOffset+=1;
										
			 }
			
			//check to see if the user pressed a non-ascii usable key
			if(userKey==LEFT)
				{	
					if(*curPosition > 0)
						*curPosition-=1; 
					else if(*strOffset > 0)
						*strOffset-=1;
			    }				
			//if you're not off the right edge of the screen
			//and the cursor position is not at the end of the field
			if(userKey==RIGHT)
				{
					if(strLen-*strOffset > fieldLength)
					{
						if(*curPosition < fieldLength)		
							*curPosition+=1;
						else
							*strOffset+=1;
					}

					else if(*curPosition < strLen - *strOffset)
						*curPosition+= 1;
				}
						
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
					j = *strOffset + *curPosition;
					while(str[j]!='\0')
						{
							str[j] = str[j+1];
							j++;
						}				
				}			

			//remove character behind cursor position, shift string left
			if(userKey==BACKSPACE)
				{
					k = (*strOffset + *curPosition)-1;
					if(k >= 0)
					{
						if(*curPosition>0)
						*curPosition-=1;
						while(str[k] != '\0')
						{
							str[k] = str[k+1];
							k++;												
						}
					 }
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
			case TAB:
			case UP:
			case DOWN:
			case PGUP:
			case PGDN:
			case F(1):
			case F(2):
			case F(3):
			case F(4):
			case F(5):
			case F(6):
			case F(7):					
			case F(8):
			case F(9):
			case F(10):
			case F(11):
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
		
		
		
