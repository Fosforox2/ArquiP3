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
