/*#include <nbMemoryManager.h>
#include <nbVector.h>
#include <nbString.h>
#include <nbAssert.h>

#include <stdio.h>
#include <string.h>
*/
typedef struct nbString nbString;

#define TOKEN_UNKNOWN 0
#define TOKEN_END_OF_FILE 1
#define TOKEN_ARBITARY 2
#define TOKEN_VOID 3
#define TOKEN_SEMICOLON 4
#define TOKEN_LEFT_BRACE 5
#define TOKEN_RIGHT_BRACE 6
#define TOKEN_LEFT_PAREN 7
#define TOKEN_RIGHT_PAREN 8
#define TOKEN_EQUALS 9


#define TOKEN_SPACE 100
#define TOKEN_TAB 101
#define TOKEN_NEW_LINE 102

#define TOKEN_COMMENT 200


#define TOKEN_KW_CLASS 300
#define TOKEN_KW_STATIC 301
#define TOKEN_KW_RETURN 302
#define TOKEN_KW_VOID 303
#define TOKEN_KW_INT 304

typedef struct Token Token;
struct Token
{
	int nLine;
	int nColumn;

	int nType;
	nbString* sToken;
};

extern void Token_DebugPrint(Token* pToken);