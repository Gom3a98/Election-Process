#include <stdio.h>
#include <string.h>
#include "mpi.h"

void loadDataFromFile( FILE *fp,int *arr,int rank,int row , int col );

int printMatrix(int *output , int row , int col);
int main(int argc , char * argv[])
{
      
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
    int CHUNK ;
     char FileName[15];
	if( my_rank == 0)
	{
       FILE *myFile; 
        printf("Enter File Name >> ");
        scanf("%s" , FileName);

        myFile = fopen(FileName, "r");
       
        fscanf(myFile , "%d" ,&Condidates);  // col=3
        fscanf(myFile , "%d" ,&Voters);  // row =4
        CHUNK = Voters / (p-1);
       fclose(myFile);
	}
    MPI_Bcast(&CHUNK , 1 , MPI_INT , tag  , MPI_COMM_WORLD);
    MPI_Bcast(&Condidates , 1 , MPI_INT , tag  , MPI_COMM_WORLD);

    printf("I'm process #%d have %d Voters To Handle\n", my_rank , CHUNK);

    int myOffset = my_rank * CHUNK *Condidates ;        // 6-2 * 2 * 3
    int *arr = malloc(CHUNK * Condidates * sizeof(int));
    
	MPI_Finalize();
	return 0;
}
void loadDataFromFile( char *FileName,int *arr,int rank,int row , int col )
{
     
   int  i,j;
  FILE * myFile = fopen(FileName, "r");
        fseek(fp,4,SEEK_SET);
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
       fclose(myFile);

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