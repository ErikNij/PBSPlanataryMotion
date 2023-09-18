#include <stdio.h>  /* standard c input/output library */
#include <stdlib.h> /* standard c library */
#include "Planet.h"
#include "Vectors.h"

#define dimentions 3
#define nMax 1024

void getData(struct Planet3D *planets[], int numbPlanets, int StartEnd)
{    
    struct Planets3D SimPlanets;
    struct Planet3D Sun2021Pos;
    double momentum[dimentions] = {0, 0, 0};
    double deltaV[dimentions] = {0, 0, 0};
    double NewMomentum[dimentions] = {0, 0, 0};
    double ImprovementPercentage[dimentions] = {0, 0, 0};
    double totalMass = 0;
    double VelToCal = 0;

    if (numbPlanets > 230)
    {
        printf("Maximum number of planets to simulate is 230, you entered, %d. Simulation set for 230 planets.", numbPlanets);
        numbPlanets = 230;
    };

    // Allocating memory for the planet array
    SimPlanets.body = (struct Planet3D *)malloc((numbPlanets) * sizeof(struct Planet3D));

    // Reading the  file
    char line[nMax];
    FILE *file = NULL;
    char *fileToOpen;
    if (StartEnd == 1)
    {
        fileToOpen = "solar_system_13sept2021.dat";
    }
    if (StartEnd == 0)
    {
        fileToOpen = "solar_system_13sept2022.dat";
    }
    file = fopen(fileToOpen, "rb");
    if (file == NULL)
    {
        printf("Cannot open specified .dat file");
        exit(1);
    }
    // looping over everyline to grab the stuff
    int j = 0;
    while (fgets(line, nMax, file) != NULL)
    {
        if (j >= 1)
        {
            if (j <= numbPlanets)
            {
                j = j - 1;
                sscanf(line, "%d %s %lf %Lf %Lf %Lf %Lf %Lf",
                       &SimPlanets.body[j].id,
                       SimPlanets.body[j].name,
                       &SimPlanets.body[j].mass,
                       &SimPlanets.body[j].pos3D.x,
                       &SimPlanets.body[j].pos3D.y,
                       &SimPlanets.body[j].pos3D.z,
                       &SimPlanets.body[j].vel3D.x,
                       &SimPlanets.body[j].vel3D.y,
                       &SimPlanets.body[j].vel3D.z);                
                j = j + 1;
            }
        }
        j = j + 1;
    }
    file = fopen("solar_system_13sept2021.dat", "rb");
    fgets(line, nMax, file);
    sscanf(line, "%d %s %lf %Lf %Lf %Lf %Lf %Lf",
           &Sun2021Pos.id,
           Sun2021Pos.name,
           &Sun2021Pos.mass,
           &Sun2021Pos.pos3D.x,
           &Sun2021Pos.pos3D.y,
           &Sun2021Pos.pos3D.z,
           &Sun2021Pos.vel3D.x,
           &Sun2021Pos.vel3D.y,
           &Sun2021Pos.vel3D.z);

    for (int i = 0; i < numbPlanets; i++)
    {
        // If a planet is "massless, set the mass to 1 kg"
        if (SimPlanets.body[i].mass == 0)
        {
            SimPlanets.body[i].mass = 1;
        }
        // Setting the sun to the center of the simulation
        SimPlanets.body[i].pos3D.x = SimPlanets.body[i].pos3D.x - Sun2021Pos.pos3D.x;
        SimPlanets.body[i].pos3D.y = SimPlanets.body[i].pos3D.y - Sun2021Pos.pos3D.y;
        SimPlanets.body[i].pos3D.z = SimPlanets.body[i].pos3D.z - Sun2021Pos.pos3D.z;

        // Finding the total momentum
        /*
        for (int j = 0; j < 3; j++)
        {
            if (j == 0)
            {
                VelToCal = SimPlanets.body[i].xvel;
            }
            if (j == 1)
            {
                VelToCal = SimPlanets.body[i].yvel;
            }
            if (j == 2)
            {
                VelToCal = SimPlanets.body[i].zvel;
            }
            // printf("The ID of the planet is %d\n",SimPlanets.body[i].id);
            momentum[j] = momentum[j] + (SimPlanets.body[i].mass * VelToCal);
        }
        totalMass = totalMass + SimPlanets.body[i].mass;
    }
    printf("The momentum in the x,y, and z direction is %lf , %lf , and, %lf kg * m/s. \n", momentum[0], momentum[1], momentum[2]);
    printf("The mass of the solar system is %lf kg. that is almost as heavy as my backpack!\n", totalMass);
    for (int i = 0; i < 3; i++)
    {
        deltaV[i] = momentum[i] / totalMass;
    }
    for (int i = 0; i < numbPlanets; i++)
    {
        // Finding the total momentum
        for (int j = 0; j < 3; j++)
        {
            if (j == 0)
            {
                SimPlanets.body[i].xvel = SimPlanets.body[i].xvel - deltaV[j];
                VelToCal = SimPlanets.body[i].xvel;
            }
            if (j == 1)
            {
                SimPlanets.body[i].yvel = SimPlanets.body[i].yvel - deltaV[j];
                VelToCal = SimPlanets.body[i].yvel;
            }
            if (j == 2)
            {
                SimPlanets.body[i].zvel = SimPlanets.body[i].zvel - deltaV[j];
                VelToCal = SimPlanets.body[i].zvel;
            }
            // printf("The ID of the planet is %d\n",SimPlanets.body[i].id);
            NewMomentum[j] = NewMomentum[j] + (SimPlanets.body[i].mass * VelToCal);
        }
    }
    printf("The new momentum in the x,y, and z direction is %lf , %lf , and, %lf kg * m/s. \n", NewMomentum[0], NewMomentum[1], NewMomentum[2]);
    for (int i = 0; i < dimentions; i++)
    {
        ImprovementPercentage[i] = (momentum[i] - NewMomentum[i]) / momentum[i] * 100;
        deltaV[i] = NewMomentum[i] / totalMass;
    }
    printf("That is an improvement of %lf, %lf, and %lf for each direction. \n", ImprovementPercentage[0], ImprovementPercentage[1], ImprovementPercentage[2]);
    printf("The velocity should change by %lf, %lf, and %lf for each direction, however floating point makes this impossible.\n", deltaV[0], deltaV[1], deltaV[2]);
    */
    }
    
    printf("Creating a list of pointers to complete the loading\n");
    for (int j = 0; j < numbPlanets; j++)
    {
        planets[j] = &SimPlanets.body[j];
        // printf("%s is now stored at %p \n", planets[j]->name, planets[j]);
    }

    free(SimPlanets.body);
}