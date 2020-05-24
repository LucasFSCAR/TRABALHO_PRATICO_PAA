#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>
#include "cidade.hpp"
#include "caixeiroViajante.hpp"

using namespace std;

// Declaracao da funcao que le a entrada

void lerEntrada(vector<Cidade> &lista);

int main()
{   
    // Declaracao lista de cidades
    vector<Cidade> lista;

    cout << "Started\n";

    lerEntrada(lista);

    // Instanciamos um objeto do tipo CaixeiroViajante com a lista de cidades
    CaixeiroViajante cv(lista);

    // Executamos as funcoes do caixeiro viajante e salvamos os tempos para cada execucao
    clock_t inicio1 = clock();
    cv.caixeiroViajanteForcaBruta();
    clock_t fim1 = clock();

    clock_t inicio2 = clock();
    cv.caixeiroViajanteDinamico();
    clock_t fim2 = clock();

    clock_t inicio3 = clock();
    cv.caixeiroViajanteBranchAndBound();
    clock_t fim3 = clock();

    clock_t inicio4 = clock();
    cv.caixeiroViajanteGenetico();
    clock_t fim4 = clock();

    double tempoDecorrido1 = double(fim1 - inicio1) / CLOCKS_PER_SEC;
    double tempoDecorrido2 = double(fim2 - inicio2) / CLOCKS_PER_SEC;
    double tempoDecorrido3 = double(fim3 - inicio3) / CLOCKS_PER_SEC;
    double tempoDecorrido4 = double(fim4 - inicio4) / CLOCKS_PER_SEC;

    // Print dos tempos para cada execucao
    cout << "\nForça Bruta: " << tempoDecorrido1 << "\n";
    cout << "Dinamico: " << tempoDecorrido2 << "\n";
    cout << "Branch And Bound: " << tempoDecorrido3 << "\n";
    cout << "Genetico: " << tempoDecorrido4 << "\n";

    return 0;
}

// Metodo que le a entrada
void lerEntrada(vector<Cidade> &lista)
{   
    // Declaracao variaveis
    int coordenadaX, coordenadaY;
    bool read = false;
    int i = 1;

    // Para cada linha da entrada
    for (string line; getline(cin, line);)
    {   
        // Pulando a primeira linha da entrada (linha que indica o numero de linhas)
        if (read == false)
        {
            read = true;
            continue;
        }

        // Array que vai conter a linha partida (resultado do split)
        vector<string> array;

        istringstream split(line);

        // Para cada parte do split, colocamos no array
        for (string temp; split >> temp;)
        {
            array.push_back(temp);
        }

        // Coordenadas
        coordenadaX = stoi(array[0]);
        coordenadaY = stoi(array[1]);

        // Criacao da cidade
        Cidade cidade(i, coordenadaX, coordenadaY);

        // Colocando na lista a cidade
        lista.push_back(cidade);

        i++;
    }
}