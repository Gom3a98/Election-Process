#include <stdio.h>
#include <string.h>
#include "mpi.h"

void loadDataFromFile( FILE *fp,int **arr,int rank,int row , int col );
int **AllocateMatrix(int row , int col);
int main(int argc , char * argv[])
{
	int my_rank;
	int p;			
	int source;
	int dest;	
	int tag = 0;	
	MPI_Status status;	
				
    MPI_Init( &argc , &argv );
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if( my_rank == 0)
	{
        int i,j;
        FILE *myFile;
        myFile = fopen("kemo.txt" , "r");
        int col , row ;
      
        fscanf(myFile , "%d" ,&col);
        fscanf(myFile , "%d" ,&row);
        
        int output[row][col];
       // output = AllocateMatrix(row,col);
        loadDataFromFile(myFile , output , my_rank , row  , col );
            printf("Hiiiwrqreiiiiiiiiiiii");
        for (i = 0 ; i < row ; i++){
            for(j = 0 ;j < col ;j++)
                printf("%d\t" , output[i][j]);
            printf("\n");
        }
            printf("Hiiii");
            fclose(myFile);
	}
	MPI_Finalize();
	return 0;
}
void loadDataFromFile( FILE *fp,int **arr,int rank,int row , int col )
{
    
   int  i,j;
   //fseek(fp , cluster , SEEK_SET);
    for(i =0 ;i < row  ;i++)
    {
        printf("Hiiiiiiiiiiiiiii\n");
         for(j = 0 ;j < col ; j++)
            fscanf(fp, "%d",(char *) & arr[i][j]);
    }


}

int **AllocateMatrix(int row , int col)
{
    int *lin , **matrix,i;
    lin = malloc(row * col *sizeof(int));
    for(i = 0 ;i < row ; i++)
    {
        matrix[i]= &lin[i*col];
    }
    return matrix;
}