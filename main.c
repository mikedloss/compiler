/* Group1, Program4
Joe Stein, Mike Dloss, Joe Osick, Josh Petrick
*/
#include <io.h>
#include "g1p4.h"
#include <string.h>

int main(int argc, char *argv[]) //main
{
	/******************calls init ******************************/
	char *in, *out;
	if (argc<1)		//nothing is entered
	{
		printf("ERROR: No command line parameters were entered\n");
	}
	if(argc==1)		//0 param are entered
	{
		init(0,0); // asks user to enter source file, and returns a int
	}
		if(argc==2)		//1 param are entered
	{
		in = argv[1]; //a points to the source file
		init(in,0);// checks the user's source file, and returns a in
	}
	if(argc==3)		//2 params are entered
	{
		in = argv[1]; //a points to the source file
		out = argv[2]; //b points to the target file
		init(in,out); // checks the user's source file, and returns a int
	}
	/*************************************************************/
	if(exitFlag == 0)
	{
		/******************calls systemGoal******************************/
		systemGoal();
		/************************************************************/
		/******************calls wrapUp******************************/
		wrapUp();
		/************************************************************/
	}
	printf("\nProgram Exits\n");
	system ("pause"); 
	return 0; //program exits
}