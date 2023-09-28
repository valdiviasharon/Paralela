#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define bar_count 100
int cant_threads;
int counter = 0;
pthread_mutex_t barrier_mutex;
pthread_cond_t ok_to_proceed;

void *Thread_work(void* rank) 
{
    #ifdef DEBUG
    long my_rank = (long) rank; 
    #endif
    for (int i = 0; i < bar_count; i++) {

        pthread_mutex_lock(&barrier_mutex);
        counter++;
        if(counter == cant_threads) 
        {
            counter = 0;
            #ifdef DEBUG
            printf("Thread %ld > Signalling other threads in barrier %d\n", my_rank, i);
            fflush(stdout);
            #endif
            pthread_cond_broadcast(&ok_to_proceed);
        } 
        else 
        {
            while (pthread_cond_wait(&ok_to_proceed, &barrier_mutex) != 0);
            #ifdef DEBUG
            printf("Thread %ld > Awakened in barrier %d\n", my_rank, i);
            fflush(stdout);
            #endif
        }
        
        pthread_mutex_unlock(&barrier_mutex);
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
   pthread_mutex_init(&barrier_mutex, NULL);
   pthread_cond_init(&ok_to_proceed, NULL);

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

   pthread_mutex_destroy(&barrier_mutex);
   pthread_cond_destroy(&ok_to_proceed);
   free(thread_handles);
   return 0;
}  

