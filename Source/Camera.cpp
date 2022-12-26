#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	// Created by multiplying each axis rotation and vertex position 
	_viewMatrix = Matrix{1,0,0,0,
						0,cos(xRotation),sin(xRotation),0,
						0,-sin(xRotation),cos(xRotation),0,
						0,0,0,1} *
				 Matrix{cos(yRotation),0,-sin(yRotation),0,
						0,1,0,0,
						sin(yRotation),0,cos(yRotation),0,
						0,0,0,1} *
				 Matrix{cos(zRotation),sin(zRotation),0,0,
						-sin(zRotation),cos(zRotation),0,0,
						0,0,1,0,
						0,0,0,1} *
				 Matrix{1,0,0,-position.GetX(),
						0,1,0,-position.GetY(),
						0,0,1,-position.GetZ(),
						0,0,0,1};
}

Camera::~Camera()
{
}

Vertex Camera::GetPosition() const
{
	return Vertex();
}

void Camera::SetPosition(Vertex)
{
}

Matrix Camera::GetViewingMatrix() const
{
	return _viewMatrix;
}

Vertex Camera::CameraPosition() const
{
	return _position;
}
