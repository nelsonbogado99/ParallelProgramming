#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define dimensionMax 100

int dimension;
int matrizA[dimensionMax][dimensionMax];
int matrizB[dimensionMax][dimensionMax];
int matrizResul[dimensionMax][dimensionMax];


void multiplicarMatrices() 
{
    double tiempoInic = omp_get_wtime();
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < dimension; i++) 
    {
        for (int j = 0; j < dimension; j++) 
        {
            matrizResul[i][j] = 0;
            for (int k = 0; k < dimension; k++) 
            {
                matrizResul[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
    
    double tiempoFin = omp_get_wtime();
    double tiempo = tiempoFin - tiempoInic;
    printf("\nEl tiempo de ejecucion de la seccion Paralelo: %lf segundos\n\n",  tiempo);
    printf("Resultado de la multiplicacion de Matriz A X Matriz B: \n");
    
}

void cargarMatriz(int matriz[][dimensionMax], int modo) 
{
    if (modo == 1) 
    {
        printf("Generando elementos de forma manual para la matriz:\n");
       
    } else {
        printf("Generando elementos de forma aleatoria para la matriz:\n");
    }

    for (int i = 0; i < dimension; i++) 
    {
        for (int j = 0; j < dimension; j++) 
        {
            if (modo == 1) 
            {
                scanf("%d", &matriz[i][j]); 
            } else {
                matriz[i][j] = 1 + rand() % 20;
            }
        }
    }
}

void mostrarMatriz(int matriz[][dimensionMax]) 
{
    for (int i = 0; i < dimension; i++) 
    {
        for (int j = 0; j < dimension; j++) 
        {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

void cargarMatrices()
{
    int modo;
    system("cls");
    printf("1.- Cargar Matriz de Forma Manual (A y B)\n");
    printf("2.- Cargar Matriz de Forma Aleatoria (A y B)\n");
    scanf("%d", &modo);

    if (modo == 1 || modo == 2) 
    {
        cargarMatriz(matrizA, modo);
        printf("\n Matriz A: \n");
        mostrarMatriz(matrizA);
        cargarMatriz(matrizB, modo);
        printf("\n Matriz B: \n");
        mostrarMatriz(matrizB);
    } else 
    {
        printf("Opcion incorrecta, vuelva a seleccionar...\n");
        cargarMatrices();
    }
}

void solicitarDimension() 
{
    printf("Ingrese la dimension de las matrices cuadradas (n x n)...\n");
    scanf("%d", &dimension);
}

int main() 
{
    srand(time(NULL));
    solicitarDimension();
    cargarMatrices();
    multiplicarMatrices();
    mostrarMatriz(matrizResul);
    return 0;
}
