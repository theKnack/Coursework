#include<mpi.h>
#include<stdio.h>

void main() {
    int a,rank, siz;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &siz);
    if(rank==0){
        scanf("%d", &a);
        printf("Root node sends %d to all others \n", a);
    }
    MPI_Bcast(&a, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank!=0){
        printf("Process %d receives %d \n",rank,a);
    }
    MPI_Finalize();
}
