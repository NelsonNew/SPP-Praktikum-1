#include <stdio.h>
#include <omp.h>

int main ( int argc, char *argv[] )
{

    printf("%d\n", omp_get_max_threads());
    omp_set_num_threads(3);

    #pragma omp parallel
    {
        printf("Hello %d\n", omp_get_thread_num());
    }

}