#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
///reprise des svg du premier semestre
constexpr char defcol[] = "black";

class Svgfile
{
    public:
        Svgfile(std::string _filename, int _width, int _height);
        ~Svgfile();

        void addDisk(double x, double y, double r=5,int agrandissement=1, std::string color=defcol);
        void addCircle(double x, double y, double r,int agrandissement=1, double ep=2, std::string color=defcol);
        void addText(double x, double y, std::string text,int agrandissement=1, std::string color=defcol);
        void addText(double x, double y, double val,int agrandissement=1, std::string color=defcol);
        void addLine(double x1, double y1, double x2, double y2,int agrandissement=1, std::string color=defcol);
        void addGrid(int agrandissement=1,double span=100.0, bool numbering=true, std::string color="lightgrey");
        void addRepere(double xmax=200,double ymax=200, std::string color="black");
        static std::string makeRGB(int r, int g, int b);

        /// Type non copiable
        Svgfile(const Svgfile&) = delete;
        Svgfile& operator=(const Svgfile&) = delete;

        static bool s_verbose;

    private:
        std::string m_filename;
        std::ofstream m_ostrm;
        int m_width;
        int m_height;

        // Pour éviter les ouverture multiples
        static std::set<std::string> s_openfiles;
};

#endif // SVGFILE_H_INCLUDED



