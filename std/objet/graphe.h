#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "sommet.h"
#include "arretes.h"
#include "combinaison.h"

class Graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        Graphe(std::string ficTopologie, std::string ficPonderations);
        Graphe();
        ~Graphe();

        void testAfficher();

        ///Prim
        Graphe *Prim(int typeCout);
        ///Double pondération
        std::unordered_set<Combinaison*> doublePonderation();

        void setSommets(std::unordered_map<std::string, Sommet*> sommets) {m_sommets = sommets;}
        void setAretes(std::unordered_map<std::string, Arete*> aretes) {m_aretes = aretes;}

    protected:
        /// Le réseau est constitué d'une collection de sommets
        std::unordered_map<std::string,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<std::string, Arete*> m_aretes;
};

#endif // GRAPHE_H_INCLUDED
