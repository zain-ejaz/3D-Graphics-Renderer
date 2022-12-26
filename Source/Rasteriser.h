#pragma once
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Model.h"
#include "Camera.h"
#include <cmath>
#include "MD2Loader.h"
#include "Polygon3D.h"
#include <vector>

class Rasteriser : public Framework
{
public:

	// Constructors and Methods
	bool Initialise();
	void Update(const Bitmap& bitmap);
	void Render(const Bitmap& bitmap);
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);
	void DrawWireFrame(const Bitmap& bitmap);

private:

	float X = 0.025f;
	int    _frameCounter = 0;
	int    _labelCounter = 0;
	int    _backfaceCounter = 201;
	Model	_model;
	Camera	_camera;
	Matrix	_perspectiveMatrix;
	Matrix	_viewMatrix;

	// Matrices for each transformation
	Matrix _identityMatrix = Matrix{1,0,0,0,
									0,1,0,0,
									0,0,1,0,
								    0,0,0,1};

	Matrix  _transformationMatrix = Matrix{1,0,0,0,
										   0,1,0,0,
										   0,0,1,0,
										   0,0,0,1};

	Matrix  _xRotationMatrix = Matrix{1,0,0,0,
									  0,cos(X),-sin(X),0,
							          0,sin(X),cos(X),0,
							          0,0,0,1};

	Matrix  _yRotationMatrix = Matrix{cos(X),0,sin(X),0,
							          0,1,0,0,
							          -sin(X),0,cos(X),0,
							          0,0,0,1};

	Matrix  _zRotationMatrix = Matrix{cos(X),-sin(X),0,0,
							          sin(X),cos(X),0,0,
							          0,0,1,0,
							          0,0,0,1};

	Matrix  _scaledMatrix = Matrix{1.009f,0,0,0,
						           0,1.009f,0,0,
						           0,0,1.009f,0,
						           0,0,0,1};

	Matrix  _translateMatrix = Matrix{1,0,0,1.0f,
									  0,1,0,1.0f,
							          0,0,1,1.0f,
							          0,0,0,1};
};

