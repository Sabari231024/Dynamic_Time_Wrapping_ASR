#include "readfile.h"
#include <stdio.h>
#include <stdlib.h>


int readfile(const char *fname,double mfcc[][DIM]){
FILE *f=fopen(fname, "r");
if(!f){
printf("File OPen Failed (readfile.c)");
return -1;
}
int coldim,numframe;
if(fscanf(f,"%d %d",&coldim,&numframe)!=2){
fprintf(stderr, "file header is misssing!!");
fclose(f);
return -1;
}
printf("Column Dimension: %d || Num_Frames: %d\n",coldim,numframe);
for(int i = 0;i < numframe;i++){
for(int j = 0;j < coldim;j++){
if(fscanf(f,"%lf",&mfcc[i][j])!= 1){
fprintf(stderr, "unable to read value from frame %d, col dimension %d.\n", i + 1, j + 1);
fclose(f);
return i; 
}}}
fclose(f);
return numframe;
}


