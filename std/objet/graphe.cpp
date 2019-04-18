#include "graphe.h"

Graphe::Graphe(std::string ficTopologie, std::string ficPoids){ ///CODE TP2/3 (adapté)
    ///Ouverture FICHIER TOPOLOGIE/////////////////////////////////
    std::ifstream ifs{ficTopologie};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + ficTopologie );

    int ordre; //nb sommets
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    int id;
    double x,y;

    ///Lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.push_back(new Sommet{id,x,y});
    }

    int taille; //nb aretes
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    int ID_s1, ID_s2;

    Arete* arete;
    ///Lecture des aretes
    for (int i=0; i<taille; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete ID");
        ifs>>ID_s1; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        ifs>>ID_s2; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        arete = new Arete{id,ID_s1, ID_s2};
        m_sommets[ID_s1]->setArete(arete);
        m_sommets[ID_s2]->setArete(arete);
        m_aretes.push_back(arete);
    }
    ifs.close();

    ///Ouverture FICHIER POIDS///////////////////////:
    std::ifstream ifs2{ficPoids};
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + ficPoids );

    int nbPonderations = 0;
    ifs2 >> taille;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe fichier ponderation");
    ifs2 >> nbPonderations;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture nombre ponderations du graphe");

    float pond;
    for(int i=0; i<taille; ++i)
    {
        ifs2 >> id; if(ifs2.fail()) throw std::runtime_error("Probleme lecture arete ID Fichier 2");
        for (int j=0;j<nbPonderations;j++)
        {
            ifs2 >> pond; if(ifs2.fail()) throw std::runtime_error("Probleme lecture ponderation arete Fichier 2");
            m_aretes[id]->setPonderations(pond);
            if (i==0)
            {
                m_coutTotal.push_back(pond);
            }
            else
            {
                m_coutTotal[j]+=pond;
            }
        }
    }
    ifs2.close();
}

void Graphe::affichage(std::string _filename, int _width, int _height) const
{
    Svgfile svgout{_filename,_width,_height};
    svgout.addGrid(2);
    int x1,x2,y1,y2;
    for (auto& arete: m_aretes)
    {
        x1=m_sommets[arete->getS1()]->get_x();
        y1=m_sommets[arete->getS1()]->get_y();
        x2=m_sommets[arete->getS2()]->get_x();
        y2=m_sommets[arete->getS2()]->get_y();
        svgout.addLine(x1,y1,x2,y2,2);
        svgout.addText((abs(x1+x2)/2)+1,(abs(y1+y2)/2)-2,arete->get_label(),2);
    }
    for (auto& sommet: m_sommets)
    {
        sommet->affichage(svgout);
    }
    std::string sortie;
    sortie.append("Cout total:(");
    std::string ponderation;
    int taille=4;
    for (auto& coutTotal: m_coutTotal)
    {
        ponderation=std::to_string(coutTotal);
        if (coutTotal>=100)
        {
            taille=5;
        }
        ponderation.erase(ponderation.begin()+taille,ponderation.end());
        sortie.append(ponderation);
        sortie.append(" ; ");
    }
    sortie.erase(sortie.end()-3,sortie.end());
    sortie.append(")");
    svgout.addText(_width/2-(16*(taille+5)),_height-70,sortie,1,32);
}

void Graphe::affichage(Svgfile & svgout,int& nombre_afficher,int xinit,int yinit) const
{
    int x1,x2,y1,y2;
    for (auto& arete: m_aretes)
    {
        x1=m_sommets[arete->getS1()]->get_x()+4020;
        y1=m_sommets[arete->getS1()]->get_y()+(nombre_afficher*433);
        x2=m_sommets[arete->getS2()]->get_x()+4020;
        y2=m_sommets[arete->getS2()]->get_y()+(nombre_afficher*433);
        svgout.addLine(x1,y1,x2,y2,0.15);
    }
    for (auto& sommet: m_sommets)
    {
        svgout.addDisk(sommet->get_x()+4020,sommet->get_y()+(nombre_afficher*433),3,0.15);
    }
    std::string sortie;
    std::string ponderation;
    int taille=4;
    for (auto& coutTotal: m_coutTotal)
    {
        ponderation=std::to_string(coutTotal);
        if (coutTotal>=100)
        {
            taille=5;
        }
        ponderation.erase(ponderation.begin()+taille,ponderation.end());
        sortie.append(ponderation);
        sortie.append(" ; ");
    }
    sortie.erase(sortie.end()-3,sortie.end());
    svgout.addText(4520,245+(nombre_afficher*433),sortie,0.15,15);
}
