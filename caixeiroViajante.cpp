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
    if (k == n) {
        string value = "";
        for (int i = 0; i < n; i++) {
            value = value + to_string(valores[i]);
        }
        resultPerm.push_back(value);
    } else {
        for (i = 0; i < n; i++) {
            if (!used[i]) {
                valores[k] = i+1;
                used[i] = true;
                permutacao(n, k+1, valores, used);
                used[i] = false;
            }
        }
    }
}

double CaixeiroViajante::calcularDistancia(Cidade a, Cidade b){
    int x1 = a.getCoordenadaX();
    int y1 = a.getCoordenadaY();
    int x2 = b.getCoordenadaX();
    int y2 = b.getCoordenadaY();

    double r1 = pow(x2 - x1, 2);
    double r2 = pow(y2 - y1, 2);

    double resultado = sqrt(r1 + r2);
    return resultado;
}

void CaixeiroViajante::limpar(){
    resultPerm.clear();
}

int CaixeiroViajante::concatenar(int x, int y) {
    int pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;
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

    int n = cidades.size();
    int valores[n];
    bool used[100];
    vector<string> result;

    for (int i = 0; i < n-1; i++) {
        valores[i] = i+1;
    }
    permutacao(n-1, 0, valores, used);

    for (int i = 0; i < resultPerm.size(); i++) {
        resultPerm[i] = "0" + resultPerm[i] + "0";
        double somaDistancia = 0.0;
        for (int j = 0; j < resultPerm[i].length() - 1; j++) {
            int cidadeA = int(resultPerm[i].at(j)) - 48;
            int cidadeB = int(resultPerm[i].at(j+1)) - 48;
            somaDistancia = somaDistancia + calcularDistancia( cidades[cidadeA], cidades[cidadeB] );
        }
        if (somaDistancia < distanciaMinima) {
            distanciaMinima = somaDistancia;
            resposta = resultPerm[i];
        }
    }

    string resp = "";
    for (int i = 0; i < resposta.length() - 1; i++) {
        int temp = int(resposta.at(i)) - 48 + 1;
        resp = resp + to_string(temp);
    }
    resposta = resp;

    //cout << "Distancia: " <<  distanciaMinima << "\n";
    //cout << "Reposta: " << resposta;
}


void CaixeiroViajante::caixeiroViajanteDinamico()
{
    double distanciaMinima = DBL_MAX;
    string resposta = "";

    int n = cidades.size();
    int valores[n];
    bool used[100];
    vector<string> result;
    map<int, int> resultadosAnteriores; // TODO: Transformar para double

    for (int i = 0; i < n-1; i++) {
        valores[i] = i+1;
    }
    permutacao(n-1, 0, valores, used);

    for (int i = 0; i < resultPerm.size(); i++) {
        resultPerm[i] = "0" + resultPerm[i] + "0";
        double somaDistancia = 0.0;
        for (int j = 0; j < resultPerm[i].length() - 1; j++) {
            int cidadeA = int(resultPerm[i].at(j)) - 48;
            int cidadeB = int(resultPerm[i].at(j+1)) - 48;
            int posicao = concatenar(cidadeA, cidadeB);
            auto it = resultadosAnteriores.find(posicao);
            int distancia = 0;
            if (false && it != resultadosAnteriores.end()) {
                distancia = resultadosAnteriores.at(posicao);
            } else {
                distancia = calcularDistancia( cidades[cidadeA], cidades[cidadeB] );
            }
            somaDistancia = somaDistancia + distancia;

            posicao = concatenar(cidadeA, cidadeB);
            resultadosAnteriores.insert( {posicao, int(distancia)} );
        }
        if (somaDistancia < distanciaMinima) {
            distanciaMinima = somaDistancia;
            resposta = resultPerm[i];
        }
    }

    string resp = "";
    for (int i = 0; i < resposta.length() - 1; i++) {
        int temp = int(resposta.at(i)) - 48 + 1;
        resp = resp + to_string(temp);
    }
    resposta = resp;

    //cout << "Distancia: " <<  distanciaMinima << "\n";
    //cout << "Reposta: " << resposta;
}


void CaixeiroViajante::caixeiroViajanteBranchAndBound()
{
}

void CaixeiroViajante::caixeiroViajanteGenetico()
{
}



// x = 123
//y = 12
///12312
//concat = (x+y)(x+y+1)/2 + y

