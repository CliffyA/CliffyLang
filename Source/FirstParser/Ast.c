#define AST_SECRET
#include "Ast.h"
#include "Token.h"

#include <nbAssert.h>
#include <nbMemoryManager.h>
#include <nbString.h>
#include <nbVector.h>

Token* Ast_PeekToken(nbVector* pTokenVector, int* pIndex)
{
	if (*pIndex >= nbVector_GetSize(pTokenVector))
	{
		printf("unexpected eof\n");
		nbAssert(TEH_FALSE);
	}

	return nbVector_Get(pTokenVector, *pIndex);
}

Token* Ast_PopToken(nbVector* pTokenVector, int* pIndex)
{
	Token* pToken = Ast_PeekToken(pTokenVector, pIndex);
	(*pIndex)++;
	return pToken;
}

/*void Ast_ParseToken(nbVector* pTokenVector, int* pIndex, int nToken)
   {
	nbAssert(Ast_PeekToken(pTokenVector, pIndex, nToken));
	(*pIndex)++;
   }*/

Ast* Ast_FindDeclare(Ast* pParent, const char* szName)
{
	Uint32 i;
	for (i = 0; i < nbVector_GetSize(pParent->pChildVector); i++)
	{
		Uint32 nIndex = nbVector_GetSize(pParent->pChildVector) - i - 1;
		Ast* pChild = nbVector_Get(pParent->pChildVector, nIndex);
		if (pChild->nType == AST_TYPE_DECLARE && strcmp(nbString_GetCString(pChild->sString), szName) == 0)
			return pChild;
	}
	return NULL;
}

Bool Ast_ParseAssignment(Ast* pParent, nbVector* pTokenVector, int* pIndex)
{
	int nTempIndex = *pIndex;
	Token* pVariableToken = Ast_PeekToken(pTokenVector, &nTempIndex);

	if (pParent->nType != AST_TYPE_BODY)
		return TEH_FALSE;

	if (pVariableToken->nType != TOKEN_ARBITARY)
		return TEH_FALSE;

	nTempIndex++;
	Token* pEqualsToken = Ast_PeekToken(pTokenVector, &nTempIndex);
	if (pEqualsToken->nType != TOKEN_EQUALS)
		return TEH_FALSE;

	nTempIndex++;
	Token* pValueToken = Ast_PeekToken(pTokenVector, &nTempIndex);
	if (pValueToken->nType != TOKEN_ARBITARY)
		return TEH_FALSE;

	*pIndex = nTempIndex+1;

	Token* pToken = Ast_PopToken(pTokenVector, pIndex);
	if (pToken->nType != TOKEN_SEMICOLON)
	{
		printf("missing ; after assignment\n");
		nbAssert(TEH_FALSE);
	}

	// walk tree to find declaration
	Ast* pDeclaration = Ast_FindDeclare(pParent, nbString_GetCString(pVariableToken->sToken));

	Ast* pAst = Ast_SubCreate(pParent, AST_TYPE_ASSIGNMENT);
	nbString_SetString(pAst->sString, pVariableToken->sToken);
	nbString_SetString(pAst->sString1, pValueToken->sToken);

	//pAst->pAst0 = pDeclaration;

	return TEH_TRUE;
}

Bool Ast_ParseBody(Ast* pParent, nbVector* pTokenVector, int* pIndex)
{
	if (Ast_PeekToken(pTokenVector, pIndex)->nType == TOKEN_LEFT_BRACE)
	{
		Ast* pAst = Ast_SubCreate(pParent, AST_TYPE_BODY);
		(*pIndex)++;

		while (TEH_TRUE)
		{
			Token* pToken = Ast_PopToken(pTokenVector, pIndex);
			if (pToken->nType == TOKEN_RIGHT_BRACE)
				break;

			if (pToken->nType == TOKEN_KW_INT)
			{
				Token* pNameToken = Ast_PopToken(pTokenVector, pIndex);
				nbAssert(pNameToken->nType == TOKEN_ARBITARY);

				pToken = Ast_PopToken(pTokenVector, pIndex);
				nbAssert(pToken->nType == TOKEN_SEMICOLON);

				Ast* pIntyBoy = Ast_SubCreate(pAst, AST_TYPE_DECLARE);
				nbString_SetString(pIntyBoy->sString, pNameToken->sToken);
				continue;
			}

			(*pIndex)--;

			if (Ast_ParseAssignment(pAst, pTokenVector, pIndex))
				continue;

			printf("unexpected!\n");
			Token_DebugPrint(pToken);

			nbAssert(TEH_FALSE);
		}

		return TEH_TRUE;
	}
	return TEH_FALSE;
}

Bool Ast_ParseFunction(Ast* pParent, nbVector* pTokenVector, int* pIndex)
{
	int nTempIndex = *pIndex;
	Token* pTypeToken = Ast_PeekToken(pTokenVector, &nTempIndex);

	if (pTypeToken->nType == TOKEN_KW_VOID)
	{
		nTempIndex++;

		Token* pNameToken = Ast_PeekToken(pTokenVector, &nTempIndex);
		if (pNameToken->nType == TOKEN_ARBITARY)
		{
			nTempIndex++;

			if (Ast_PeekToken(pTokenVector, &nTempIndex)->nType == TOKEN_LEFT_PAREN)
			{
				nTempIndex++;

				*pIndex = nTempIndex;

				Ast* pAst = Ast_SubCreate(pParent, AST_TYPE_FUNCTION);
				nbString_SetString(pAst->sString, pNameToken->sToken);

				if (!(Ast_PeekToken(pTokenVector, pIndex)->nType == TOKEN_RIGHT_PAREN))
				{
					printf("unclosed params!");
					nbAssert(TEH_FALSE);
				}
				(*pIndex)++;

				if (!Ast_ParseBody(pAst, pTokenVector, pIndex))
				{
					printf("function missing body!");
					nbAssert(TEH_FALSE);
				}

				return TEH_TRUE;
			}
		}
	}
	return TEH_FALSE;
}

Bool Ast_ParseClass(Ast* pParent, nbVector* pTokenVector, int* pIndex)
{
	Token* pToken = nbVector_Get(pTokenVector, *pIndex);

	if (pToken->nType == TOKEN_KW_CLASS)
	{
		(*pIndex)++;

		pToken = Ast_PopToken(pTokenVector, pIndex);
		if (pToken->nType != TOKEN_ARBITARY)
		{
			printf("expected arbitary for class name");
			nbAssert(TEH_FALSE);
		}

		Ast* pAst = Ast_SubCreate(pParent, AST_TYPE_CLASS);
		nbString_SetString(pAst->sString, pToken->sToken);

		pToken = Ast_PopToken(pTokenVector, pIndex);
		if (pToken->nType != TOKEN_LEFT_BRACE)
		{
			printf("expected {");
			nbAssert(TEH_FALSE);
		}

		while (TEH_TRUE)
		{
			pToken = Ast_PopToken(pTokenVector, pIndex);
			if (pToken->nType == TOKEN_RIGHT_BRACE)
				break;

			(*pIndex)--;

			if (Ast_ParseFunction(pAst, pTokenVector, pIndex))
				continue;

			printf("unexpected!\n");
			Token_DebugPrint(pToken);

			nbAssert(TEH_FALSE);
		}

		return TEH_TRUE;
	}

	return TEH_FALSE;
}

Ast* Ast_Create(nbVector* pTokenVector)
{
	Ast* pAst = Ast_SubCreate(NULL, AST_TYPE_ROOT);
	int nIndex = 0;
	while (nIndex < nbVector_GetSize(pTokenVector))
	{
		if (Ast_ParseClass(pAst, pTokenVector, &nIndex))
			continue;

		nbAssert(TEH_FALSE);
	}

	return pAst;
}

Ast* Ast_SubCreate(Ast* pParent, int nType)
{
	Ast* pAst = nbMalloc(sizeof(Ast));
	pAst->pParent = pParent;
	pAst->nType = nType;
	pAst->sString = nbString_Create("");
	pAst->sString1 = nbString_Create("");
	pAst->pChildVector = nbVector_Create();

	if (pParent)
		nbVector_PushBack(pParent->pChildVector, pAst);

	return pAst;
}

void Ast_Destroy(Ast* pAst)
{
	while (nbVector_GetSize(pAst->pChildVector) > 0)
		Ast_Destroy(nbVector_PopFront(pAst->pChildVector));
	nbVector_Destroy(pAst->pChildVector);
	nbString_Destroy(pAst->sString);
	nbString_Destroy(pAst->sString1);
	nbFree(pAst);
}

void Ast_StringPad(nbString* sString, int nDepth)
{
	int i;
	for (i = 0; i < nDepth; i++)
		nbString_AppendChar(sString, '\t');
}

void Ast_StringifyChildren(Ast* pAst, nbString* sString, int nDepth)
{
	int i;
	for (i = 0; i < nbVector_GetSize(pAst->pChildVector); i++)
	{
		Ast* pChildAst = nbVector_Get(pAst->pChildVector, i);
		Ast_Stringify(pChildAst, sString, nDepth);
	}
}

void Ast_Stringify(Ast* pAst, nbString* sString, int nDepth)
{
	switch (pAst->nType)
	{
	case AST_TYPE_ROOT:
	{
		Ast_StringifyChildren(pAst, sString, nDepth);

		break;
	}
	case AST_TYPE_CLASS:
	{
		Ast_StringPad(sString, nDepth);
		nbString_Append(sString, "class ");
		nbString_AppendString(sString, pAst->sString);
		nbString_AppendChar(sString, '\n');

		Ast_StringPad(sString, nDepth);
		nbString_Append(sString, "{\n");

		//nbString_Append(sString, "class ");

		nDepth++;
		Ast_StringifyChildren(pAst, sString, nDepth);
		nDepth--;

		Ast_StringPad(sString, nDepth);
		nbString_Append(sString, "}\n");

		break;
	}
	case AST_TYPE_FUNCTION:
	{
		Ast_StringPad(sString, nDepth);
		nbString_Append(sString, "function ");
		nbString_AppendString(sString, pAst->sString);
		nbString_Append(sString, "()");
		nbString_AppendChar(sString, '\n');
		Ast_StringifyChildren(pAst, sString, nDepth);
		break;
	}
	case AST_TYPE_BODY:
	{
		Ast_StringPad(sString, nDepth);
		nbString_Append(sString, "{\n");
		nDepth++;

		Ast_StringifyChildren(pAst, sString, nDepth);

		nDepth--;
		Ast_StringPad(sString, nDepth);
		nbString_Append(sString, "}\n");

		break;
	}
	case AST_TYPE_DECLARE:
	{
		Ast_StringPad(sString, nDepth);
		nbString_Append(sString, "int ");
		nbString_AppendString(sString, pAst->sString);
		nbString_Append(sString, ";\n");

		break;
	}
	case AST_TYPE_ASSIGNMENT:
	{
		Ast_StringPad(sString, nDepth);
		nbString_AppendString(sString, pAst->sString);
		nbString_Append(sString, " = ");
		nbString_AppendString(sString, pAst->sString1);
		nbString_Append(sString, ";\n");

		break;
	}
	default:
	{
		printf("unhandled stringify %d\n", pAst->nType);
		nbAssert(TEH_FALSE);
	}
	}
}

void Ast_CStringifyChildren(Ast* pAst, nbString* sString, int nDepth)
{
	int i;
	for (i = 0; i < nbVector_GetSize(pAst->pChildVector); i++)
	{
		Ast* pChildAst = nbVector_Get(pAst->pChildVector, i);
		Ast_CStringify(pChildAst, sString, nDepth);
	}
}

void Ast_CStringify(Ast* pAst, nbString* sString, int nDepth)
{
	switch (pAst->nType)
	{
	case AST_TYPE_ROOT:
	{
		Ast_CStringifyChildren(pAst, sString, nDepth);

		break;
	}
	case AST_TYPE_CLASS:
	{
		Ast_StringPad(sString, nDepth);
		nbString_Append(sString, "// ");
		nbString_AppendString(sString, pAst->sString);
		nbString_AppendChar(sString, '\n');

		nDepth++;
		Ast_CStringifyChildren(pAst, sString, nDepth);
		nDepth--;

		break;
	}
	case AST_TYPE_FUNCTION:
	{
		Ast* pParent = pAst->pParent;
		nbAssert(pParent->nType == AST_TYPE_CLASS);
		Ast_StringPad(sString, nDepth);
		nbString_Append(sString, "void ");
		nbString_AppendString(sString, pParent->sString);
		nbString_Append(sString, "_");
		nbString_AppendString(sString, pAst->sString);
		nbString_Append(sString, "()");
		nbString_AppendChar(sString, '\n');
		Ast_CStringifyChildren(pAst, sString, nDepth);
		break;
	}
	case AST_TYPE_BODY:
	{
		Ast_StringPad(sString, nDepth);
		nbString_Append(sString, "{\n");
		nDepth++;

		Ast_CStringifyChildren(pAst, sString, nDepth);

		nDepth--;
		Ast_StringPad(sString, nDepth);
		nbString_Append(sString, "}\n");

		break;
	}
	case AST_TYPE_DECLARE:
	{
		Ast_StringPad(sString, nDepth);
		nbString_Append(sString, "int ");
		nbString_AppendString(sString, pAst->sString);
		nbString_Append(sString, ";\n");

		break;
	}
	case AST_TYPE_ASSIGNMENT:
	{
		Ast_StringPad(sString, nDepth);
		nbString_AppendString(sString, pAst->sString);
		nbString_Append(sString, " = ");
		nbString_AppendString(sString, pAst->sString1);
		nbString_Append(sString, ";\n");

		break;
	}
	default:
	{
		printf("unhandled stringify %d\n", pAst->nType);
		nbAssert(TEH_FALSE);
	}
	}
}
