/* Group1, Program4
Joe Stein, Mike Dloss, Joe Osick, Josh Petrick
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g1p4.h"
void systemGoal()
{
	/* function SystemGoal()
	Parameters: none
	Return: nothing
	description calls scanner and parser to scan and parse the source File.*/
	int   flag = 0, lineCount = 1, i = 1;
	int j = 0;
	int *tokenNumbers;
	char *tbuffer, *token, *append1, *append2;
	char outLine [256], inLine [256],  temp [256];
	
	parse = 0;
	beginFlag = 0;
	tempSpot = 1;

	for(j; j<=999; j++)
		strcpy(symbolTable[j],"0");

	j = 0;
	for(j; j<=999; j++)
		strcpy(temps[j],"0");
	
	if ( inFile != NULL )
	{
		while ( fgets ( inLine, sizeof inLine, inFile ) != NULL ) // copies source line to target line until the end of the file
		{
			strcpy(outLine, inLine);
			tbuffer = outLine;
			clearTokenBuffer();
			lexFlag = 0;
			syntaxFlag = 0;
			writeFlag = 0;
			readFlag = 0;
			stringIndex = 0;
			semiColonFlag = 0;
			statementFlag = 0;
			idStatementFlag = 0;
			lParenCount = 0;
			tempSpot = 1;
			
			while(stringIndex < sizeof(outLine)) //loop breaks when the stringIndex is larger than the line size
			{
				token = scanner(tbuffer); //scanner grabs the token
				if(strcmp(token,"")!=0 && strcmp(token,"--")!=0 && syntaxFlag == 0)
					parser(token);//scanner passes the token to the parser
			}
			fprintf (outFile , "LINE %d: %s", lineCount, outLine);//prints the line count, and the line pulled from the input file to the output file
			if (lexFlag == 1) //checks for a lexical error
				fprintf(outFile, "LEXICAL ERROR, LINE: %d, INVALID CHAR: %c\n",lineCount, invalidChar); // prints the line number and the character that causes the lex error
			if (syntaxFlag == 1)
				fprintf(outFile, "SYNTAX ERROR, LINE: %d, UNEXPECTED: \"%s\" EXPECTED: %s\n",lineCount, syntaxToken, expectedToken); // prints the line number and the character that causes the lex error
			if(lParenCount != 0)
			{
				syntaxFlag = 1;
				//fprintf(temp3,"Syntax Error: Unmatched \"(\"\n");
				fprintf(outFile, "SYNTAX ERROR, LINE: %d, UNMATCHED \"(\"\n",lineCount);
				parse = 1;
				syntaxCount++;
			}
			if(semiColonFlag == 0 && lexFlag == 0 && syntaxFlag == 0 && statementFlag == 1)
			{
				//fprintf(temp3,"Syntax Error: Expected: \";\"\n");
				fprintf(outFile, "SYNTAX ERROR, LINE: %d, EXPECTED: \";\"\n",lineCount);
				syntaxFlag = 1;
				parse = 1;
				syntaxCount++;
			}
			//fprintf(temp3,"PROGRAM LINE: %s\n",outLine);
			lineCount++; //increases line count

			if(lexFlag == 0 && syntaxFlag == 0 && idStatementFlag == 1)
				convertStatement(outLine); 
		}
		if(beginFlag != 0)
		{
			//fprintf(temp3,"Syntax Error: Expected: \"END\"\n");
			fprintf(outFile, "\nSYNTAX ERROR, LINE: %d, EXPECTED: \"END\"\n",lineCount);
			syntaxCount++;
		}
		//fprintf(temp3, "\nmatching 14, token is 14, buffer is Ÿ\n");
		//fprintf(temp3,"\n%d		Lexical Errors\n", lexCount);
		//fprintf(temp3,"%d		Syntax Errors\n",syntaxCount);
		fprintf(outFile,"\n\nThis file contained %d lexical errors.\n", lexCount);
		fprintf(outFile,"This file contained %d syntax errors.\n", syntaxCount);
		/*prints to the C file and listing file if the program compiled with errors*/
		if (syntaxCount == 0 && lexCount == 0)
		{
			fprintf(outFile,"The Program Compiled without Error.\n");
			fprintf(temp2,"/*The Program Compiled without Error.*/\n");
		}
		else 
		{
			fprintf(outFile,"The Program Compiled with Error(s).\n");
			fprintf(temp2,"/*The Program Compiled with Error.*/\n");
		}
	}
	printf("\n%s is your listing file.\n",targetFileNameLis);
	printf("\n%s is your C file.\n",targetFileNameC);
	return; // exits the function
}