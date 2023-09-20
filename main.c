#include <stdio.h>  /* standard c input/output library */
#include <stdlib.h> /* standard c library */

#include "LoadDatFile.h"
#include "DataAnalysis.h"
#include "Planet.h"
#include "Vectors.h"

int main()
{
    printf("Initializing simulation...\n");

    // Constants and settings
    double t_sim =  365 * 24 * 60 * 60; // s
    double dt = 1440;               // s
    int numberOfPLotPoints = 365/5;
    
    //365 days and dt = 3600 are  good settings, that give solid results quickly
    int itrWOsaving = floor(t_sim / dt / numberOfPLotPoints);
    //int N_PLANETS = 230;

    //The number of planets can also be determined by the user:

    int N_PLANETS;
    printf("How many planets do you want? 230 is the max.\n");
    scanf("%d",&N_PLANETS);


    char currentFileName[36];
    char *folderName = "createdData";

    // Declaring an arrays of pointers
    struct Vector3D *force[N_PLANETS];
    struct Planet3D *planets[N_PLANETS];
    struct Planet3D *planetsEnd[N_PLANETS];

    for (int i = 0; i < N_PLANETS; i++)
    {
        force[i] = (struct Vector3D *)malloc(sizeof(struct Vector3D*));
        planets[i] = (struct Planet3D *)malloc(sizeof(struct Planet3D*));
        planetsEnd[i] = (struct Planet3D *)malloc(sizeof(struct Planet3D*));
    }

    // Load planet data from provided .dat files
    getData(planets, N_PLANETS, 1);
    getData(planetsEnd, N_PLANETS, 0);
    printf("Loaded planet data\n");

    // Open files to write planet data to   
    printf("Opening files\n");
    void *filePointers[230];
    FILE *filePointerEnergy;
    filePointerEnergy = fopen("EnergyOverTime.txt", "w");
    FILE *filePointerEndDiff;
    filePointerEndDiff = fopen("PlanetsEnd.txt", "w");
    for (int i = 0; i < N_PLANETS; i++)
    {
        snprintf(currentFileName, sizeof(currentFileName), "%s/%s.txt", folderName, planets[i]->name);
        filePointers[i] = fopen(currentFileName, "w");
    }

    printf("Total simulation time: %0.2lf seconds, time step: %0.2lf\n", t_sim, dt);
    printf("Starting simulation...\n");
    
    // Run sumulations    
    for (int j = 0; j < numberOfPLotPoints; j++)
    {
        printf("_");
    }
    printf("\n");

    // Run sumulations
    int i = 0;
    for (double t = 0; t < t_sim; t = t + dt)
    {
        updatePlanets3D(planets, force, N_PLANETS, dt);
        // To avoid too large files, only write every n th data point
        if (i % itrWOsaving == 0)
        {            
            //  Save planet positions to files
            for (int j = 0; j < N_PLANETS; j++)
            {

                fprintf(filePointers[j], "%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf\n",
                        t, planets[j]->pos3D.x, planets[j]->pos3D.y, planets[j]->pos3D.z,
                        planets[j]->vel3D.x, planets[j]->vel3D.y, planets[j]->vel3D.z);
            }
            KEandPE(planets, N_PLANETS, t, filePointerEnergy);

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

    // Compare simulated positions with actual positions
    FinalPostion(planets, planetsEnd, N_PLANETS, filePointerEndDiff);

    // Close files
    for (int i = 0; i < N_PLANETS; i++)
    {
        fclose(filePointers[i]);
    }
    fclose(filePointerEnergy);
    fclose(filePointerEndDiff);

    printf("All files closed\n");

    printf("Simulation finished!\n");

    // Free memory
    free(*planets);
    free(*planetsEnd);
    //free(*force);
    

    return 0;
}