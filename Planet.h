#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vectors.h"
#include <math.h>

struct Planet2D
{
    struct Vector2D pos2D;
    struct Vector2D vel2D;
    struct Vector2D acc2D;
    double mass;
    char name[32];    
};

struct Planet3D
{
    struct Vector3D pos3D;
    struct Vector3D vel3D;
    struct Vector3D acc3D;
    double mass;
    char *name;
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

struct Vector2D CalcGravityForce2D(struct Planet2D * part1, struct Planet2D * part2)
{   
    struct Vector2D distanceVec = subVec2D(&part1->pos2D, &part2->pos2D);
    double distanceMagnitude = pow(inProdVec2D(&distanceVec, &distanceVec), 0.5);

    struct Vector2D direction = {distanceVec.x/distanceMagnitude, distanceVec.y/distanceMagnitude};        

    double gravConst = 6.6743015 * pow(10, -11);
    double forceMagnitude = (gravConst) * (part1->mass * part2->mass) / inProdVec2D(&distanceVec, &distanceVec);
    
    struct Vector2D force = {forceMagnitude * direction.x, forceMagnitude * direction.y};

    return force;
}

struct Vector3D CalcGravityForce3D(struct Planet3D * part1, struct Planet3D * part2)
{   
    struct Vector3D distanceVec = subVec3D(&part1->pos3D, &part2->pos3D);
    double distanceMagnitude = pow(inProdVec3D(&distanceVec, &distanceVec), 0.5);

    struct Vector3D direction = {distanceVec.x/distanceMagnitude, distanceVec.y/distanceMagnitude, distanceVec.z/distanceMagnitude};        

    double gravConst = 6.6743015 * pow(10, -11);
    double forceMagnitude = (gravConst) * (part1->mass * part2->mass) / inProdVec3D(&distanceVec, &distanceVec);
    
    struct Vector3D force = {forceMagnitude * direction.x, forceMagnitude * direction.y, forceMagnitude * direction.z};    

    return force;
}

void updatePlanets2D(struct Planet2D * planets[], int N, double dt)
{
    for(int i=0; i<N; i++)
    {
        struct Vector2D force = {0, 0};

        for(int j=0; j<N; j++)
        {
            if(i!=j)
            {
                struct Vector2D forceContribution = CalcGravityForce2D(planets[i], planets[j]);
                force = sumVec2D(&force, &forceContribution);            
            }           
        }

        struct Vector2D acceleration = {force.x/planets[i]->mass, force.y/planets[i]->mass};
        planets[i]->acc2D = sumVec2D(&planets[i]->acc2D, &acceleration);
        planets[i]->vel2D = sumVec2D(&planets[i]->vel2D, &planets[i]->acc2D);
        planets[i]->pos2D = sumVec2D(&planets[i]->pos2D, &planets[i]->vel2D);
    }
}

void updatePlanets3D(struct Planet3D * planets[], int N, float dt)
{
    for(int i=0; i<N; i++)
    {
        struct Vector3D force = {0, 0};

        for(int j=0; j<N; j++)
        {
            if(i!=j)
            {
                struct Vector3D forceContribution = CalcGravityForce3D(planets[i], planets[j]);
                force = sumVec3D(&force, &forceContribution);            
            }           
        }

        struct Vector3D acceleration = {force.x/planets[i]->mass, force.y/planets[i]->mass, force.z/planets[i]->mass};
        planets[i]->acc3D = sumVec3D(&planets[i]->acc3D, &acceleration);
        planets[i]->vel3D = sumVec3D(&planets[i]->vel3D, &planets[i]->acc3D);
        planets[i]->pos3D = sumVec3D(&planets[i]->pos3D, &planets[i]->vel3D);
    }
}


#endif