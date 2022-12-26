#pragma once
#include "Vertex.h"
#include <vector>
#include "Polygon3D.h"
#include "Matrix.h"
#include <vector>
#include "Camera.h"

using namespace std;

class Model
{
public:
	Model();
	~Model();
	// Accessors
    const vector <Polygon3D>& GetPolygons();
	const vector <Vertex>& GetVertices();
	const vector <Vertex>& GetTransformedVertices();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);
	void ApplyTransformToLocalVertices(const Matrix& transform);
	void ApplyTransformToTransformedVertices(const Matrix& transform);
	void Dehomogenize();
	
	void CalculateBackfaces(Camera camera);
	static bool SortAverageZ(const Polygon3D& polygon1, const Polygon3D& polygon2);
	void Sort(void);
	
private:
	 vector<Polygon3D>	_polygons;
	 vector<Vertex>	    _vertices;
	 vector<Vertex>     _transformedVertices;
};

