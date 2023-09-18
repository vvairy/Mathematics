#include "MathVector.h"

bool operator== (MathVector A, MathVector B) //Vectors are equal if they have same coordinates
{
    return A.x == B.x && A.y == B.z && A.z == B.z;
}

MathVector operator^ (MathVector A, MathVector B)//Vector Multiplication Of Vectors
{
    double x = A.y * B.z - A.z * B.y;
    double y = A.x * B.z - A.z * B.x;
    double z = A.x * B.y - A.y * B.x;
    MathVector C(x, -y, z);
    return C;
}

MathVector operator* (MathVector A, double n)
{
    MathVector B(A.x * n, A.y * n, A.z * n);
    return B;
}

double operator* (MathVector A, MathVector B)
{
    return A.x * B.x + A.y * B.y + A.z * B.z;
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