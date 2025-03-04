#include "Start.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"

#include "Algorithm/AStar.h"
Start::Start(GameLevel* level)
	: DrawableActor("e"), gameLevel(level)
{
	color = Color::White;
	SetWorldPosition(Vector2(
		static_cast<int>(level->GetWorldSize().x / 2 + 5),
		static_cast<int>(level->GetWorldSize().y / 2+5)
	)
	);
}

void Start::Update(float deltaTime)
{
	Super::Update(deltaTime);


}