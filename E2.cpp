#include <iostream>
#include <mpi.h>
#include <array>
#include <cstdlib>
#include <ctime>  

using namespace std;
int main(int argc, char** argv) {
    int rango;
    int size;
    int recv_data;
    srand(time(NULL)); // inicializa la semilla del generador aleatorio (solo una vez por ejecución)
    MPI_Init(&argc, &argv); //inicialización entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rango); //rango del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // número total de procesos

    //antes teniamos este codigo arriba, ahora como no sabemos aun el size lo tenemos que poner debajo de saber el size
    int send_data[size]; //buffer envío 
    for (int i = 0; i < size; i++) {
        send_data[i] = (rand() % 10)+1; // genera un número entre 0 y 10 y lo mete en la posicion x del array (inicializacion del array)
    }
    int result_data[size]; // buffer para recoger resultados en el proceso raíz

    if (size < 2) {
        if (rango == 0)
            cout << "Este programa requiere mas de 1 proceso.\n";
        MPI_Finalize();
        return 0;
    }
    
    //Mandamos los datos
    MPI_Scatter(&send_data, 1, MPI_INT, &recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    cout << "Proceso " << rango << " ha recibido el número " << recv_data << endl;
    recv_data += rango;
    //Recibimos Los Datos
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