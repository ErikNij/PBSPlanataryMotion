#include "Planet.h"
#include "Vectors.h"

int main()
{
    printf("Starting simulation...\n");

    // Constants
    double t_sim = 10000; // s
    double dt = 0.01; // s
    int N_PLANETS = 2;
    double SUN_RADIUS = 696342000; // m
    double EARTH_RADIUS = 6378137; // m
    double EARTH_ORBIT_DIST = 149600000000; // m
    double EARTH_ORBIT_VEL = 29782.7; // m/s
    double EARTH_MASS = 5.972168 * pow(10, 24); // kg
    double SUN_MASS = 1.9885 * pow(10, 30); // kg

    printf("Total simulation time: %0.2lf seconds, time step: %0.2lf\n", t_sim, dt);

    // Initial position, velocities, accelerations
    struct Vector3D zeroVec3D = {0,0,0};
    struct Vector3D sunPos = {0,0,0};
    struct Vector3D earthPos = {EARTH_ORBIT_DIST,0,0};
    struct Vector3D earthVel = {0,EARTH_ORBIT_VEL,0};

    // Declare and initialize planets and open log files for each planet
    struct Planet3D sun = {sunPos, zeroVec3D, zeroVec3D, SUN_MASS, "sun"};
    void * fptr_sun = fopen("sun.txt", "w");
    struct Planet3D earth = {earthPos, earthVel, zeroVec3D, EARTH_MASS, "earth"};
    void * fptr_earth = fopen("earth.txt", "w");    

    // Add pointers to planets and planet files to array, Making sure they are added in the same order
    struct Planet3D * planets[] = {&sun, &earth};
    void * filePointers[] = {fptr_sun, fptr_earth};

    // Print starting positions of planets
    for(int i=0; i<N_PLANETS; i++)
    {
        printf("starting position %s: {%f,%f,%f}\n", planets[i]->name, planets[i]->pos3D.x, planets[i]->pos3D.y, planets[i]->pos3D.z);
    }

    // Run sumulations
    int i = 0;
    for(double t=0; t<t_sim; t=t+dt)
    {
        updatePlanets3D(planets, N_PLANETS, dt);
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
        printf("starting position %s: {%f,%f,%f}\n", planets[i]->name, planets[i]->pos3D.x, planets[i]->pos3D.y,  planets[i]->pos3D.z);
    }

    // Close files
    for(int i=0; i<N_PLANETS; i++)
    {
        fclose(filePointers[i]);
    }
    
    printf("Simulation finished!\n");

    return 0;
}