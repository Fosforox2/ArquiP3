#include <iostream>
#include <mpi.h>

using namespace std;
int main(int argc, char** argv) {
    int rango;
    int size;
    MPI_Init(&argc, &argv); //inicialización entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rango); //rango del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // número total de procesos

    if (size < 1) {
        if (rango == 0)
            cout << "Este programa requiere almenos 1 proceso.\n";
        MPI_Finalize();
        return 0;
    }
    int DatosProceso[3];
    DatosProceso[0] = rango - 2;
    DatosProceso[1] = rango - 4;
    DatosProceso[2] = rango - 6;
    for(int i = 1; i < 4;i++){
        DatosProceso[i-1] = rango - (i*2);
    }

    // Mostramos lo que genera cada proceso
    cout << "Proceso " << rango << " generó: ";
    for (int i = 0; i < 3; i++) {
        cout << DatosProceso[i] << " ";
    }    
    cout << endl;

    // Reducimos (sumamos elemento a elemento) todos los arrays
    int sumaGlobal[3];
    MPI_Reduce(DatosProceso, sumaGlobal, 3, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // El proceso 0 muestra la suma final
    if (rango == 0) {
        cout << "\nSuma total por posición:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "Elemento " << i << ": " << sumaGlobal[i] << endl;
        }
    }

    MPI_Finalize();
    return 0;
}