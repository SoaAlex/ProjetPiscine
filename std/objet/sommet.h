#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include "arretes.h"

class Sommet
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Sommet(std::string id,double x,double y);
        ~Sommet();
        void setArete(Arete* arete);
        std::string getID() const{
            return m_id;
        };
        std::vector<Arete*> getAretes()const{
            return m_aretes;
        };

        void ajouterVoisin(std::string voisin); ///Principe du TP3
        std::vector<std::string> getVoisins() {return m_voisins;}

    private:
        /// Données spécifiques du sommet
        std::string m_id; // Identifiant
        double m_x, m_y; // Position
        std::vector<Arete*> m_aretes;
        std::vector<std::string> m_voisins;
};

#endif // SOMMET_H_INCLUDED
