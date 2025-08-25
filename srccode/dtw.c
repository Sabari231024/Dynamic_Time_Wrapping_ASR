#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "dtw.h"
double dtw(double aud1[][FEAT_DIM],int aud1len,double aud2[][FEAT_DIM],int aud2len)
{
double **mat = (double **)malloc((aud1len+1)*sizeof(double *));
for(int i=0;i<=aud1len;i++){
mat[i] = (double *)malloc((aud2len+1)*sizeof(double));
}
for(int i=0;i<=aud1len;i++){
for(int j=0;j<=aud2len;j++){
mat[i][j] = INFINITY;
}}
mat[0][0] = 0; // all set now.
for(int i=1;i<=aud1len;i++){
for(int j=1; j<=aud2len;j++){
double d = distance(aud1[i-1],aud2[j-1],FEAT_DIM);
double prev = fmin(fmin(mat[i-1][j],mat[i][j-1]),mat[i-1][j-1]);
mat[i][j] = d + prev;
}}
double final = mat[aud1len][aud2len];
for(int i=0;i<=aud1len;i++){
free(mat[i]);
}
free(mat);
return final;
}


