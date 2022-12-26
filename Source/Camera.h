#pragma once
#include "Vertex.h"
#include "Matrix.h"
#include <cmath>

class Camera
{
public:

	// Constructors 
	Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	~Camera();

	// Accessors
	Vertex	GetPosition() const;
	void	SetPosition(Vertex);
	Matrix	GetViewingMatrix() const;
	Vertex	CameraPosition() const;

private:
	Vertex	_position = Vertex(0, 0, -50, 1);
	Matrix	_viewMatrix;
};

