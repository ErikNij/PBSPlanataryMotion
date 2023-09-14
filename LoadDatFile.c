#include <stdio.h>          /* standard c input/output library */
#include <stdlib.h>         /* standard c library */
#define dimentions


int main(void)
{
    struct Planet 
        {
            int id;
            char strName[32];
            double mass;
            double xpos;
            double ypos;
            double zpos;
            double xvel;
            double yvel;
            double zvel;
        };
    struct Planets
        {
            struct  Planet *body;
        };
    struct Planets SimPlanets;


    int numbPlanets = 100;

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
    for (int i = 0; i<3; i++)
    {
        ImprovementPercentage[i] = (momentum[i]-NewMomentum[i])/momentum[i]*100;
        deltaV[i] = NewMomentum[i]/totalMass;
    }
    printf("That is an improvement of %lf, %lf, and %lf for each direction. \n" , ImprovementPercentage[0], ImprovementPercentage[1],ImprovementPercentage[2]);
    printf("The velocity should change by %lf, %lf, and %lf for each direction, however floating point makes this impossible.", deltaV[0],deltaV[1],deltaV[2]);
   
    return 0;
}