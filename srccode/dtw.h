#ifndef DTW_H
#define DTW_H

#include "distance.h"
#define FEAT_DIM 38 

double dtw(double aud1[][FEAT_DIM], int aud1len, double aud2[][FEAT_DIM], int aud2len);

#endif 
