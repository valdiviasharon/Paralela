#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define bar_count 100

int cant_threads;
int counter;
sem_t barrier_sems[bar_count];
sem_t cant_sem;

void *Thread_work(void* rank) 
{
   #ifdef DEBUG
      long my_rank = (long) rank;
   #endif

   for (int i = 0; i < bar_count; i++) 
   {
      sem_wait(&cant_sem);
      if (counter == cant_threads - 1) 
      {
         counter = 0;
         sem_post(&cant_sem);
         for (int j = 0; j < cant_threads-1; j++)
            sem_post(&barrier_sems[i]);
      } 
      else 
      {
         counter++;
         sem_post(&cant_sem);
         sem_wait(&barrier_sems[i]);
      }
      #ifdef DEBUG
      if (my_rank == 0) 
      {
         printf("All threads completed barrier %d\n", i);
         fflush(stdout);
      }
      #endif
   }

   return NULL;
}

int main(int argc, char* argv[]) 
{
   pthread_t* thread_handles; 
   double start, finish;
   struct timeval t; 
   cant_threads = strtol(argv[1], NULL, 10);

   thread_handles = malloc (cant_threads*sizeof(pthread_t));
   for (int i = 0; i < bar_count; i++)
      sem_init(&barrier_sems[i], 0, 0);
   sem_init(&cant_sem, 0, 1);

   gettimeofday(&t, NULL); 
   start = t.tv_sec + t.tv_usec/1000000.0; 
   for (long thread = 0; thread < cant_threads; thread++)
      pthread_create(&thread_handles[thread], NULL, Thread_work, (void*) thread); //crea los threads

   for (long thread = 0; thread < cant_threads; thread++) {  //Une los pthreads
      pthread_join(thread_handles[thread], NULL);
   }
   gettimeofday(&t, NULL); 
   finish = t.tv_sec + t.tv_usec/1000000.0; 

   printf("Elapsed time = %e seconds\n", finish - start);

   sem_destroy(&cant_sem);
   for (int i = 0; i < bar_count; i++)
      sem_destroy(&barrier_sems[i]);

   free(thread_handles);
   return 0;
}  

