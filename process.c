#include <stdio.h>
#include <string.h>
#include "mpi.h"

void loadDataFromFile( char *fp,int *arr,int rank,int row, int col );
int printMatrix(int *output, int row, int col);
void FirstRound(int *voters , int portionSize , int NumOfCondidates ,double *result);
int main(int argc, char * argv[])
{

    int my_rank;
    int p;
    int source;
    int dest;
    int tag = 0;
    double *RecvedArr ;

    MPI_Status status;

    MPI_Init( &argc, &argv );
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if( my_rank == 0)
    {
        FILE *myFile;
        int CHUNK ;
        int Condidates, Voters ;
        char FileName[15];
        printf("Enter File Name >> ");
        scanf("%s", FileName);

        myFile = fopen(FileName, "r");

        fscanf(myFile, "%d",&Condidates);    // col=3
        fscanf(myFile, "%d",&Voters);    // row =4

        RecvedArr = malloc(Condidates*sizeof(double));

        CHUNK = Voters / (p-1);
        int i;
        for(i =1 ; i < p; i++)
        {
            MPI_Send(&CHUNK, 1, MPI_INT, i,tag, MPI_COMM_WORLD);
            MPI_Send(&Condidates, 1, MPI_INT, i,tag, MPI_COMM_WORLD);
            MPI_Send(FileName, 15, MPI_CHAR, i,tag, MPI_COMM_WORLD);

        }
         for(i =0 ;i < Condidates ;i++)
         {
             printf("Candidate[%d] = %f\n",i+1,RecvedArr[i]);

         }



        fclose(myFile);
    }
    else
    {
        int portion,columns;
        char myname[15];
        MPI_Recv(&portion, 1, MPI_INT, 0,tag, MPI_COMM_WORLD,&status);
        MPI_Recv(&columns, 1, MPI_INT, 0,tag, MPI_COMM_WORLD,&status);
        MPI_Recv(myname, 15, MPI_CHAR, 0,tag, MPI_COMM_WORLD,&status);


        int *arr = malloc(portion*columns* sizeof(int));
        loadDataFromFile(myname,arr,my_rank,portion,columns);
        int i;
        double  *FRound = malloc(columns*sizeof(double ));
        for (i = 0 ;i < columns ;i++)
        {
            FRound[i] =0.0;
        }
    //    printf("Process#%d\n",my_rank);
        FirstRound(arr , portion , columns ,FRound);
        MPI_Reduce(FRound , RecvedArr , columns ,MPI_DOUBLE ,MPI_SUM ,0,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
void loadDataFromFile( char *FileName,int *arr,int rank,int row, int col )
{

    int  i,j;

    int myOffset = (rank-1) *row*col ;
    FILE * myFile = fopen(FileName, "r");
    fseek(myFile,myOffset+4,SEEK_SET);
    for(i =0 ; i < row  ; i++)
    {

        for(j = 0 ; j < col ; j++)
        {
            int x;

            fscanf(myFile, "%d",(char *) &x);
            arr[(i*col)+j] = x;
        }
        fseek(myFile,1, SEEK_CUR);

    }
    fclose(myFile);

}

int printMatrix(int *output, int row, int col)
{
    int i,j;
    for (i = 0 ; i < row ; i++)
    {
        for(j = 0 ; j < col ; j++)
            printf("%d\t", output[(i*col)+j]);
        printf("\n");
    }
}

void FirstRound(int *voters , int portionSize , int NumOfCondidates ,double *result)
{
     int i ;
     for(i = 0 ; i < portionSize; i++)
    {
        result[voters[i* NumOfCondidates]-1]++;
    }
     for(i = 0 ; i < NumOfCondidates; i++)
    {
        result[i]/=portionSize;
        printf("%f\n",result[i]);
    }



}
