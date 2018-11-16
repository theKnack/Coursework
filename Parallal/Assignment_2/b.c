#include<mpi.h>
#include<stdio.h>

void main() {
    int a,b,rank,siz;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &siz);
    if(rank==0) {
        scanf("%d",&a);
        printf("Master sends %d \n",a);
        MPI_Send(&a,1,MPI_INT,1,1,MPI_COMM_WORLD);
    }
    else{
        MPI_Recv(&b,1,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("Slave receives %d \n",b);
    }
    MPI_Finalize();
}
