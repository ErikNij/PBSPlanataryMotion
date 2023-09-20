#include <stdio.h>  /* standard c input/output library */
#include <stdlib.h> /* standard c library */

#include "Vectors.h"
#include "Planet.h"

#include "LoadDatFile.h"


#define nMax 1024

void getData(struct Planet3D *planets[], int numbPlanets, int StartEnd)
{    
    struct Planets3D SimPlanets;
    struct Planet3D Sun2021Pos;

    if (numbPlanets > 230)
    {
        printf("Maximum number of planets to simulate is 230, you entered, %d. Simulation set for 230 planets.", numbPlanets);
        numbPlanets = 230;
    }

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
                sscanf(line, "%d %s %lf %lf %lf %lf %lf %lf %lf",
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

    file = fopen(fileToOpen, "rb");
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

    }
    
    for (int j = 0; j < numbPlanets; j++)
    {
        planets[j] = &SimPlanets.body[j];
    }
}