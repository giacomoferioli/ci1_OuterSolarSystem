#include "Graph.hpp"

#define GRAPH_WIDTH img.getSize().x
#define GRAPH_HEIGHT img.getSize().y


Graph::Graph(sf::Image& img) : img(img), size(img.getSize().x) {};

void Graph::reset(){
    for(unsigned int i = 0; i < GRAPH_WIDTH;i++)
        for(unsigned int j = 0; j < GRAPH_HEIGHT;j++)
            img.setPixel(i,j,sf::Color::Black);
    setGrid(hlines,vlines);
}

void Graph::setGrid(unsigned int horizontal_lines_number, unsigned int vertical_line_number){
    hlines = horizontal_lines_number;
    vlines = vertical_line_number;
    for(unsigned int i = GRAPH_PADDING;i < GRAPH_WIDTH - GRAPH_PADDING;i++){
        img.setPixel(i,GRAPH_PADDING,sf::Color::White);
        img.setPixel(i,GRAPH_HEIGHT-GRAPH_PADDING-1,sf::Color::White);
    }

    for(unsigned int j = GRAPH_PADDING;j < GRAPH_HEIGHT - GRAPH_PADDING;j++){
        img.setPixel(GRAPH_PADDING,j,sf::Color::White);
        img.setPixel(GRAPH_HEIGHT - GRAPH_PADDING-1,j,sf::Color::White);
    }

    double spacing = (double)(GRAPH_WIDTH - 2 * GRAPH_PADDING) / (vertical_line_number+1);
    for(unsigned int i = 0; i < vertical_line_number; i++){
        int x = GRAPH_PADDING + (int)round(spacing * (1+i));
        for(unsigned int j = GRAPH_PADDING+1;j < GRAPH_HEIGHT-GRAPH_PADDING-1;j++)
            img.setPixel(x,j,sf::Color(0x888888FF)); 
    }

    spacing = (double)(GRAPH_HEIGHT - 2 * GRAPH_PADDING) / (horizontal_lines_number+1);
    for(unsigned int j = 0; j < horizontal_lines_number; j++){
        int y = GRAPH_PADDING + (int)round(spacing * (1+j));
        for(unsigned int i = GRAPH_PADDING+1;i < GRAPH_WIDTH-GRAPH_PADDING-1;i++)
            img.setPixel(i,y,sf::Color(0x888888FF)); 
    }
}

void Graph::drawPoint(double x,double y,sf::Color color){
    if(x < x0 || x > x1 || y < y0 || y > y1)
        return;

    unsigned int ix = (int)round(ipol(x0,x1,GRAPH_PADDING+1,GRAPH_WIDTH-GRAPH_PADDING-1,x));
    unsigned int iy = (int)round(ipol(y0,y1,GRAPH_HEIGHT-GRAPH_PADDING-1,GRAPH_PADDING+1,y));

    img.setPixel(ix,iy,color);
}