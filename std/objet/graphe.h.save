#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "sommet.h"
#include "combinaison.h"

class Graphe
{
    public:
        ///destructeur
        ~Graphe(){}
        ///constructeur qui charge le graphe en mémoire
        Graphe(std::string ficTopologie, std::string ficPoids);
        Graphe(std::vector<Sommet*> sommets, std::vector<Arete*> aretes,std::vector<float> coutTotal)
            :m_sommets{sommets}, m_aretes{aretes},m_coutTotal{coutTotal}{}
        ///affichage d'un graphe
        void affichage(std::string _filename="output.svg", int _width=1000, int _height=1000) const;
        void affichage(Svgfile & svgout,int& nombre_afficher,int xinit,int yinit) const;
        ///créer un graphe de poids minimum à partir d'un sommet et d'une pondération
        Graphe* Prim(int typeCout,int s0=0);
        void PrimComplet(int s0=0);

        ///Double pondération
        std::vector<Combinaison*> doublePonderation();
        ///Optimisation bi-objectif coût / distance : 3ème partie
        std::vector<Combinaison*> cout_distance(int ponderation);
        ///BFS
        size_t connexiteBFS(std::vector<Arete*> aretes);
        ///DIJKSTRA
        int Dijkstra(std::vector<Arete*> aretes, int s0, int typePonderation, std::unordered_map<Sommet*,int> heurist = {});
        ///A*
        int AStar(std::vector<Arete*> aretes, int s0, int sFin, int typePonderation);

    protected:
        /// Le réseau est constitué d'une collection de sommets
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;
        std::vector<float> m_coutTotal;
};

#endif // GRAPHE_H_INCLUDED
