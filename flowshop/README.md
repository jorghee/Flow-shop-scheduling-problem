## Instancias de FSSP

En el directorio [flowshop/](./flowshop/) se encuentran 121 instancias. Las 
instancias son archivos con el formato *ASCII text* los cuales estan disponibles 
para ser cargados y usados en el cálculo del `makespan`. El formato de archivo de 
datos para el FSSP comienza con dos números en la primera linea: el número de 
trabajos y el número de máquinas [1]. Por ejemplo, veamos la estructura de la 
instancia [flowshop/br66](./flowshop/br66)

```zsh
6 6
0 3 1 6 2 3 3 3 4 4 5 3
0 4 1 3 2 5 3 3 4 5 5 2
0 6 1 5 2 2 3 2 4 2 5 4
0 4 1 5 2 2 3 2 4 5 5 5
0 2 1 2 2 5 3 6 4 3 5 5
0 2 1 3 2 5 3 5 4 3 5 3
```
Luego, el archivo tiene *nT* líneas, una para cada trabajo. Cada línea tiene *2 x mM*
columnas para ese trabajo; es decir, tiene dos columnas para cada actividad de ese 
trabajo: **el número de la máquina y le timepo de procesamiento** [1].

## La función `cargar`

El objetivo es cargar correctamente una instancia en una arreglo bidimensional 
(matriz). En esta ocasión a nosotros solo nos importa los tiempos de procesamiento 
de cada trabajo en cada máquina, por ello vamos a obviar cargar el número de la 
máquina.

```cpp
#include <bits/stdc++.h>
using namespace std;

int nT, mM, P[900][70];

void cargar(string nombre) {
  ifstream archivo(nombre);
  archivo >> nT >> mM;
  int basura;
  for (int j = 0; j < nT; j++)
    for (int i = 0; i < mM; i++)
      archivo >> basura >> P[j][i];
}
```

Como observamos, *nT* y *mM* es el número de trabajos y el número de máquinas, 
respectivamente. Luego, *basura* es el **número de la máquina**, que nos nos 
importa en este análisis. Podemos comprobar la carga exitosa imprimiendo los 
valores desde la matriz *P*.

```cpp
int main(void) {
  cargar("flowshop/br66");
  for (int j = 0; j < nT; j++) {
    for (int i = 0; i < mM; i++)
      cout << P[j][i] << " ";
    cout << "\n";
  }
}
```

Como resultado tenemos lo siguiente, donde confirmamos la correcta carga de los 
datos de cualquier instancia con el formato presentado.

```zsh
3 6 3 3 4 3
4 3 5 3 5 2
6 5 2 2 2 4
4 5 2 2 5 5
2 2 5 6 3 5
2 3 5 5 3 3

```

## La función `makespan`

## La función `prioridadNEH`

## Aceleración de `Taillard` (1990)

## Heurística constructiva NEH

## Heurística de Búsqueda local 

## Referencias
- [1] A. Benavides, "Programa inicial para FSSP con C++," presentado en el curso de Análisis y Diseño de Algoritmos, Universidad Católica San Pablo, Arequipa, Perú, 2022.

