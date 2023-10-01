
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#ifdef DEBUG
const int RMAX = 100;
#else
const int RMAX = 10000000;
#endif

int thread_count;

void Get_args(int argc, char* argv[], int* n_p) {

   thread_count = strtol(argv[1], NULL, 10);
   *n_p = strtol(argv[2], NULL, 10);
}
void Generate_list(int a[], int n) {
   int i;

   srandom(1);
   for (i = 0; i < n; i++)
      a[i] = random() % RMAX;
}
void Print_list(int a[], int n, char* title) {
   int i;

   printf("%s:\n", title);
   for (i = 0; i < n; i++)
      printf("%d ", a[i]);
   printf("\n\n");
}
void Odd_even(int a[], int n) {
   int phase, i, tmp;

#  pragma omp parallel num_threads(thread_count) \
      default(none) shared(a, n) private(i, tmp, phase)
   for (phase = 0; phase < n; phase++) {
      if (phase % 2 == 0)
#        pragma omp for 
         for (i = 1; i < n; i += 2) {
            if (a[i-1] > a[i]) {
               tmp = a[i-1];
               a[i-1] = a[i];
               a[i] = tmp;
            }
         }
      else
#        pragma omp for 
         for (i = 1; i < n-1; i += 2) {
            if (a[i] > a[i+1]) {
               tmp = a[i+1];
               a[i+1] = a[i];
               a[i] = tmp;
            }
         }
   }
}

int main(int argc, char* argv[]) 
{
   int  n;
   int* a;
   double start, finish;

   Get_args(argc, argv, &n);
   a = malloc(n*sizeof(int));
      Generate_list(a, n);
#     ifdef DEBUG
      Print_list(a, n, "Before sort");
#     endif

   start = omp_get_wtime();
   Odd_even(a, n);
   finish = omp_get_wtime();

#  ifdef DEBUG
   Print_list(a, n, "After sort");
#  endif
   
   printf("Elapsed time = %e seconds\n", finish - start);

   free(a);
   return 0;
}  
