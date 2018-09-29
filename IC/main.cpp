#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>

/// Alterar Aqui o Caminho para o Arquivo com os Dados
#define DATA_PATH "Exemplo.txt"

using namespace std;

void tabelaDistribuicaoBenford(int n_max)
{
    int n = 1;      // n-ésima Posição do Dígito
    int d = 1;      // Dígito
    int k = 0;      // Iterador para o somatório
    double soma[n_max + 1][10]; //Resultado

/** Zerando a Matriz de Soma **/
    for(n = 0; n <= n_max; n++)
    {
        for(d = 0; d <= 9; d++)
        {
            soma[n][d] = 0;
        }
    }

/** Calculando as Probabilidades de que cada um dos dígitos
    ocupe cada uma das quatro primeiras posições            **/
    for(n = 1; n <= n_max; n++)
    {
        for(d = 0; d <= 9; d++)
        {
            for(k = pow(10, n - 2); k <= (pow(10, n - 1) - 1); k++)
            {
                soma[n][d] += log10(1 + 1.0/(10.0*k + d));
            }
        }
    }

    printf("\nImprimindo a Tabela de Probabilidade de Benford!\n");
    for(n = 1; n <= n_max; n++)
    {
        printf("\n%da Posicao\n", n);
        printf("Di = Prob\n");
        for(d = 0; d <= 9; d++)
        {
            printf("%d  = %.3f\n", d, soma[n][d]*100);
        }
        printf("\n");
    }
}

int main()
{
/** Processamento dos Dados dos Arquivos:
    Os dados devem estar armazenados em um arquivo com extensão .txt

    Os valores devem estar com a seguinte formatação dentro do arquivo:
    2678.25
    1613
    7384.50
    5868.00
    ...                                                             **/

    double* dados = NULL;
    ifstream Arquivo;
    string line;
    int n = 0, i, j;

    //Abrindo o arquivo, DATA_PATH pode ser alterado no cabeçalho do programa
    Arquivo.open(DATA_PATH);
	if (Arquivo.fail())
	{
		cerr << "Cannot open file";
	}
	else
    {
        // Quantidade de Dados
        while(!Arquivo.eof())
        {
            getline(Arquivo, line);
            n++;
        }
        // Reposicionando o iterador do arquivo no começo
        Arquivo.clear();
        Arquivo.seekg(0);
        // Armazenagem dos dados
        dados = new double[n];
        for(i = 0; !Arquivo.eof(); i++)
        {
            Arquivo >> dados[i];
        }
    }


/** Calculo da Frequencia e Probabilidade de Cada Digito **/
    int freq[10];
    int total = 0;

    // Zerando o vetor de probabilidades
    for(i = 0; i <= 9; i++)
        freq[i] = 0;

    // Calculando a Frequencia
    for(i = 0; i < n; i++)
    {
        j = dados[i];
        while((j/10) != 0)
        {
            j = j/10;
        }

        freq[j]++;
    }

    // Calculando o Total das Frequências
    for(i = 0; i <= 9; i++)
    {
        total += freq[i];
    }

    // Imprimindo a Frequencia de Cada 1ª Dígito
    printf("Di = Freq\n");
    for(j = 0; j <= 9; j++)
    {
        printf("%d  = %d\n", j, freq[j]);
    }
    printf("Total = %d\n", total);


/** Calculando as Probabilidades de Cada Dígito **/
    double prob[10];

    // Zerando o vetor de probabilidades
    for(i = 0; i <= 9; i++)
    {
        prob[i] = 0;
    }

    // Calculando as Probabilidades
    for(i = 0; i <= 9; i++)
    {
        prob[i] = (double)freq[i] / (double)total;
    }

    printf("\nDi = Prob\n");
    for(i = 0; i <= 9; i++)
        printf("%d  = %.3f\n", i, prob[i]*100);


/** Imprimindo a Tabela de Benford Para as Probabilidades **/
    // Escolhendo Até Qual Posição Mostrar
    int pos_max = 1;

    // Imprimindo a Tabela
    tabelaDistribuicaoBenford(pos_max);


/** Deletar as variaveis alocadas dinamicamente **/
    delete [] dados;

    return 0;
}
