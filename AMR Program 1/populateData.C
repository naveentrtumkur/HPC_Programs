#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simple_amr.h"
void setNeighbor(box *box1,int sideref,int numNeighbor, int **neigh);

int main()
{
    FILE* fp;
	box *box1;
char ch;
//gridBox grid[20];
    char file[20]="testgrid_1";
//	grid = (gridBox *)malloc(sizeof(gridBox)*20);
    int i=0,i1=0,j=0,id, x, y, h, w, numNeighbor, tmp;
  //  int numBox=0, numRow=0,numCol=0;
    float dsv;
    fp=fopen(file,"r");
	printf("enter numbox,numrow,numcol");
    fscanf(fp,"%d %d %d\n", &numBox, &numRow,&numCol);
	box1 = (box *)malloc(sizeof(box)*10);
	//printf("value===%d %d %d",numBox, numRow,numCol);
    while(fscanf(fp,"%c\n",&ch)!=EOF)
    {	
	fscanf(fp,"%d\n",&i);
	printf("store x,y,h,w\n");
	fscanf(fp,"%d %d %d %d\n", &x, &y, &h, &w);
	printf("In place 1\n");
	box1[i].upp_y = y;
	box1[i].upp_x = x;
	box1[i].height = h;
	box1[i].width = w;
	for( i1=0;i1<4;i1++)
	{
		printf("Enter neighbor value\n");
	    fscanf(fp,"%d\n",&numNeighbor);
	    int *neigh;
	    neigh = (int *)malloc(sizeof(int)*numNeighbor);
	    for( int j=0;j<numNeighbor;j++)
	    {
		printf("Enter teh tmp\n");
		fscanf(fp,"%d\n",&tmp);
		neigh[j] = tmp;
	    }
	    setNeighbor(&box1[i1], i1, numNeighbor, &neigh);
	}
	printf("Enter dsv\n");
	fscanf(fp,"%d\n",&dsv);
	box1[i].dsv = 10;
	printf("value=%d",box1[i].dsv);
	/*grid[i].id=id;
	grid[i].Box.upp_x =box1.upp_x;
	grid[i].Box.upp_y =box1.upp_y;
	grid[i].Box.low_x =box1.low_x;
	grid[i].Box.low_x =box1.low_x;
	j++;
	//fscanf(fp,"%c\n",&id);
*/
i++;
	}
	for(j=0;j<9;j++)
	{
	printf("%d\n",box1[j].upp_x);
	printf("%d\n",box1[j].dsv);
}	
return 0;
}
void setNeighbor(box *box1,int sideref,int numNeighbor, int **neigh)
{
switch(sideref)
{
    case 0:(*box1).nTop = numNeighbor;
            (*box1).topNbor = (*neigh);
            break;
        case 1:(*box1).nBot = numNeighbor;
            (*box1).botNbor = (*neigh);
            break;
        case 2:(*box1).nLeft = numNeighbor;
            (*box1).leftNbor = (*neigh);
            break;
        case 3:(*box1).nRight = numNeighbor;
               (*box1).rightNbor = (*neigh);
               break;
        default:
            break;
}
}
