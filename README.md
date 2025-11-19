# Practica 3 Arquitectura de Computadores
   
## Ejercicio 1

En este ejercicio trabajo con el reparto de datos entre procesos usando MPI.
El programa necesita ejecutarse con exactamente 5 procesos, porque cada uno recibirá un número distinto del array {0, 1, 2, 3, 4}.

Primero preparo ese array en el proceso 0 y lo envío a los demás usando MPI_Scatter, de forma que cada proceso recibe un único valor.
Cuando cada proceso recibe su número, le suma su propio rango (el identificador que MPI les asigna: 0, 1, 2, 3 y 4).

Después, todos esos resultados se devuelven al proceso 0 mediante MPI_Gather.
Una vez recibidos, el proceso 0 muestra por pantalla qué valor ha enviado cada proceso tras hacer la suma.

### Resultados:
mpirun -np 5 ./Exe1

Proceso 0 ha recibido el número 0

Resultados recibidos de cada proceso:
Proceso 0 envió el valor 0                                                                                           
Proceso 1 ha recibido el número 1                                                                                           
Proceso 2 ha recibido el número 2                                                                                           
Proceso 3 ha recibido el número 3                                                                                           
Proceso 4 ha recibido el número 4                                                                                           
                                                                                                                                                                                      
Proceso 1 envió el valor 2                                                                                           
Proceso 2 envió el valor 4                                                                                           
Proceso 3 envió el valor 6                                                                                           
Proceso 4 envió el valor 8                                                                                           



## Ejercicio 2

En este ejercicio hago algo parecido al anterior, pero con una diferencia importante: en lugar de enviar un array fijo, genero los valores de forma aleatoria.
Como no conozco el número de procesos hasta que MPI comienza, creo el array después de obtener el size, que es lo que indica cuántos procesos hay funcionando.

Cada posición del array se rellena con un número aleatorio entre 1 y 10. Luego, igual que en el ejercicio anterior, reparto esos valores entre los procesos usando MPI_Scatter, de forma que cada proceso recibe un único número.

Una vez recibido, cada proceso le suma su rango (su identificador).
Después, todos los procesos devuelven su resultado al proceso 0 con MPI_Gather, y ese proceso los muestra todos por pantalla.

Resultados:
mpirun -np 7 ./Exe2

Proceso 0 ha recibido el número 4
Proceso 1 ha recibido el número 2
Proceso 2 ha recibido el número 1
Proceso 3 ha recibido el número 9
Proceso 4 ha recibido el número 9
Proceso 5 ha recibido el número 4
Proceso 6 ha recibido el número 11

Resultados recibidos de cada proceso:
Proceso 0 envió el valor 4
Proceso 1 envió el valor 3
Proceso 2 envió el valor 3
Proceso 3 envió el valor 12
Proceso 4 envió el valor 13
Proceso 5 envió el valor 9
Proceso 6 envió el valor 17

## Ejercicio 3

MPI_Reduce sirve para combinar datos que provienen de todos los procesos.
Cada proceso genera un pequeño array de 3 elementos. Esos valores dependen del rango, restando 2, 4 y 6 respectivamente.
El resultado es que cada proceso crea un array distinto según su identificador.

Antes de hacer la reducción, muestro por pantalla qué valores ha generado cada proceso para poder ver qué está aportando cada uno.

Después uso MPI_Reduce para sumar todos estos arrays posición por posición.
Es decir, todos los elementos en la posición 0 se suman entre sí, lo mismo con la posición 1 y la posición 2.
El resultado solo lo recibe el proceso 0, así que es ese proceso el que se encarga de imprimir el resultado final con las sumas acumuladas.

Resultados:
mpirun -np 4 ./Exe3

Proceso 0 generó: -2 -4 -6 
Proceso 1 generó: -1 -3 -5 
Proceso 2 generó: 0 -2 -4 
Proceso 3 generó: 1 -1 -3 

Suma total por posición:
Elemento 0: -2
Elemento 1: -10
Elemento 2: -18


## Ejercicio 4

El proceso 0 tiene un valor que el resto no conoce. Ese valor lo envío a todos usando MPI_Bcast, que permite que un mismo dato llegue a todos los procesos al mismo tiempo.

Una vez recibido, cada proceso le suma su rango para generar su propio valor actualizado.
La parte interesante está en cómo el proceso 0 recoge esos valores: en lugar de esperar a tenerlos todos y procesarlos después, voy comparando cada valor según va llegando para encontrar el mínimo y el máximo directamente durante la recepción.

Como el proceso 0 también calcula su propio valor actualizado, lo uso para iniciar las variables de mínimo y máximo. Después voy recibiendo los valores de los demás procesos usando MPI_Recv con MPI_ANY_SOURCE, que me permite aceptar los mensajes en cualquier orden. Cada vez que recibo uno, comparo y actualizo el mínimo y el máximo si hace falta.

Cuando ya he recibido todos los valores, muestro cuál ha sido el menor y cuál el mayor.

Resultados: (numero del proceso 0 = 11)
mpirun -np 6 ./Exe4
Valor mínimo = 11
Valor máximo = 16
