#include "parte2.h"

TraceData *leer_traza(const char *nombre_archivo) {
    FILE *file = fopen(nombre_archivo, "r");
    if (!file) {
        perror("Error al abrir el archivo de traza");
        return NULL;
    }

    // Inicialización de memoria dinámica
    int capacidad = 10000;
    int count = 0;
    
    // Asignar memoria inicial
    unsigned int *buffer = malloc(sizeof(unsigned int) * capacidad);
    if (!buffer) {
        perror("Error de memoria");
        fclose(file);
        return NULL;
    }

    unsigned int valor_hex;

    // Leer el archivo línea por línea buscando hexadecimales
    // %x ignora saltos de línea y espacios
    while (fscanf(file, "%x", &valor_hex) == 1) {
        
        // Si se llena el buffer, duplicar su tamaño
        if (count >= capacidad) {
            capacidad *= 2;
            unsigned int *temp = realloc(buffer, sizeof(unsigned int) * capacidad);
            if (!temp) {
                perror("Error al redimensionar memoria");
                free(buffer);
                fclose(file);
                return NULL;
            }
            buffer = temp;
        }

        buffer[count] = valor_hex;
        count++;
    }

    fclose(file);

    TraceData *resultado = malloc(sizeof(TraceData));
    resultado->direcciones = buffer;
    resultado->n_lineas = count;

    return resultado;
}



void free_traza(TraceData *traza) {
    if (traza) {
        if (traza->direcciones) {
            free(traza->direcciones);
        }
        free(traza);
    }
}