#ifndef PARTE2_H
#define PARTE2_H

// includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// Structs de datos

typedef struct {
   unsigned int NM; // Marco de página
   int V;  // Bit válido
   int R;  // Bit de referencia (se setea cuando la página es leída o escrita)
   int M;  // Dirty bit (se setea cuando la pagina ha sido escrita)
} PTE;


typedef struct {
   int ocupado;  // 1 si tiene pagina asignada, 0 si esta vacío
   unsigned long npv;  // Guarda la página virtual
} Marco;


typedef struct {
   unsigned long dv_hex;   // Dirección virtual en hexadeciaml
   unsigned long npv;
   unsigned long offset;
} DireccionVirtual;


typedef struct {
   unsigned int marco;     // Marco fisico de la pagina virtual
   unsigned long df;       // Dirección física
} DireccionFisica;

// Struct para la trace
typedef struct {
    unsigned int *direcciones;
    int n_lineas;
} TraceData;


// leer_traza.c

TraceData *leer_traza(const char *nombre_archivo);
void free_traza(TraceData *trace);


// simulador_utils.c

DireccionVirtual descomponer_dv(unsigned long dv, int b, unsigned long mask);

DireccionFisica calcular_df(unsigned int marco,int b,unsigned long offset);

int asignar_marco(
    Marco *memoria_fisica,
    PTE *tabla_paginas,
    int *manecilla,
    int N_marcos
);

void resolver_fallo_de_pagina(
    unsigned long npv_fallo,
    PTE *tabla_paginas,
    Marco *memoria_fisica,
    int *manecilla,
    int N_marcos
);

DireccionFisica traducir_direccion(
    DireccionVirtual dv,
    PTE *tabla_paginas,
    int b,
    Marco *memoria_fisica,
    int *manecilla,
    int N_marcos
);

#endif