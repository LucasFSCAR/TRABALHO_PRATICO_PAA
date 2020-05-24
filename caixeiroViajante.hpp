#ifndef CAIXEIRO_HPP
#define CAIXEIRO_HPP
#include "cidade.hpp"
#include <vector>
#include <string>

using namespace std;

class CaixeiroViajante
{

private:
    std::vector<Cidade> cidades;

public:
    CaixeiroViajante(std::vector<Cidade> _cidades);
    void caixeiroViajanteForcaBruta();
    void caixeiroViajanteBranchAndBound();
    void caixeiroViajanteDinamico();
    void caixeiroViajanteGenetico();

    void permutacao(int n, int k, int valores[], bool used[]);
    double calcularDistancia(Cidade a, Cidade b);
    void limpar();
    int concatenar(int x, int y);
    int charParaInteiro(char c);
    int charParaInteiro(char a, char b);
    vector<int> randomizar(vector<int> item, int num);
    std::string vectorParaString(std::vector<int> vetor);
    void normalizar();
    int pegarUm();
    std::vector<int> mutacao(std::vector<int>);
    void montaResposta(std::string s, double d, int tipoResposta);
};
#endif