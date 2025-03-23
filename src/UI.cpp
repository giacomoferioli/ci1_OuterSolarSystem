#include "UI.hpp"

UI::UI(Simulation& sim) : w(sf::VideoMode(2*SIZE,SIZE),"Outer Solar System"), sim(sim), cam(img,Vec3::X), gr(graph){
    img.create(SIZE,SIZE,sf::Color::Black);
    graph.create(SIZE,SIZE,sf::Color::Black);
    
    gr.setGrid(5,0);
    gr.setXrange(0,sim.maxSteps());
    gr.setYrange(0,1.3*sim.H());
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
    if(reset){
        cam.setHeading(Vec3(1,0,0));
        cam.rotateZ(phi);
        cam.rotateY(theta);
        for(int i = 0; i < SIZE * SIZE; i++){
            img.setPixel(i/SIZE,i%SIZE,sf::Color::Black);
        }

        gr.reset();
        


        sim.reset();
    }
    if( checkKey(sf::Keyboard::Enter)){
        std::string filename("export-");
        filename = filename + std::to_string(ms());

        save(filename);        
    }
}

void UI::save(std::string filename){
    img.saveToFile(filename+".png");

    sim.reset();

    /*
    std::ofstream energy(filename+".csv");
    energy << "N,H\n";
    energy << "0," << sim.H() << "\n";

        
    for(int i = 1;!sim.done();i+=STEPS_PER_SAVE,sim.step(100,STEPS_PER_SAVE))
        energy << std::to_string(i) << "," << sim.H() << "\n";
        
    energy.close();
    */
}

void UI::draw(){
    for(int i=0; i<6;i++){
        cam.drawPoint(sim.getPlanetPos(i),colors[i]);
    }

    gr.drawPoint(sim.steps(),sim.H(),sf::Color::Green);
}

void UI::display(){
    sf::Texture text1;
    text1.loadFromImage(img);
    sf::Sprite sprite1(text1);

    sf::Texture text2;
    text2.loadFromImage(graph);
    sf::Sprite sprite2(text2);

    sprite2.setPosition(sf::Vector2f(SIZE,0));

    w.clear();
    w.draw(sprite1);
    w.draw(sprite2);
    w.display();
}

void UI::tick(){
    long lastframe = ms();
    input();
    
    while(ms() - lastframe < FRAMELENGTH){
        if(!sim.done()){
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