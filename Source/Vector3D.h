#pragma once
class Vector3D
{
public:
	// Constructors
	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& other);

	// Deconstructor
	~Vector3D();

	static float DotProduct(const Vector3D& vectorA, const Vector3D& vectorB);
	static Vector3D CrossProduct(const Vector3D& vectorA, const Vector3D& vectorB);

	// Accessors
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float z);

private:

	float _x;
	float _y;
	float _z;
};


