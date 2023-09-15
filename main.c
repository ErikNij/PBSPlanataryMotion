#include <stdio.h>          /* standard c input/output library */
#include <stdlib.h>         /* standard c library */
#include "Planet.h"
#include "Vectors.h"
#include "LoadDatFile.h"
#define dimentions 3

int main()
{
    printf("Starting simulation...\n");

    
    // Constants
    double t_sim = 10000; // s
    double dt = 0.01; // s
    int N_PLANETS = 2;
    int numbPlanets = N_PLANETS;

    // Declare an array of pointers
    struct Vector3D *force[N_PLANETS];
    struct Planet3D *planets[N_PLANETS];
    
    for (int i = 0; i < N_PLANETS; i++) {
        force[i] = (struct Vector3D *) malloc(sizeof(struct Vector3D));
        planets[i] = (struct Planet3D *) malloc(sizeof(struct Planet3D));
    }

    getData(planets,N_PLANETS);


    printf("Total simulation time: %0.2lf seconds, time step: %0.2lf\n", t_sim, dt);

    void * fptr_sun = fopen("sun.txt", "w");
    void * fptr_mecur = fopen("mecur.txt", "w");    

    // Add pointers to planets and planet files to array, Making sure they are added in the same order
    //struct Planet3D * planets[] = {&sun, &earth};
    void * filePointers[] = {fptr_sun, fptr_mecur};

    // Print starting positions of planets
    for(int i=0; i<N_PLANETS; i++)
    {
        printf("starting position %s: {%f,%f,%f}\n", planets[i]->name, planets[i]->pos3D.x, planets[i]->pos3D.y, planets[i]->pos3D.z);
    }

    // Run sumulations
    int i = 0;

    for(double t=0; t<t_sim; t=t+dt)
    {
        updatePlanets3D(planets,force, N_PLANETS, dt);
        // To avoid too large files, only write every 100th data point
        if(i%1000 == 0)
        {
            // Save planet positions to files
            for(int j=0; j<N_PLANETS; j++)
            {
                fprintf(filePointers[j], "%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf\n", t, planets[j]->pos3D.x, planets[j]->pos3D.y, planets[j]->pos3D.z, planets[j]->vel3D.x, planets[j]->vel3D.y, planets[j]->vel3D.z);    
            }
        }
        i++;        
    }

    // Print final positions of planets
    for(int i=0; i<N_PLANETS; i++)
    {
        printf("Final position %s: {%f,%f,%f}\n", planets[i]->name, planets[i]->pos3D.x, planets[i]->pos3D.y,  planets[i]->pos3D.z);
    }

    // Close files
    for(int i=0; i<N_PLANETS; i++)
    {
        fclose(filePointers[i]);
    }
    
    printf("Simulation finished!\n");

    return 0;
}