typedef struct nbString nbString;
typedef struct nbVector nbVector;



#define AST_TYPE_ROOT 0
#define AST_TYPE_CLASS 1
#define AST_TYPE_FUNCTION 2
#define AST_TYPE_BODY 3
#define AST_TYPE_PARAMETER_LIST 4
#define AST_TYPE_DECLARE 5
#define AST_TYPE_ASSIGNMENT 6


typedef struct Ast Ast;
struct Ast
{
	int nLine;
	int nColumn;

	int nType;
	nbString* sString;
	nbString* sString1;

	//nbVector* pChildVector;
	nbVector* pChildVector;
};

extern Ast* Ast_Create(nbVector* pTokenVector);
extern void Ast_Destroy(Ast* pAst);

extern void Ast_Stringify(Ast* pAst, nbString* sString, int nDepth);

#ifdef AST_SECRET
	extern Ast* Ast_SubCreate(Ast* pParent, int nType);
#endif