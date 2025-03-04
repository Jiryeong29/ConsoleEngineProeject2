#include "QuadMesh.h"
#include "Vertex.h"
#include "../Shader/Shader.h"
#include "Shader/TextureMappingShader.h"
#include "Math/Matrix4.h"

namespace Blue
{
	QuadMesh::QuadMesh()
	{
		// 정점 배열.
		std::vector<Vertex> vertices =
		{
			Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
			Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f)),
			Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f)),
			Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(1.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f)),
		};

		// 인덱스 배열.
		std::vector<uint32> indices = { 0, 1, 3, 1, 2, 3 };

		meshes.emplace_back(std::make_shared<MeshData>(vertices, indices));
		shaders.emplace_back(std::make_shared<TextureMappingShader>("T_coord.png"));

		//transform.scale = Vector3::One * 0.2f;
		//transform.position = Vector3(-0.5f, 0.0f, 0.5f);
	}

	void QuadMesh::Update(float deltaTime)
	{
		static float angle = 0.0f;
		angle += 60.0f * deltaTime;
		
		//Rotate(angle);

		//transform.rotation.z += 60.0f * deltaTime;

		static float t = 0.0f;
		static float direction = 1.0f;
		t += direction * (deltaTime / 2.0f);

		if (t > 1)
		{
			direction = -1.0f;
		}
		if (t < 0.0f)
		{
			direction = 1.0f;
		}
		
		static Vector3 startScale = Vector3::One * 1.0f;
		static Vector3 endScale = Vector3::One * 2.0f;
		//transform.scale = Lerp(startScale, endScale, t);
		//Scale(t);
	}

	void QuadMesh::Draw()
	{
		transform.Bind();
		Mesh::Draw();
	}

	void QuadMesh::Rotate(float angle)
	{
		// 정점 배열.
		static std::vector<Vertex> vertices =
		{
			Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
			Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f)),
			Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f)),
			Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(1.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f)),
		};

		static bool hasInitialized = false;
		static std::vector<Vertex> result;
		if (!hasInitialized)
		{
			result.assign(vertices.begin(), vertices.end());
			hasInitialized = true;
		}

		Matrix4 rotation = Matrix4::RotationZ(angle);
		result[0].position = vertices[0].position * rotation;
		result[1].position = vertices[1].position * rotation;
		result[2].position = vertices[2].position * rotation;
		result[3].position = vertices[3].position * rotation;

		meshes[0]->UpdateVertexBuffer(result);
	}

	void QuadMesh::Scale(float scaleFactor)
	{
		// 정점 배열.
		static std::vector<Vertex> vertices =
		{
			Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)),
			Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f)),
			Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f)),
			Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(1.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f)),
		};

		static Vector3 startScale = Vector3::One * 1.0f;
		static Vector3 endScale = Vector3::One * 2.0f;

		static bool hasInitialized = false;
		static std::vector<Vertex> result;
		if (!hasInitialized)
		{
			result.assign(vertices.begin(), vertices.end());
			hasInitialized = true;
		}

		Matrix4 scale = Matrix4::Scale(Lerp(startScale, endScale, scaleFactor));
		result[0].position = vertices[0].position * scale;
		result[1].position = vertices[1].position * scale;
		result[2].position = vertices[2].position * scale;
		result[3].position = vertices[3].position * scale;

		meshes[0]->UpdateVertexBuffer(result);
	}
}