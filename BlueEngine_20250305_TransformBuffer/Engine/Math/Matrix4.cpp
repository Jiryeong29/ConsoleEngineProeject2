#include "Matrix4.h"
#include <cmath>
#include <DirectXMath.h>

namespace Blue
{
	Matrix4 Matrix4::Identity = Matrix4();

	Matrix4::Matrix4()
	{
		memset(elements, 0, sizeof(float) * 4 * 4);
		m00 = m11 = m22 = m33 = 1.0f;
	}

	Matrix4::Matrix4(const Matrix4& other)
	{
		memcpy(elements, other.elements, sizeof(float) * 4 * 4);
	}

	Matrix4 Matrix4::Translation(const Vector3& position)
	{
		return Matrix4::Translation(position.x, position.y, position.z);
	}

	Matrix4 Matrix4::Translation(float x, float y, float z)
	{
		Matrix4 m;
		m.m00 = 1.0f;	m.m01 = 0.0f;	m.m02 = 0.0f;	m.m03 = 0.0f;
		m.m10 = 0.0f;	m.m11 = 1.0f;	m.m12 = 0.0f;	m.m13 = 0.0f;
		m.m20 = 0.0f;	m.m21 = 0.0f;	m.m22 = 1.0f;	m.m23 = 0.0f;
		m.m30 = x;		m.m31 = y;		m.m32 = z;		m.m33 = 1.0f;

		return m;
	}

	Matrix4 Matrix4::Rotation(const Vector3& rotation)
	{
		return Rotation(rotation.x, rotation.y, rotation.z);
	}

	Matrix4 Matrix4::Rotation(float x, float y, float z)
	{
		return RotationX(x) * RotationY(y) * RotationZ(z);
	}

	Matrix4 Matrix4::RotationX(float angle)
	{
		Matrix4 m;

		float cosAngle = std::cos(angle * DegreeToRadian);
		float sinAngle = std::sin(angle * DegreeToRadian);

		m.m00 = 1.0f;	m.m01 = 0.0f;		m.m02 = 0.0f;		m.m03 = 0.0f;
		m.m10 = 0.0f;	m.m11 = cosAngle;	m.m12 = sinAngle;	m.m13 = 0.0f;
		m.m20 = 0.0f;	m.m21 = -sinAngle;	m.m22 = cosAngle;	m.m23 = 0.0f;
		m.m30 = 0.0f;	m.m31 = 0.0f;		m.m32 = 0.0f;		m.m33 = 1.0f;

		return m;
	}

	Matrix4 Matrix4::RotationY(float angle)
	{
		Matrix4 m;

		float cosAngle = std::cos(angle * DegreeToRadian);
		float sinAngle = std::sin(angle * DegreeToRadian);

		m.m00 = cosAngle;	m.m01 = 0.0f;	m.m02 = -sinAngle;	m.m03 = 0.0f;
		m.m10 = 0.0f;		m.m11 = 1.0f;	m.m12 = 0.0f;		m.m13 = 0.0f;
		m.m20 = sinAngle;	m.m21 = 0.0f;	m.m22 = cosAngle;	m.m23 = 0.0f;
		m.m30 = 0.0f;		m.m31 = 0.0f;	m.m32 = 0.0f;		m.m33 = 1.0f;

		return m;
	}

	Matrix4 Matrix4::RotationZ(float angle)
	{
		Matrix4 m;

		float cosAngle = std::cos(angle * DegreeToRadian);
		float sinAngle = std::sin(angle * DegreeToRadian);

		m.m00 = cosAngle;	m.m01 = sinAngle;	m.m02 = 0.0f;	m.m03 = 0.0f;
		m.m10 = -sinAngle;	m.m11 = cosAngle;	m.m12 = 0.0f;	m.m13 = 0.0f;
		m.m20 = 0.0f;		m.m21 = 0.0f;		m.m22 = 1.0f;	m.m23 = 0.0f;
		m.m30 = 0.0f;		m.m31 = 0.0f;		m.m32 = 0.0f;	m.m33 = 1.0f;

		return m;
	}

	Matrix4 Matrix4::Scale(const Vector3& scale)
	{
		return Scale(scale.x, scale.y, scale.z);
	}

	Matrix4 Matrix4::Scale(float x, float y, float z)
	{
		Matrix4 m;

		m.m00 = x;		m.m01 = 0.0f;	m.m02 = 0.0f;	m.m03 = 0.0f;
		m.m10 = 0.0f;	m.m11 = y;		m.m12 = 0.0f;	m.m13 = 0.0f;
		m.m20 = 0.0f;	m.m21 = 0.0f;	m.m22 = z;		m.m23 = 0.0f;
		m.m30 = 0.0f;	m.m31 = 0.0f;	m.m32 = 0.0f;	m.m33 = 1.0f;

		return m;
	}

	Matrix4 Matrix4::Perspective(float fieldOfView, float width, float height, float zNear, float zFar)
	{
		return Matrix4();
	}

	Matrix4 Matrix4::Transpose(const Matrix4& target)
	{
		Matrix4 m = target;

		std::swap(m.m01, m.m10);
		std::swap(m.m02, m.m20);
		std::swap(m.m03, m.m30);

		std::swap(m.m12, m.m21);
		std::swap(m.m13, m.m31);
		std::swap(m.m23, m.m32);

		return m;
	}

	Matrix4& Matrix4::operator=(const Matrix4& other)
	{
		memcpy(elements, other.elements, sizeof(float) * 4 * 4);
		return *this;
	}

	Matrix4 Matrix4::operator*(const Matrix4& other)
	{
		Matrix4 m;
		m.m00 = other.m00 * m00 + other.m10 * m01 + other.m20 * m02 + other.m30 * m03;
		m.m01 = other.m01 * m00 + other.m11 * m01 + other.m21 * m02 + other.m31 * m03;
		m.m02 = other.m02 * m00 + other.m12 * m01 + other.m22 * m02 + other.m32 * m03;
		m.m03 = other.m03 * m00 + other.m13 * m01 + other.m23 * m02 + other.m33 * m03;

		m.m10 = other.m00 * m10 + other.m10 * m11 + other.m20 * m12 + other.m30 * m13;
		m.m11 = other.m01 * m10 + other.m11 * m11 + other.m21 * m12 + other.m31 * m13;
		m.m12 = other.m02 * m10 + other.m12 * m11 + other.m22 * m12 + other.m32 * m13;
		m.m13 = other.m03 * m10 + other.m13 * m11 + other.m23 * m12 + other.m33 * m13;

		m.m20 = other.m00 * m20 + other.m10 * m21 + other.m20 * m22 + other.m30 * m23;
		m.m21 = other.m01 * m20 + other.m11 * m21 + other.m21 * m22 + other.m31 * m23;
		m.m22 = other.m02 * m20 + other.m12 * m21 + other.m22 * m22 + other.m32 * m23;
		m.m23 = other.m03 * m20 + other.m13 * m21 + other.m23 * m22 + other.m33 * m23;

		m.m30 = other.m00 * m30 + other.m10 * m31 + other.m20 * m32 + other.m30 * m33;
		m.m31 = other.m01 * m30 + other.m11 * m31 + other.m21 * m32 + other.m31 * m33;
		m.m32 = other.m02 * m30 + other.m12 * m31 + other.m22 * m32 + other.m32 * m33;
		m.m33 = other.m03 * m30 + other.m13 * m31 + other.m23 * m32 + other.m33 * m33;

		return m;
	}

	Matrix4 Matrix4::operator*=(const Matrix4& other)
	{
		*this = *this * other;
		return *this;
	}

	Vector3 operator*(const Matrix4& matrix, const Vector3& vector)
	{
		return vector * matrix;
	}

	Vector3 operator*(const Vector3& vector, const Matrix4& matrix)
	{
		Vector3 result;

		result.x = matrix.m00 * vector.x + matrix.m10 * vector.y + matrix.m20 * vector.z;
		result.y = matrix.m01 * vector.x + matrix.m11 * vector.y + matrix.m21 * vector.z;
		result.z = matrix.m02 * vector.x + matrix.m12 * vector.y + matrix.m22 * vector.z;

		return result;
	}
}