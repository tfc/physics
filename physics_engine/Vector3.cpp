/*
 *  Vector3.cpp
 *  GameBase
 *
 *  Created by Administrator on 12.10.10.
 *  Copyright 2010 Kristof Niederholtmeyer. All rights reserved.
 *
 */

#include "Vector3.h"
#include <math.h>
#include <iostream>

Vector3::Vector3()
{
  val.x = 0.0f;
  val.y = 0.0f;
  val.z = 0.0f;
  val.dummy = 0.0f;
}

Vector3::Vector3(const double xCoordinate,
    const double yCoordinate,
    const double zCoordinate,
    const double dum)
{
  val.x = xCoordinate;
  val.y = yCoordinate;
  val.z = zCoordinate;
  val.dummy = dum;
}

Vector3::Vector3(const Vector3& vector)
{
  val.x = vector.val.x;
  val.y = vector.val.y;
  val.z = vector.val.z;
  val.dummy = vector.val.dummy;
}

Vector3::~Vector3()
{

}

double Vector3::x() const
{
  return val.x;
}

double Vector3::y() const
{
  return val.y;
}

double Vector3::z() const
{
  return val.z;
}

Vector3 Vector3::rotatedZ(const double angle) const
{
  return Vector3(val.x*cos(angle) -val.y*sin(angle), val.x*sin(angle) +val.y*cos(angle), val.z);
}

Vector3 Vector3::perpendicular() const
{
  return Vector3(-val.y, val.x, val.y, val.z);
}

Vector3& Vector3::operator = (const Vector3& vector)
{
  val.x = vector.val.x;
  val.y = vector.val.y;
  val.z = vector.val.z;
  val.dummy = vector.val.dummy;

  return *this;
}

Vector3 Vector3::operator * (const double scalar)
{
  Vector3 newVector(val.x * scalar,
      val.y * scalar,
      val.z * scalar,
      val.dummy * scalar);
  return newVector;
}

Vector3 Vector3::operator *= (const double scalar)
{
  *this = *this * scalar;
  return *this;
        }

Vector3 Vector3::operator / (const double scalar)
{
  Vector3 newVector(val.x / scalar,
      val.y / scalar,
      val.z / scalar,
      val.dummy / scalar);
  return newVector;
}

Vector3 Vector3::operator + (const Vector3& vector)
{
  Vector3 newVector(val.x + vector.val.x, val.y + vector.val.y, val.z + vector.val.z, val.dummy +vector.val.dummy);
  return newVector;
}

Vector3 Vector3::operator - (const Vector3& vector)
{
  Vector3 newVector(val.x - vector.val.x, val.y - vector.val.y, val.z - vector.val.z);
  return newVector;
}

Vector3& Vector3::operator += (const Vector3& vector)
{
  val.x += vector.val.x;
  val.y += vector.val.y;
  val.z += vector.val.z;
  val.dummy += vector.val.dummy;

  return *this;
}

Vector3& Vector3::operator -= (const Vector3& vector)
{
  val.x -= vector.val.x;
  val.y -= vector.val.y;
  val.z -= vector.val.z;
  val.dummy -= vector.val.dummy;

  return *this;
}

// scalar product
double Vector3::operator * (const Vector3& vector)
{
  return (val.x * vector.val.x +
      val.y * vector.val.y +
      val.z * vector.val.z);
}

Vector3 Vector3::operator ^ (const Vector3& vector)
{
  return Vector3(
      val.y*vector.val.z -val.z*vector.val.y,
      -val.x*vector.val.z +val.z*vector.val.x,
      val.x*vector.val.y -val.y*vector.val.x);
}

bool Vector3::operator == (const Vector3& vector)
{
  return (val.x == vector.val.x &&
      val.y == vector.val.y &&
      val.z == vector.val.z);
}

bool Vector3::operator != (const Vector3& vector)
{
  return !(val.x == vector.val.x &&
      val.y == vector.val.y &&
      val.z == vector.val.z);
}

void Vector3::normalize()
{
  double l = length();
  val.x /= l;
  val.y /= l;
  val.z /= l;
}

double Vector3::length() const
{
  return sqrt(val.x*val.x +
      val.y*val.y +
      val.z*val.z);
}

double Vector3::lengthSquare() const
{
  return (val.x*val.x +
      val.y*val.y +
      val.z*val.z);
}

double Vector3::angle() const
{
  return atan2(val.y,val.x);
}

std::ostream &operator << (std::ostream &stream, const Vector3 &vector)
{
  stream << "Vector:" << std::endl;
  stream << "---------------------" << std::endl;
  stream << vector.val.x << std::endl;
  stream << vector.val.y << std::endl;
  stream << vector.val.z << std::endl;
  stream << "---------------------" << std::endl;

  return stream;
}
