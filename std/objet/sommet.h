#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include "arretes.h"

class Sommet
{
    public:
        ///constructeur qui re�oit en params les donn�es du sommet
        Sommet(std::string id,double x,double y);
        ~Sommet();
        void setArete(Arete* arete);
        std::string getID() const{
            return m_id;
        };
        std::vector<Arete*> getAretes()const{
            return m_aretes;
        };

    private:
        /// Donn�es sp�cifiques du sommet
        std::string m_id; // Identifiant
        double m_x, m_y; // Position
        std::vector<Arete*> m_aretes;
};

#endif // SOMMET_H_INCLUDED
