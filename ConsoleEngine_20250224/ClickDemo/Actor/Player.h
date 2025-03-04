#pragma once
#include <vector>
#include "Algorithm/Node.h"
#include "Actor/DrawableActor.h"
class AStar;
class GameLevel;
class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(GameLevel* level);
	virtual void Update(float deltaTime) override;
	//virtual void Draw() override;
	AStar* aStar;
	GameLevel* gameLevel;
};