
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  int siz,rank,len;
  MPI_Comm_size(MPI_COMM_WORLD, &siz);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  MPI_Get_processor_name(processor_name, &len);
  printf("Processor Name: %s\n Processor Rank: %d\n Size:%d\n Message: Hello World\n",processor_name, rank, siz);
  MPI_Finalize();
}
