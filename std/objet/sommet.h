#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include "Arete.h"

class Sommet
{
    public:
        ///constructeur qui re�oit en params les donn�es du sommet
        Sommet(std::string id,double x,double y);
        ~Sommet();

    private:
        /// Donn�es sp�cifiques du sommet
        std::string m_id; // Identifiant
        double m_x, m_y; // Position
        std::vector<Arete*> m_aretes; ///Ar�tes adjacentes
};

#endif // SOMMET_H_INCLUDED
