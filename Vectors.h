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

struct Vector2D sumVec2D(struct Vector2D *vec1, struct Vector2D *vec2)
{
    double xnew = vec1->x + vec2->x;
    double ynew = vec1->y + vec2->y;
    struct Vector2D result = {xnew, ynew};
    return result;
}

struct Vector2D subVec2D(struct Vector2D *vec1, struct Vector2D *vec2)
{
    double xnew = vec1->x - vec2->x;
    double ynew = vec1->y - vec2->y;
    struct Vector2D result = {xnew, ynew};
    return result;
}

struct Vector3D sumVec3D(struct Vector3D *vec1, struct Vector3D *vec2)
{
    double xnew = vec1->x + vec2->x;
    double ynew = vec1->y + vec2->y;
    double znew = vec1->z + vec2->z;
    struct Vector3D result = {xnew, ynew, znew};
    return result;
}

struct Vector3D subVec3D(struct Vector3D *vec1, struct Vector3D *vec2)
{
    double xnew = vec1->x - vec2->x;
    double ynew = vec1->y - vec2->y;
    double znew = vec1->z - vec2->z;
    struct Vector3D result = {xnew, ynew, znew};
    return result;
}

struct Vector3D doublexVec3D(struct Vector3D *vec1, double coeff)
{
    double xnew = vec1->x * coeff;
    double ynew = vec1->y * coeff;
    double znew = vec1->z * coeff;
    struct Vector3D result = {xnew, ynew, znew};
    return result;
}

double inProdVec2D(struct Vector2D *vec1, struct Vector2D *vec2)
{
    return (vec1->x * vec2->x + vec1->y * vec2->y);
}

double inProdVec3D(struct Vector3D *vec1, struct Vector3D *vec2)
{
    return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
}

void printVec2D(struct Vector2D *vec)
{
    printf("{%lf, %lf}\n", vec->x, vec->y);
}

void printVec3D(struct Vector3D *vec)
{
    printf("{%lf, %lf, %lf}\n", vec->x, vec->y, vec->z);
}

#endif