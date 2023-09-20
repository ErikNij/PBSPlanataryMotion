#ifndef VECTORS_H
#define VECTORS_H

#include <stdio.h>

struct Vector2D
{
    double x;
    double y;
};

struct Vector3D
{
    double x;
    double y;
    double z;
};

struct Vector2D sumVec2D(struct Vector2D *vec1, struct Vector2D *vec2);

struct Vector2D subVec2D(struct Vector2D *vec1, struct Vector2D *vec2);

struct Vector3D sumVec3D(struct Vector3D *vec1, struct Vector3D *vec2);

struct Vector3D subVec3D(struct Vector3D *vec1, struct Vector3D *vec2);


struct Vector3D doublexVec3D(struct Vector3D *vec1, double coeff);

double inProdVec2D(struct Vector2D *vec1, struct Vector2D *vec2);

double inProdVec3D(struct Vector3D *vec1, struct Vector3D *vec2);

void printVec2D(struct Vector2D *vec);

void printVec3D(struct Vector3D *vec);
#endif