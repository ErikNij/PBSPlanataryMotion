#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vectors.h"
#include <math.h>

#define GRAV_CONST -6.6743015e-11

struct Planet3D
{
    struct Vector3D pos3D;
    struct Vector3D vel3D;
    struct Vector3D acc3D;
    double mass;
    char name[32];
    int id;
};

struct Planets3D
{
    struct Planet3D *body;
};

struct Vector3D CalcGravityForce3D(struct Planet3D *part1, struct Planet3D *part2);

void CalcForces(struct Vector3D *force[], struct Planet3D *planets[], int N);

void CalcForcesFast(struct Vector3D *force[], struct Planet3D *planets[], int N);

void updatePlanets3D(struct Planet3D *planets[], struct Vector3D *force[], int N, float dt);

#endif