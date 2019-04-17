#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "sommet.h"
#include "combinaison.h"
#include "../outils.h"

class Graphe
{
    public:
        ///destructeur
        ~Graphe(){}
        ///constructeur qui charge le graphe en mémoire
        Graphe(std::string ficTopologie, std::string ficPoids);
        Graphe(std::vector<Sommet*> sommets, std::vector<Arete*> aretes)
            :m_sommets{sommets}, m_aretes{aretes}{}
        ///affichage d'un graphe
        void affichage(std::string _filename="output.svg", int _width=1000, int _height=1000) const;
        ///créer un graphe de poids minimum à partir d'un sommet et d'une pondération
        Graphe* Prim(int typeCout,int s0=0);
        ///Double pondération
        std::vector<Combinaison*> doublePonderation();
        ///Optimisation bi-objectif coût/distance
        std::vector<Combinaison*> cout_ditance();
        ///Dijkstra
        Dijkstra(std::vector<Arete*> aretes, int s0, int typeCout);

    protected:
        /// Le réseau est constitué d'une collection de sommets
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;
};

#endif // GRAPHE_H_INCLUDED
