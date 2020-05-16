#include <iostream>
#include <vector>
#include "cidade.hpp"
#include "caixeiroViajante.hpp"

using namespace std;

int main()
{
    cout << "Started\n";

    Cidade cidade0(1, 100, 100);
    Cidade cidade1(2, 900, 100);
    Cidade cidade2(3, 900, 900);
    Cidade cidade3(4, 100, 900);
    //Cidade cidade4(5, 500, 500);


    vector<Cidade> lista;
    lista.push_back(cidade0);
    lista.push_back(cidade1);
    lista.push_back(cidade2);
    lista.push_back(cidade3);
    //lista.push_back(cidade4);

    CaixeiroViajante cv(lista);
    cv.caixeiroViajanteForcaBruta();
    return 0;
}