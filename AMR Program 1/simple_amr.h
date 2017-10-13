/***********************************************
* Header File for Adaptive mesh refinement IPC Class
**
**
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(a,b) (a>b ? a:b)
#define min(a,b) (a<b ? a:b)

//int loadData(File *fp);

void mem_alloc();
int readValues();
void print_box();
void deallocate();
void copy_data();
void compute_contact_distance();
void update_DSV();

 struct Box{
	int upp_y, upp_x, height, width;
	int nTop, nBot, nLeft, nRight;
	int *topNbor, *topContact;
	int *botNbor, *botContact;
	int *leftNbor, *leftContact;
	int *rightNbor, *rightContact;
	//float dsv;
	//float newDsv;
	} *box;

