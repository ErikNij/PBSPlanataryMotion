#include <stdio.h>          /* standard c input/output library */
#include <stdlib.h>         /* standard c library */
#include "Planet.h"
#include "Vectors.h"
//#include "LoadDatFile.h"
#define dimentions 3

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
    int numbPlanets = N_PLANETS;

    

    struct Planet3D **getData(int numbPlanets);
    
    struct Planets SimPlanets;
    struct Planets3D NewSimPlanets;
    //int numbPlanets = 100;
    double momentum[dimentions] = {0,0,0};
    double deltaV[dimentions] = {0,0,0};
    double NewMomentum[dimentions] = {0,0,0};
    double ImprovementPercentage[dimentions] = {0,0,0};
    double totalMass = 0;
    double VelToCal = 0;
    if (numbPlanets > 230)
    {
        printf("Maximum number of planets to simulate is 230, you entered, %d. Simulation set for 230 planets.",numbPlanets);
        numbPlanets = 230;
    };
    //Allocating memory for the planet array
    SimPlanets.body = (struct Planet *) malloc((numbPlanets-1)*sizeof(struct Planet));
    NewSimPlanets.body = (struct Planet3D *) malloc((numbPlanets-1)*sizeof(struct Planet3D));
    //Reading the  file
    const int nMax = 1024;
    char line[nMax];
    FILE *file = NULL;
    char *fileToOpen = "solar_system_13sept2021.dat";
    file = fopen(fileToOpen,"rb");
    if (file == NULL)
    {
        printf("Your file is wrong you goof");
        exit(1);
    }
    // looping over everyline to grab the stuff
    int j = 0;
    while(fgets(line,nMax,file) != NULL)
    {
        if (j >= 1 )
        {
            if (j<=numbPlanets)
            {   
                j = j - 1;
                sscanf(line,"%d %s %lf %lf %lf %lf %lf %lf",
                &SimPlanets.body[j].id,
                SimPlanets.body[j].strName,
                &SimPlanets.body[j].mass,
                &SimPlanets.body[j].xpos,
                &SimPlanets.body[j].ypos,
                &SimPlanets.body[j].zpos,
                &SimPlanets.body[j].xvel,
                &SimPlanets.body[j].yvel,
                &SimPlanets.body[j].zvel
                );
                printf("loaded %s with ID %d. This is planet #%d for us!\n",SimPlanets.body[j].strName,SimPlanets.body[j].id,j+1);
                j = j + 1;
            }
        }
        j = j + 1;
    }
    for (int i=0; i<numbPlanets; i++)
    {
        //If a planet is "massless, set the mass to 1 kg"
        if (SimPlanets.body[i].mass == 0)
        {
            SimPlanets.body[i].mass = 1;
        }
        //Finding the total momentum
        for (int j=0; j<3; j++)
        {
            if (j == 0){VelToCal = SimPlanets.body[i].xvel;}
            if (j == 1){VelToCal = SimPlanets.body[i].yvel;}
            if (j == 2){VelToCal = SimPlanets.body[i].zvel;}
            //printf("The ID of the planet is %d\n",SimPlanets.body[i].id);
            momentum[j]=momentum[j]+(SimPlanets.body[i].mass * VelToCal);
        }
        totalMass = totalMass + SimPlanets.body[i].mass;
    }
    printf("The momentum in the x,y, and z direction is %lf , %lf , and, %lf kg * m/s. \n", momentum[0], momentum[1],momentum[2]);
    printf("The mass of the solar system is %lf kg. that is almost as heavy as my backpack!\n",totalMass);
    for (int i = 0; i<3; i++)
    {
        deltaV[i] = momentum[i]/totalMass;
    }
    for (int i=0; i<numbPlanets; i++)
    {
        //Finding the total momentum
        for (int j=0; j<3; j++)
        {
            if (j == 0){SimPlanets.body[i].xvel = SimPlanets.body[i].xvel - deltaV[j]; 
            VelToCal = SimPlanets.body[i].xvel;}
            if (j == 1){SimPlanets.body[i].yvel = SimPlanets.body[i].yvel - deltaV[j];
            VelToCal = SimPlanets.body[i].yvel;}
            if (j == 2){SimPlanets.body[i].zvel = SimPlanets.body[i].zvel - deltaV[j];
            VelToCal = SimPlanets.body[i].zvel;}
            //printf("The ID of the planet is %d\n",SimPlanets.body[i].id);
            NewMomentum[j]=NewMomentum[j]+(SimPlanets.body[i].mass * VelToCal);
        }
    }
    printf("The new momentum in the x,y, and z direction is %lf , %lf , and, %lf kg * m/s. \n", NewMomentum[0], NewMomentum[1],NewMomentum[2]);
    for (int i = 0; i<dimentions; i++)
    {
        ImprovementPercentage[i] = (momentum[i]-NewMomentum[i])/momentum[i]*100;
        deltaV[i] = NewMomentum[i]/totalMass;
    }
    printf("That is an improvement of %lf, %lf, and %lf for each direction. \n" , ImprovementPercentage[0], ImprovementPercentage[1],ImprovementPercentage[2]);
    printf("The velocity should change by %lf, %lf, and %lf for each direction, however floating point makes this impossible.\n", deltaV[0],deltaV[1],deltaV[2]);
    printf("\nReformating to match the other style.\n");
    for (int j = 0; j<numbPlanets; j++)
    {
        NewSimPlanets.body[j].name = SimPlanets.body[j].strName;
        printf("the name of the new planet is %s\n",NewSimPlanets.body[j].name);
        NewSimPlanets.body[j].mass = SimPlanets.body[j].mass;
        NewSimPlanets.body[j].acc3D.x = 0;
        NewSimPlanets.body[j].acc3D.y = 0;
        NewSimPlanets.body[j].acc3D.z = 0;
        for (int i = 0; i < dimentions; i++)
        {
            if (i==0)
            {
                NewSimPlanets.body[j].vel3D.x = SimPlanets.body[j].xvel;
                NewSimPlanets.body[j].pos3D.x = SimPlanets.body[j].xpos;
            }
            if (i==1)
            {
                NewSimPlanets.body[j].vel3D.y = SimPlanets.body[j].yvel;
                NewSimPlanets.body[j].pos3D.y = SimPlanets.body[j].ypos;
            }
            if (i==2)
            {
                NewSimPlanets.body[j].vel3D.z = SimPlanets.body[j].zvel;
                NewSimPlanets.body[j].pos3D.z = SimPlanets.body[j].zpos;
            }
        }
    }
    printf("Reformation complete. \n");
    printf("Creating a list of pointers to complete the transition\n");
    struct Planet3D *pointerPlanet[230];
    for (int j = 0; j<numbPlanets; j++)
    {
        pointerPlanet[j] = &NewSimPlanets.body[j];
        printf("%p is the location of the converted planet.\n",pointerPlanet[j]);
    }
    struct Planet3D **planets = pointerPlanet;

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