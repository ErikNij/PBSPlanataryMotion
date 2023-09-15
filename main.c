#include <stdio.h>  /* standard c input/output library */
#include <stdlib.h> /* standard c library */
#include "Planet.h"
#include "Vectors.h"
#include "LoadDatFile.h"
#define dimentions 3

int main()
{
    printf("Starting simulation...\n");

    // Constants
    double t_sim = 5000000; // s
    double dt = 2500;       // s
    int N_PLANETS = 89;
    int numbPlanets = N_PLANETS;
    // char fileNames[36*230];
    char currentFileName[36];
    char *folderName = "createdData";
    // Declare an arrays of pointers
    struct Vector3D *force[N_PLANETS];
    struct Planet3D *planets[N_PLANETS];

    for (int i = 0; i < N_PLANETS; i++)
    {
        force[i] = (struct Vector3D *)malloc(sizeof(struct Vector3D));
        planets[i] = (struct Planet3D *)malloc(sizeof(struct Planet3D));
    }

    getData(planets, N_PLANETS);

    printf("Total simulation time: %0.2lf seconds, time step: %0.2lf\n", t_sim, dt);

    void *filePointers[230];

    for (int i = 0; i < N_PLANETS; i++)
    {
        snprintf(currentFileName, sizeof(currentFileName), "%s/%s.txt", folderName, planets[i]->name);
        filePointers[i] = fopen(currentFileName, "w");
    }

    // Print starting positions of planets
    for (int i = 0; i < N_PLANETS; i++)
    {
        printf("starting position %s: {%f,%f,%f}\n", planets[i]->name, planets[i]->pos3D.x, planets[i]->pos3D.y, planets[i]->pos3D.z);
    }

    // Run sumulations
    int i = 0;

    for (double t = 0; t < t_sim; t = t + dt)
    {
        updatePlanets3D(planets, force, N_PLANETS, dt);
        // To avoid too large files, only write every 100th data point
        if (i % 40 == 0)
        {
            // Save planet positions to files
            for (int j = 0; j < N_PLANETS; j++)
            {
                // printf("about to save");
                fprintf(filePointers[j], "%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf\n",
                        t, planets[j]->pos3D.x, planets[j]->pos3D.y, planets[j]->pos3D.z,
                        planets[j]->vel3D.x, planets[j]->vel3D.y, planets[j]->vel3D.z);
            }

            // Flush the buffer to write data to the file immediately
            if (i % 80 == 0)
            {
                for (int j = 0; j < N_PLANETS; j++)
                {
                    fflush(filePointers[j]);
                }
            }
            // printf("Done flushing");
        }
        i++;
    }

    // Print final positions of planets
    for (int i = 0; i < N_PLANETS; i++)
    {
        printf("Final position %s: {%f,%f,%f}\n", planets[i]->name, planets[i]->pos3D.x, planets[i]->pos3D.y, planets[i]->pos3D.z);
    }

    // Close files
    for (int i = 0; i < N_PLANETS; i++)
    {
        fclose(filePointers[i]);
    }

    printf("Simulation finished!\n");

    return 0;
}