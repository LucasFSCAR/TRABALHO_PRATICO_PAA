#include "caixeiroViajante.hpp"
#include "cidade.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <limits.h>
#include <float.h>
#include <bits/stdc++.h>
#include <algorithm>
#include <random>
#include <cstdlib>

using namespace std;
vector<string> resultPerm;
vector<double> fitness;

/* Metodos auxiliares
*/

//Metodo para criar todas permutacoes de tamanho n
void CaixeiroViajante::permutacao(int n, int k, int valores[], bool used[])
{
    int i;
    if (k == n)
    {
        string value = "";
        for (int i = 0; i < n; i++)
        {
            if (valores[i] < 10)
            {
                value = value + '0' + to_string(valores[i]);
            }
            else
            {
                value = value + to_string(valores[i]);
            }
        }
        resultPerm.push_back(value);
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            if (!used[i])
            {
                valores[k] = i + 1;
                used[i] = true;
                permutacao(n, k + 1, valores, used);
                used[i] = false;
            }
        }
    }
}

// calcula a distancia entre duas cidades
double CaixeiroViajante::calcularDistancia(Cidade a, Cidade b)
{
    int x1 = a.getCoordenadaX();
    int y1 = a.getCoordenadaY();
    int x2 = b.getCoordenadaX();
    int y2 = b.getCoordenadaY();

    double r1 = pow(x2 - x1, 2);
    double r2 = pow(y2 - y1, 2);

    double resultado = sqrt(r1 + r2);
    return resultado;
}

// limpa a lista de permutacoes
void CaixeiroViajante::limpar()
{
    resultPerm.clear();
    fitness.clear();
}

// combina dois inteiros em somente um
int CaixeiroViajante::concatenar(int x, int y)
{
    if (x == 0)
        return y;
    int pow = 10;
    while (y >= pow)
        pow *= 10;
    return x * pow + y;
}

// cast de char para int
int CaixeiroViajante::charParaInteiro(char c)
{
    return int(c) - 48;
}

// cast de dois char para inteiro
int CaixeiroViajante::doisCharParaInteiro(char a, char b)
{
    return concatenar(int(a) - 48, int(b) - 48);
}

std::vector<int> CaixeiroViajante::randomizar(std::vector<int> item, int num) {
    for (int i = 0; i < num; i++) {
        int indexA = rand() % item.size();
        int indexB = rand() % item.size();

        if (indexA == 0 || indexB == 0) {
            continue;
        }
        int temp = item[indexA];
        item[indexA] = item[indexB];
        item[indexB] = temp;
    }

    return item;
}

std::string CaixeiroViajante::vectorParaString(std::vector<int> vetor) {
    // [1,2,3,4]
    string resultado = "";
    for (int i = 0; i < vetor.size(); i++) {
        resultado = resultado + " " + to_string(vetor[i]); 
    }
    return resultado;
}

// ajusta e mostra a resposta na tela
void CaixeiroViajante::montaResposta(string caminho, double distancia)
{
    string resp = "";
    for (int i = 0; i < caminho.length() - 2; i += 2)
    {
        int item = doisCharParaInteiro(caminho.at(i), caminho.at(i + 1)) + 1;
        resp = resp + " " + to_string(item);
    }
    caminho = resp;

    cout << "Distancia: " << distancia << "\n";
    cout << "Reposta: " << caminho << "\n";
}

void CaixeiroViajante::normalizar() {
    double soma = 0.0;

    for (int i = 0; i < fitness.size(); i++) {
        soma += fitness[i];
    }

    for (int i = 0; i < fitness.size(); i++) {
        fitness[i] = fitness[i] / soma;
    }
}

int CaixeiroViajante::pegarUm() {
    srand(time(0));
    int index = 0;
    int r = rand() % fitness.size();
    cout << "aa: " << rand() << '\n';

    while (r > 0) {
        r = r - fitness[index];
        index++;
    }
    index--;
    return index;
}

std::vector<int> CaixeiroViajante::mutacao(std::vector<int> item) {
    bool valido = false;
    int indexA = 0;
    int indexB = 0;
    while (!valido) {
        indexA = rand() % item.size();
        indexB = rand() % item.size();
        if (indexA != 0 && indexB != 0 && indexA != item.size()-1 && indexB != item.size()-1) {
            valido = true;
        }
    }
    int temp = item[indexA];
    item[indexA] = item[indexB];
    item[indexB] = temp;
    return item;
}

/* Metodos principais
*/
// Construtor
CaixeiroViajante::CaixeiroViajante(std::vector<Cidade> _cidades)
{
    cidades = _cidades;
}

// Metodo do caixeiro viajante usando forca bruta
void CaixeiroViajante::caixeiroViajanteForcaBruta()
{
    double distanciaMinima = DBL_MAX;
    string resposta = "";
    int canPrint = 0;

    int n = cidades.size();
    int valores[n];
    bool used[100];
    vector<string> result;

    for (int i = 0; i < n - 1; i++)
    {
        valores[i] = i + 1;
    }

    permutacao(n - 1, 0, valores, used);

    for (int i = 0; i < resultPerm.size(); i++)
    {
        resultPerm[i] = "00" + resultPerm[i] + "00";

        double somaDistancia = 0.0;
        for (int j = 0; j < resultPerm[i].length() - 3; j += 2)
        {
            int cidadeA = doisCharParaInteiro(resultPerm[i].at(j), resultPerm[i].at(j + 1));
            int cidadeB = doisCharParaInteiro(resultPerm[i].at(j + 2), resultPerm[i].at(j + 3));

            somaDistancia = somaDistancia + calcularDistancia(cidades[cidadeA], cidades[cidadeB]);
        }

        if (somaDistancia < distanciaMinima)
        {
            distanciaMinima = somaDistancia;
            resposta = resultPerm[i];
        }
    }

    montaResposta(resposta, distanciaMinima);
}

// Metodo do caixeiro viajante usando programacao dinamica
void CaixeiroViajante::caixeiroViajanteDinamico()
{
    limpar();
    double distanciaMinima = DBL_MAX;
    string resposta = "";

    int n = cidades.size();
    int valores[n];
    bool used[100];
    vector<string> result;
    double matriz[n][n];

    //inicializa a matriz
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz[i][j] = 0;
        }
    }

    for (int i = 0; i < n - 1; i++)
    {
        valores[i] = i + 1;
    }

    permutacao(n - 1, 0, valores, used);

    for (int i = 0; i < resultPerm.size(); i++)
    {
        resultPerm[i] = "00" + resultPerm[i] + "00";
        double somaDistancia = 0.0;
        for (int j = 0; j < resultPerm[i].length() - 3; j += 2)
        {
            int cidadeA = doisCharParaInteiro(resultPerm[i].at(j), resultPerm[i].at(j + 1));
            int cidadeB = doisCharParaInteiro(resultPerm[i].at(j + 2), resultPerm[i].at(j + 3));

            double distancia = 0;

            if (matriz[cidadeA][cidadeB] != 0)
            {
                distancia = matriz[cidadeA][cidadeB];
            }
            else
            {
                distancia = calcularDistancia(cidades[cidadeA], cidades[cidadeB]);
                matriz[cidadeA][cidadeB] = distancia;
            }

            somaDistancia = somaDistancia + distancia;
        }

        if (somaDistancia < distanciaMinima)
        {
            distanciaMinima = somaDistancia;
            resposta = resultPerm[i];
        }
    }

    montaResposta(resposta, distanciaMinima);
}

// Metodo do caixeiro viajante usando branch and bound
void CaixeiroViajante::caixeiroViajanteBranchAndBound()
{
    limpar();
    double distanciaMinima = DBL_MAX;
    string resposta = "";

    int n = cidades.size();
    int valores[n];
    bool used[100];
    vector<string> result;

    for (int i = 0; i < n - 1; i++)
    {
        valores[i] = i + 1;
    }

    permutacao(n - 1, 0, valores, used);

    for (int i = 0; i < resultPerm.size(); i++)
    {
        resultPerm[i] = "00" + resultPerm[i] + "00";
        double somaDistancia = 0.0;
        for (int j = 0; j < resultPerm[i].length() - 3; j += 2)
        {
            int cidadeA = doisCharParaInteiro(resultPerm[i].at(j), resultPerm[i].at(j + 1));
            int cidadeB = doisCharParaInteiro(resultPerm[i].at(j + 2), resultPerm[i].at(j + 3));

            if (somaDistancia > distanciaMinima)
            {
                j = resultPerm[i].length();
            }

            somaDistancia = somaDistancia + calcularDistancia(cidades[cidadeA], cidades[cidadeB]);
        }

        if (somaDistancia < distanciaMinima)
        {
            distanciaMinima = somaDistancia;
            resposta = resultPerm[i];
        }
    }

    montaResposta(resposta, distanciaMinima);
}

// Metodo do caixeiro viajante usando algoritmo genetico
void CaixeiroViajante::caixeiroViajanteGenetico()
{
    // limpar();
    const int tamanhoPopulacao = 10;
    const int qtdRandomizacoes = 10;
    const int geracoes = 1;
    double distanciaMinima = DBL_MAX;
    string resposta = "";
    vector<vector<int>> populacao;
    vector<int> ordem, original;

    for ( int i = 0; i < cidades.size(); i++ ) {
        original.push_back(i);
        ordem.push_back(i);
    }

    int posicaoMutada = -1;
    for (int gen = 0; gen < geracoes; gen++) {
        // Criar uma população de caminhos aleatorios
        for ( int i = 0; i < tamanhoPopulacao; i++ ) {
            //if (i != posicaoMutada) {
                populacao[i] = (randomizar(ordem, qtdRandomizacoes));
            
        }


    // populacao = 
    // [
    //   [1,2,3],
    //   [3,2,1],
    //   [2,1,3]
    // ]



        for ( int i = 0; i < populacao.size(); i++ ) { // [0,1,2,0]
            populacao[i].push_back(0);
            double somaDistancia = 0.0;
            for (int j = 0; j < populacao[i].size() - 1; j++)
            {
                Cidade cidadeA = cidades[populacao[i][j]];
                Cidade cidadeB = cidades[populacao[i][j+1]];

                somaDistancia = somaDistancia + calcularDistancia(cidadeA, cidadeB);
            }
            if (somaDistancia < distanciaMinima) {
                distanciaMinima = somaDistancia;
                resposta = vectorParaString(populacao[i]);
            }
            
            // Calcular fitness
            fitness.push_back( 1 / (somaDistancia+1));
    
        }
        // Normalizar
        normalizar();
        posicaoMutada = pegarUm();

 // Mutação com o melhor resultado
        for ( int i = 0; i < populacao.size(); i++ ) {
            for ( int j = 0; j < populacao[i].size(); j++ ) {
                cout << populacao[i][j] << " ";
            }
            cout << '\n';
        }



        populacao[posicaoMutada] = mutacao(populacao[posicaoMutada]);
    }



   
    // Gerar proxima geração

    // cout << "resp: " << resposta;










    // for ( int i = 0; i < fitness.size(); i++ ) {
    //    cout << fitness[i] << "\n";
    // }
        cout << "\n\n\n";

    for ( int i = 0; i < populacao.size(); i++ ) {
        for ( int j = 0; j < populacao[i].size(); j++ ) {
            cout << populacao[i][j] << " ";
        }
        cout << '\n';
    }





}