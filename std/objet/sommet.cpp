#include<unordered_map>
#include<unordered_set>
#include "sommet.h"

Sommet::Sommet(std::string id,double x,double y)
    :m_id{id}, m_x{x}, m_y{y}
{ }

Sommet::~Sommet()
{
    //dtor
}
