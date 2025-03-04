#include "Core/Engine.h"
#include <iostream>

using namespace Blue;

int main()
{
	Engine engine(1280, 800, TEXT("Engine Demo"), GetModuleHandle(nullptr));
	engine.Run();
}