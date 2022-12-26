#include "Vector3D.h"

Vector3D::Vector3D()
{
    _x = 0.0f;
    _y = 0.0f;
    _z = 0.0f;
}

Vector3D::Vector3D(float x, float y, float z)
{
    _x = x;
    _y = y;
    _z = z;
}

Vector3D::Vector3D(const Vector3D& other)
{
    _x = other.GetX();
    _y = other.GetY();
    _z = other.GetZ();
}

Vector3D::~Vector3D()
{
}

float Vector3D::DotProduct(const Vector3D& vectorA, const Vector3D& vectorB)
{
    float dotProductCalculation = 0.0f;
    dotProductCalculation = (vectorA.GetX() * vectorB.GetX())
                          + (vectorA.GetY() * vectorB.GetY())
                          + (vectorA.GetZ() * vectorB.GetZ());
    return dotProductCalculation;
}

Vector3D Vector3D::CrossProduct(const Vector3D& vectorA, const Vector3D& vectorB)
{
    Vector3D crossProductCalculation;
    crossProductCalculation.SetX((vectorA.GetY() * vectorB.GetZ()) - (vectorA.GetZ() * vectorB.GetY()));
    crossProductCalculation.SetY((vectorA.GetZ() * vectorB.GetX()) - (vectorA.GetX() * vectorB.GetZ()));
    crossProductCalculation.SetZ((vectorA.GetX() * vectorB.GetY()) - (vectorA.GetY() * vectorB.GetX()));
    return crossProductCalculation;
}

float Vector3D::GetX() const
{
    return _x;
}

void Vector3D::SetX(const float x)
{
    _x = x;
}

float Vector3D::GetY() const
{
    return _y;
}

void Vector3D::SetY(const float y)
{
    _y = y;
}

float Vector3D::GetZ() const
{
    return _z;
}

void Vector3D::SetZ(const float z)
{
    _z = z;
}