#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdbool.h>

#define N 300
#define M 400
#define P 500

//Konsolenausgabe der Matrizen ein- oder ausschalten
#define AUSGABE false

int main(int argc, char *argv[]);
void fillMatrices(int n, int m, int p, double b[][P], double c[][N]);
void multiplyMatricesSequential(int n, int m, int p, double result[][N], double first[][P], double second[][N]);
void multiplyMatricesParallel(int n, int m, int p, double result[][N], double first[][P], double second[][N]);
void printB (double matrix[][P], int n, int m);
void printC (double matrix[][N], int n, int m);
void printResult (double matrix[][N], int n, int m);

/******************************************************************************/

int main(int argc, char *argv[]) 
{
    //Zeitmessung:
    double wtime;

    //Dimensionen:
    int n = N;
    int m = M;
    int p = P;

    //Matrizen:
    double a[M][N];
    double b[M][P];
    double c[P][N];
    
    //Matrizen mit Pseudo-Zufallszahlen füllen
    fillMatrices(n, m, p, b, c);

    printf("\n\n");

    if(AUSGABE)
    {
        printf("Matrix B: \n");
        printB(b, m, p);
    }
    
    if(AUSGABE)
    {
        printf("Matrix C: \n");
        printC(c, p, n);
    }
    
    
/*
    Test sequential
*/


    wtime = omp_get_wtime();
    multiplyMatricesSequential(n, m, p, a, b, c);
    wtime = omp_get_wtime() - wtime;
    printf ( "  Sequential time: %lf\n", wtime );

    //Sequentielles Ergebnis ausgeben
    if(AUSGABE)
    {
        printf("  Sequential Result:\n\n");
        printResult(a, m, n);
    }
    
/*
    Test parallel
*/
    wtime = omp_get_wtime();
    multiplyMatricesParallel(n, m, p, a, b, c);
    wtime = omp_get_wtime() - wtime;
    printf ( "  Parallel time: %lf\n", wtime );

    //Paralleles Ergebnis ausgeben
    if(AUSGABE)
    {
        printf("  Parallel Result:\n\n");
        printResult(a, m, n);
    }
    
    
    /*
     Terminate.
    */
    printf ( "\n" );
    printf ( "MATRIX_MULT\n" );
    printf ( "  Normal end of execution.\n" );


    return 0;
}

//Matrizen mit pseudo-zufälligen Werten füllen
void fillMatrices(int n, int m, int p, double b[][P], double c[][N])
{
    srand(4);

    int i;
    int j;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < p; j++)
        {
            b[i][j] = rand() % 100;
        }
    }
    
    for (i = 0; i < p; i++)
    {
        for (j = 0; j < n; j++)
        {
            c[i][j] = rand() % 100;
        }
        
    }


}

void printB (double matrix[][P], int n, int m)
{
    int i;
    int j;
    for ( i = 0; i < n; i++)
    {
        for( j = 0; j < m; j++) {
            printf("%lf   ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printC(double matrix[][N], int n, int m)
{
    int i;
    int j;
    for ( i = 0; i < n; i++)
    {
        for( j = 0; j < m; j++) {
            printf("%lf   ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printResult (double matrix[][N], int n, int m)
{
    int i;
    int j;
    for ( i = 0; i < n; i++)
    {
        for( j = 0; j < m; j++) {
            printf("%lf   ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void multiplyMatricesSequential(int n, int m, int p, double result[][N], double first[][P], double second[][N])
{
    int i;
    int j;
    int k;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            result[i][j] = 0;

            for (k = 0; k < p; k++)
            {
                result[i][j] += first[i][k] * second[k][j];
            }
        }
        
    }
    
}

void multiplyMatricesParallel(int n, int m, int p, double result[][N], double first[][P], double second[][N])
{
    int i;
    int j;
    int k;

    #pragma omp for collapse(2) schedule(dynamic, n)    // shared: n, m, k, p, first, second, result
    for (i = 0; i < m; i++)                             // private: i, j
    {
        for (j = 0; j < n; j++)
        {
            result[i][j] = 0;
        }
        
    }
    
    #pragma omp for collapse(3) schedule(dynamic, p)    // shared: m, n, p, first, second, result
    for (i = 0; i < m; i++)                             // private: i, j, k
    {
        for (j = 0; j < n; j++)
        {

            for (k = 0; k < p; k++)
            {
                result[i][j] += first[i][k] * second[k][j];
            }
        }
        
    }
}