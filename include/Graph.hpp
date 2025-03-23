#include <SFML/Graphics.hpp>
#include <Common.hpp>
#include <sstream>
#include "math.h"
#include "util.hpp"

#ifndef GRAPH_RENDERER
#define GRAPH_RENDERER

class Graph{
    sf::Image img;
    double x0, x1;
    double y0, y1;
    unsigned int hlines, vlines;

    public:
    Graph(unsigned int width, unsigned int height);
    void setXrange(double x0, double x1) { this->x0 = x0; this->x1 = x1;};
    void setYrange(double y0, double y1) { this->y0 = y0; this->y1 = y1;};

    void setGrid(unsigned int horizontal_lines_number, unsigned int vertical_line_number);

    const sf::Image& get_img() {return img;};
    void reset();
    void drawPoint(double x,double y,sf::Color color = sf::Color::White);

    friend std::ostream& operator<<(std::ostream& os, Graph const & g) {
        return os << "Graph x=[" << g.x0 << "," << g.x1 << "]" << " y=[" << g.y0 << "," << g.y1 << "]";
    }
    std::string toString(){
        return (std::stringstream() << "Graph-x=[" << x0 << "," << x1 << "]-y=[" << y0 << "," << y1 << "]").str();
    }
};

#endif