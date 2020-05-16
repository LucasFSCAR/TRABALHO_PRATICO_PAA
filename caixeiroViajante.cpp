#include "caixeiroViajante.hpp"
#include "cidade.hpp"
#include <vector>
#include <iostream>

using namespace std;


CaixeiroViajante::CaixeiroViajante(std::vector<Cidade> _cidades)
{
    cidades = _cidades;
}

void CaixeiroViajante::caixeiroViajanteForcaBruta()
{
    for (int i = 0; i < cidades.size(); i++) {
        cout << cidades.at(i).getId();
    }

}

void CaixeiroViajante::caixeiroViajanteBranchAndBound()
{
}

void CaixeiroViajante::caixeiroViajanteDinamico()
{
}

void CaixeiroViajante::caixeiroViajanteGenetico()
{
}
