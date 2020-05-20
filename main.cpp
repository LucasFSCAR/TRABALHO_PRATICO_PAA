#include <iostream>
#include <sstream>
#include <string>
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


    vector<Cidade> lista;
    lista.push_back(cidade0);
    lista.push_back(cidade1);
    lista.push_back(cidade2);
    lista.push_back(cidade3);
    //lista.push_back(cidade4);
    
    //lerEntrada();

    CaixeiroViajante cv(lista);
    cv.caixeiroViajanteForcaBruta();

    return 0;
}

void lerEntrada() {
    string entrada1, entrada2;
    bool read = false;

    for (string line; getline(cin, line);) {
        if(read == false){
            read = true;
            continue;
        }

        vector<string> array;

        istringstream split(line);

        for(string temp; split >> temp;){
            array.push_back(temp);
        }

        entrada1 = array[0];
        entrada2 = array[1];
        
        //cout << entrada1 << " " << entrada2 << endl;
        
        //FAZER O QUE FOR NECESSARIO
    }
}