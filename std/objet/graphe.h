#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "sommet.h"
#include "arretes.h"

class Graphe
{
    public:
        ///constructeur qui charge le graphe en m�moire
        Graphe(std::string);
        void affichage();
        Graphe(std::string ficTopologie, std::string ficPonderations);
        ~Graphe();
        //testAfficher();

    protected:
        /// Le r�seau est constitu� d'une collection de sommets
        std::unordered_map<std::string,Sommet*> m_sommets;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)
};

//class Combinaison :

#endif // GRAPHE_H_INCLUDED
