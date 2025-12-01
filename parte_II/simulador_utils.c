#include "parte2.h"

/**
 * Descomposición de la DV
 */
DireccionVirtual descomponer_dv(unsigned long dv, int b, unsigned long mask) {
    DireccionVirtual dv_struct;
    
    dv_struct.dv_hex = dv;
    dv_struct.npv = dv >> b;
    dv_struct.offset = dv & mask;
    
    return dv_struct;
}

/**
 * Calcular la dirección física
 */
DireccionFisica calcular_df(unsigned int marco, int b, unsigned long offset) {
    DireccionFisica df_struct;
    
    df_struct.marco = marco;
    df_struct.df = (marco << b) | offset;
    
    return df_struct;
}


int asignar_marco(
    Marco *memoria_fisica,
    PTE *tabla_paginas,
    int *manecilla,
    int N_marcos
) {
    
    // Buscar marco libre
    for (int i = 0; i < N_marcos; i++) {
        if (memoria_fisica[i].ocupado == 0) {
            return i;
        }
    }

    // Si no había libres, ejecutar Algoritmo de Reloj
    while (true) {
        int candidato = *manecilla;
        unsigned long npv_vieja = memoria_fisica[candidato].npv;

        if (tabla_paginas[npv_vieja].R == 1) {
            // CASO PAGINA USADA RECIENTEMENTE (dar segunda oportunidad)
            tabla_paginas[npv_vieja].R = 0;
            // Avanzar el puntero para seguir recorriendo
            *manecilla = (*manecilla + 1) % N_marcos;
        } else {
            // CASO PAGINA ES ELEGIDA PARA REEMPLAZO
            // Se encontró una víctima
            
            // Invalidar npv expulsada
            tabla_paginas[npv_vieja].V = 0;
            tabla_paginas[npv_vieja].NM = 0;

            // Avanzar el puntero para la proxima vez
            *manecilla = (*manecilla + 1) % N_marcos;
            return candidato;
        }
    }
}



void resolver_fallo_de_pagina(
    unsigned long npv_fallo,
    PTE *tabla_paginas,
    Marco *memoria_fisica,
    int *manecilla,
    int N_marcos
) {

    int marco_seleccionado = asignar_marco(
        memoria_fisica,
        tabla_paginas,
        manecilla,
        N_marcos
    );

    // Mapear npv con fallo a marco
    memoria_fisica[marco_seleccionado].ocupado = 1;
    memoria_fisica[marco_seleccionado].npv = npv_fallo;

    // Actualizar Tabla de Paginas
    tabla_paginas[npv_fallo].NM = marco_seleccionado;
    tabla_paginas[npv_fallo].V = 1;
    tabla_paginas[npv_fallo].R = 1;
}



DireccionFisica traducir_direccion(
    DireccionVirtual dv,
    PTE *tabla_paginas,
    int b,
    Marco *memoria_fisica,
    int *manecilla,
    int N_marcos
) {
    
    // *entrada por comodidad para no escribir tabla_paginas[dv.npv] a cada rato xd
    PTE *entrada = &tabla_paginas[dv.npv];

    // CASO MISS (fallo de pagina)
    if (entrada->V == 0) {
        resolver_fallo_de_pagina(dv.npv, tabla_paginas, memoria_fisica, manecilla, N_marcos);
        
        return traducir_direccion(dv, tabla_paginas, b, memoria_fisica, manecilla, N_marcos);
    }

    // CASO HIT (o MISS resuelto)
    entrada->R = 1;
    
    return calcular_df(entrada->NM, b, dv.offset);
}