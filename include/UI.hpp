#include <SFML/Graphics.hpp>
#include <Simulation.hpp>
#include <Camera.hpp>
#include <Graph.hpp>
#include <fstream>


#ifndef UI_1234
#define UI_1234

class UI{
    sf::RenderWindow w;
    sf::Image img;
    sf::Image graph;
    Simulation& sim;
    
    Camera cam;
    Graph gr;

    private:
        void tick();
        void input();
        void draw();
        void display();

    public:
        UI(Simulation& sim);
        void start();
        void save(std::string filename);

};

#endif