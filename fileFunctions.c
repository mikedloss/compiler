/* Group1, Program4
Joe Stein, Mike Dloss, Joe Osick, Josh Petrick
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g1p4.h"

typedef enum {Begin, End, Read, Write} tokens;

void init(char *source, char *target)
{
	/* init(char *source) prompts the user for a input file or if a input file is passed it checks the passed input file
	* It checks that the input file has a extension and that the extension is correct.
	* It also checks that the file exist.
	*If the user enters NULL when prompted for the input file the program exists.
	*this funcion returns a int*/
	/*This function calls promptOutput*/
	int flag = 0, invalidFlag=0, count = 0, xx=0, i = 0;	
	char inFileName[81] = {0}; //string to hold source file name
	char *inSource;
	exitFlag = 0;
	if (source != 0) // if source is 0 the user will prompted to enter a source file
		strcpy(inFileName,source);
	while(flag == 0) //main loop of the funcion
	{
		if(count > 0 || source == 0)
		{
			/*the user will be prompted to enter a source file when a 0 is passed
			*or the source file that was enter as a paramater is invalid*/
			invalidFlag = 0;
			printf("\nPLEASE ENTER THE SOURCE FILE'S NAME: "); //prompts the user for the file name
			gets(inFileName);
			if(strlen(inFileName) == 0) //if the user enters NULL the program exits
			{
				exitFlag = 1;
				return;
			}
		}
		inExtensionCount = strcspn(inFileName, "."); //finds the period in the string
		if (flag == 0);
		{
			if (inExtensionCount==(strlen(inFileName)))//a file extension is not given
			{
				printf("\nA file extension has not been entered\n");
				printf("The program assumes");
				strcat(inFileName,IN_EXTENSION); //concatenates the file name and .in extension
				printf(" your file name is: %s\n", inFileName);
			}
			if (inExtensionCount!=(strlen(inFileName))) // a file extension if given
			{
				inExt=strrchr(inFileName, '.');			//fills inExt to contain the source file extension
				if(invalidFlag == 0)
				{
					if(access(inFileName, 0)) //checks that the source file exists
					{
						invalidFlag = 1;
						printf("\nERROR: %s does not exist, please choose a new file\n", inFileName);
					}
					else //source file is valid
					{
						inSource = inFileName;
						flag = 1;

						i = 0;
						for(i=0;i<=strlen(inSource);i++)
						{
							if(inSource[i]>=97&&inSource[i]<=122) //converts string to uppercase
							inSource[i]=inSource[i]-32;
						}
						/*the code below will creat the target files*/
						outExtensionCount = strcspn(inFileName, ".");
						xx = outExtensionCount;
						strcpy(targetFileNameNoExt,inFileName);
						xx++;
						/*the loop below removes the source file's extension*/
						while(targetFileNameNoExt[xx] != '\0')
						{
							targetFileNameNoExt[xx] = ' ';
							xx++;
						}
						/*creates inFileName.LIS*/
						strcpy(targetFileNameLis,targetFileNameNoExt);
						targetFileNameLis[outExtensionCount+1] = 'L';
						targetFileNameLis[outExtensionCount+2] = 'I';
						targetFileNameLis[outExtensionCount+3] = 'S';
						targetFileNameLis[outExtensionCount+4] = '\0';
						/*creates inFileName.C*/
						strcpy(targetFileNameC,targetFileNameNoExt);
						targetFileNameC[outExtensionCount+1] = 'C';
						targetFileNameC[outExtensionCount+2] = '\0';
						/*creates inFileName.TMP*/
						strcpy(targetFileNameTmp,targetFileNameNoExt);
						targetFileNameTmp[outExtensionCount+1] = 'T';
						targetFileNameTmp[outExtensionCount+2] = 'M';
						targetFileNameTmp[outExtensionCount+3] = 'P';
						targetFileNameTmp[outExtensionCount+4] = '\0';

						if (strcmp(inFileName,targetFileNameTmp)==0 ||
							strcmp(inFileName,targetFileNameC)==0 ||
							strcmp(inFileName,targetFileNameLis)==0)
						{
							flag = 0;
							printf("ERROR: your source file cannot end with the Extension .TMP, .C, or .LIS.\n");
						}
					}
				}
			}
		}
		count++;
	}
	if (flag != 2)
	{
		promptOutput(inSource,target);
	}
	return; //exits the function
}

void promptOutput(char *inSource, char *target)
{
	/* promptOutput(char *target) creates and backs up output files
	*If the user enters NULL when prompted for the output file is named the same as the source file with a .out extension.*/
	/*parameters: char *, Char*/
	/*returns: nothing*/
	/*this function calls Scanner*/
	int flag = 0, invalidFlag=0, i=0, j=1, count = 0, xx=0;
	int fileChar1Count, fileChar2Count, fileChar3Count, fileChar4Count, fileChar5Count, fileChar6Count;
	int	fileChar7Count, fileChar8Count, fileChar9Count;
	char  outFileBackupName[81] = {0}; //string to hold target file's name and the targer file's back up's name

	if(!(access(targetFileNameC, 0)))//backs up the C file
	{
		strcpy(outFileBackupName,targetFileNameC); //backs up the C file
		outFileBackupName[outExtensionCount] = '1';
		j = 1;
		for (i = 0; i < 4; i++)
		{
		/*loops through and changes the back up file name by adding a 1 before the extension*/
			outFileBackupName[outExtensionCount+j] = targetFileNameC[outExtensionCount+i];
			j++;
		}
		backUpOutput(targetFileNameC,outFileBackupName);
	}
	strcpy(outFileBackupName, " ");
	if(!(access(targetFileNameLis, 0)))//backs up listing file
	{
		strcpy(outFileBackupName,targetFileNameLis); // copys the source file name to the back up file name
		outFileBackupName[outExtensionCount] = '1';
		j = 1;
		for (i = 0; i < 4; i++)
		{
		/*loops through and changes the back up file name by adding a 1 before the extension*/
			outFileBackupName[outExtensionCount+j] = targetFileNameLis[outExtensionCount+i];
			j++;
		}
		backUpOutput(targetFileNameLis,outFileBackupName);
	}
	strcpy(sourceFileName,inSource); // copies the source file
	temp1 = fopen(targetFileNameC, "w" ); //creates C file
	temp2 = fopen(targetFileNameTmp, "w" ); //creates temp file 
	inFile = fopen( sourceFileName, "r" ); //opens the source file
	outFile = fopen(targetFileNameLis, "w" );//creates listing file
	return; //exits the function
}
void backUpOutput(char *in, char *out)
{
	/* Backs up the output file*/
	/*parmeters: string, string*/
	/*returns: nothing*/
	/*description: copies a source file to a output file*/
	char inLine [ 256 ];
	char outLine [256];

	inFile = fopen( in, "r" ); //opens the source file
	outFile = fopen(out, "w" );//opes the target file

	if ( inFile != NULL )
	{
		while ( fgets ( inLine, sizeof inLine, inFile ) != NULL ) // copies source line to target line until the end of the file
		{
			strcpy(outLine, inLine);
			fprintf (outFile , outLine);
		}
	}
	fclose(inFile);
	fclose(outFile);
	printf("\n%s has been copied to %s\n", in , out);
	return;
}
void appendTempFiles()
{
	/*Appends temp2 to temp1*/
	/*parmeters: string, string*/
	/*returns: nothing*/
	/*description: places temp2's contents on the bottom on temp3*/
	char inLine [ 256 ];
	char outLine [256];
	
	inFile = fopen(targetFileNameTmp, "r" ); //opens the source file
	outFile = fopen(targetFileNameC, "ab" );//opes the target file

	fprintf(outFile, "\n");
	if ( inFile != NULL )
	{
		while ( fgets ( inLine, sizeof inLine, inFile ) != NULL ) // copies source line to target line until the end of the file
		{
			fprintf (outFile , "%s", inLine);
			fprintf(outFile, "\r\n");
		}
	}
	printf("\n%s has been appended to %s\n", targetFileNameTmp, targetFileNameC);
	fclose(inFile);
	fclose(outFile);
	return;
}

void wrapUp()
{
	fclose(temp2);
	fclose(temp1);
	fclose(outFile); // closes the target file
	fclose(inFile); // closes the source file
	appendTempFiles();//appends the temp file in wrap up
	remove(targetFileNameTmp); // removes .TMP file
	return;
}