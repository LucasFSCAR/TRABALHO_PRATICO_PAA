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

using namespace std;
vector<string> resultPerm;

/* Metodos auxiliares
*/

// Metodo para criar todas permutacoes de tamanho n
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

/* Método para calcular a distancia entre duas cidades
@param1 Cidade A
@param2 Cidade B
@return resultado da distancia entre as duas cidades
*/

double CaixeiroViajante::calcularDistancia(Cidade a, Cidade b)
{   
    // Pegando as coordenadas das cidades
    int x1 = a.getCoordenadaX();
    int y1 = a.getCoordenadaY();
    int x2 = b.getCoordenadaX();
    int y2 = b.getCoordenadaY();

    // Calculo de pitágoras
    double r1 = pow(x2 - x1, 2);
    double r2 = pow(y2 - y1, 2);

    // Resultado = raiz de r1² + r2²
    double resultado = sqrt(r1 + r2);

    return resultado;
}

// Limpa a lista de permutacoes
void CaixeiroViajante::limpar()
{
    resultPerm.clear();
}

/* combina dois inteiros em somente um
@param1 x inteiro
@param2 y inteiro
@return int dos 2 numeros concatenados. Ex: concatenar(2, 1) = 21
*/
int CaixeiroViajante::concatenar(int x, int y)
{
    // Se x == 0, nao tem o que concatenar
    if (x == 0)
        return y;
    
    int pow = 10;

    // Multiplicando por 10 ate a quantidade de algarismos de x ter mesmo numero da resultante da 
    // concatenação
    // Ex: concatenar(3, 37), o pow tem que ser igual a 100, para que x(3) * 100 seja = 300
    // para depois somente somar com y, resultando 337
    while (y >= pow)
        pow *= 10;
    
    // Multiplicamos x por pow para ficar com a quantidade de algarismos certa e somamos com y
    return x * pow + y;
}

// Metodo que faz a conversao de char para int, tomando como base a tabela ascii
// @param char c para conversao para inteiro
// @return inteiro referente a esse char
int CaixeiroViajante::charParaInteiro(char c)
{
    return int(c) - 48;
}

// Sobrecarga do metodo charParaInteiro para o caso de 2 char's
// @param1 char a para conversao para inteiro
// @param2 char b para conversao para inteiro
// @return inteiro referente aos 2 char's concatenados
int CaixeiroViajante::charParaInteiro(char a, char b)
{
    return concatenar(int(a) - 48, int(b) - 48);
}

/* Metodo que printa no terminal a saida(resposta)
@param1 string caminho com todas cidades
@param2 double distancia entre as cidades
*/
void CaixeiroViajante::montaResposta(string caminho, double distancia)
{
    string resp = "";
    int item;

    // Para cada cidade da string de caminho(pulando de 2 em 2)
    for (int i = 0; i < caminho.length() - 2; i += 2)
    {
        // Pegamos a cidade e concatenamos com a anterior
        item = charParaInteiro(caminho.at(i), caminho.at(i + 1)) + 1;
        resp = resp + " " + to_string(item);
    }

    caminho = resp;

    // Prints da distancia e resposta(caminho)
    cout << "Distancia: " << distancia << "\n";
    cout << "Reposta: " << caminho << "\n";
}

/* Metodo que verifica se um certo elemento existe dentro de um array de inteiros
@param1 int elemento a verificar
@param2 vector<int> array
@return bool true ou false se o elemento existe ou nao
*/
bool CaixeiroViajante::elementoExiste(int elemento, vector<int> array) {
    for (int x = 0; x < array.size(); x++) {
        if (array[x] == elemento) {
            return true;
        }
    }

    return false;
}

/* Metodo que randomiza um vetor, colocando os elementos em ordem aleatoria
@param1 vector<int> array
@return vector<int> array randomizado
*/
vector<int> CaixeiroViajante::randomizarVetor(vector<int> array) {
    // Inicializando variaveis e setando seed do randomizador
    int aleatorio;
    vector<int> gerados;
    vector<int> retorno;
    srand(time(NULL));
    
    // Para cada posicao do array
    for (int x = 0; x < array.size(); x++) {
        aleatorio = rand() % array.size();
        
        // Gero um numero aleatorio (entre 0 e size do array -1) e verifico se ele 
        // ja foi sorteado alguma vez
        while (elementoExiste(aleatorio, gerados)) {
            aleatorio = rand() % array.size();
        }

        // Coloco esse valor gerado aleatorio no vetor que salva esses valores
        gerados.push_back(aleatorio);

        // Coloco no array a ser retornado o valor do array original no indice do numero aleatorio 
        // gerado
        retorno.push_back(array[aleatorio]);
    }

    return retorno;
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
    // Inicializando variaveis
    double distanciaMinima = DBL_MAX;
    string resposta = "";
    int canPrint = 0;
    int n = cidades.size();
    int valores[n];
    bool used[100];
    vector<string> result;

    // Inicializando vetor de valores
    for (int i = 0; i < n - 1; i++)
    {
        valores[i] = i + 1;
    }

    // Fazemos a permutacao entre todas as cidades e colocamos no resultPerm array (global)
    permutacao(n - 1, 0, valores, used);

    // Para cada caminho da permutacao
    for (int i = 0; i < resultPerm.size(); i++)
    {
        resultPerm[i] = "00" + resultPerm[i] + "00";


        // Calculamos a distancia entre cada cidade e somamos da distancia final
        double somaDistancia = 0.0;
        for (int j = 0; j < resultPerm[i].length() - 3; j += 2)
        {
            int cidadeA = charParaInteiro(resultPerm[i].at(j), resultPerm[i].at(j + 1));
            int cidadeB = charParaInteiro(resultPerm[i].at(j + 2), resultPerm[i].at(j + 3));

            somaDistancia = somaDistancia + calcularDistancia(cidades[cidadeA], cidades[cidadeB]);
        }

        // Se a soma dessas distancias desse caminho for a menor ate agora
        if (somaDistancia < distanciaMinima)
        {
            // Igualamos a distancia minima a essa encontrada e pegamos a resposta (caminho)
            distanciaMinima = somaDistancia;
            resposta = resultPerm[i];
        }
    }

    // Por fim montamos e printamos a resposta
    montaResposta(resposta, distanciaMinima);
}

// Metodo do caixeiro viajante usando programacao dinamica
void CaixeiroViajante::caixeiroViajanteDinamico()
{   
    // Limpamos o array global e inicializamos as variaveis
    limpar();
    double distanciaMinima = DBL_MAX;
    string resposta = "";
    int n = cidades.size();
    int valores[n];
    bool used[100];
    vector<string> result;
    double matriz[n][n];

    //inicializa a matriz que vai conter a distancia dos caminhos anteriores (para usar caso repitam)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz[i][j] = 0;
        }
    }

    // Inicializando valores
    for (int i = 0; i < n - 1; i++)
    {
        valores[i] = i + 1;
    }

    // Fazemos a permutacao entre todas as cidades e colocamos no resultPerm array (global)
    permutacao(n - 1, 0, valores, used);

    // Para cada caminho da permutacao
    for (int i = 0; i < resultPerm.size(); i++)
    {
        resultPerm[i] = "00" + resultPerm[i] + "00";
        double somaDistancia = 0.0;

        // Pegamos as cidades
        for (int j = 0; j < resultPerm[i].length() - 3; j += 2)
        {
            int cidadeA = charParaInteiro(resultPerm[i].at(j), resultPerm[i].at(j + 1));
            int cidadeB = charParaInteiro(resultPerm[i].at(j + 2), resultPerm[i].at(j + 3));

            double distancia = 0;

            // Se a distancia entre as cidades ja tiver sido calculada e salva alguma vez
            if (matriz[cidadeA][cidadeB] != 0)
            {
                distancia = matriz[cidadeA][cidadeB];
            }
            // Caso contrario, calculamos a distancia entre elas e armazenamos na matriz
            else
            {
                distancia = calcularDistancia(cidades[cidadeA], cidades[cidadeB]);
                matriz[cidadeA][cidadeB] = distancia;
            }

            // Calculo da soma das distancias do caminho
            somaDistancia = somaDistancia + distancia;
        }

        // Se esse caminho teve a menor distancia
        if (somaDistancia < distanciaMinima)
        {   
            // Salvamos na variavel a menor distancia e a resposta
            distanciaMinima = somaDistancia;
            resposta = resultPerm[i];
        }
    }

    // Por fim montamos e printamos a resposta
    montaResposta(resposta, distanciaMinima);
}

// Metodo do caixeiro viajante usando branch and bound
void CaixeiroViajante::caixeiroViajanteBranchAndBound()
{
    // Limpamos o array global e inicializamos as variaveis
    limpar();
    double distanciaMinima = DBL_MAX;
    string resposta = "";
    int n = cidades.size();
    int valores[n];
    bool used[100];
    vector<string> result;

    // Inicializando valores
    for (int i = 0; i < n - 1; i++)
    {
        valores[i] = i + 1;
    }

    // Fazemos a permutacao entre todas as cidades e colocamos no resultPerm array (global)
    permutacao(n - 1, 0, valores, used);

    // Para cada caminho da permutacao
    for (int i = 0; i < resultPerm.size(); i++)
    {
        resultPerm[i] = "00" + resultPerm[i] + "00";
        double somaDistancia = 0.0;

        // Iterando pelos resultados da permutacao
        for (int j = 0; j < resultPerm[i].length() - 3; j += 2)
        {
            // Se a soma das distancias for maior que a menor soma encontrada ate agora
            if (somaDistancia > distanciaMinima)
            {
                // Saimos do loop no fim dessa iteracao
                break;
            }

            // Caso contrario pegamos as cidades e somamos as distancias do caminho ate agora
            int cidadeA = charParaInteiro(resultPerm[i].at(j), resultPerm[i].at(j + 1));
            int cidadeB = charParaInteiro(resultPerm[i].at(j + 2), resultPerm[i].at(j + 3));

            somaDistancia = somaDistancia + calcularDistancia(cidades[cidadeA], cidades[cidadeB]);
        }

        // Se esse caminho teve a menor distancia
        if (somaDistancia < distanciaMinima)
        {
            // Salvamos na variavel a distancia minima e a resposta (caminho)
            distanciaMinima = somaDistancia;
            resposta = resultPerm[i];
        }
    }

    // Por fim montamos e printamos a resposta
    montaResposta(resposta, distanciaMinima);
}

// Metodo do caixeiro viajante usando algoritmo genetico
void CaixeiroViajante::caixeiroViajanteGenetico()
{
    //limpar();
    
    vector<int> ordem;
    vector<vector<int>> populacao;
    const int tamanhoPopulacao = 10;

    for (int i = 0; i < cidades.size(); i++) {
        ordem.push_back(i);
    }

    for (int i = 0; i < tamanhoPopulacao; i++) {
        ordem = randomizarVetor(ordem);

        populacao.push_back(ordem);
    }
}
