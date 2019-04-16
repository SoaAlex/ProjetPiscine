#ifndef COMBINAISON_H_INCLUDED
#define COMBINAISON_H_INCLUDED

class Combinaison
{
public:
    Combinaison(std::unordered_map<std::string,Sommet*> sommets, std::unordered_map<std::string, Arete*> aretes,
                float cout1, float cout2, bool elimine)
        :m_sommets{sommets}, m_aretes{aretes}, m_coutTotalFinancier{cout1}, m_coutTotalEnvironnement{cout2}, m_elimine{elimine} { }
    ~Combinaison() { }

    int getNbrSommets() {return(m_sommets.size());}
    int getNbrAretes() {return(m_aretes.size());}

private:
    std::unordered_map<std::string,Sommet*> m_sommets;
    std::unordered_map<std::string, Arete*> m_aretes;
    float m_coutTotalFinancier;
    float m_coutTotalEnvironnement;
    bool m_elimine;
};


#endif // COMBINAISON_H_INCLUDED
