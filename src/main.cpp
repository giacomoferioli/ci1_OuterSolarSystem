#include "data.h"
#include <iostream>
#include <fstream>
#include "math.h"
#include <SFML/Graphics.hpp>
#include "Matrix.hpp"
#include "Camera.hpp"
#include "Simulation.hpp"

int main(){
    //init
    sf::RenderWindow window(sf::VideoMode(SIZE, SIZE), "SFML works!");
    sf::Image img;
    sf::Texture text;
    sf::Sprite sprite;
    
    img.create(SIZE,SIZE,sf::Color::Black);
    text.loadFromImage(img);
    sprite.setTexture(text);

    Simulation sim(m,v_q,SYMPLECTIC_EULER);
    Camera cam(img,Vec3(1,0,0));

    //std::ofstream output("../output.dat",std::ios::binary);
    sf::CircleShape circle[6];
    for(int i = 0; i < 6; i++)
        circle[i].setRadius(1);

    bool done = false;
    long lastframe = 0;
    double phi=0,theta=0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //checks input
        bool reset = false;
        if( ISDOWN(sf::Keyboard::A)){
            phi += ANGLUAR_MOVEMENT_INCREMENT;
            reset=true;
        }
        if( ISDOWN(sf::Keyboard::D)){
            phi -= ANGLUAR_MOVEMENT_INCREMENT;
            reset=true;
        }
        if( ISDOWN(sf::Keyboard::W)){
            theta -= ANGLUAR_MOVEMENT_INCREMENT;
            if(theta < -M_PI/2)
                theta = -M_PI/2;
        
            reset=true;
        }
        if( ISDOWN(sf::Keyboard::S)){
            theta += ANGLUAR_MOVEMENT_INCREMENT;
            if(theta > M_PI/2)
                theta = M_PI/2;
            reset=true;
        }
        if(reset){
            cam.setHeading(Vec3(1,0,0));
            cam.rotateZ(phi);
            cam.rotateY(theta);
            for(int i = 0; i < SIZE * SIZE; i++){
                img.setPixel(i/SIZE,i%SIZE,sf::Color::Black);
            }
            
            sim.reset();
        }
        if( checkKey(sf::Keyboard::Enter)){
            std::string filename("export-");
            filename = filename + std::to_string(ms()) + ".png";

            img.saveToFile(filename);
        }

        //renders
        while(ms() - lastframe < FRAMELENGTH){
            if(!sim.done()){
                for(int i=0; i<6;i++){
                    cam.drawPoint(sim.getPlanetPos(i),colors[i]);
                }
                
                sim.step(100);
            }
        }
        
        lastframe = ms();
        window.clear();
        text.loadFromImage(img);
        window.draw(sprite);
        window.display();
    }

    return 0;
}
