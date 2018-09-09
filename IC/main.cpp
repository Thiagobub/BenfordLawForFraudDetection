#include <iostream>
#include <math.h>

#define N_MAX 5

using namespace std;



int main()
{
    int n = 1;      /// n-ésima Posição do Dígito
    int d = 1;      /// Dígito
    int k = 0;      /// Iterador para o somatório
    double soma[N_MAX + 1][10]; ///Resultado

    /// Zerando a Matriz de Soma
    for(n = 0; n <= N_MAX; n++)
    {
        for(d = 0; d <= 9; d++)
        {
            soma[n][d] = 0;
        }
    }

    /// Calculando as Probabilidades de que cada um dos dígitos
    /// ocupe cada uma das quatro primeiras posições
    for(n = 1; n <= N_MAX; n++)
    {
        for(d = 0; d <= 9; d++)
        {
            for(k = pow(10, n - 2); k <= (pow(10, n - 1) - 1); k++)
            {
                soma[n][d] += log10(1 + 1.0/(10.0*k + d));
            }
        }
    }

    printf("  "); //Apenas ppara deixar mais organizado a tabela seguinte
    /// Imprimindo a Tabela com os Resultados
    for(n = 1; n <= N_MAX; n++)
    {
        for(d = 0; d <= 9; d++)
        {
            printf("  %.2f", soma[n][d]*100);
        }
        printf("\n");
    }
}
