#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>
#include "cidade.hpp"
#include "caixeiroViajante.hpp"

using namespace std;

void lerEntrada(vector<Cidade> &lista);

int main()
{
    vector<Cidade> lista;

    cout << "Started\n";

    // Cidade cidade0(1, 100, 100);
    // Cidade cidade1(2, 900, 100);
    // Cidade cidade2(3, 900, 900);
    // Cidade cidade3(4, 100, 900);
    // Cidade cidade4(5, 500, 500);
    // Cidade cidade5(1, 100, 100);
    // Cidade cidade6(2, 900, 100);
    // Cidade cidade7(3, 900, 900);
    // Cidade cidade8(4, 100, 900);
    // Cidade cidade9(5, 500, 500);
    // //Cidade cidade10(1, 1000, 1000);
    // //Cidade cidade11(2, 900, 100);

    // lista.push_back(cidade0);
    // lista.push_back(cidade1);
    // lista.push_back(cidade2);
    // lista.push_back(cidade3);
    // lista.push_back(cidade4);
    // lista.push_back(cidade5);
    // lista.push_back(cidade6);
    // lista.push_back(cidade7);
    // lista.push_back(cidade8);
    // lista.push_back(cidade9);
    // //lista.push_back(cidade10);
    // //lista.push_back(cidade11);

    lerEntrada(lista);

    CaixeiroViajante cv(lista);

    clock_t inicio1 = clock();
    cv.caixeiroViajanteForcaBruta();
    clock_t fim1 = clock();

    clock_t inicio2 = clock();
    cv.caixeiroViajanteBranchAndBound();
    clock_t fim2 = clock();

    clock_t inicio3 = clock();
    cv.caixeiroViajanteDinamico();
    clock_t fim3 = clock();

    double tempoDecorrido1 = double(fim1 - inicio1) / CLOCKS_PER_SEC;
    double tempoDecorrido2 = double(fim2 - inicio2) / CLOCKS_PER_SEC;
    double tempoDecorrido3 = double(fim3 - inicio3) / CLOCKS_PER_SEC;

    cout << "Força Bruta: " << tempoDecorrido1 << "\n";
    cout << "Branch And Bound: " << tempoDecorrido2 << "\n";
    cout << "Dinamico: " << tempoDecorrido3 << "\n";

    return 0;
}

void lerEntrada(vector<Cidade> &lista)
{
    int coordenadaX, coordenadaY;
    bool read = false;
    int i = 1;

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

        coordenadaX = stoi(array[0]);
        coordenadaY = stoi(array[1]);

        Cidade cidade(i, coordenadaX, coordenadaY);

        lista.push_back(cidade);

        i++;
    }
}