#include <stdio.h>          /* standard c input/output library */
#include <stdlib.h>         /* standard c library */
#include "Planet.h"
#include "Vectors.h"
#include "LoadDatFile.h"
#include <string.h>

#define DIMENSIONS 3

int main()
{
    printf("Starting simulation...\n");
    
    // Constants
    double t_sim = 10000000; // s
    double dt = 50; // s
    int N_PLANETS = 20;
    char * currentFileName = malloc(20*sizeof(char));
    char fileExtension[] = ".txt";

    // Declare arrays of pointers
    struct Vector3D *force[N_PLANETS];
    struct Planet3D *planets[N_PLANETS]; 
    
    for (int i = 0; i < N_PLANETS; i++){
        force[i] = (struct Vector3D *) malloc(sizeof(struct Vector3D));
        planets[i] = (struct Planet3D *) malloc(sizeof(struct Planet3D));
    }

    getData(planets,N_PLANETS);

    printf("Total simulation time: %0.2lf seconds, time step: %0.2lf\n", t_sim, dt);

    void * filePointers[N_PLANETS];

    for(int i = 0; i < N_PLANETS; i++)
    {       
        strcpy(currentFileName, planets[i]->name);
        strcat(currentFileName, fileExtension);

        char filePath[30] = "planets/";
        strcat(filePath, currentFileName);
        filePointers[i] = fopen(filePath, "w");
    }

    /*
    // Print starting positions of planets
    for(int i=0; i<N_PLANETS; i++)
    {
        printf("starting position %s: {%f,%f,%f}\n", planets[i]->name, planets[i]->pos3D.x, planets[i]->pos3D.y, planets[i]->pos3D.z);
    }
    */

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
                //printf("about to save");
                fprintf(filePointers[j], "%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf,%0.2lf\n", t, planets[j]->pos3D.x, planets[j]->pos3D.y, planets[j]->pos3D.z, planets[j]->vel3D.x, planets[j]->vel3D.y, planets[j]->vel3D.z);    
            } 
        }
        i++;        
    }

    /*/
    // Print final positions of planets
    for(int i=0; i<N_PLANETS; i++)
    {
        printf("Final position %s: {%f,%f,%f}\n", planets[i]->name, planets[i]->pos3D.x, planets[i]->pos3D.y,  planets[i]->pos3D.z);
    }
    */

    // Close files
    for(int i=0; i<N_PLANETS; i++)
    {
        fclose(filePointers[i]);
    }
    
    printf("Simulation finished!\n");

    return 0;
}