# Introducción: Investigación operativa

**Scheduling** (programación de tareas). Consiste en asignar recursos a actividades en el tiempo. Matemáticamente estos problemas están calificados como los más difíciles.

## Flow Shop Scheduling Problem (FSSP)

Es un problema de líneas de producción. Los trabajos \(J_i\) deben ser procesados en 
las máquinas \(M_i\) con tiempos fijos \(p_{ji}\), y son independientes para cada 
trabajo. Además, asumimos que los tiempos de trabajo ya han sido optimizados.

![Instancia a analizar](./.github/fssp_impossible/1733238439.png)
*Figura 1. Instancia a analizar*

Rápidamente, sin analizar el tiempo que puede demorar encontrar la solución óptima, 
podemos pensar en diseñar un algoritmo de fuerza bruta. Es sencillo para nosotros 
pero imposible para la máquina.

![Algoritmo de fuerza bruta](./.github/fssp_impossible/1733239898.png)
*Figura 2. Algoritmo de fuerza bruta*

### ¿Qué es una Heurística?

Procedimiento simple diseñado de manera inteligente para crear una solución o para 
buscar mejores soluciones que satisfagan cierto problema de optimización.

- Idea, criterio, método o regla que ayuda a decidir cuál alternativa es mejor.
- Idea basada en la intuición o en el sentido común.
- Idea que utiliza la estructura o contexto del problema.

La primera heurística en la historia fue nombrada *Método Monte Carlo* y se basaba 
en escoger una muestra del total y observar cuántos cumplen con el propósito.

#### Búsqueda aleatoria para el FSSP

Selecciona una muestra aleatoria extraída del espacio de soluciones para encontrar 
un resultado numérico (media esperada, mejor, peor).

![Búsqueda aleatoria](./.github/fssp_impossible/1733241212.png)
*Figura 3. Búsqueda aleatoria*

Este enfoque es muy general y puede ayudar a resolver otros tipos de problemas. Sin 
embargo, no es el mejor para resolver el problema propuesto:

- La muestra puede ser demasiado pequeña y no representativa.
- La media de la muestra \( \approx \) la media de la población.
- El mejor de la muestra no es el mejor de la población.

---

# Métodos heurísticos básicos

## Heurísticas constructivas

Construyen una solución desde cero, añadiendo uno a uno los componentes a la solución 
parcial, hasta que la solución esté completa. La pregunta importante para diseñar 
esta heurística es:

> **¿Cuál elemento debería añadir y cómo?**

### Heurística constructiva de Nawaz, Enscore y Ham (NEH)

Propuesta en 1983 para resolver el FSSP y se divide en dos partes importantes

#### Primera etapa: ¿Cuál es el elemento que debo insertar?

Determina un orden de inserción. En este caso, se ordena del más grande al más 
pequeño según su tiempo total de procesamiento.  
\[
\pi_0 = (J_4, J_5, J_1, J_2, J_3, J_6)
\]

#### Segunda etapa: ¿Cómo o dónde lo debo de insertar?

Insertar estos trabajos, uno a uno, en la mejor posición, comenzando con:  
\[
\pi = (J_4)
\]

![Heurística NEH](./.github/fssp_impossible/1733245449.png)
*Figura 4. Heurística NEH*

- Si ocurren empates al realizar la segunda etapa, se puede utilizar una técnica para solucionarlo. Por el momento, tomaremos el orden del primer resultado.
- La calidad de la solución se mide con el desvío relativo:
\[
DR = \frac{C_{\text{max}}(\pi) - C_{\text{max}}(\pi^*)}{C_{\text{max}}(\pi^*)}
\]
