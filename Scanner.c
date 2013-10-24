/* Group1, Program4
Joe Stein, Mike Dloss, Joe Osick, Josh Petrick
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g1p4.h"
char* scanner(char * tokenString)
{
	/* function copySourceFile(char *in, char *out) has two file names passed to it.
	Parameters: char*
	Return: string
	description: Finds the token from a string that is passed to it.*/

	char  beginInsert[] = "Token Number:0		Token Type:BEGIN	Actual Token:begin";
	char  endInsert[] = "Token Number:1			Token Type:END		Actual Token:end";
	char  writeInsert[] = "Token Number:2		Token Type:WRITE	Actual Token:write";
	char  readInsert[] = "Token Number:3		Token Type:READ		Actual Token:read";
	char* returnToken;
	int length = 0, flag = 0, jumpFlag = 0, i = 0;
	strcpy(tokenBuffer,tokenString);
	length = 0;

	idFlag = 0;
	intFlag = 0;
	if (tokenBuffer[stringIndex] == ' ' || tokenBuffer[stringIndex] == '\t' || tokenBuffer[stringIndex] == '\0' || tokenBuffer[stringIndex] == '\n') //skips tabs, spaces, \n, and Null characters
	{
		flag  = 1;
		returnToken = "";//empty token
		if (stringIndex == sizeof(tokenBuffer) || tokenBuffer[stringIndex] == '\0' || tokenBuffer[stringIndex] == '\n')
		{
			jumpFlag = 1;
			stringIndex = sizeof(tokenBuffer);
		}
		else	
			stringIndex++;
	}
	if(jumpFlag == 0) // jumps to end of function
	{
		if (isalpha(tokenBuffer[stringIndex]) && flag != 1) //is alpha loop
		{	 
			while(1)
			{
				if ((stringIndex + length) == sizeof(tokenBuffer)) //breaks if the end of the line is reached
				{
					flag = 1;
					break;
				}
				length++;
				if(!(isalnum(tokenBuffer[stringIndex + length])) || tokenBuffer[stringIndex + length] == ' ' || 
					tokenBuffer[stringIndex + length] == '\t' || tokenBuffer[stringIndex + length] == '\0') //breaks if its not a number/alpha
				{
					flag = 1;
					break;
				}	
			}
			strncpy(subStr, tokenBuffer+stringIndex, length); //this is the substring that was found from the loop
			subStr[length] = '\0';
			returnToken = subStr;
			for(i=0;i<=strlen(subStr);i++)
			{
				if(subStr[i]>=97&&subStr[i]<=122) //converts string to uppercase
				subStr[i]=subStr[i]-32;
			}
			if(strcmp(subStr, "WRITE")!=0 && strcmp(subStr, "READ")!=0 &&
			strcmp(subStr, "END")!=0 && strcmp(subStr, "BEGIN")!=0)
			{
				////fprintf(temp3,"Token Number:4			Token Type:ID		Actual Token:%s\n", subStr);
				idFlag = 1;
			}
			stringIndex = stringIndex + length; //sets the new string index to go to the next substring in the string
			returnToken = subStr;
		}
		if (isdigit(tokenBuffer[stringIndex]) && flag != 1) //is digit loop
		{ 
			intFlag = 1;
			while(1)
			{
				if ((stringIndex + length) == sizeof(tokenBuffer)) //breaks if the end of the line is reached
				{
					flag = 1;
					break;
				}
				length++;
				if(!(isdigit(tokenBuffer[stringIndex + length]))) //breaks if it is not a digit
				{
					flag = 1;
					break;
				}	
			}

			strncpy(subStr, tokenBuffer+stringIndex, length); //this is the substring that was found from the loop
			returnToken = subStr;
			subStr[length] = '\0'; //places a null at the end of the string
			////fprintf(temp3,"Token Number:5		Token Type:INTLITERAL	Actual Token:%s\n", subStr); 
			stringIndex = stringIndex + length; //sets the new stringIndex for the next substring to be processed
		}
		if (!(isdigit(tokenBuffer[stringIndex])) && !(isalpha(tokenBuffer[stringIndex])) && flag != 1) //not a digit, not a alpha
		{
			if(tokenBuffer[stringIndex] == '(')
			{
				////fprintf(temp3,"Token Number:6		Token Type:LPAREN	Actual Token:(\n");
				flag = 1;
				returnToken = "(";
			}
			if(tokenBuffer[stringIndex] == ')')
			{
				//fprintf(temp3,"Token Number:7		Token Type:RPAREN	Actual Token:)\n");
				flag = 1;
				returnToken = ")";
			}
			if(tokenBuffer[stringIndex] == ';')
			{
				//fprintf(temp3,"Token Number:8		Token Type:SEMICOLON	Actual Token: ;\n");
				flag = 1;
				returnToken = ";";
			}
			if(tokenBuffer[stringIndex] == ',')
			{
				//fprintf(temp3,"Token Number:9		Token Type:COMMA	Actual Token: ,\n");
				flag = 1;
				returnToken = ",";
			}
			if(tokenBuffer[stringIndex] == '+')
			{
				//fprintf(temp3,"Token Number:11		Token Type:PLUSOP	Actual Token: +\n");
				flag = 1;
				returnToken = "+";
			}
			if(tokenBuffer[stringIndex] == '-')
			{
				if(tokenBuffer[stringIndex+1] == '-') //checks for a comment
				{
					flag = 2; //flag = 2 ignores the rest of the line
					returnToken = "--"; //coment
				}
				else
				{
					//fprintf(temp3,"Token Number:12		Token Type:MINUSOP	Actual Token: -\n");
					flag = 1;
					returnToken = "-";

				}
			}
			if(tokenBuffer[stringIndex] == ':')
			{
				if(tokenBuffer[stringIndex+1] == '=') //checks for assignop
				{
					//fprintf(temp3,"Token Number:10		Token Type:ASSIGNOP 	Actual Token: :=\n");
					flag = 1;
					stringIndex ++;
					returnToken = ":=";
				}
			}
			if(flag != 1)
			{
				if(flag != 2) //if flag = 2 its a comment and takes a short cut out of the loop
				{
					lexFlag = 1; //sets lexical error flag
					//fprintf(temp3,"Token Number:14		Token Type:ERROR	Actual Token: %c\n",tokenBuffer[stringIndex]);
					lexCount++;
					invalidChar = tokenBuffer[stringIndex];
					returnToken = "LEXICAL ERROR";
				}
				stringIndex =  sizeof(tokenBuffer) + 1; //exits scanner
			}
			stringIndex ++;//sets new string index for the next substring to be processed
		}
	}
	flag = 0; //resets the flag for the next substring
	return returnToken;
}
void clearTokenBuffer()
{
	/* function: clearTokenBuffer
	Parameters: none
	Return: nothing
	description: Clears the tokenBuffer and subStr.*/
	strcpy(subStr, " ");
	strcpy(tokenBuffer, " ");
}