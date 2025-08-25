#include <stdio.h>
#include <stdlib.h>

#include "dtw.h"
#include "readfile.h"

#define MAX_MFCC 1000  // maximum number of time frames to store in an array
#define DIM 38         // each column feature vecotr dimension

int main(int argc, char *argv[]) {
double mfcc1[MAX_MFCC][DIM];
double mfcc2[MAX_MFCC][DIM];
int aud1len = readfile("ac_1.mfcc",mfcc1);
int aud2len = readfile("mk_1.mfcc",mfcc2);
if(aud1len<= 0 || aud2len <= 0){
printf("Insufficient length to perform dtw");
return -1;
}
double res = dtw(mfcc1, aud1len, mfcc2, aud2len);
printf("The Final Cost Value for the DTW: %lf\n", res);
return 0;
}

