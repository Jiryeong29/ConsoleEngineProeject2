#pragma once

#include "Vector3.h"
#include "Matrix4.h"
#include <d3d11.h>

namespace Blue
{
	class Transform
	{
		friend class Actor;
	public:
		Transform();
		~Transform();

		void Bind();

	public:
		Vector3 position = Vector3::Zero;
		Vector3 rotation = Vector3::Zero;
		Vector3 scale = Vector3::One;

	private:
		Matrix4 transformMatrix;
		ID3D11Buffer* constantBuffer = nullptr;
	};
}