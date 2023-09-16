#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vectors.h"
#include <math.h>

struct Planet3D
{
    struct Vector3D pos3D;
    struct Vector3D vel3D;
    struct Vector3D acc3D;
    double mass;
    char name[20];
};

struct Planet 
{
    int id;
    char strName[32];
    double mass;
    double xpos;
    double ypos;
    double zpos;
    double xvel;
    double yvel;
    double zvel;
};

struct Planets
{
    struct  Planet *body;
};

struct Planets3D
{
    struct  Planet3D *body;
};


struct Vector3D CalcGravityForce3D(struct Planet3D * part1, struct Planet3D * part2)
{   
    struct Vector3D distanceVec = subVec3D(&part1->pos3D, &part2->pos3D);
    double distanceMagnitude = pow(inProdVec3D(&distanceVec, &distanceVec), 0.5);

    struct Vector3D direction = {distanceVec.x/distanceMagnitude, distanceVec.y/distanceMagnitude, distanceVec.z/distanceMagnitude};        

    double gravConst = -6.6743015 * pow(10, -11);
    double forceMagnitude = (gravConst) * (part1->mass * part2->mass) / inProdVec3D(&distanceVec, &distanceVec);
    
    struct Vector3D force = {forceMagnitude * direction.x, forceMagnitude * direction.y, forceMagnitude * direction.z};    

    return force;
}

void CalcForces(struct Vector3D *force[],struct Planet3D *planets[], int N)
{
    for(int i=0; i<N; i++)
    {
        //Setting the force at the start to 0
        *force[i] = subVec3D(force[i],force[i]);
        //*force[i] = {0,0,0};

        for(int j=0; j<N; j++)
        {
            if(i!=j)
            {
                struct Vector3D forceContribution = CalcGravityForce3D(planets[i], planets[j]);
                *force[i] = sumVec3D(force[i], &forceContribution);            
            }           
        }
    }
    
}

void updatePlanets3D(struct Planet3D * planets[], struct Vector3D * force[], int N, float dt)
{
    //Calculating half a time step
    double hdt = dt/2;
    
    for(int i=0; i<N; i++)
    {
        //Calculating forces at t = t
        CalcForces(force,planets,N);

        //calculating acceration, and changing the velocity for a half a time step and postion for a full time step. 
        struct Vector3D acceleration = {force[i]->x/planets[i]->mass, force[i]->y/planets[i]->mass, force[i]->z/planets[i]->mass};
        struct Vector3D dV = doublexVec3D(&planets[i]->acc3D,hdt);
        struct Vector3D dPos = doublexVec3D(&planets[i]->vel3D,dt);
        planets[i]->acc3D = acceleration;
        planets[i]->vel3D = sumVec3D(&planets[i]->vel3D, &dV);
        planets[i]->pos3D = sumVec3D(&planets[i]->pos3D, &dPos);

        //Calculating force at t = t + dt
        CalcForces(force,planets,N);


        //Calculating acceleration, and changing the velocity for half a time step. (only)
        struct Vector3D accelerationPrime = {force[i]->x/planets[i]->mass, force[i]->y/planets[i]->mass, force[i]->z/planets[i]->mass};
        struct Vector3D dVPrime = doublexVec3D(&planets[i]->acc3D,hdt);

        planets[i]->acc3D = accelerationPrime;
        planets[i]->vel3D = sumVec3D(&planets[i]->vel3D, &dVPrime);
    }
}


#endif