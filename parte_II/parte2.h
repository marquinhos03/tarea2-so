#ifndef PARTE2_H
#define PARTE2_H

// includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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


#endif