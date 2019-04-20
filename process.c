#include <stdio.h>
#include <string.h>
#include "mpi.h"

void loadDataFromFile( FILE *fp,int *arr,int rank,int row , int col );

int printMatrix(int *output , int row , int col);
int main(int argc , char * argv[])
{
       FILE *myFile;
	int my_rank;
	int p;			
	int source;
	int dest;	
	int tag = 0;	
     int Condidates, Voters ;
    
	MPI_Status status;	
				
    MPI_Init( &argc , &argv );
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if( my_rank == 0)
	{
        
     
        char FileName[15];
        printf("Enter File Name >> ");
        scanf("%s" , FileName);

        myFile = fopen(FileName, "r");
       
        fscanf(myFile , "%d" ,&Condidates);  // col=3
        fscanf(myFile , "%d" ,&Voters);  // row =4

       fclose(myFile);
	}
	MPI_Finalize();
	return 0;
}
void loadDataFromFile( FILE *fp,int *arr,int rank,int row , int col )
{
    
   int  i,j;

  // printf("%d\t%d\n" , row , col );
    for(i =0 ;i < row  ;i++)
    {   
        
         for(j = 0 ;j < col ; j++)
            {
                int x ; 
                fscanf(fp, "%d",(char *) &x);
                 arr[(i*col)+j] = x;
            }
           fseek(fp,1, SEEK_CUR);
           
    }


}

int printMatrix(int *output , int row , int col)
{
    int i,j;
       for (i = 0 ; i < row ; i++){
            for(j = 0 ;j < col ;j++)
                printf("%d\t" , output[(i*col)+j]);
            printf("\n");
        }
}