#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Map/Map.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	const char* path = "Map/MapData.txt";

	Engine engine;
	engine.LoadLevel(new GameLevel());
	engine.Run();

}
