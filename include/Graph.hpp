#include <SFML/Graphics.hpp>
#include <Common.hpp>
#include "math.h"
#include "util.hpp"

#ifndef GRAPH_RENDERER
#define GRAPH_RENDERER

class Graph{
    sf::Image& img;
    double x0, x1;
    double y0, y1;
    unsigned int hlines, vlines;
    int size;

    public:
    Graph(sf::Image& img);
    void setXrange(double x0, double x1) { this->x0 = x0; this->x1 = x1;};
    void setYrange(double y0, double y1) { this->y0 = y0; this->y1 = y1;};

    void setGrid(unsigned int horizontal_lines_number, unsigned int vertical_line_number);


    void reset();
    void drawPoint(double x,double y,sf::Color color = sf::Color::White);

};

#endif