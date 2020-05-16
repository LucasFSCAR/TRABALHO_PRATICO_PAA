#ifndef CIDADE_HPP
#define CIDADE_HPP
class Cidade
{

    private:
        int id;
        int coordenadaX;
        int coordenadaY;

    public:
        int getId();
        int getCoordenadaX();
        int getCoordenadaY();

        void setId(int _id);
        void setCoordenadaX(int _coordenadaX);
        void setCoordenadaY(int _coordenadaY);

        Cidade();
        Cidade(int _id, int _coordenadaX, int _coordenadaY);
};
#endif