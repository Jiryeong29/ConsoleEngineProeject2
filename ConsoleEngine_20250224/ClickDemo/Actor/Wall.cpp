#include "Wall.h"

Wall::Wall(int x, int y)
	: DrawableActor("#")
{
	color = Color::Red;
	SetWorldPosition(Vector2(x,y));

}
