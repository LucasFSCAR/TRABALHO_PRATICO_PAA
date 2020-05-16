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

Cidade::Cidade()
{
    id = 0;
    coordenadaX = 0;
    coordenadaY = 0;
}

Cidade::Cidade(int _id, int _coordenadaX, int _coordenadaY)
{
    id = _id;
    coordenadaX = _coordenadaX;
    coordenadaY = _coordenadaY;
}