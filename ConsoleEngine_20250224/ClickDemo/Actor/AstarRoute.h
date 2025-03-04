#pragma once
#include "Actor/DrawableActor.h"
class AstarRoute : public DrawableActor
{
	RTTI_DECLARATIONS(AstarRoute, DrawableActor)
public:
	AstarRoute(int x, int y);
	~AstarRoute();
};

