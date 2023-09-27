#include "MathVector.h"

bool MathVector::operator== (MathVector B) //Vectors are equal if they have same coordinates
{
    return this->x == B.x && this->y == B.z && this->z == B.z;
}

MathVector MathVector::operator^ (MathVector B)//Vector Multiplication Of Vectors
{
    double x = this->y * B.z - this->z * B.y;
    double y = this->x * B.z - this->z * B.x;
    double z = this->x * B.y - this->y * B.x;
    MathVector C(x, -y, z);
    return C;
}

MathVector MathVector::operator* (double n)
{
    MathVector B(this->x * n, this->y * n, this->z * n);
    return B;
}

double MathVector::operator* (MathVector B)
{
    return this->x * B.x + this->y * B.y + this->z * B.z;
}

double MathVector::moduleOfVector(MathVector A)
{
    return sqrt(A.x * A.x + A.y * A.y + A.z * A.z);
}

double MathVector::angleBetweenVectors(MathVector A, MathVector B)
{
    return acos((A * B) / (moduleOfVector(A) * moduleOfVector(B)));
}

double MathVector::volumeOfParallelepipedOnVectors(MathVector A, MathVector B, MathVector C)
{
    return abs((A ^ B) * C); // Mixed Vector Multiplication
}

double MathVector::volumeOfPiramidOnVectors(MathVector A, MathVector B, MathVector C)
{
    return abs((A ^ B) * C) / 6;
}

void MathVector::normalize()
{
    (*this)* (1 / moduleOfVector(*this));
}