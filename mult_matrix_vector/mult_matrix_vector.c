//Multiply matrix on vector

#include "mpi.h"
#include <stdio.h>
#include <omp.h>

#define SIZE 16
#define VECTOR 16
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
int main(int argc, char *argv[])
{
 int numtasks, rank, source, dest, outbuf, tag = 1,i,j;
 int inbuf[4] = {MPI_PROC_NULL, MPI_PROC_NULL,MPI_PROC_NULL,MPI_PROC_NULL};
int nbrs[4], dims[2] = {4,4}; periods[2]= {1,1}, reoder=0, coords[2];
int mass[4][4], vector[VECTOR], sum;
MPI_Request reqs[8];
MPI_Status stats[8];
MPI_Comm cartcomm;


MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
if(numtasks == SIZE)
{
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
for(i=0; i<4; i++)
{
   for(j=0; j<4; j++)
{
mass[i][j]=0;
}
}
vector[0]= ((rank+1)+clock())%32;
for(i=1; i<VECTOR; i++)
vector[i]=(15*vector[i-1]+(rank+1)*31)%32;
sum=0;
#pragma omp parallel
{
#pragma omp for reduction(+:sum)
for(i=0; i<VECTOR; i++)
sum = sum+vector[i];
}
mass[rank/4][rank%4] = sum;
for(i=0; i<16; i++)
MPI_Bcast(&mass[i/4][i%4],1,MPI_INT,i,MPI_COMM_WORLD);
if(rank==0){
for(i=0; i<4; i++){
for(j=0; j<4; j++) {
printf("%d", mass[i][j]);
if(j==3)
printf("\n");

}
}
printf("\n");
}
MPI_Cart_create(MPI_COMM_WORLD,2,dims,periods,reoder,&cartcomm);
MPI_Cart_shift(cartcomm,0,1,&nbrs[UP],&nbrs[DOWN]);
MPI_Cart_shift(cartcomm,1,1,&nbrs[LEFT],&nbrs[RIGHT]);
outbuf=mass[rank/4][rank%4]
for(i=0; i<4; i++){
dest=nbrs[i];
source=nbrs[i];
MPI_Isend(&outbuf,1,MPI_INT,dest,tag,MPI_COMM_WORLD,&reqs[i]);
MPI_Irecv(&inbuf[i],1,MPI_INT,source,tag,MPI_COMM_WORLD,&reqs[i+4]);
}
MPI_Waitall98,reqs,stats);
mass[rank/4][rank%4]=(inbuf[0]+inbuf[1]+inbuf[2]+inbuf[3])/4;
for(i=0; i<16; i++)
MPI_Bcast(&mass[i/4][i%4],1,MPI_INT,i,MPI_COMM_WORLD);
if(rank==0){
for(i=0; i<4; i++){
for(j=0; j<4; j++) {
printf("%d", mass[i][j]);
if(j==3)
printf("\n");

}
}
printf("\n");
}
else
printf("Must specify %d tasks. \n", SIZE);
MPI_Finalize();
return 0;
}

