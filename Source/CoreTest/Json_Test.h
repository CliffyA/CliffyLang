NB_TEST_BEGIN(Json, Load)
{
	FILE* pProcess;
	char c;

	pProcess = popen("clang-11 -Xclang -ast-dump=json Source/Executable/main.c", "r");

	ASSERT_TRUE(pProcess);

	while ((c = fgetc(pProcess)) != EOF)
		putchar(c);

	pclose(pProcess);


	/*Uint8 nX;
	Uint8 nY;
	Uint8 nMineCount;

	Game* pGame = Game_Create(10, 20, 1, 5, 0);

		ASSERT_EQ(Game_GetWidth(pGame), 10);
		ASSERT_EQ(Game_GetHeight(pGame), 20);

		nMineCount = 0;
		for (nX = 0; nX < Game_GetWidth(pGame); nX++)
			for (nY = 0; nY < Game_GetHeight(pGame); nY++)
				if (Game_GetMineType(pGame, nX, nY) > 0)
					nMineCount++;
		ASSERT_EQ(nMineCount, 5);

	Game_Destroy(pGame);*/

	printf("TEST!");
}
