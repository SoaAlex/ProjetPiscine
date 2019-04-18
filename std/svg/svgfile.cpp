﻿#include "svgfile.h"
#include <iostream>
#include <sstream>

const std::string svgHeader =
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" ";

const std::string svgEnding = "\n\n</svg>\n";

/// Effets "Boule en relief", voir données à la fin de ce fichier
extern const std::string svgBallGradients;

std::set<std::string> Svgfile::s_openfiles;

bool Svgfile::s_verbose = true;

Svgfile::Svgfile(std::string _filename, int _width, int _height) :
    m_filename{_filename}, m_width{_width}, m_height{_height}
{
    if ( s_openfiles.count(m_filename) )
        throw std::runtime_error( "File " + m_filename + " already open !" );

    m_ostrm.open(m_filename);
    s_openfiles.insert(m_filename);

    if (!m_ostrm)
    {
        std::cout << "Problem opening " << m_filename << std::endl;
        throw std::runtime_error("Could not open file " + m_filename );
    }
    // Writing the header into the SVG file
    m_ostrm << svgHeader;
    m_ostrm << "width=\"" << m_width << "\" height=\"" << m_height << "\">\n\n";
}

Svgfile::~Svgfile()
{
    // Writing the ending into the SVG file
    m_ostrm << svgEnding;

    // Removing this file from the list of open files
    s_openfiles.erase(m_filename);

    // No need to explicitly close the ofstream object (automatic upon destruction)
}

// Helper templated function
template<typename T>
std::string attrib(std::string name, T val)
{
    std::ostringstream oss;
    oss << name << "=\"" << val << "\" ";
    return oss.str();
}

void Svgfile::addDisk(double x, double y, double r,float agrandissement, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x*agrandissement)
            << attrib("cy", y*agrandissement)
            << attrib("r",  r)
            << attrib("fill", color )
            << "/>\n";
}

void Svgfile::addCircle(double x, double y, double r,float agrandissement,double ep, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x*agrandissement)
            << attrib("cy", y*agrandissement)
            << attrib("r",  r)
            << attrib("fill", "none")
            << attrib("stroke", color )
            << attrib("stroke-width", ep )
            << "/>\n";
}

void Svgfile::addLine(double x1, double y1, double x2, double y2,float agrandissement, std::string color)
{
    m_ostrm << "<line "
            << attrib("x1", x1*agrandissement)
            << attrib("y1", y1*agrandissement)
            << attrib("x2", x2*agrandissement)
            << attrib("y2", y2*agrandissement)
            << attrib("stroke", color)
            << "/>\n";
}

void Svgfile::addText(double x, double y, std::string text,float agrandissement,int taillePolice, std::string color)
{
    m_ostrm << "<text "
            << attrib("x", x*agrandissement)
            << attrib("y", y*agrandissement)
            << attrib("fill", color)
            << attrib("font-size", taillePolice)
            << ">" << text << "</text>\n";
}

void Svgfile::addText(double x, double y, double val,float agrandissement, std::string color)
{
    std::ostringstream oss;
    oss << val;
    addText(x, y, oss.str(),agrandissement,16, color);
}

void Svgfile::addGrid(float agrandissement,double span, bool numbering, std::string color)
{
    double y=0;
    while (y<=m_height/agrandissement)
    {
        addLine(0, y, m_width/agrandissement, y,agrandissement, color);
        if (numbering)
            addText(5, y-5, y,agrandissement, color);
        y+=span;
    }

    double x=0;
    while (x<=m_width/agrandissement)
    {
        addLine(x, 0, x, m_height/agrandissement,agrandissement, color);
        if (numbering)
            addText(x+5, 15, x,agrandissement, color);
        x+=span;
    }
}

void Svgfile::addRepere(double xmax, double ymax,double xmin, double ymin, std::string color)
{
    ///axe des absices
    addLine(20,600-20,600-20,600-20,1,color);
    ///flèche
    addLine(600-30,600-30,600-20,600-20,1,color);
    addLine(600-30,600-10,600-20,600-20,1,color);
    ///min
    addLine(40,600-10,40,600-30,1,color);
    int taille=4;
    std::string ponderation=std::to_string(xmin);
    if (xmin>=100){taille=5;}
    ponderation.erase(ponderation.begin()+taille,ponderation.end());
    addText(40,600,ponderation);
    ponderation.clear();
    taille=4;
    ///max
    addLine(600-50,600-10,600-50,600-30,1,color);
    ponderation=std::to_string(xmax);
    if (xmax>=100){taille=5;}
    ponderation.erase(ponderation.begin()+taille,ponderation.end());
    addText(600-80,600,ponderation);
    ponderation.clear();
    taille=4;
    ///légende
    addText(600-40,600,"Coût1");
    ///axe des ordonnées
    addLine(20,600-20,20,20,1,color);
    ///flèche
    addLine(30,30,20,20,1,color);
    addLine(10,30,20,20,1,color);
    ///min
    addLine(30,600-40,10,600-40,1,color);
    ponderation=std::to_string(ymin);
    if (ymin>=100){taille=5;}
    ponderation.erase(ponderation.begin()+taille,ponderation.end());
    addText(30,600-40,ponderation);
    ponderation.clear();
    taille=4;
    ///max
    addLine(30,40,10,40,1,color);
    ponderation=std::to_string(ymax);
    if (ymax>=100){taille=5;}
    ponderation.erase(ponderation.begin()+taille,ponderation.end());
    addText(32,40,ponderation);
    ///légende
    addText(32,25,"Coût2");
}

std::string Svgfile::makeRGB(int r, int g, int b)
{
    std::ostringstream oss;
    oss << "rgb(" << r << "," << g << "," << b << ")";
    return oss.str();
}
