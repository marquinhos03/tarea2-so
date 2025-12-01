# Tarea 2: Sistemas Operativos

## Sobre la Tarea 

### Parte I. Sincronización con Barrera reutilizable
> **Actividad 1:** Implementación de la barrera (Monitor).
>
> **Actividad 2:** Aplicación de verificación de comportamiento de la barrera.

### Parte II. Simulador simple de Memoria Virtual
> En esta parte debe implementar un simulador, **sim** con paginación simple y soporte de algoritmo de reemplazo Reloj con un solo puntero.


## 💻 Instalación, Compilación y Ejecución

Pasos para clonar, compilar y ejecutar **Parte I** y **Parte II**.

### 1. Clonar el Repositorio

```
 git clone https://github.com/marquinhos03/tarea2-so.git
 cd tarea2-so
```

### 2. Compilación

Ambas partes utilizan un Makefile para la compilación. Ejecute el comando **make** para crear ambos ejecutables.

```
 make
```
### 3. Ejecución

```
 ./parte1
 ./parte1 <Nhebras> <Netapas>
```

```
 ./sim <Nmarcos> <tamañomarco> trace1.txt (o trace2.txt)
 ./sim <Nmarcos> <tamañomarco> --verbose trace1.txt (o trace 2.txt)
```

## 📝 Ejemplos de salida

* **Parte I**

```
 ./parte1
 [4] esperando en etapa 0
 [2] esperando en etapa 0
 [3] esperando en etapa 0
 [0] esperando en etapa 0
 [1] esperando en etapa 0
 [1] paso barrera en etapa 0
 [0] paso barrera en etapa 0
 [2] paso barrera en etapa 0
 [3] paso barrera en etapa 0
 [4] paso barrera en etapa 0
 ...
 ...
 ...
 [4] esperando en etapa 3
 [2] esperando en etapa 3
 [0] esperando en etapa 3
 [1] esperando en etapa 3
 [3] esperando en etapa 3
 [3] paso barrera en etapa 3
 [2] paso barrera en etapa 3
 [1] paso barrera en etapa 3
 [4] paso barrera en etapa 3
 [0] paso barrera en etapa 3
```

* **Parte II**

```
 ./sim 8 4096 traza1.txt
 Iniciando simulación con 8 marcos...

 Totales: Referencias | Fallos de página | Tasa de fallos
             8192              1               0.0001
```
