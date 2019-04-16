#ifndef COMBINAISON_H_INCLUDED
#define COMBINAISON_H_INCLUDED

class Combinaison
{
public:
    Combinaison(std::unordered_map<std::string, Arete*> aretes, float cout1, float cout2, bool elimine)
        :m_aretes{aretes}, m_coutTotalFinancier{cout1}, m_coutTotalEnvironnement{cout2}, m_elimine{elimine} { }
    ~Combinaison() { }

    std::unordered_map<std::string, Arete*> getAretes() {return(m_aretes);}


private:
    std::unordered_map<std::string, Arete*> m_aretes;
    float m_coutTotalFinancier;
    float m_coutTotalEnvironnement;
    bool m_elimine;
};


#endif // COMBINAISON_H_INCLUDED
