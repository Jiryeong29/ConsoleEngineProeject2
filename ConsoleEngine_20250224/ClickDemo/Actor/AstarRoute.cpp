#include "AstarRoute.h"

AstarRoute::AstarRoute(int x, int y)
	: DrawableActor("*")
{
	color = Color::Green;
	SetWorldPosition(Vector2(x, y));
}

AstarRoute::~AstarRoute()
{
}
