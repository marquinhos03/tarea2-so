#include "parte1.h"

Barrier barrera;
int N = N_DEFAULT;
int E = E_DEFAULT;

// Ejecución de una etapa
void *ejecutar_etapa(void* arg) {
   long tid = (long)arg;

   for (int e = 0; e < E; e++) {
      // a) Realiza trabajo simulado (usleep con ± aleatorio).
      int tiempo = (rand() % 400000) + 100000;
      usleep(tiempo);

      // b) Imprime antes de esperar
      printf("[%ld] esperando en etapa %d\n", tid, e);

      // c) Llama a wait()
      barrier_wait(&barrera);

      // d) Imprime después de pasar
      printf("[%ld] paso barrera en etapa %d\n", tid, e);
   }
}

// main
int main(int argc, char *argv[]) {
   srand(time(NULL));

   if (argc > 1) N = atoi(argv[1]); 
   if (argc > 2) E = atoi(argv[2]);
   
   barrier_init(&barrera, N);
   pthread_t hebras[N];

   for (long i = 0; i < N; i++) {
      pthread_create(&hebras[i], NULL, ejecutar_etapa, (void*)i);
   }

   for (int i = 0; i < N; i++) {
      pthread_join(hebras[i], NULL);
   }

   barrier_destroy(&barrera);

   return 0;
}