#include "caixeiroViajante.hpp"
#include "cidade.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <limits.h>
#include <float.h>
#include <bits/stdc++.h>

using namespace std;
vector<string> resultPerm;

/* Metodos auxiliares
*/
void CaixeiroViajante::permutacao(int n, int k, int valores[], bool used[])
{
    int i;
    if (k == n)
    {
        string value = "";
        for (int i = 0; i < n; i++)
        {
            if (valores[i] < 10) {
                value = value + '0' + to_string(valores[i]);
            } else {
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

void CaixeiroViajante::limpar()
{
    resultPerm.clear();
}

int CaixeiroViajante::concatenar(int x, int y)
{
    if (x == 0) return y;
    int pow = 10;
    while (y >= pow)
        pow *= 10;
    return x * pow + y ;
}

int CaixeiroViajante::charParaInteiro(char c)
{
    return int(c) - 48;
}

int CaixeiroViajante::doisCharParaInteiro(char a, char b)
{
    return concatenar( int(a) - 48, int(b) - 48 );
}

void CaixeiroViajante::montaResposta(string caminho, double distancia)
{
    string resp = "";
    for (int i = 0; i < caminho.length() - 2; i+=2)
    {
        int item = doisCharParaInteiro(caminho.at(i), caminho.at(i+1)) + 1;
        resp = resp + " " + to_string(item);
    }
    caminho = resp;

    cout << "Distancia: " << distancia << "\n";
    cout << "Reposta: " << caminho << "\n";
}

/* Metodos principais
*/
CaixeiroViajante::CaixeiroViajante(std::vector<Cidade> _cidades)
{
    cidades = _cidades;
}

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
        for (int j = 0; j < resultPerm[i].length() - 3; j+=2)
        {
            int cidadeA = doisCharParaInteiro(resultPerm[i].at(j), resultPerm[i].at(j+1));
            int cidadeB = doisCharParaInteiro(resultPerm[i].at(j+2), resultPerm[i].at(j+3));

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

void CaixeiroViajante::caixeiroViajanteDinamico()
{
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
        for (int j = 0; j < resultPerm[i].length() - 3; j+=2)
        {
            int cidadeA = doisCharParaInteiro(resultPerm[i].at(j), resultPerm[i].at(j+1));
            int cidadeB = doisCharParaInteiro(resultPerm[i].at(j+2), resultPerm[i].at(j+3));

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

void CaixeiroViajante::caixeiroViajanteBranchAndBound()
{
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
        for (int j = 0; j < resultPerm[i].length() - 2; j+=2)
        {
            int cidadeA = doisCharParaInteiro(resultPerm[i].at(j), resultPerm[i].at(j+1));
            int cidadeB = doisCharParaInteiro(resultPerm[i].at(j+2), resultPerm[i].at(j+3));

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

void CaixeiroViajante::caixeiroViajanteGenetico()
{
}
