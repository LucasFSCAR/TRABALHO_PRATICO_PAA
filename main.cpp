#include <iostream>
#include <vector>
#include "cidade.hpp"
#include "caixeiroViajante.hpp"

using namespace std;

int main()
{
    int n = 5;
    Cidade cidade0(0, 100, 100);
    Cidade cidade1(1, 400, 400);
    Cidade cidade2(2, 200, 200);
    Cidade cidade3(3, 300, 300);
    Cidade cidade4(4, 418, 954);

    vector<Cidade> lista;
    lista.push_back(cidade0);
    lista.push_back(cidade1);
    lista.push_back(cidade2);
    lista.push_back(cidade3);
    lista.push_back(cidade4);

    CaixeiroViajante cv(lista);
    cv.caixeiroViajanteForcaBruta();
    return 0;
}