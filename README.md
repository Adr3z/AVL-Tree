[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/W5WIE0kO)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-7f7980b617ed060a017424585567c406b6ee15c891e84e1186181d67ecf80aa0.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=13030997)
# Tarea 10: Árboles Balanceados AVL
## Estructuras de Datos II
## Fecha de publicación: Martes 21 de noviembre de 2023
## Fecha de entrega: Martes 28 de noviembre de 2023

## Descripción del problema
Un árbol binario es una estructura de datos
jerárquica autoreferenciada, donde cada elemento de la
estructura denominado *nodo* contiene un valor único
y un par de referencias a otros dos *nodos* denominados hijos.
Existe un nodo especial llamado *raiz* al cual ningún otro nodo
hace referencia, y los *nodos* que no tienen referencias
hacia ningún otro se denominan *hojas*.

Un árbol binario de búsqueda mantiene la propiedad de que
para cualquier nodo $X$, el conjunto de valores {$I$}
de los nodos del subárbol izquierdo son menores que $X$,
y el conjunto de valores {$D$} de los nodos del
subárbol derecho son mayores que $X$, de tal forma que
{$I$} $\lt X \lt$ {$D$}. Los valores $X$ en el árbol binario
de búsqueda no se pueden repetir.

La altura de un nodo en un árbol binario se define
como la máxima cantidad de aristas que existen en algún
camino que va desde el nodo en cuestión hasta alguna
de sus hojas.
De esta manera, la altura de una hoja es $0$ y
la altura $h$ de un nodo $n$ se define como
$h(n)=1+max(h(n\rightarrow izq), h(n\rightarrow der))$,
por definición la altura de un nodo nulo es $-1$.

Un árbol binario de búsqueda balanceado **AVL**
tiene la propiedad de que para cualquiera de sus nodos
existe una diferencia máxima de $1$ entre la altura de su
subárbol izquierdo con respecto a la altura de su subárbol derecho.
Para poder expresar esto de manera más concreta, se define el
factor de equilibrio $fe$ de un nodo $n$ como
$fe(n)=h(n\rightarrow der)-h(n\rightarrow izq)$.

Escribir un programa para realizar las operaciones de inserción y
eliminación de números enteros en un árbol AVL, además de poder
consultar la altura del arbol e imprimir su contenido por niveles.

## Entrada
La primer línea de entrada contiene un entero $N$ ($1 \leq N \leq 10^5$),
la cantidad de operaciones a realizar.
Cada una de las siguientes $N$ líneas definen una operación a realizar
sobre un árbol inicialmente vacío.
La operación de inserción se identifica por la letra `I` seguida de un
entero $X$ ($-10^9 \leq X \leq 10^9$) que será agregado al árbol.
La operación de eliminación se representa por medio de la letra `E`
seguida de un entero $X$ ($-10^9 \leq X \leq 10^9$) a eliminar.

La letra `A` imprime la altura del árbol, y la letra `P` imprime
el contenido del árbol por niveles de arriba hacia abajo y de izquierda
a derecha, todo en una misma línea. Si el árbol está vacío entonces
imprime una línea vacía.

## Salida
Imprimir una línea por cada operación `A` o `P` de acuerdo con lo descrito
en el párrafo anterior.

## Ejemplo de entrada
```
13
I 20
I 15
I 5
A
P
I 40
I 50
I 18
A
P
E 20
E 40
P
```

## Ejemplo de salida
```
1
15 5 20
2
20 15 40 5 18 50
15 5 50 18
```

## Ejecución
Para ejecutar este programa desde Codespaces solamente es necesario
escribir desde terminal el comando:
```console
$ make
```

# EVALUACION
* El 50% de la calificación de esta tarea estará determinada 
por la evaluación que obtenga en el juez de omegaUp.
* Para poder evaluarlo es necesario que se registre en omegaUp y 
agregue su nombre de usuario en los comentarios del archivo `main.c`.
* **En omegaUp solamente se envía el contenido del archivo `main.c`, por lo
cual es necesario colocar todo el código en un mismo archivo.**
* Se deben dejar en **comentarios** las líneas `#define DEBUG` y `freopen()` antes de evaluarlo en omegaUp.
* El juez donde se debe evaluar la solución es https://omegaup.com/arena/problem/Arboles-Balanceados-AVL/

# IMPORTANTE
* Realizar `commit` y `push` continuos para un desarrollo incremental.
* Consultar el ejemplo de prueba en el archivo `input.txt` y la salida esperada en `expected_output.txt`.


