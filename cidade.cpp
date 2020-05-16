#include <iostream>
#include "cidade.hpp"

using namespace std;

int Cidade::getId()
{
    return id;
}

int Cidade::getCoordenadaX()
{
    return coordenadaX;
}

int Cidade::getCoordenadaY()
{
    return coordenadaY;
}

void Cidade::setId(int _id)
{
    id = _id;
}

void Cidade::setCoordenadaX(int _coordenadaX)
{
    coordenadaX = _coordenadaX;
}

void Cidade::setCoordenadaY(int _coordenadaY)
{
    coordenadaY = _coordenadaY;
}