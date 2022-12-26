#include "Rasteriser.h"

Rasteriser app;

bool Rasteriser::Initialise()
{
	_camera = Camera(0.0f, 0.0f, 0.0f, Vertex(0, 0, -50, 1));
	
	if (!MD2Loader::LoadModel("cartman.md2", _model,
							&Model::AddPolygon,
							&Model::AddVertex))
	{
		return false;
	}
	return true;
}

void Rasteriser::Update(const Bitmap& bitmap)
{
	_frameCounter++;

	// Performing transformation within specific frame intervals
	if (_frameCounter > 0 && _frameCounter <= 100)
	{
		_transformationMatrix = _transformationMatrix * _yRotationMatrix;
	}
	else if (_frameCounter > 100 && _frameCounter <= 101)
	{
		_transformationMatrix = _identityMatrix;
	}
	else if (_frameCounter > 101 && _frameCounter <= 200)
	{
		_transformationMatrix = _transformationMatrix * _xRotationMatrix;
	}
	else if (_frameCounter > 200 && _frameCounter <= 201)
	{
		_transformationMatrix = _identityMatrix;
	}
	else if (_frameCounter > 201 && _frameCounter <= 300)
	{
		_transformationMatrix = _transformationMatrix * _zRotationMatrix;
	}
	else if (_frameCounter > 300 && _frameCounter <= 301)
	{
		_transformationMatrix = _identityMatrix;
	}
	else if (_frameCounter > 301 && _frameCounter <= 400)
	{
		_transformationMatrix = _transformationMatrix * _scaledMatrix;
	}
	else if (_frameCounter > 400 && _frameCounter <= 401)
	{
		_transformationMatrix = _identityMatrix;
	}
	else if (_frameCounter > 401 && _frameCounter <= 500)
	{
		_transformationMatrix = _transformationMatrix * _translateMatrix  ;
	}
	else if (_frameCounter > 500 && _frameCounter <= 501)
	{
		_transformationMatrix = _identityMatrix;
	}
	else
	{
		// Returning back to the Y rotation once finished
		_transformationMatrix = _transformationMatrix * _yRotationMatrix;
	}
	
	GenerateViewMatrix(1, bitmap.GetWidth(), bitmap.GetHeight());
	GeneratePerspectiveMatrix(1, float(bitmap.GetWidth()) / float(bitmap.GetHeight()));
}

void Rasteriser::Render(const Bitmap& bitmap)
{
	if (_frameCounter < _backfaceCounter)
	{
		bitmap.Clear(RGB(255, 255, 255));
		_model.ApplyTransformToLocalVertices(_transformationMatrix);
		_model.ApplyTransformToTransformedVertices(_camera.GetViewingMatrix());
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_model.Dehomogenize();
		_model.ApplyTransformToTransformedVertices(_viewMatrix);
		DrawWireFrame(bitmap);
	}
	else
	{
		bitmap.Clear(RGB(255, 255, 255));
		_model.ApplyTransformToLocalVertices(_transformationMatrix);
		_model.CalculateBackfaces(_camera);
		_model.ApplyTransformToTransformedVertices(_camera.GetViewingMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_model.Dehomogenize();
		_model.ApplyTransformToTransformedVertices(_viewMatrix);
		DrawWireFrame(bitmap);
	}
}

void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	 _perspectiveMatrix = Matrix{d/aspectRatio,0,0,0,
							     0,d,0,0,
							     0,0,d,0,
							     0,0,1,0};
}

void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	_viewMatrix = Matrix{float(width)/2,0,0,float(width)/2,
						 0,float(-height)/2,0,float(height)/2,
						 0,0,d/2,d/2,
						 0,0,0,1};
}

void Rasteriser::DrawWireFrame(const Bitmap& bitmap)
{
	// Creating text for each transformation
	HDC hdc = bitmap.GetDC();
	RECT rect = { 20, 20, 400, 400 };
	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);

	// Adding 1 the counter every time
	_labelCounter++;

	if (_labelCounter > 0 && _labelCounter <= 100)
	{
		DrawText(hdc, L"Wireframe     Y - Rotation", -1, &rect, DT_LEFT);
	}
	else if (_labelCounter > 100 && _labelCounter <= 200)
	{
		DrawText(hdc, L"Wireframe     X - Rotation", -1, &rect, DT_LEFT);
	}
	else if (_labelCounter > 200 && _labelCounter <= 300)
	{
		DrawText(hdc, L"Backface Culling     Z - Rotation", -1, &rect, DT_LEFT);
	}
	else if (_labelCounter > 300 && _labelCounter <= 400)
	{
		DrawText(hdc, L"Backface Culling     Scaling", -1, &rect, DT_LEFT);
	}
	else if (_labelCounter > 400 && _labelCounter <= 500)
	{
		DrawText(hdc, L"Backface Culling     Translating", -1, &rect, DT_LEFT);
	}
	else
	{
		// Return back to the Y rotation after finishing 
		DrawText(hdc, L"Backface Culling     Y - Rotation", -1, &rect, DT_LEFT);
	}

	std::vector<Polygon3D> polygonStore = _model.GetPolygons();
	std::vector<Vertex> vertexStore = _model.GetTransformedVertices();
	
	if (_frameCounter < _backfaceCounter)
	{
		for (int i = 0; i < polygonStore.size(); i++)
		{
			
				// PolygonStore[i] references current polygon in loop
				// GetIndex will retrieve value at given index
				// PolygonStore[i].getIndex will return correct item from given index
				Vertex vertex1 = vertexStore[polygonStore[i].GetIndex(0)];
				Vertex vertex2 = vertexStore[polygonStore[i].GetIndex(1)];
				Vertex vertex3 = vertexStore[polygonStore[i].GetIndex(2)];

				MoveToEx(hdc, (int)vertex1.GetX(), (int)vertex1.GetY(), NULL);
				LineTo(hdc, (int)vertex2.GetX(), (int)vertex2.GetY());
				LineTo(hdc, (int)vertex3.GetX(), (int)vertex3.GetY());
				LineTo(hdc, (int)vertex1.GetX(), (int)vertex1.GetY());
			
		}
	}
	else
	{
		for (int i = 0; i < polygonStore.size(); i++)
		{
			if (polygonStore[i].GetCulling() == false)
			{
				Vertex vertex1 = vertexStore[polygonStore[i].GetIndex(0)];
				Vertex vertex2 = vertexStore[polygonStore[i].GetIndex(1)];
				Vertex vertex3 = vertexStore[polygonStore[i].GetIndex(2)];

				MoveToEx(hdc, (int)vertex1.GetX(), (int)vertex1.GetY(), NULL);
				LineTo(hdc, (int)vertex2.GetX(), (int)vertex2.GetY());
				LineTo(hdc, (int)vertex3.GetX(), (int)vertex3.GetY());
				LineTo(hdc, (int)vertex1.GetX(), (int)vertex1.GetY());
			}
		}
	}
}