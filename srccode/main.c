#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<float.h>
#include<math.h>
#include "dtw.h"
#include "readfile.h"

#define MAX_MFCC 100  // maximum number of time frames to store in an array
#define DIM 38         // each column feature vecotr dimension
#define MAX_FILENAME 30

typedef struct{
char filename[MAX_FILENAME];
double score;
}scr;

double dtw_calc(const char *file1,const char *file2)
{
double mfcc1[MAX_MFCC][DIM];
double mfcc2[MAX_MFCC][DIM];
char path1[256], path2[256];
snprintf(path1, sizeof(path1), "Dataset/Test/%s", file1);
snprintf(path2, sizeof(path2), "Dataset/Train/%s", file2);
int aud1len = readfile(path1,mfcc1);
int aud2len = readfile(path2,mfcc2);
if(aud1len<= 0 || aud2len <= 0){
printf("Insufficient length to perform dtw");
return DBL_MAX;// instead of -1 i put double max so that it gets ignored instead of getting into the score array
}
return dtw(mfcc1, aud1len, mfcc2, aud2len);
}

void sorter(scr arr[],int k){
for(int i=0;i<k-1;i++){
for(int j=i+1;j<k;j++){
if(arr[i].score > arr[j].score){
scr temp = arr[i];
arr[i] = arr[j];
arr[j] = temp;
}}}
}

void add(const char *filename, double score, scr arr[],int k){
if(score<arr[k-1].score)
{
strncpy(arr[k-1].filename,filename,MAX_FILENAME-1);
arr[k-1].filename[MAX_FILENAME-1]='\0';
arr[k-1].score = score;
sorter(arr,k);
}}



void printscore(scr arr[],int k,const char *file){ //i have added the max vote logic within this function
int var1 = 0;
int var4 = 0;
int var6 = 0;
int varo = 0;
int varz = 0;
printf("Top-%d matches for %s:\n", k, file);
for(int i=0;i<k;i++){
printf("%s:%f\n",arr[i].filename,arr[i].score);
char labext = *(strchr(arr[i].filename,'_')+1);//i have extracted the label from each files 
switch(labext){
case '1':
	var1++;
	break;
case '4':
	var4++;
	break;
case '6':
	var6++;
	break;
case 'o':
	varo++;
	break;
case 'z':
	varz++;
	break;
}}
int max = 0;
char pred = "N";
if(var1 > max)
{ 
max = var1;
pred = '1';
 }
if(var4 > max) 
{
max = var4;
pred = '4';
}
if(var6 > max){
max = var6;
pred = '6';
}
if(varo > max){ 
max = varo; 
pred = 'o'; 
}
if(varz > max){
max = varz;
pred = 'z'; 
}
char actual = *(strchr(file, '_') + 1);
printf("Actual Label: %c\n", actual);
printf("Predicted Label: %c :: %d votes)\n", pred, max);
const char *csv = "predictionsubmission.csv";
FILE *csvfile = fopen(csv, "a");
fprintf(csvfile, "%s,%c,%c\n", file, actual, pred);
fclose(csvfile);
}


int main(int argc, char *argv[]) {
//let's put argv[0] as k
int k = atoi(argv[1]);
scr *scores = malloc(sizeof(scr)*k);
for(int i=0;i<k;i++)
{
scores[i].filename[0] = '\0';
scores[i].score = DBL_MAX;
}
double score;
struct dirent *di,*dj;
DIR *test = opendir("Dataset/Test");
DIR *train = opendir("Dataset/Train");

while((di = readdir(test)) != NULL)
{
if(di->d_name[0] == '.'){
continue;
}
for(int i=0;i<k;i++){
scores[i].filename[0] = '\0';
scores[i].score = DBL_MAX;
}
rewinddir(train);
while((dj=readdir(train)) != NULL)
{
if(dj->d_name[0] == '.'){
continue;
}
score = dtw_calc(di->d_name,dj->d_name);
add(dj->d_name,score,scores,k);
}
//break;
printscore(scores,k,di->d_name);
}
closedir(test);
closedir(train);
free(scores);
return 0;
}

