#pragma once

#include "Actor/DrawableActor.h"
class AStar;
class GameLevel;
class Start : public DrawableActor
{
public:
	Start(GameLevel* level);

	virtual void Update(float deltaTime) override;
private:
	GameLevel * gameLevel;
	AStar* aStar;
};