#ifndef COMBINAISON_H_INCLUDED
#define COMBINAISON_H_INCLUDED
#include "arete.h"

class Combinaison
{
    public:
        Combinaison(std::vector<Arete*> aretes, std::vector<float> totPond, bool elimine)
            :m_aretes{aretes}, m_totauxPonderations{totPond}, m_elimine{elimine} { }
        ~Combinaison() { }

        void afficher();
        void calculTotPond(std::vector<float> totPond) {m_totauxPonderations = totPond;}
        void setElimine(bool val) {m_elimine = val;}

        std::vector<Arete*> getAretes() const {return(m_aretes);}
        std::vector<float> getTotPond() const {return(m_totauxPonderations);}
        bool getElimine() const {return(m_elimine);}
        void afficher(Svgfile & svgout) const;

    private:
        std::vector<Arete*> m_aretes;
        std::vector<float> m_totauxPonderations;/// Ensemble des totaux des pondérations
        bool m_elimine;
};


#endif // COMBINAISON_H_INCLUDED
