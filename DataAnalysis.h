#include <stdio.h>  /* standard c input/output library */
#include <stdlib.h> /* standard c library */
#include "Planet.h"
#include "Vectors.h"

void KEandPE(struct Planet3D *planets[], int numbPlanets, double t, FILE *filePointer)

{
    double KE[230];
    double PE[230];
    double CurrentPE;
    double gravConst = 6.6743015 * pow(10, -11);
    double SumPE = 0;
    double SumKE = 0;
    double SumE = 0;
    double SumPEWithoutM = 0;
    double SumKEWithoutM = 0;
    double SumEWithoutM = 0;

    for (int i = 0; i < 230; i++)
    {
        PE[i] = 0;
    }
    for (int i = 0; i < numbPlanets; i++)
    {
        KE[i] = 0.5 * planets[i]->mass * (pow(planets[i]->vel3D.x, 2) + pow(planets[i]->vel3D.y, 2) + pow(planets[i]->vel3D.z, 2));
        for (int j = i + 1; j < numbPlanets; j++)
        {
            struct Vector3D distanceVec = subVec3D(&planets[i]->pos3D, &planets[j]->pos3D);
            double distanceMagnitude = sqrt(inProdVec3D(&distanceVec, &distanceVec));
            CurrentPE = gravConst * planets[i]->mass * planets[j]->mass / distanceMagnitude;
            PE[i] = PE[i] + CurrentPE;
            PE[j] = PE[j] + CurrentPE;
        }
    }
    for (int i = 0; i < numbPlanets; i++)
    {
        SumPE = SumPE + PE[i];
        SumKE = SumKE + KE[i];
    }
    SumE = SumPE + SumKE;

    struct Vector3D distanceVec = subVec3D(&planets[0]->pos3D, &planets[1]->pos3D);
    double distanceMagnitude = sqrt(inProdVec3D(&distanceVec, &distanceVec));
    CurrentPE = gravConst * planets[0]->mass * planets[1]->mass / distanceMagnitude;

    SumPEWithoutM = SumPE - (2 * CurrentPE);
    SumKEWithoutM = SumKE - (0.5 * planets[1]->mass * (pow(planets[1]->vel3D.x, 2) + pow(planets[1]->vel3D.y, 2) + pow(planets[1]->vel3D.z, 2)));
    SumEWithoutM = SumKEWithoutM + SumPEWithoutM;

    fprintf(filePointer, "%lf, %lf,%lf,%lf,%lf,%lf,%lf\n",
            t, SumPE, SumKE, SumE, SumPEWithoutM, SumKEWithoutM, SumEWithoutM);
}

void FinalPostion(struct Planet3D *planets[], struct Planet3D *planetsEnd[], int numbPlanets, FILE *filePointer)
{
    struct Vector3D dr;
    double percentOff;

    for (int i = 0; i < numbPlanets; i++)
    {
        dr = subVec3D(&planets[i]->pos3D, &planetsEnd[i]->pos3D);
        percentOff = fabs(dr.x / planetsEnd[i]->pos3D.x) + fabs(dr.y / planetsEnd[i]->pos3D.y);
        fprintf(filePointer, "%s, %lf, %lf\n",
                planets[i]->name, dr.x + dr.y, percentOff);
    }
}