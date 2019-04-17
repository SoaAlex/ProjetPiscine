#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include"arete.h"

class Sommet
{
    public:
        ///destructeur
        ~Sommet(){}
        ///constructeur qui re�oit en params les donn�es du sommet
        Sommet(int id,double x,double y)
            :m_id{id}, m_x{x}, m_y{y}{}
        ///ajoute une ar�te sortante
        void setArete(Arete* arete){m_aretes.push_back(arete);}
        ///retourne l'id
        int getID() const{return m_id;}
        ///retourne les ar�tes sortantes
        std::vector<Arete*> getAretes()const{return m_aretes;}
        ///retourne les coordonn�es
        double get_x() const{return m_x;}
        double get_y() const{return m_y;}
        ///affiche un sommet dans la console
        void affichage (Svgfile& svgout) const;
    private:
        int m_id; /// Identifiant
        double m_x, m_y; /// Position
        std::vector<Arete*> m_aretes; /// Ar�tes sortantes
};

#endif // SOMMET_H_INCLUDED
