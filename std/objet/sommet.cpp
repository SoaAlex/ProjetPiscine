#include"sommet.h"

void Sommet::affichage (Svgfile& svgout) const
{
    svgout.addDisk(m_x,m_y,6,2,"white");///nettoyage de la zone
    svgout.addCircle(m_x,m_y,6,2);///contour du sommet
    if (m_id<10)///détection de la longueur de l'id
    {
        svgout.addText(m_x-2,m_y+2,m_id,2);///affichage centré des id en dessous de 10
    }
    else
    {
        svgout.addText(m_x-4,m_y+2,m_id,2);///affichage centré des id au dessus de 10
    }
}
