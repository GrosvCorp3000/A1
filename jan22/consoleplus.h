
/*
This function displays the C-style, null-terminated string pointed to
by str, starting at row row and column col of the console screen in a
field of fieldLen characters.  

Row value 0 refers to the top row, and column value 0 refers to the
left-most column.  If the string is longer than fieldLen, your function
displays the first fieldLen characters.  If the string is shorter than
fieldLen, your function displays the portion of the entire string that
fits on the screen, followed by enough trailing spaces to fill out the
field completely.

If fieldLen is 0 or less, your function displays the portion of the
entire string that fits on the screen with no trailing spaces.  

Your function positions the cursor after the last character displayed,
but excluding any added trailing spaces, if the last character is not
in the last column of the screen; otherwise, your function positions
the cursor under the last character on the screen.

Your function does not flush the output buffer. The results are
undefined if the starting position of the string is not within the
dimensions of the screen. 
*/
void display(const char *str, int row, int col, int fieldLen);

int columnCheck();

int edit(char *str, int row, int col, int fieldLength, int maxStrLength,
		 bool* insertMode, int* strOffset, int* curPosition);
