#define TOKEN_SECRET
#include "Ast.h"

#include <nbMemoryManager.h>
#include <nbAssert.h>
#include <nbString.h>
#include <nbVector.h>

#include <stdio.h>
#include <string.h>

#include "Token.h"


void Token_DebugPrint(Token* pToken)
{
	const char* szType;
	const char* szDesc = "";
	switch (pToken->nType)
	{
		case TOKEN_UNKNOWN: szType = "TOKEN_UNKNOWN"; break; 
		case TOKEN_END_OF_FILE: szType = "TOKEN_END_OF_FILE"; break;
		case TOKEN_ARBITARY:
		{
			szType = "TOKEN_ARBITARY";
			szDesc = nbString_GetCString(pToken->sToken);
			break;
		}
		case TOKEN_VOID: szType = "TOKEN_VOID"; break;
		case TOKEN_SEMICOLON: szType = "TOKEN_SEMICOLON"; break;
		case TOKEN_LEFT_BRACE: szType = "TOKEN_LEFT_BRACE"; break;
		case TOKEN_RIGHT_BRACE: szType = "TOKEN_RIGHT_BRACE"; break;
		case TOKEN_LEFT_PAREN: szType = "TOKEN_LEFT_PAREN"; break;
		case TOKEN_RIGHT_PAREN: szType = "TOKEN_RIGHT_PAREN"; break;
		case TOKEN_EQUALS: szType = "TOKEN_EQUALS"; break;
		
		

		case TOKEN_SPACE: szType = "TOKEN_SPACE"; break;
		case TOKEN_TAB: szType = "TOKEN_TAB"; break;
		case TOKEN_NEW_LINE: szType = "TOKEN_NEW_LINE"; break;

		case TOKEN_COMMENT: szType = "TOKEN_COMMENT"; break;
		
		case TOKEN_KW_CLASS: szType = "TOKEN_KW_CLASS"; break;
		case TOKEN_KW_STATIC: szType = "TOKEN_KW_STATIC"; break;
		case TOKEN_KW_RETURN: szType = "TOKEN_KW_RETURN"; break;
		case TOKEN_KW_VOID: szType = "TOKEN_KW_VOID"; break;
		case TOKEN_KW_INT: szType = "TOKEN_KW_INT"; break;

		default: nbAssert(TEH_FALSE);
	}

	printf("%s %s\n", szType, szDesc);
}