#include "distance.h" 
#include <math.h>    

double distance(double *vect1, double *vect2, int coldim) {
    double sum = 0.0;
    for (int i = 0; i < coldim; i++) {
        sum += fabs(vect1[i] - vect2[i]);
    }
    return sum;
}
