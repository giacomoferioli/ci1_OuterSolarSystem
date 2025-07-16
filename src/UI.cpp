#include "UI.hpp"

UI::UI(Simulation& sim) : w(sf::VideoMode(2*SIZE,SIZE),"Outer Solar System"), sim(sim), cam(img,Vec3::X), graph(SIZE,SIZE/2){
    img.create(SIZE,SIZE,sf::Color::Black);

    sim.reset(); //il reset nel costruttore della sim non è in grado di chiamare gli init ovverridati, da rivedere meglio

    graph.setGrid(5,8);
    graph.setXrange(0,sim.getMaxSteps());
    graph.setYrange(0,1.2);
}

void UI::input(){
    static double theta = 0, phi = 0;
    sf::Event event;
    while (w.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            w.close();
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
    if( ISDOWN(sf::Keyboard::PageUp)){
        cam.zoom(.95);
        reset = true;
    }
    if( ISDOWN(sf::Keyboard::PageDown)){
        cam.zoom(1.05);
        reset = true;
    }
    if(reset){
        cam.setHeading(Vec3(1,0,0));
        cam.rotateZ(phi);
        cam.rotateY(theta);
        for(int i = 0; i < SIZE * SIZE; i++){
            img.setPixel(i/SIZE,i%SIZE,sf::Color::Black);
        }

        graph.reset();
        sim.reset();
    }
    if( checkKey(sf::Keyboard::Enter))
        saveImg();
    if( checkKey(sf::Keyboard::G))
        saveGraph();
    
}

void UI::saveImg(std::string filename){
    img.saveToFile(filename+sim.toString()+".png");
    std::cout << sim.toString() << std::endl;
}

void UI::saveGraph(std::string filename){
    graph.get_img().saveToFile(filename+graph.toString() + ".png");
    std::cout << graph << std::endl;
}

void UI::draw(){
    for(int i=0; i<6;i++){
        cam.drawPoint(sim.getPlanetPos(i),colors[i]);
    }

    graph.drawPoint(sim.getStepsDone(),sim.H_rel(),sf::Color::Green);
}

void UI::display(){
    sf::Texture text1;
    text1.loadFromImage(img);
    sf::Sprite sprite1(text1);

    sf::Texture text2;
    text2.loadFromImage(graph.get_img());
    sf::Sprite sprite2(text2);

    sprite2.setPosition(sf::Vector2f(SIZE,0));

    w.clear();
    w.draw(sprite1);
    w.draw(sprite2);
    w.display();
}

//potrebbe venir pensata meglio
void UI::tick(){
    long lastframe = ms();
    input();

    while(ms() - lastframe < FRAMELENGTH){
        if(!sim.isDone()){
            sim.step();
            draw();
        }
    }

    display();
}

void UI::start(){
    while(w.isOpen()){
        tick();
    }
}