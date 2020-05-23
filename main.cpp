#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>
#include "cidade.hpp"
#include "caixeiroViajante.hpp"

using namespace std;

void lerEntrada();

int main()
{
    cout << "Started\n";

    Cidade cidade0(1, 100, 100);
    Cidade cidade1(2, 900, 100);
    Cidade cidade2(3, 900, 900);
    Cidade cidade3(4, 100, 900);
    //Cidade cidade4(5, 500, 500);
    //Cidade cidade5(1, 100, 100);
    //Cidade cidade6(2, 900, 100);
    //Cidade cidade7(3, 900, 900);
    //Cidade cidade8(4, 100, 900);
    //Cidade cidade9(5, 500, 500);
    //Cidade cidade10(1, 100, 100);
    // Cidade cidade11(2, 900, 100);
    //Cidade cidade12(3, 900, 900);
    //Cidade cidade13(4, 100, 900);
    //Cidade cidade14(3, 900, 900);

    vector<Cidade> lista;
    lista.push_back(cidade0);
    lista.push_back(cidade1);
    lista.push_back(cidade2);
    lista.push_back(cidade3);
    //lista.push_back(cidade4);
    //lista.push_back(cidade5);
    //lista.push_back(cidade6);
    //lista.push_back(cidade7);
    //lista.push_back(cidade8);
    //lista.push_back(cidade9);
    //lista.push_back(cidade10);
    // lista.push_back(cidade11);
    //lista.push_back(cidade12);
    //lista.push_back(cidade13);
    //lista.push_back(cidade14);

    //lerEntrada();

    CaixeiroViajante cv(lista);

   // clock_t inicio1 = clock();
   // cv.caixeiroViajanteDinamico();
   // clock_t fim1 = clock();

    //cv.limpar();

    clock_t inicio2 = clock();
    cv.caixeiroViajanteForcaBruta();
    clock_t fim2 = clock();

    //cv.limpar();

    //clock_t inicio3 = clock();
//    cv.caixeiroViajanteBranchAndBound();
   // clock_t fim3 = clock();

   // cv.limpar();

    // double tempoDecorrido1 = double(fim1 - inicio1) / CLOCKS_PER_SEC;
    double tempoDecorrido2 = double(fim2 - inicio2) / CLOCKS_PER_SEC;
    // double tempoDecorrido3 = double(fim3 - inicio3) / CLOCKS_PER_SEC;

    // cout << "\n\nDinamico: " << tempoDecorrido1 << "\n\n";
    cout << "Força Bruta: " << tempoDecorrido2 << "\n\n";
    // cout << "Branch And Bound: " << tempoDecorrido3 << "\n\n";

    return 0;
}

void programa()
{
}

void lerEntrada()
{
    string entrada1, entrada2;
    bool read = false;

    for (string line; getline(cin, line);)
    {
        if (read == false)
        {
            read = true;
            continue;
        }

        vector<string> array;

        istringstream split(line);

        for (string temp; split >> temp;)
        {
            array.push_back(temp);
        }

        entrada1 = array[0];
        entrada2 = array[1];

        programa();
    }
}