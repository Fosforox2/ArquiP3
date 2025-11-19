#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv) {
    int rango, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rango);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int valor_secreto;

    if (rango == 0) {
        valor_secreto = 11; //valor secreto del proceso 0
    }

    //enviamos el valor secreto al resto de procesos
    MPI_Bcast(&valor_secreto, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //cada proceso calcula su nuevo valor
    int valor_actualizado = valor_secreto + rango;

    //proceso 0 debe recibir resultados y detectar min y max DURANTE la recepción
    int minimo, maximo;

    if (rango == 0) {

    minimo = valor_actualizado;  
    maximo = valor_actualizado;

    int recibidos = 1; //ya contamos el valor de proceso 0

    //recibir valores desde cualquier proceso
    while (recibidos < size) {

        int valor;
        MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (valor < minimo) minimo = valor;
        if (valor > maximo) maximo = valor;

        recibidos++;
    }

    cout << "Valor mínimo = " << minimo << endl;
    cout << "Valor máximo = " << maximo << endl;
}
else {
        //el resto de procesos envían su valor actualizado al proceso 0
        MPI_Send(&valor_actualizado, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
