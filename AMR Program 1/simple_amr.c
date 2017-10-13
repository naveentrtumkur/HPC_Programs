#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define NS_PER_US 1000000000
#include "simple_amr.h"

int num_box, num_rows, num_cols;
double EPSILON;
double AFFECT_RATE;
double max_DSV, min_DSV;
double *temp_old, *temp_new;

void mem_alloc()
{
 box = (struct Box *)malloc(num_box*sizeof(struct Box));
 temp_new = (double *) malloc(num_box*sizeof(double));
 temp_old = (double *) malloc(num_box*sizeof(double));
}

int readValues(){
int i,j, box_id;

//read num_grid, num_rows, nums_cols 
scanf("%d %d %d", &num_box, &num_rows, &num_cols);

//allocate memory
mem_alloc();

for(i=0; i < num_box ; i++ ){
scanf( "%d", &box_id);
scanf( "%d %d %d %d", &(box[box_id].upp_y), &(box[box_id].upp_x), &(box[box_id].height), &(box[box_id].width));

// read the top neighbours
scanf( "%d", &(box[i].nTop));

box[box_id].topNbor = (int *) malloc(box[i].nTop * sizeof(int));
box[box_id].topContact = (int *) malloc(box[i].nTop * sizeof(int));
for(j=0 ; j< box[i].nTop; j++){
scanf( "%d", &(box[box_id].topNbor[j]));
}

// read teh  bottom neigh
scanf( "%d", &(box[i].nBot));

box[box_id].botNbor = (int *) malloc(box[i].nBot * sizeof(int));
box[box_id].botContact = (int *) malloc(box[i].nBot * sizeof(int));

for(j=0 ; j< box[i].nBot; j++){
scanf( "%d", &(box[box_id].botNbor[j]));
} 

//read left neighbours
scanf( "%d", &(box[i].nLeft));

box[box_id].leftNbor = (int *) malloc(box[i].nLeft * sizeof(int));
box[box_id].leftContact = (int *) malloc(box[i].nLeft * sizeof(int));

for(j=0 ; j< box[i].nLeft; j++){
scanf( "%d", &(box[box_id].leftNbor[j]));
} 

// read right neighbours
scanf( "%d", &(box[i].nRight));

box[box_id].rightNbor = (int *) malloc(box[i].nRight * sizeof(int));
box[box_id].rightContact = (int *) malloc(box[i].nRight * sizeof(int));

for(j=0 ; j< box[i].nRight; j++){
scanf( "%d", &(box[box_id].rightNbor[j]));
} 
scanf("%lf", &(temp_old[i]));
max_DSV = max(max_DSV, temp_old[i]);
min_DSV = min(min_DSV, temp_old[i]);  
}
return 1;
}

void print_box(){


int i,j;

for(i=0;i<num_box;i++){

for(j=0; j <box[i].nTop;j++)
{
printf("%d ", box[i].topNbor[j]);
}
printf("\nBOTTOM values\n");
for(j=0; j <box[i].nBot;j++)
{
printf("%d ", box[i].botNbor[j]);
}
printf("\nLEFT value\n");
for(j=0; j <box[i].nLeft;j++)
{
printf("%d ", box[i].leftNbor[j]);
}

printf("\nRIGHT Values");
for(j=0; j <box[i].nRight;j++)
{
printf("%d ", box[i].rightNbor[j]);
}
printf("\n temp_old = %lf \n", temp_old[i]);
}
}

void deallocate(){
int i;
for(i=0; i<num_box ; i++){
free(box[i].topNbor);
free(box[i].botNbor);
free(box[i].leftNbor);
free(box[i].rightNbor);
}
free(box);
}

void copy_data(){
int i;
max_DSV=0;
min_DSV=INT_MAX;
for(i=0; i<num_box ; i++)
{
temp_old[i]=temp_new[i];
max_DSV = max(max_DSV, temp_old[i]);
min_DSV = min(min_DSV, temp_old[i]);
}
}

void compute_contact_distance(){
int j;
int temp_box,curr_box;

for(curr_box=0;curr_box<num_box; curr_box++){
//compute teh answers for top neighbours
for(j=0;j<box[curr_box].nTop;j++){

temp_box = box[curr_box].topNbor[j];

box[curr_box].topContact[j] = min(box[temp_box].upp_x + box[temp_box].width, box[curr_box].upp_x + box[curr_box].width) - max(box[temp_box].upp_x , box[curr_box].upp_x);
}


//compute teh answers for bottom neighbours
for(j=0;j<box[curr_box].nBot;j++){

temp_box = box[curr_box].botNbor[j];

box[curr_box].botContact[j] = min(box[temp_box].upp_x + box[temp_box].width, box[curr_box].upp_x + box[curr_box].width) - max(box[temp_box].upp_x , box[curr_box].upp_x);
}



//compute teh answers for left neighbours

for(j=0; j<box[curr_box].nLeft;j++){

temp_box = box[curr_box].leftNbor[j];

box[curr_box].leftContact[j] = min(box[temp_box].upp_y + box[temp_box].height, box[curr_box].upp_y + box[curr_box].height) - max(box[temp_box].upp_y , box[curr_box].upp_y);
}


//compute the answers for right neighbours

for(j=0; j<box[curr_box].nRight;j++){

temp_box = box[curr_box].rightNbor[j];

box[curr_box].rightContact[j] = min(box[temp_box].upp_y + box[temp_box].height, box[curr_box].upp_y + box[curr_box].height) - max(box[temp_box].upp_y , box[curr_box].upp_y);
}

}
}

void update_DSV(){

int contact_dist;
double sum, average;
int j, temp_box, curr_box;

for(curr_box=0 ;curr_box<num_box; curr_box++){

sum=0;

//compute for top neighbours
if(box[curr_box].nTop == 0)
sum += (temp_old[curr_box]*box[curr_box].width);

for(j=0; j<box[curr_box].nTop;j++){

temp_box = box[curr_box].topNbor[j];

sum += (box[curr_box].topContact[j]*temp_old[temp_box]);
}


//compute for bottom neighbours
if(box[curr_box].nBot == 0)
sum += (temp_old[curr_box]*box[curr_box].width);

for(j=0; j<box[curr_box].nBot;j++){

temp_box = box[curr_box].botNbor[j];

sum += (box[curr_box].botContact[j]*temp_old[temp_box]);
}



//compute for left neighbours
if(box[curr_box].nLeft == 0)
sum += (temp_old[curr_box]*box[curr_box].height);

for(j=0; j<box[curr_box].nLeft;j++){

temp_box = box[curr_box].leftNbor[j];
sum += (box[curr_box].leftContact[j]*temp_old[temp_box]);
}


//compute for right neighbours
if(box[curr_box].nRight == 0)
sum += (temp_old[curr_box]*box[curr_box].height);

for(j=0; j<box[curr_box].nRight;j++){

temp_box = box[curr_box].rightNbor[j];
sum += (box[curr_box].rightContact[j]*temp_old[temp_box]);
}


average = sum/ (2*(box[curr_box].height + box[curr_box].width));
temp_new[curr_box] = temp_old[curr_box]-(AFFECT_RATE*(temp_old[curr_box]-average));
}

}


//Beginning of main program

int main(int argc, char *argv[])
{

long long int num_iterations = 0;
//int clock_time=0;
float seconds_time=0;
double diff=0;
clock_t clock_time;
time_t timer_start;
time_t timer_end;
struct timespec chrono_start;
struct timespec start, end;
//printf ("%d", argc);
//printf("%s|\n%s|\n%s", argv[0],argv[1],argv[2]);
if(argc != 3)
{
printf("Invalid parameters");
return 0;
}

// Fetch epsilon and affect rate
EPSILON= atof(argv[2]);
AFFECT_RATE = atof(argv[1]);
//printf("%lf %lf %s",EPSILON, AFFECT_RATE, argv[2]);
//print_box();

readValues();
compute_contact_distance();
//printf("max = %lf    min = %lf \n", max_DSV, min_DSV);
time(&timer_start);
clock_time = clock();
clock_gettime(CLOCK_REALTIME, &chrono_start);
while((max_DSV - min_DSV) > (EPSILON* max_DSV)){

update_DSV();
//  print_data();
copy_data();
num_iterations++;
 // printf("max = %lf    min = %lf iteration =%lld\n", max_DSV, min_DSV, num_iterations);
}
//Timer value calculations
time(&timer_end);
seconds_time = difftime(timer_end,timer_start);
clock_time = clock()- clock_time;
clock_gettime(CLOCK_REALTIME, &end);
diff =(double)( ((end.tv_sec - start.tv_sec)*CLOCKS_PER_SEC) + ((end.tv_nsec - start.tv_nsec)/NS_PER_US));
//printf("\niterations = %lld\n",num_iterations);

printf("\n ********************************************** \n");
printf("\n dissipation converged in %ld iterations, with max DSV = %lf and min DSV = %lf", num_iterations,max_DSV, min_DSV);
printf("\n affectrate =%lf ;   epsilon=%lf", AFFECT_RATE, EPSILON);
printf("\n\n Elapsed converged loop-time (clock) : %lu", clock_time);
printf("\n\n Elapsed converged loop-time (time) : %.f", seconds_time); 
printf("\n\n Elapsed converged loop-time (chrono) : %.f", diff);
printf("\n ********************************************** \n");

deallocate();
return 0;
}

