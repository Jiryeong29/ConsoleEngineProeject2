#pragma once
#include "Actor/DrawableActor.h"
class Wall : public DrawableActor
{
	RTTI_DECLARATIONS(Wall, DrawableActor)
public:
	Wall(int x, int y);

private:
};