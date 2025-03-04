#pragma once

#include "Actor.h"

class ENGINE_API DrawableActor : public Actor
{
	// RTTI.
	RTTI_DECLARATIONS(DrawableActor, Actor)

public:
	DrawableActor(const char* image = "");
	//virtual ~DrawableActor() = default;
	virtual ~DrawableActor();

	virtual void Draw() override;
	virtual void SetPosition(const Vector2& newPosition) override;


	// 월드 좌표를 반환하는 함수.
	Vector2 GetWorldPosition() const { return worldPosition; };

	// 월드 좌표를 설정하는 함수.
	void SetWorldPosition(int x, int y);
	void SetWorldPosition(const Vector2& newPosition);


	// 충돌 확인 함수.
	bool Intersect(const DrawableActor& other);

	// Getter.
	inline int Width() const { return width; }

protected:

	// 월드 좌표를 저장하는 벡터.
	Vector2 worldPosition;

	// 화면에 그릴 문자 값.
	char* image;

	// 너비(문자열 길이).
	int width = 0;

	// 색상 값.
	Color color = Color::White;
};