#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simple_amr.h"
void setNeighbor(box *box1,int sideref,int numNeighbor, int *neigh);

int main()
{
	FILE* fp;
	box *box1;
	char ch;
    char file[20]="testgrid_1";
    int i=0,i1=0,j=0,id, x, y, h, w, numNeighbor, tmp;
    int numBox=0, numRow=0,numCol=0;
    float dsv;
    fp=fopen(file,"r");
	printf("enter numbox,numrow,numcol");
    fscanf(fp,"%d %d %d\n", &numBox, &numRow,&numCol);
	box1 = (box *)malloc(sizeof(box)*numBox);
	//printf("value===%d %d %d",numBox, numRow,numCol);
fscanf(fp,"%d\n",&id);
    while(id!=-1)
    {	
	//fscanf(fp,"%d\n",&id);
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
	    //setNeighbor(&box1[i], i1, numNeighbor, neigh);
	switch(i1)
{
    case 0:box1[i].nTop = numNeighbor;
            box1[i].topNbor = (neigh);
            printf("value1= %d , value 2= %d\n",box1[i].nTop,(box1[i].topNbor[0]));
            break;
        case 1:box1[i].nBot = numNeighbor;
            box1[i].botNbor = (neigh);
            printf("value1= %d , value 2= %d\n",box1[i].nBot,box1[i].botNbor[1]);
            break;
        case 2:box1[i].nLeft = numNeighbor;
            box1[i].leftNbor = (neigh);
            printf("value1= %d , value 2= %d\n",(*box1).nLeft,(*box1).leftNbor[2]);
            break;
        case 3:box1[i].nRight = numNeighbor;
               box1[i].rightNbor = (neigh);
            printf("value1= %d , value 2= %d\n",(*box1).nRight,(*box1).rightNbor[3]);
               break;
        default:
            break;
}

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
	//j++;
	//fscanf(fp,"%c\n",&id);
*/
//i++;
fscanf(fp,"%d\n",&id);
	}
	for(j=0;j<9;j++)
	{
	printf("%d\n",box1[j].upp_x);
	printf("%d\n",box1[j].dsv);
}	
return 0;
}
void setNeighbor(box *box1,int sideref,int numNeighbor, int *neigh)
{
switch(sideref)
{
    case 0:(*box1).nTop = numNeighbor;
            (*box1).topNbor = (neigh);
	    printf("value1= %d , value 2= %d\n",(*box1).nTop,(*box1).topNbor);
            break;
        case 1:(*box1).nBot = numNeighbor;
            (*box1).botNbor = (neigh);
	    printf("value1= %d , value 2= %d\n",(*box1).nBot,(*box1).botNbor);
            break;
        case 2:(*box1).nLeft = numNeighbor;
            (*box1).leftNbor = (neigh);
	    printf("value1= %d , value 2= %d\n",(*box1).nLeft,(*box1).leftNbor);
            break;
        case 3:(*box1).nRight = numNeighbor;
               (*box1).rightNbor = (neigh);
	    printf("value1= %d , value 2= %d\n",(*box1).nRight,(*box1).rightNbor);
               break;
        default:
            break;
}
}
