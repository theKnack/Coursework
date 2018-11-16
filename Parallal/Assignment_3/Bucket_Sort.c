#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int MaxPos(int A[], int size) {
    int mi= 0;
    for (int i=0; i<size; i++){
        if(A[i]>A[mi]){
            mi=i;
        }
    }
    return mi;
}
void sort(int A[],int  size){
    int mi,temp;
    for(int i=size;i>1;i--) 
    {
        mi=MaxPos(A,i);
        temp=A[mi];
        A[mi]=A[i-1];
        A[i-1]=temp;
    }
}

void main() {
    int A[100],rank,size,rec;
    float ans = 0.0;
    MPI_Init(NULL, NULL);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0){
        for(int i=0; i<30; i++) {
            A[i] = rand() % size;
        }
        int max = 30;//A[0];
        int element[size];
        for(int d=1; d < size; d++) {
            element[d] = 0;
        }
        for(int d=0; d < 30; d++) {
            int inc = max/(size-1);
            int itr = 1;
            bool flag=0;
            for(int j = inc; j <= max; j = j + inc) {
                if(A[d] <= j) {
                    element[itr]++;
                    flag=1;
                    break;
                }
                itr++;
            }
            if (!flag) {
                element[itr-1]++;
            }
        }
        for(int i=1; i<size; i++) {
            MPI_Send(&element[i], 1, MPI_INT, i, 2, MPI_COMM_WORLD);
        }
        for(int d=0; d < 30; d++) {
            int inc = max/(size-1);
            int itr = 1;
            bool flag = false;
            for ( int j = inc; j <= max; j = j + inc) {
                if(A[d] <= j) {
                    MPI_Send(&A[d], 1, MPI_INT, itr, 4, MPI_COMM_WORLD);
                    flag = true;
                    break;
                }
                itr++;
            }
            if (!flag) {
                MPI_Send(&A[d], 1, MPI_INT, itr-1, 4, MPI_COMM_WORLD);
            }
        }
        int lastIndex = 0, ind = 0, last;
        for(int i=1; i < size; i++) {
            int recvArray[element[i]];
            MPI_Recv(&recvArray[0], element[i], MPI_INT, i, 5, MPI_COMM_WORLD, &status);
            if(last == 0) {
                last = element[i];
            }
            for(int j=0; j<element[i]; j++) {
                A[ind] = recvArray[j];
                ind++;
            }
        }
        for(int c = 0 ; c < 30 ; c++)  {
            printf("%d ",A[c]);
        }
    }
    else {
        int newsize; 

        MPI_Recv(&newsize, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
        int localArray[newsize]; 
        for(int li = 0; li < newsize; li++) {
            MPI_Recv(&rec, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);
            localArray[li] =  rec;
        }
        sort(localArray,newsize);

        MPI_Send(localArray, newsize, MPI_INT, 0, 5, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}


