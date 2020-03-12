#include <omp.h>
#include "mpi.h"
#include <stdio.h>
#include <unistd.h>

double measure_time();

int main(int argc, char *argv[])
{
	int sum_pr, num_pr;
	int k = 512*1024*1024;
	double time, time_pr, all_time, vel;
	MPI_Init(&argc, &argv);
	MPI_Comm_size( MPI_COMM_WORLD, &sum_pr);
	MPI_Comm_rank( MPI_COMM_WORLD, &num_pr);
	
	time_pr = measure_time(); // time of work processor

	MPI_Reduce(&time_pr, &all_time, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if( num_pr == 0 )
	{
		time = all_time/sum_pr;
		printf(" time:	%f sec \n", time);

		vel = (32.0 * k) / (time * 1024 * 1024 * 1024 ); // velocity
		printf(" velocity:	%f Gb/sec \n", vel);
	}
	MPI_Finalize();
}

