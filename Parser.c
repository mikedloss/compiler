/* Group1, Program4
Joe Stein, Mike Dloss, Joe Osick, Josh Petrick
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g1p4.h"
void parser(char *parseToken) 
{
	/* function parser(char *)
	Parameters: char *
	Return: nothing
	description: Scanner grabs the token from the buffer and passes it to parser.
				 Parser then knows what the token should be and matches it.
				 If parser finds a unexpected token it prints a syntax error.*/
	if (parse == 0) // the program is expecting begin
		matchBegin(parseToken);
	else if (parse == 1)// the program is expecting a read,write,id or end
		matchStatement(parseToken);
	else if (parse == 3)//the program is expecting a :=
		matchAssignOp(parseToken);
	else if (parse == 4)// the program is expecting a (
		matchLparen(parseToken);
	else if (parse == 5)//the program is expecting a Id
		matchId(parseToken);
	else if (parse == 6)//the program is expecting a ) or a comma
		matchRparen(parseToken);
	else if (parse == 7) //the program is expecting a ;
		matchSemiColon(parseToken);
	else if (parse == 8)
		matchExpression(parseToken);// the program is expecting a int or Id
	else if (parse == 9)
		matchSemiColonRead(parseToken);//the program is expecting a ; or + or -


	if(idFlag == 1)
		insertSymbolTable(parseToken);
	if(writeFlag == 1 && idFlag == 1)
		convertWrite(parseToken);
	if(readFlag == 1 && idFlag == 1)
		convertRead(parseToken);


	return;
}
void matchBegin(char *parseToken)
{
	/* function matchBegin(char *)
	Parameters: char *
	Return: nothing
	description: Matches the BEGIN token.*/
	if(strcmp(parseToken,"BEGIN")==0) //matches BEGIN
	{
		beginFlag = 1;
		//fprintf(temp3,"matching 0, token is 0, buffer is %s\n", parseToken);
		parse = 1;
		convertBegin();
	}
	else
		syntaxError(parseToken, "\"BEGIN\"");
	return;
}
void matchStatement(char *parseToken)
{
	/* function matchStatement(char *)
	Parameters: char *
	Return: nothing
	description: Matches the READ, WRITE, ID, or, END token.*/
	if(idFlag == 1)
	{
		//fprintf(temp3,"matching 4, token is 4, buffer is %s\n", parseToken);
		parse = 3;
		statementFlag = 1;
		idStatementFlag = 1;
	}
	else if(strcmp(parseToken,"READ")==0)
	{
		//fprintf(temp3,"matching 3, token is 3, buffer is %s\n", parseToken);
		parse = 4;
		readFlag = 1;
		statementFlag = 1;
	}
	else if(strcmp(parseToken,"WRITE")==0)
	{
		//fprintf(temp3,"matching 2, token is 2, buffer is %s\n", parseToken);
		parse = 4;
		writeFlag = 1;
		statementFlag = 1;
	}
	else if(strcmp(parseToken,"END")==0)
	{
		//fprintf(temp3,"matching 1, token is 1, buffer is %s\n", parseToken);
		if(endFlag == 0)
			syntaxError(parseToken,"STATEMENT before END"); //statement needed
		convertEnd();
		parse = 0;
		beginFlag = 0;
	}
	else
		syntaxError(parseToken,"\"READ\",\"WRITE\",\"END\", OR \"ID\"");
	return;
}
void matchAssignOp(char *parseToken)
{
	/* function matchAssginOp(char *)
	Parameters: char *
	Return: nothing
	description: Matches the := token.*/
	if(strcmp(parseToken,":=")==0)
	{
		//fprintf(temp3,"matching 10, token is 10, buffer is %s\n", parseToken);
		parse = 8;
	}
	else
		syntaxError(parseToken, "\":=\"");
}
void matchLparen(char *parseToken)
{
	/* function matchLparen(char *)
	Parameters: char *
	Return: nothing
	description: Matches the ( token.*/
	if (parse == 4)
	{
		if(strcmp(parseToken,"(")==0)
		{
		//fprintf(temp3,"matching 6, token is 6, buffer is %s\n", parseToken);
		if (writeFlag == 1)
			parse = 8;
		else
			parse = 5;
		}
		else 
			syntaxError(parseToken, "\"(\"");
	}
}
void matchId(char *parseToken)
{
	/* function matchId(char *)
	Parameters: char *
	Return: nothing
	description: Matches a ID token.*/
	if(idFlag == 1)
	{
		//fprintf(temp3,"matching 4, token is 4, buffer is %s\n", parseToken);
		parse = 6;
	}
	else
		syntaxError(parseToken, "\"ID\"");	
}
void matchRparen(char *parseToken)
{
	/* function matchRparen(char *)
	Parameters: char *
	Return: nothing
	description: Matches the ) or comma token.*/
	if(strcmp(parseToken,")")==0)
	{
		//fprintf(temp3,"matching 7, token is 7, buffer is %s\n", parseToken);
		parse = 7;
	}
	else if(strcmp(parseToken,",")==0)
	{
		//fprintf(temp3,"matching 5, token is 9, buffer is %s\n", parseToken);
		if (writeFlag == 1)
			parse = 8;
		else
			parse = 5;
	}
	else 
		syntaxError(parseToken, "\")\" OR \",\"");
}
void matchSemiColon(char *parseToken)
{
	/* function matchSemiColon(char *)
	Parameters: char *
	Return: nothing
	description: Matches the ; token.*/
	if(strcmp(parseToken,";")==0)
	{
		//fprintf(temp3,"matching 8, token is 8, buffer is %s\n", parseToken);
		endFlag = 1;
		parse = 1;
		semiColonFlag = 1;
	}
	else 
		syntaxError(parseToken,";");
}
void matchSemiColonRead(char *parseToken)
{
	/* function matchSemiColonRead(char *)
	Parameters: char *
	Return: nothing
	description: Matches the ; or + or - token.*/
	if(strcmp(parseToken,";")==0)
	{
		//fprintf(temp3,"matching 8, token is 8, buffer is %s\n", parseToken);
		endFlag = 1;
		parse = 1;
		semiColonFlag = 1;
	}
	else if(strcmp(parseToken,"+")==0)
	{
		//fprintf(temp3,"matching 11, token is 11, buffer is %s\n", parseToken);
		parse = 8;
	}
	else if(strcmp(parseToken,"-")==0)
	{
		//fprintf(temp3,"matching 12, token is 12, buffer is %s\n", parseToken);
		parse = 8;
	}
	else if(strcmp(parseToken,")")==0)
	{
		//fprintf(temp3,"matching 7, token is 7, buffer is %s\n", parseToken);
		parse = 8;
		lParenCount--;
	}
	else 
	{
		syntaxError(parseToken, "\"+\", \"-\", OR \";\"");
	}
}
void matchExpression(char *parseToken)
{
	/* function matchExpression(char *)
	Parameters: char *
	Return: nothing
	description: Matches a int or ID token.*/
	if (intFlag == 1)
	{
		//fprintf(temp3,"matching 5, token is 5, buffer is %s\n", parseToken);
		if (writeFlag == 0)
			parse = 9;
		else
			parse = 6;
	}
	else if (idFlag == 1)
	{
		//fprintf(temp3,"matching 4, token is 4, buffer is %s\n", parseToken);
		if (writeFlag == 0)
			parse = 9;
		else
			parse = 6;
	}
	else if (strcmp(parseToken,"(")==0 && idStatementFlag == 1)
	{
		//fprintf(temp3,"matching 6, token is 6, buffer is %s\n", parseToken);
		parse = 8;
		lParenCount++;
	}
	else if (strcmp(parseToken,";")==0 && idStatementFlag == 1)
	{
		matchSemiColonRead(parseToken);
	}
	else if (strcmp(parseToken,")")==0 && lParenCount > 0 && idStatementFlag == 1)
	{
		matchSemiColonRead(parseToken);
	}
	else if (strcmp(parseToken,"+")==0 && idStatementFlag == 1)
	{
		matchSemiColonRead(parseToken);
	}
	else if (strcmp(parseToken,"-")==0 && lParenCount > 0 && idStatementFlag == 1)
	{
		matchSemiColonRead(parseToken);
	}
	else
		syntaxError(parseToken, "\"INTEGER\" OR \"ID\"");
	return;
}
void syntaxError(char *parseToken, char *synError)
{
	/* function syntaxError(char *, char *)
	Parameters: char *, char *
	Return: nothing
	description: prints a syntax error., first prints what the unexpected token is, then what the expected token is.*/
	char *a, *b;
	parse = 1;

	a = parseToken;
	b = "LEXICAL ERROR";
	if(strcmp(a,b)!=0) // checks if the token was a lexical error
	{
		syntaxFlag = 1;
		a = syntaxToken;
		b = parseToken; //unexpected token
		strcpy(a,b);
		a = expectedToken; //expected token
		b = synError;
		strcpy(a,b);
		//fprintf(temp3,"Syntax Error: Unexpected: \"%s\", Expected %s\n", syntaxToken, expectedToken);
		syntaxCount++;
	}
	return;
}	
void convertBegin() //converts BEGIN into the C code
{
	fprintf(temp1,"#include <stdio.h>\n#include <stdlib.h>\n");
	fprintf(temp1,"\nint main()\n{\n");
	return;
}
void convertEnd() //converts END into the C code
{
	fprintf(temp2,"	system (\"pause\");\n");
	fprintf(temp2,"	return 0;\n");
	fprintf(temp2,"}\n");
	return;
}
void convertStatement(char *statement) // converts a statement into C code
{
	int Length = 0, j = 0,i =0, leftParenCount = 0, holdTemp = 0, first = 0, count = 0, stringSpot, skipFlag = 0, firstTime=0;
	char tempVar[256], subStr2[256], leftStatement[256], rightStatement[256];

	/*sets the left side of the statement*/
	stringSpot = strcspn(statement, ":");
	while(stringSpot>i)
	{
		leftStatement[i] = statement[i];
		i++;
	}
	leftStatement[i] = '\0';
	
	/*sets the right side of the statement*/
	i = 0;
	stringSpot = strcspn(statement, "=");
	stringSpot++;
	while(statement[stringSpot] != ';')
	{
		rightStatement[i] = statement[stringSpot];
		i++;
		stringSpot++;
	}
	rightStatement[i] = ';';
	rightStatement[i+1] = '\0';

	i=0;
	/*counts left Parens*/
	while(rightStatement[j] != ';')
	{
		if(rightStatement[j] == '(')
			Length++;
		j++;
	}
	j = 0;
		while(Length >= 0)
		{
			while(leftParenCount < Length)
			{
				if(rightStatement[j] == '(')
					leftParenCount++;
				j++;
			}
			if (Length != 0)
			{
				sprintf(tempVar, "temp%d", tempSpot);
				insertSymbolTable(tempVar);
			}
			while(rightStatement[j] != ')' || count != 0 )
			{
				if(Length!=0 && firstTime == 0)
					fprintf(temp2,"	%s = ",tempVar); 
				else if(firstTime == 0)
					fprintf(temp2,"	%s = ",leftStatement);
				firstTime = 1;
				if(rightStatement[j] == '(')
				{
					count++;
					skipFlag = 1;
					if(count == 1)
						fprintf(temp2,"temp%d", holdTemp-(count-1));
				}
				else if(rightStatement[j] == ';')
					break;
				else if (count == 0)
				{
					subStr2[i]=rightStatement[j];
					fprintf(temp2,"%c",subStr2[i]);
				}
				else if(rightStatement[j] == ')')
					count--;
				j++;
				i++;
			}
			subStr2[i] = '\0';
			fprintf(temp2,";\n");
			leftParenCount = 0;
			Length--;
			holdTemp = tempSpot;
			tempSpot++;
			first = 1;
			firstTime = 0;
			j = 0;
			i = 0;
			strcpy(subStr2, "\0");
		}
	return;
}
void convertWrite(char *id) //converts WRITE into C code
{
	fprintf(temp2,"	printf(\"%s\\n\",%s);\n","%d", id);
	return;
}

void convertRead(char *id) //convets READ into C code
{
	fprintf(temp2,"	scanf(\"%s\",&%s);\n","%d", id);
	return;
}

void insertSymbolTable(char *id) //inserts into the symbol table
{
	/* function insertSymbolTable(char *)
	Parameters: char *
	Return: nothing
	description: checks if a symbol is in the symbol table if not inserts it*/
	int j = 0, symbolFlag = 0;
	char idBuffer[256];

	strcpy(idBuffer,id);

	//the symbol table is filled with "0"
	while(symbolFlag == 0)
	{
		if(strcmp(symbolTable[j],id)==0) // checks if the symbol table matches the passed symbol
		{
			symbolFlag = 1;
		}
		else if(strcmp(symbolTable[j],"0")!=0) //checks if there is a symbol in this spot
		{
			j++;
		}
		else if(j == 999) //the table is full
		{
			symbolFlag = 1;
		}
		else //the symbol is not in the table and get inserted into the table
		{
			symbolFlag = 1;
			strcpy(symbolTable[j],idBuffer);
			fprintf(temp1,"	int %s;\n",id);
		}
	}
	return;
}
