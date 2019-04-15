#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include "Arete.h"

class Sommet
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Sommet(std::string id,double x,double y);
        ~Sommet();

    private:
        /// Données spécifiques du sommet
        std::string m_id; // Identifiant
        double m_x, m_y; // Position
        std::vector<Arete*> m_aretes; ///Arêtes adjacentes
};

#endif // SOMMET_H_INCLUDED
