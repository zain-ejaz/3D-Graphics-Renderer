#include "Model.h"
#include <algorithm>

using namespace std;

Model::Model()
{
}

Model::~Model()
{
}

const vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

const vector <Vertex>& Model::GetVertices()
{
	return _vertices;
}

const vector <Vertex>& Model::GetTransformedVertices()
{
	return _transformedVertices;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetVertexCount() const
{
	return _vertices.size();
}

void Model::AddVertex(float x, float y, float z)
{
	_vertices.push_back(Vertex(x, y, z, 1));
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2));
}

void Model::ApplyTransformToLocalVertices(const Matrix& transform)
{
	_transformedVertices.clear(); // Empty the Vector
	// Loop through all vertices
	for (int i = 0; i < _vertices.size(); i++)
	{
		Vertex tranformVertices = transform * _vertices[i]; // Multiply each vertex to "transform"
		_transformedVertices.push_back(tranformVertices); // Add result to _transformedVertices vector
	}
}

void Model::ApplyTransformToTransformedVertices(const Matrix& transform)
{
	// Loop through all transformed vertices
	for (int i = 0; i < _transformedVertices.size(); i++)
	{
		// Multiply each transform matrix by transformed vertices
		_transformedVertices[i] = transform * _transformedVertices[i];
	}
}

void Model::Dehomogenize()
{
	// Looping through all the transformed vertcies in the model.
	for (int i = 0; i < _transformedVertices.size(); i++)
	{
		// Creating a temporary vertex.
		Vertex tempVertex = _transformedVertices.at(i);
		// Dehomogenizing by dividing each value by W
		tempVertex.SetX(tempVertex.GetX() / tempVertex.GetW());
		tempVertex.SetY(tempVertex.GetY() / tempVertex.GetW());
		tempVertex.SetZ(tempVertex.GetZ() / tempVertex.GetW());
		tempVertex.SetW(tempVertex.GetW() / tempVertex.GetW());

		_transformedVertices[i] = tempVertex;
	}
}

void Model::CalculateBackfaces(Camera camera)
{
	for (int i = 0; i < GetPolygonCount(); i++)
	{
		// Getting vertices of the indicies that make up the polygon
		Vertex vertex0 = _transformedVertices[_polygons[i].GetIndex(0)];
		Vertex vertex1 = _transformedVertices[_polygons[i].GetIndex(1)];
		Vertex vertex2 = _transformedVertices[_polygons[i].GetIndex(2)];

		// Constructing subtract vectors 
		Vector3D vectorA = Vertex::SubtractVertex(vertex0, vertex1);
		Vector3D vectorB = Vertex::SubtractVertex(vertex0, vertex2);

		Vector3D normalVector = Vector3D::CrossProduct(vectorB, vectorA);
		Vector3D eyeVector = Vertex::SubtractVertex(vertex0, camera.CameraPosition());
		float dotProduct = Vector3D::DotProduct(normalVector, eyeVector);

		if (dotProduct < 0.0f)
		{
			// Marking the polygon for culling
			_polygons[i].SetCulling(true);
		}
		else
		{
			_polygons[i].SetCulling(false);
		}
	}
}

bool Model::SortAverageZ(const Polygon3D& polygon1, const Polygon3D& polygon2)
{
	return polygon1.GetAverageDepth() > polygon2.GetAverageDepth();
}

void Model::Sort(void)
{
	for (int i = 0; i < _polygons.size(); i++)
	{
		Vertex vertex0 = _transformedVertices[_polygons[i].GetIndex(0)];
		Vertex vertex1 = _transformedVertices[_polygons[i].GetIndex(1)];
		Vertex vertex2 = _transformedVertices[_polygons[i].GetIndex(2)];

		// Calculating the average Z depth and storing the value
		float averageZDepth = (vertex0.GetZ() + vertex1.GetZ() + vertex2.GetZ()) / 3;
		_polygons[i].SetAverageDepth(averageZDepth);
	}

	// Sort algorithm
	sort(_polygons.begin(), _polygons.end(), SortAverageZ);
}