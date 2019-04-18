#include "combinaison.h"
#include <math.h>
#include "graphe.h"

void Combinaison::afficher()
{
    for(size_t i=0; i<m_totauxPonderations.size(); ++i)
    {
        std::cout<<m_totauxPonderations[i]<<"  ";
    }
    std::cout<<m_elimine<<std::endl;
}

void Combinaison::afficher(Svgfile & svgout,float echellex,float echelley,float xmin,float ymin,float moyennex,float moyenney) const
{
    float rayon= 5/*log10(abs(m_totauxPonderations[0]-moyennex)+abs(m_totauxPonderations[1]-moyenney)+1)*/;
    if (m_elimine)
    {
        svgout.addDisk(((m_totauxPonderations[0]-xmin)*echellex)+40,560-((m_totauxPonderations[1]-ymin)*echelley),rayon,1,"red");
    }
}

void Combinaison::afficherSelec(Svgfile  & svgout,float echellex,float echelley,int& nombre_afficher,std::vector<Sommet*> sommets,float xmin,float ymin) const
{
    svgout.addDisk(((m_totauxPonderations[0]-xmin)*echellex)+40,560-((m_totauxPonderations[1]-ymin)*echelley),5,1,"green");
    ///affichage combinaisons choisies
    Graphe graphe{sommets,m_aretes,m_totauxPonderations};
    graphe.affichage(svgout,nombre_afficher,0,0);
    svgout.addLine(((m_totauxPonderations[0]-xmin)*echellex)+40,560-((m_totauxPonderations[1]-ymin)*echelley),610,30+(65*nombre_afficher));
    nombre_afficher++;
}
