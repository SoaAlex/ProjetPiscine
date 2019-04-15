#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "sommet.h"
#include "arete.h"

class Graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        Graphe(std::string);
        void affichage();
        Graphe(std::string ficTopologie, std::string ficPonderations);
        ~Graphe();
        //testAfficher();

        std::vector<Arete*> doublePonderation();

    protected:
        /// Le réseau est constitué d'une collection de sommets
        std::unordered_map<std::string,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
}

class Combinaison : public Graphe
{
public:

private:
    float m_coûtTotalFinancier, m_coûtTotalEnvironnement;
    bool m_eliminer;
};

#endif // GRAPHE_H_INCLUDED
