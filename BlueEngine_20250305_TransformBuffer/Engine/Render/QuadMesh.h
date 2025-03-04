#pragma once

#include "Mesh.h"
#include "Math/Transform.h"

namespace Blue
{
	// 삼각형 메시 클래스.
	class QuadMesh : public Mesh
	{
	public:
		QuadMesh();

		void Update(float deltaTime);
		virtual void Draw() override;

	private:
		void Rotate(float angle);
		void Scale(float scaleFactor);

	private:
		Transform transform;
	};
}