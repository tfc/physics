/*
 *  Vector3.h
 *  GameBase
 *
 *  Created by Administrator on 12.10.10.
 *  Copyright 2010 Kristof Niederholtmeyer. All rights reserved.
 *
 */

#ifndef GB_VECTOR_H
#define GB_VECTOR_H

#include <ostream>

class Vector3
{
public:
	Vector3();
    Vector3(const double xCoordinate,
             const double yCoordinate,
			 const double zCoordinate = 0.0f);
	Vector3(const Vector3& vector);
	~Vector3();
	
	double x() const;
	double y() const;
	double z() const;
	
	Vector3 operator * (const double scalar);
    Vector3 operator *= (const double scalar);
    Vector3 operator / (const double scalar);
	
	Vector3& operator = (const Vector3& vector);
	Vector3 operator + (const Vector3& vector);
	Vector3 operator - (const Vector3& vector);
	Vector3& operator += (const Vector3& vector);
	Vector3& operator -= (const Vector3& vector);
	bool operator == (const Vector3& vector);
	bool operator != (const Vector3& vector);
	// scalar product
	double operator * (const Vector3& vector);
	
	void normalize();
	double length() const;
    double angle() const;
	
	// publicly available coordinates
	// 4th field is dummy to enable SSE stuff.
	union {
		struct {
			double x, y, z, dummy;
        } val;
		double field[4];
	};
	//double x, y, z;
	
};

std::ostream &operator << (std::ostream &stream, const Vector3 &vector);

#endif
