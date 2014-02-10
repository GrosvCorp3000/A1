#include <cstring>
#include "keys.h"
#include "console.h"
#include "consoleplus.h"
#include <iostream>

int main()
{
	bool insertMode = true;
	int strOffset = 10;
	int curPosition = 5;

		display("hello", 0, 14, 20);
		display("nick is a guy", 14, 5, 0);
		display("**********************************************", 9, 14, 100);
		display("**********************************************", 10, 14, 100);
		display("**********************************************", 11, 14, 100);
		
		edit("happy happy joy joy wont somebody think of the children", 10, 17, 20, 100, &insertMode, &strOffset, &curPosition);
getchar();
return 0;
}