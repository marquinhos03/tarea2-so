#include "parte1.h"

int barrier_init(Barrier *b, int N) {
   b->count = 0;
   b->N = N;
   b->etapa = 0;

   pthread_mutex_init(&b->mutex, NULL);
   pthread_cond_init(&b->cond, NULL);

   return 0;
}

int barrier_wait(Barrier *b) {
   pthread_mutex_lock(&b->mutex);

   // Captura local
   int etapa_actual = b->etapa;
   int ultima = b->N;

   b->count++;

   if (b->count == ultima) {
      // Caso: Es la ultima en llegar
      
      // (i) incrementar etapa
      b->etapa++;
      // (ii) resetear count
      b->count = 0;

      // (iii) broadcast para despertar a todas.
      pthread_cond_broadcast(&b->cond);

      // unlock
      pthread_mutex_unlock(&b->mutex);

      return -1;
   } else {
      // Caso: Esperar mientras no cambie (poner a dormir)
      while (b->etapa == etapa_actual) {
         pthread_cond_wait(&b->cond, &b->mutex);
      }
      
      // unlock
      pthread_mutex_unlock(&b->mutex);

      return 0;
   }
}

int barrier_destroy(Barrier *b) {
   pthread_mutex_destroy(&b->mutex);
   pthread_cond_destroy(&b->cond);

   return 0;
}