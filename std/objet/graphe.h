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
        ///constructeur qui charge le graphe en m�moire
        Graphe(std::string ficTopologie, std::string ficPoids);
        Graphe(std::vector<Sommet*> sommets, std::vector<Arete*> aretes,std::vector<float> coutTotal)
            :m_sommets{sommets}, m_aretes{aretes},m_coutTotal{coutTotal}{}
        ///affichage d'un graphe
        void affichage(std::string _filename="output.svg", int _width=1000, int _height=1000) const;
        ///cr�er un graphe de poids minimum � partir d'un sommet et d'une pond�ration
        Graphe* Prim(int typeCout,int s0=0);
        void PrimComplet(int s0=0);
        ///Double pond�ration
        std::vector<Combinaison*> doublePonderation(int ponderation);
        ///Optimisation bi-objectif co�t/distance
        std::vector<Combinaison*> cout_ditance(int ponderation);
        ///Dijkstra
        int Dijkstra(/*std::vector<Arete*> aretes, */int s0, int typeCout);

    protected:
        /// Le r�seau est constitu� d'une collection de sommets
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;
        std::vector<float> m_coutTotal;
};

#endif // GRAPHE_H_INCLUDED
