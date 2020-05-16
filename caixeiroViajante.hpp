#include "cidade.hpp"
#include <vector>

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
};