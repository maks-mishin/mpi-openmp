#include <omp.h>
#include "mpi.h"

double measure_time()
{
	int i, n;
	int k = 1024*1024*512;
	
	double time, start = 0.0, end = 0.0, q = 0.05;
	double *a = (double*)malloc(k*sizeof(double));
	double *b = (double*)malloc(k*sizeof(double));
	double *c = (double*)malloc(k*sizeof(double));

	for(i=0; i< k; i++)
	{
		a[i] = 0.0;
		b[i] = 0.1;
		c[i] = 0.5;
	}

	start = MPI_Wtime();
	
	for(n = 1; n <= 100; n++) {
	#pragma omp parallel for shared( k, a, b, c, q ) private(i)
		for(i = 0; i < k; i++)
			a[i] = b[i] + q * c[i];
	}
	end = MPI_Wtime();
	time = (end - start)/100;
	return time;
}














