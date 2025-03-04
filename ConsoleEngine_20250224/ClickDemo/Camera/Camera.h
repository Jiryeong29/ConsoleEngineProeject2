#pragma once
#include "Actor/DrawableActor.h"

class GameLevel;
class Camera : public DrawableActor
{


	RTTI_DECLARATIONS(Camera, DrawableActor)
public:
	Camera(GameLevel* level);
	virtual ~Camera();

	
	void Draw() override;
	void Update(float deltaTime) override;
private:

	GameLevel* gameLevel;
	bool toggle;
};