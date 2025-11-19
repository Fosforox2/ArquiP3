#include <iostream>
#include <mpi.h>
#include <array>

using namespace std;
int main(int argc, char** argv) {
    int rango;
    int size;
    int recv_data; //buffer recepción
    int send_data[5] = {0, 1, 2, 3, 4}; //buffer envío  
    int result_data[5]; // buffer para recoger resultados en el proceso raíz
    MPI_Init(&argc, &argv); //inicialización entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rango); //rango del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // número total de procesos

    if (size != 5) {
        if (rango == 0)
            cout << "Este programa requiere exactamente 5 procesos.\n";
        MPI_Finalize();
        return 0;
    }
    //mandamos los datos
    MPI_Scatter(&send_data, 1, MPI_INT, &recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    cout << "Proceso " << rango << " ha recibido el número " << recv_data << endl;
    recv_data += rango;
    //recibimos Los Datos
    MPI_Gather(&recv_data, 1, MPI_INT, result_data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rango == 0) {
        cout << "\nResultados recibidos de cada proceso:" << endl;
        for (int i = 0; i < size; i++) {
            cout << "Proceso " << i << " envió el valor " << result_data[i] << endl;
        }
    }
    MPI_Finalize(); //fin entorno MPI
    return 0;
}