#include <nbMemoryManager.h>
#include <nbVector.h>
#include <nbString.h>
#include <nbAssert.h>

#include <stdio.h>
#include <string.h>

#include "Token.h"
#include "Ast.h"

int main() {
	// printf() displays the string inside quotation
	printf("Hello, World!\n");

	nbMemoryManager_Startup();

	nbVector* pTokenVector = nbVector_Create();

	{
		FILE* pFile = fopen("../../../Source/FirstParser/test.cl", "rb");
		if (pFile)
		{
			int i;
			int nSize;

			int nLine = 0;
			int nColumn = 0;

			char* szBuffer;
			nbString* sRead = nbString_Create("");

			fseek(pFile, 0, SEEK_END);
			nSize = ftell(pFile);
			rewind(pFile);
			

			//printf("%zu\n", nSize);

			szBuffer = nbMalloc(nSize+1);

			fread(szBuffer, 1, nSize, pFile);
			szBuffer[nSize] = '\0';

			//printf("%s\n", szBuffer);

			i = 0;
			while (TEH_TRUE)
			{
				char c;
				int nType = TOKEN_UNKNOWN;

				if (i == nSize)
				{
					nType = TOKEN_END_OF_FILE;
				}
				else
				{
					char c2 = 0;

					c = szBuffer[i];

					if (i < nSize-1)
						c2 = szBuffer[i+1];


					switch (c)
					{
						case ';': nType = TOKEN_SEMICOLON; break;
						case '{': nType = TOKEN_LEFT_BRACE; break;
						case '}': nType = TOKEN_RIGHT_BRACE; break;
						case '(': nType = TOKEN_LEFT_PAREN; break;
						case ')': nType = TOKEN_RIGHT_PAREN; break;
						case '=': nType = TOKEN_EQUALS; break;

						case '/':
						{
							if (c2 == '/')
							{
								i++;
								i++;
								while (TEH_TRUE)
								{
									if (i == nSize -1 || szBuffer[i] == '\n')
										break;
									i++;
								}
								nType = TOKEN_COMMENT;
								break;
							}

							if (c2 == '*')
							{
								i++;
								i++;

								while (TEH_TRUE)
								{
									if (i == nSize - 1)
										nbAssert(NB_FALSE);

									if (szBuffer[i] == '*' && szBuffer[i+1] == '/')
									{
										i++;
										break;
									}

									i++;
								}


								nType = TOKEN_COMMENT;
								break;
							}

							printf ("%c %c\n", c, c2);

							nbAssert(TEH_FALSE);
						}

						case ' ': nType = TOKEN_SPACE; break;
						case '\t': nType = TOKEN_TAB; break;
						case '\n': nType = TOKEN_NEW_LINE; break;

					}
				}

				if (nType != TOKEN_UNKNOWN)
				{
					if (nbString_GetLength(sRead) > 0)
					{
						Token* pToken = nbMalloc(sizeof(Token));

						if (strcmp(nbString_GetCString(sRead), "class") == 0)
						{
							pToken->nType = TOKEN_KW_CLASS;
							nbString_Set(sRead, "");
						}
						else if (strcmp(nbString_GetCString(sRead), "static") == 0)
						{
							pToken->nType = TOKEN_KW_STATIC;
							nbString_Set(sRead, "");
						}
						else if (strcmp(nbString_GetCString(sRead), "return") == 0)
						{
							pToken->nType = TOKEN_KW_RETURN;
							nbString_Set(sRead, "");
						}
						else if (strcmp(nbString_GetCString(sRead), "void") == 0)
						{
							pToken->nType = TOKEN_KW_VOID;
							nbString_Set(sRead, "");
						}
						else if (strcmp(nbString_GetCString(sRead), "int") == 0)
						{
							pToken->nType = TOKEN_KW_INT;
							nbString_Set(sRead, "");
						}
						else
						{
							pToken->sToken = sRead;
							pToken->nType = TOKEN_ARBITARY;
							sRead = nbString_Create("");
						}

						nbVector_PushBack(pTokenVector, pToken);
					}

					if (nType == TOKEN_END_OF_FILE)
						break;


					if (nType != TOKEN_SPACE &&
						nType != TOKEN_TAB &&
						nType != TOKEN_NEW_LINE &&
						nType != TOKEN_COMMENT
						)
					{
						Token* pToken = nbMalloc(sizeof(Token));
						pToken->nType = nType;
						nbVector_PushBack(pTokenVector, pToken);
					}
				}
				else
				{
					nbString_AppendChar(sRead, c);
				}

				i++;
				//nLine++;
				//nColumn++;
			}

			nbFree(szBuffer);
			fclose(pFile);

			nbString_Destroy(sRead);
		}
			
	}

	{
		int i = 0;
		for (i = 0; i < nbVector_GetSize(pTokenVector); i++)
		{
			Token* pToken = nbVector_Get(pTokenVector, i);
			Token_DebugPrint(pToken);
		}
	}



	{
		Ast* pAst = Ast_Create(pTokenVector);
		nbString* sTemp = nbString_Create("");

		Ast_CStringify(pAst, sTemp, 0);
		printf("%s\n", nbString_GetCString(sTemp));

		nbString_Destroy(sTemp);
		Ast_Destroy(pAst);
	}

	// cleanup
	while (nbVector_GetSize(pTokenVector) > 0)
	{
		Token* pToken = nbVector_PopFront(pTokenVector);
		if (pToken->sToken)
			nbString_Destroy(pToken->sToken);
		nbFree(pToken);
	}

	nbVector_Destroy(pTokenVector);

	nbMemoryManager_Shutdown();

	return 0;
}

