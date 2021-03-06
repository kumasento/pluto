#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#include "mkl.h"

#define N MYN
#define alpha MYalpha 
double *A;
double *B;

void init_arrays()
{
  int i,j;
  A = (double*) malloc(N*N*sizeof(double));
  B = (double*) malloc(N*N*sizeof(double));
  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      {
	B[i*N+j] = (i+j) % 5 + 1;
	if (i < j)
	  A[i*N+j] = (i+j) % 5 + 1;
	else if (i == j)
	  A[i*N+j] = 1;
	else
	  A[i*N+j] = -1;
      }
}

void print_array() 
{ 
  int i, j; 
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) { 
      fprintf(stderr, "%lf ", round(B[i*N+j])); 
      if (j%80 == 79) fprintf(stderr, "\n"); 
    } 
    fprintf(stderr, "\n"); 
  } 
  fprintf(stderr, "\n"); 
} 

double rtclock()
{
  struct timezone tzp;
  struct timeval tp;
  int stat;
  gettimeofday (&tp, &tzp);
  return (tp.tv_sec + tp.tv_usec*1.0e-6);
}

int main()
{
  init_arrays();

  double annot_t_start=0, annot_t_end=0, annot_t_total=0;
  int annot_i;

  for (annot_i=0; annot_i<REPS; annot_i++)
  {
    annot_t_start = rtclock();
    
    cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasUnit, 
		N, N, MYalpha, A, N, B, N); 
    
    annot_t_end = rtclock();
    annot_t_total += annot_t_end - annot_t_start;
  }
  
  annot_t_total = annot_t_total / REPS;
  printf("%f\n", annot_t_total);

  //print_array();
  
  return ((int) B[0*N+0]); 
}
                                    

