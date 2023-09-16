#include <stdio.h>  /* standard c input/output library */
#include <stdlib.h> /* standard c library */
#include "Planet.h"
#include "Vectors.h"
#include "LoadDatFile.h"
#define dimentions 3

int main()
{
    printf("Initializing simulation...\n");


    // Constants
    double t_sim = 365 * 24 * 60 * 60; // s
    double dt = 24 * 60 * 2;           // s
    int numberOfPLotPoints = 365 / 5;
    int itrWOsaving = floor(t_sim / dt / numberOfPLotPoints);
    int N_PLANETS = 171;
    char *folderName = "createdData";    
    char * currentFileName = malloc(20*sizeof(char));

    // Declare arrays of pointers
    struct Vector3D *force[N_PLANETS];
    struct Planet3D *planets[N_PLANETS];
    struct Planet3D *planetsEnd[N_PLANETS];

    for (int i = 0; i < N_PLANETS; i++)
    {
        force[i] = (struct Vector3D *)malloc(sizeof(struct Vector3D));
        planets[i] = (struct Planet3D *)malloc(sizeof(struct Planet3D));
        planetsEnd[i] = (struct Planet3D *)malloc(sizeof(struct Planet3D));
    }

    getData(planets, N_PLANETS, 1);
    getData(planetsEnd, N_PLANETS, 0);

    printf("Total simulation time: %0.2lf seconds, time step: %0.2lf\n", t_sim, dt);
    printf("Starting simulation...\n");

    void *filePointers[230];

    for (int i = 0; i < N_PLANETS; i++)
    {
        snprintf(currentFileName, sizeof(currentFileName), "%s/%s.txt", folderName, planets[i]->name);
        filePointers[i] = fopen(currentFileName, "w");
    }

    /*
    // Print starting positions of planets
    for (int i = 0; i < N_PLANETS; i++)
    {
        printf("starting position %s: {%f,%f,%f}\n", planets[i]->name, planets[i]->pos3D.x, planets[i]->pos3D.y, planets[i]->pos3D.z);
    }
    */
    
    printf("Beun loading bar:\n");

    for (int j = 0; j < numberOfPLotPoints; j++)
    {
        printf("|");
    }
    printf("\n");
    
    // Run sumulations
    int i = 0;
    for (double t = 0; t < t_sim; t = t + dt)
    {
        updatePlanets3D(planets, force, N_PLANETS, dt);
        // To avoid too large files, only write every 100th data point
        if (i % itrWOsaving == 0)
        {
            // printf("about to save");
            //  Save planet positions to files
            for (int j = 0; j < N_PLANETS; j++)
            {

                fprintf(filePointers[j], "%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf\n",
                        t, planets[j]->pos3D.x, planets[j]->pos3D.y, planets[j]->pos3D.z,
                        planets[j]->vel3D.x, planets[j]->vel3D.y, planets[j]->vel3D.z);
            }

            // Flush the buffer to write data to the file immediately
            if (i % itrWOsaving == 0)
            {
                for (int j = 0; j < N_PLANETS; j++)
                {
                    fflush(filePointers[j]);
                }
            }
            printf("|");
        }
        i++;
    }

    printf("\n");

    /*
    // Print final positions of planets
    for (int i = 0; i < N_PLANETS; i++)
    {
        printf("Final position %s: {%f,%f,%f}\n", planets[i]->name, planets[i]->pos3D.x, planets[i]->pos3D.y, planets[i]->pos3D.z);
    }
    */

    // Close files
    for (int i = 0; i < N_PLANETS; i++)
    {
        fclose(filePointers[i]);
    }

    printf("Simulation finished!\n");

    return 0;
}