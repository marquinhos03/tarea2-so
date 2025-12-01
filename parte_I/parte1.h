#ifndef PARTE1_H
#define PARTE1_H

// includes
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// Inicialización por defecto N hebras y E etapas
#define N_DEFAULT 5
#define E_DEFAULT 4

// Struct para la barrera
typedef struct {
   /** número de hebras que han llegado a la barrera en la etapa actual. */
   int count;
   /** número total de hebras que deben esperar (parámetro de inicialización). */
   int N;
   /** identificador de etapa donde operan N hebras. */
   int etapa;

   /** Garantiza exclusión mutua del estado interno. */
   pthread_mutex_t mutex;  
   /** Para que los hebras esperen hasta que lleguen todas al punto de espera. */
   pthread_cond_t cond;

} Barrier;

// Funciones
int barrier_init(Barrier *b, int N);
int barrier_wait(Barrier *b);
int barrier_destroy(Barrier *b);

#endif