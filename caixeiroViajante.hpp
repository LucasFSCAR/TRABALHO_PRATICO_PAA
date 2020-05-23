#ifndef CAIXEIRO_HPP
#define CAIXEIRO_HPP
#include "cidade.hpp"
#include <vector>
#include <string>

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
    int doisCharParaInteiro(char a, char b);
    void montaResposta(std::string s, double d);
};
#endif