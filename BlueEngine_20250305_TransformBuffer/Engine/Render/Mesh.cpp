#include "Mesh.h"
#include "../Core/Engine.h"
#include "../Shader/Shader.h"

namespace Blue
{
	MeshData::MeshData()
	{
	}

	MeshData::MeshData(
		const std::vector<Vertex>& vertices, 
		const std::vector<uint32>& indices)
	{
		// 파라미터 복사.
		this->vertices.assign(vertices.begin(), vertices.end());
		stride = Vertex::Stride();
		this->indices.assign(indices.begin(), indices.end());

		D3D11_BUFFER_DESC vertexbufferDesc = {};
		vertexbufferDesc.ByteWidth = stride * (uint32)vertices.size();
		vertexbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		// 정점 데이터.
		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = vertices.data();

		// 장치 얻어오기.
		ID3D11Device& device = Engine::Get().Device();

		// (정점)버퍼 생성
		auto result = device.CreateBuffer(
			&vertexbufferDesc, &vertexData, &vertexBuffer);

		if (FAILED(result))
		{
			MessageBoxA(
				nullptr,
				"Failed to create vertex buffer",
				"Error",
				MB_OK
			);

			__debugbreak();
		}

		D3D11_BUFFER_DESC indexbufferDesc = {};
		indexbufferDesc.ByteWidth = sizeof(uint32) * (uint32)indices.size();
		indexbufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		// 정점 데이터.
		D3D11_SUBRESOURCE_DATA indexData = {};
		indexData.pSysMem = indices.data();

		// 인덱스 버퍼 생성.
		result = device.CreateBuffer(
			&indexbufferDesc, &indexData, &indexBuffer
		);

		if (FAILED(result))
		{
			MessageBoxA(
				nullptr,
				"Failed to create index buffer",
				"Error",
				MB_OK
			);

			__debugbreak();
		}
	}

	MeshData::~MeshData()
	{
		// 리소스 해제.
		if (vertexBuffer)
		{
			vertexBuffer->Release();
		}
		if (indexBuffer)
		{
			indexBuffer->Release();
		}
	}

	void MeshData::UpdateVertexBuffer(const std::vector<Vertex>& vertices)
	{
		// 파라미터 복사.
		this->vertices.assign(vertices.begin(), vertices.end());

		if (vertexBuffer)
		{
			vertexBuffer->Release();
			vertexBuffer = nullptr;
		}

		D3D11_BUFFER_DESC vertexbufferDesc = {};
		vertexbufferDesc.ByteWidth = stride * (uint32)vertices.size();
		vertexbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		// 정점 데이터.
		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = vertices.data();

		// 장치 얻어오기.
		ID3D11Device& device = Engine::Get().Device();

		// (정점)버퍼 생성
		auto result = device.CreateBuffer(
			&vertexbufferDesc, &vertexData, &vertexBuffer);

		if (FAILED(result))
		{
			MessageBoxA(
				nullptr,
				"Failed to create vertex buffer",
				"Error",
				MB_OK
			);

			__debugbreak();
		}
	}

	void MeshData::Bind()
	{
		// 컨텍스트 얻어오기.
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// 정점/인덱스 버퍼 바인딩.
		static uint32 offset = 0;
		context.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context.IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	Mesh::Mesh()
	{
	}

	void Mesh::Draw()
	{
		// 컨텍스트 얻어오기.
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// 루프 순회하면서 바인딩 & 드로우.
		for (int ix = 0; ix < (int32)meshes.size(); ++ix)
		{
			meshes[ix]->Bind();
			shaders[ix]->Bind();
			context.DrawIndexed(meshes[ix]->IndexCount(), 0, 0);
		}
	}
}