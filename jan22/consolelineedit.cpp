#include <cstring>
#include "keys.h"
#include "console.h"
#include "consoleplus.h"
#include <cstdio>


void display(const char *str, int row, int col, int fieldLen)
{
	if (str==NULL) return;

	int numCharsToPrint = 0;
	int startRow = row, startCol = col;
	int strLen = std::strlen(str);
	
	if (fieldLen==0)
		numCharsToPrint = strLen;

	else if (strLen < fieldLen) 
		{
			numCharsToPrint = strLen;			
		}

	else numCharsToPrint = fieldLen;
	
	for (int i = 0; i < numCharsToPrint; i++) 
	{
		if(columnCheck()!=1)
		{
			cio::console.setPosition(row, col + i);
			cio::console.setCharacter(str[i]);
			cio::console.setPosition(row, col + i);
			cio::console.drawCharacter();
		}
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
	int i=0, userKey=0, returnValue = 0, strLen = strlen(str), flag = 0;
		
	char* tempStr;
	tempStr = new char[strLen+1];
	strcpy(tempStr,str);
	
	display(str + *strOffset, row, col, fieldLength);
	
	
	//if the string offset is greater than the maximum length of the string,
	//set it to that that max length
	if(*strOffset > strLen - fieldLength)
		*strOffset = strLen - fieldLength;

	//if cursors position is greater than or equal to the field length, set it to field length minus 1
	if(*curPosition+col >= fieldLength+col)
		*curPosition = fieldLength+col-1;

	
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
	//and cursor position is not in the last column of the field
	//If so, add the character to the string

	if(userKey >= ' ' && userKey <= '~')
			{
		
			if(*insertMode==true && strLen+2 < maxStrLength)
			
				//if(*curPosition < col + fieldLength-2)
				{
					for(i=strLen+2;i>(*curPosition+*strOffset);i--)
					{
					str[i] = str[i-1];
					cio::console.setPosition(row, *curPosition+1);
					cio::console.setCharacter(userKey);
					cio::console.drawCharacter();
					cio::console.setPosition(row, col + i);
					}
					str[strLen+2]='\0';
				}
			
				//if insertMode is off, check the string is still not full,
				//overwrite the character at the current position and every other character until the user stops
				//entering ascii keys
				if(*insertMode==false && strLen+2 < maxStrLength)
				{
					cio::console.setPosition(row, *curPosition);
					cio::console.setCharacter(userKey);
				}

			
			}
	
			//check to see if the user pressed a non-ascii usable key
			//move position in string offset/field as required
			//or delete the current character and shift string left or backspace,
			//removing the previous character and shift left
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
					{
						*strOffset-=1;
						//display(str + *strOffset, row, col, fieldLength);
						//cio::console.setPosition(row, *curPosition+col);
					}
					

			
					//if you're not off the right edge of the screen
					//and the cursor position is not at the end of the field
			if(userKey==RIGHT)
				if(*curPosition < fieldLength)		
						{
							*curPosition+=1;
							cio::console.setPosition(row, *curPosition+col);
						}

					else if(*strOffset < strLen+1)
						{	
							*strOffset+= 1;
							//display(str + *strOffset, row, col, fieldLength);
							//cio::console.setPosition(row, *curPosition+col);
						}
		
					//move cursor position to beginning of field
					// or the string offset back to zero, aka the 
					//beginning of the string if curPos is already there
			if(userKey==HOME)
				{
					*curPosition=col;
					*strOffset=0;
					 cio::console.setPosition(row, *curPosition);					
				}
				

					//the reverse of home,
					//Move to space after last character in the string
					//and or the last space in the field
			if(userKey==END)
				{
					*curPosition=fieldLength+col;
					cio::console.setPosition(row, *curPosition);
					*strOffset=strLen-fieldLength;		
					
				}
							

					//remove the character at cursor position, shift string left
			if(userKey==DEL)
				{
					i = *strOffset + *curPosition;
					do
					{
						str[i] = str[i+1];
						i++;
						
					}
					while(str[i]!='\0');
				}
		
				

				//remove character behind cursor position, shift string left
			if(userKey==BACKSPACE)
				{
					i = *strOffset + *curPosition;
					do
					{
						str[i-1] = str[i];
						i++;
						cio::console.setPosition(row,*curPosition-1);
						
					}
					while(*strOffset != 0);
				}
			
			

				//turn Insert Mode on or off
			if(userKey==INSERT)
			{
				if(*insertMode==true)
					*insertMode=false;

				else if(*insertMode==false)
					*insertMode=true;
			}
			
	


		//If the user pushes any of the following keys (as defined by keys.h), editing ends.
		/*	case ENTER:
					flag = 1;
					return ENTER;
					break;
					
				
			case TAB:
					flag=1;
					return TAB;
					break;
				
			case UP:
					flag=1;
					return UP;
					break;

			case DOWN:
					flag=1;
					return DOWN;
					break;
				
			case PGUP:
					flag=1;
					return PGUP;
					break;			
				
			case PGDN:
					flag=1;
					return PGDN;
					break;
				
			case F(1):
					flag=1;
					return F(1);
					break;
				
			case F(2):
					flag=1;
					return F(2);
					break;
				
			case F(3):
					flag=1;
					return F(3);
					break;
				
			case F(4):
					flag=1;
					return F(4);
					break;
				
			case F(5):
					flag=1;
					return F(5);
					break;
				
			case F(6):
					flag=1;
					return F(6);
					break;
				
			case F(7):
					flag=1;
					return F(7);
					break;
									
			case F(8):
					flag=1;
					return F(8);
					break;
				
			case F(9):
					flag=1;
					return F(9);
					break;
				
			case F(10):
					flag=1;
					return F(10);
					break;
				
			case F(11):
					flag=1;
					return F(11);
					break;
				
			case F(12):
					flag=1;
					return F(12);
					break;

			case ESCAPE:
					strcpy(str,tempStr);
					flag=1;
					return ESCAPE;
					break;
				}*/
}while(flag!=1);
return userKey;
		}
		
		
		
