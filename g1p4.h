/* Group1, Program4
Joe Stein, Mike Dloss, Joe Osick, Josh Petrick
*/
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>

#ifndef G1P4_H
#define G1P4_H

#define IN_EXTENSION (".in") //in file extension
#define OUT_EXTENSION (".out")//out file extension

FILE * inFile; //source file
FILE * outFile; //target file
FILE * outBackUp; //target file back up
FILE * temp1; // temp file1
FILE * temp2; //temp file2
FILE * parseFile;
int inExtensionCount, outExtensionCount, lexFlag, syntaxFlag,beginFlag, idFlag, idStatementFlag, exitFlag; 
int readFlag, writeFlag, semiColonFlag, statementFlag, endFlag, intFlag, stringIndex, lexCount, syntaxCount, parse, lParenCount;
char  *inExt, *outExt, *source, *targ; //pointers to the file extensions
char tokenBuffer[256], subStr [256], syntaxToken [256], expectedToken [256], invalidChar;
char targetFileName[81],sourceFileName[81],targetFileNameNoExt[81],targetFileNameLis[81],targetFileNameC[81],targetFileNameTmp[81];
char temps[1000][256], symbolTable[1000][256];
int tempSpot;

/*file functions*/
void init(char *, char *);
void appendTempFiles();
void backUpOutput(char *, char *);
void promptOutput(char *, char *);
void wrapUp();

/*scanner functions*/
char * scanner(char *);
void clearTokenBuffer();

/*system goal*/
void systemGoal();

/*parser functions*/
void parser(char *);
void matchBegin(char *);
void matchStatement(char *);
void matchAssignOp(char *);
void matchLparen(char *);
void matchRparen(char *);
void matchId(char *);
void matchSemiColon(char *);
void matchSemiColonRead(char *);
void matchExpression(char *);
void syntaxError(char *,char *);

void insertSymbolTable(char *);
void convertBegin();
void convertEnd();
void convertRead(char *);
void convertWrite(char *);
void convertStatement(char *);

#endif

