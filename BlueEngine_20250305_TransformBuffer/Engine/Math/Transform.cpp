#include "Transform.h"
#include "Core/Engine.h"

namespace Blue
{
	Transform::Transform()
	{
		transformMatrix = Matrix4::Scale(scale) * Matrix4::Rotation(rotation) * Matrix4::Translation(position);
		transformMatrix = Matrix4::Transpose(transformMatrix);

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = Matrix4::Stride();
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA bufferData = {};
		bufferData.pSysMem = &transformMatrix;

		ID3D11Device& device = Engine::Get().Device();
		auto result = device.CreateBuffer(&bufferDesc, &bufferData, &constantBuffer);
		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Error: Failed to create transform buffer.", "D3D Error", MB_OK);
			__debugbreak();
		}
	}

	Transform::~Transform()
	{
		if (constantBuffer)
		{
			constantBuffer->Release();
			constantBuffer = nullptr;
		}
	}

	void Transform::Bind()
	{
		static ID3D11DeviceContext& context = Engine::Get().Context();

		transformMatrix = Matrix4::Scale(scale) * Matrix4::Rotation(rotation) * Matrix4::Translation(position);
		transformMatrix = Matrix4::Transpose(transformMatrix);

		//D3D11_BUFFER_DESC bufferDesc = {};
		//bufferDesc.ByteWidth = Matrix4::Stride();
		//bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		//D3D11_SUBRESOURCE_DATA bufferData = {};
		//bufferData.pSysMem = &transformMatrix;

		context.UpdateSubresource(constantBuffer, 0, nullptr, &transformMatrix, 0, 0);
		context.VSSetConstantBuffers(0, 1, &constantBuffer);
	}
}