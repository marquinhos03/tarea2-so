#include "parte2.h"

#define MAX_PAGES 1048576

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Uso: %s <N_marcos> <tam_marco> [--verbose] <archivo_traza>\n", argv[0]);
        return 1;
    }

    int N_marcos = atoi(argv[1]);
    int tam_marco = atoi(argv[2]);  // PAGE_SIZE
    bool verbose = false;
    char *archivo = NULL;

    if (strcmp(argv[3], "--verbose") == 0) {
        if (argc < 5) return 1;

        verbose = true;
        archivo = argv[4];
    } else {
        archivo = argv[3];
    }

    TraceData *traza = leer_traza(archivo);
    if (!traza) return 1;

    int b = (int)log2(tam_marco);
    unsigned long mask = (1UL << b) - 1;

    PTE *tabla_paginas = calloc(MAX_PAGES, sizeof(PTE));
    Marco *memoria_fisica = calloc(N_marcos, sizeof(Marco));
    int manecilla = 0;

    // Estadísticas
    int total_referencias = 0;
    int total_fallos = 0;
    float tasa_fallos = 0.0;

    printf("Iniciando simulación con %d marcos...\n\n", N_marcos);

    for (int i = 0; i < traza->n_lineas; i++) {
        unsigned long dir = traza->direcciones[i];
        total_referencias++;

        DireccionVirtual dv = descomponer_dv(dir, b, mask);
        char *resultado_acceso;

        if (tabla_paginas[dv.npv].V == 0) {
            resultado_acceso = "FALLO";
            total_fallos++;
        } else {
            resultado_acceso = "HIT";
        }

        DireccionFisica df = traducir_direccion(
            dv, tabla_paginas, b, memoria_fisica, &manecilla, N_marcos
        );

        if (verbose) {
            // Formato : DV, nvp, offset, HIT/FALLO, marco usado, DF
            printf("DV: 0x%04lx | npv: %lu | offset: %lu | %s | Marco: %d | DF: 0x%04lx\n", 
                dv.dv_hex, dv.npv, dv.offset, resultado_acceso, df.marco, df.df
            );
        }
    }

    // Salida de simulación
    if (total_referencias > 0) tasa_fallos = (float)total_fallos / total_referencias;
    
    printf("Totales: Referencias | Fallos de página | Tasa de fallos\n");
    printf("             %d              %d               %.4f\n",
        total_referencias, total_fallos, tasa_fallos
    );
    
    free(tabla_paginas);
    free(memoria_fisica);
    free_traza(traza);

    return 0;
}
