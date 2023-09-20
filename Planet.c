#include "Vectors.h"

#include "Planet.h"

struct Vector3D CalcGravityForce3D(struct Planet3D *part1, struct Planet3D *part2)
{
    struct Vector3D distanceVec = subVec3D(&part1->pos3D, &part2->pos3D);
    double distanceMagnitude = sqrt(inProdVec3D(&distanceVec, &distanceVec));

    struct Vector3D direction = {distanceVec.x / distanceMagnitude, distanceVec.y / distanceMagnitude, distanceVec.z / distanceMagnitude};

    double forceMagnitude = (GRAV_CONST) * (part1->mass * part2->mass) / inProdVec3D(&distanceVec, &distanceVec);

    struct Vector3D force = {forceMagnitude * direction.x, forceMagnitude * direction.y, forceMagnitude * direction.z};

    return force;
}

void CalcForces(struct Vector3D *force[], struct Planet3D *planets[], int N)
{
    for (int i = 0; i < N; i++)
    {
        // Setting the force at the start to 0
        *force[i] = subVec3D(force[i], force[i]);

        for (int j = 0; j < N; j++)
        {
            if (i != j)
            {
                struct Vector3D forceContribution = CalcGravityForce3D(planets[i], planets[j]);
                *force[i] = sumVec3D(force[i], &forceContribution);
            }
        }
    }
}

void CalcForcesFast(struct Vector3D *force[], struct Planet3D *planets[], int N)
{
    int system[230];
    struct Vector3D forceContribution;

    // Setting the system of the planets
    for (int i = 0; i < N; i++)
    {
        if (planets[i]->id < 1000)
        {
            system[i] = planets[i]->id / 100;
        }
        else
        {
            system[i] = planets[i]->id / 10000;
        }
    }
    
    // Doing the force calcuations
    // Looping over every planet
    for (int i = 0; i < N; i++)
    {
        // Setting the force at the start to 0
        // The sun has influnce on everything
        if (planets[i]->id == 10)
        {
            // Setting the force on the Sun to 0
            *force[i] = subVec3D(force[i], force[i]);
            for (int j = 1; j < N; j++)
            {
                // Setting the force of the planet to 0
                *force[j] = subVec3D(force[j], force[j]);
                forceContribution = CalcGravityForce3D(planets[i], planets[j]);
                *force[i] = sumVec3D(force[i], &forceContribution);
                // The force on the planet is oppisete of the sun
                *force[j] = subVec3D(force[j], &forceContribution);
            }
        }
        // Loop for planets
        else
        {
            // Jupiter's pull is also omnipresent
            if (planets[i]->id == 599)
            {
                for (int j = 1; j < N; j++)
                {
                    // don't double update Jupiter's system
                    if (system[j] != 5)
                    {
                        forceContribution = CalcGravityForce3D(planets[i], planets[j]);
                        *force[i] = sumVec3D(force[i], &forceContribution);
                        // The force on the planet is oppisete of the Juipter
                        *force[j] = subVec3D(force[j], &forceContribution);
                    }
                }
            }
            else
            {
                // NOTE: Looping from i+1 onwards.
                for (int j = i + 1; j < N; j++)
                {
                    // Only calc forces if they are in the same system
                    if (system[i] == system[j])
                    {
                        forceContribution = CalcGravityForce3D(planets[i], planets[j]);
                        *force[i] = sumVec3D(force[i], &forceContribution);
                        // The force on the planet is oppisete of the other planet
                        *force[j] = subVec3D(force[j], &forceContribution);
                    }
                }
            }
        }
    }
}

void updatePlanets3D(struct Planet3D *planets[], struct Vector3D *force[], int N, float dt)
{
    // Calculating half a time step
    double hdt = dt / 2;

    CalcForcesFast(force, planets, N);

    for (int i = 0; i < N; i++)
    {
        // Calculating forces at t = t
        // calculating acceration, and changing the velocity for a half a time step and postion for a full time step.
        struct Vector3D acceleration = {force[i]->x / planets[i]->mass, force[i]->y / planets[i]->mass, force[i]->z / planets[i]->mass};
        struct Vector3D dV = doublexVec3D(&planets[i]->acc3D, hdt);
        struct Vector3D dPos = doublexVec3D(&planets[i]->vel3D, dt);
        planets[i]->acc3D = acceleration;
        planets[i]->vel3D = sumVec3D(&planets[i]->vel3D, &dV);
        planets[i]->pos3D = sumVec3D(&planets[i]->pos3D, &dPos);
    }

    CalcForcesFast(force, planets, N);

    for (int i = 0; i < N; i++)
    {
        // Calculating force at t = t + dt
        // Calculating acceleration, and changing the velocity for half a time step. (only)
        struct Vector3D accelerationPrime = {force[i]->x / planets[i]->mass, force[i]->y / planets[i]->mass, force[i]->z / planets[i]->mass};
        struct Vector3D dVPrime = doublexVec3D(&planets[i]->acc3D, hdt);

        planets[i]->acc3D = accelerationPrime;
        planets[i]->vel3D = sumVec3D(&planets[i]->vel3D, &dVPrime);
    }
}