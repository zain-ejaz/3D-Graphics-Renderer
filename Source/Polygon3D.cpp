#include "Polygon3D.h"


Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
	_culling = false;
	_averageDepth = 0;
}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_culling = false;
	_averageDepth = 0;
}

Polygon3D::~Polygon3D()
{
}

Polygon3D::Polygon3D(const Polygon3D& p)
{
	_indices[0] = p.GetIndex(0);
	_indices[1] = p.GetIndex(1);
	_indices[2] = p.GetIndex(2);
	_culling = p._culling;
	_averageDepth = p._averageDepth;
}

int Polygon3D::GetIndex(int i) const
{
	return _indices[i];
}

bool Polygon3D::GetCulling() const
{
	return _culling;
}

void Polygon3D::SetCulling(bool culling)
{
	_culling = culling;
}

float Polygon3D::GetAverageDepth() const
{
	return _averageDepth;
}

void Polygon3D::SetAverageDepth(const float averageDepth)
{
	_averageDepth = averageDepth;
}

Polygon3D& Polygon3D::operator=(const Polygon3D& rhs)
{
	if (this != &rhs)
	{
		_indices[0] = rhs.GetIndex(0);
		_indices[1] = rhs.GetIndex(1);
		_indices[2] = rhs.GetIndex(2);
		_culling = rhs._culling;
		_averageDepth = rhs._averageDepth;
	}
	return *this;
}




	


