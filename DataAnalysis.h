#ifndef DATA_ANALYSIS_H
#define DATA_ANALYSIS_H

#include <math.h>
#include <stdio.h>

void KEandPE(struct Planet3D *planets[], int numbPlanets, double t, FILE *filePointer);

void FinalPostion(struct Planet3D *planets[], struct Planet3D *planetsEnd[], int numbPlanets, FILE *filePointer);

#endif