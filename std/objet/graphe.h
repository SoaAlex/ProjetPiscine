#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "sommet.h"
#include "arretes.h"
#include "combinaison.h"

class Graphe
{
    public:
        ///constructeur qui charge le graphe en m�moire
        Graphe(std::string ficTopologie, std::string ficPonderations);
        ~Graphe();
        void testAfficher();

        ///Prim
        Combinaison Prim();
        ///Double pond�ration
        std::unordered_set<Combinaison*> doublePonderation();

    protected:
        /// Le r�seau est constitu� d'une collection de sommets
        std::unordered_map<std::string,Sommet*> m_sommets;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<std::string, Arete*> m_aretes;
};

#endif // GRAPHE_H_INCLUDED
