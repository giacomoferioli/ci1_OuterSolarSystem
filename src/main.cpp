#include "data.h"
#include <iostream>
#include <fstream>
#include "math.h"
#include <SFML/Graphics.hpp>
#include "Matrix.hpp"
#include "Camera.hpp"
#include "Simulation.hpp"
#include "UI.hpp"
#include <sstream>

int main(){
    //init
    Simulation sim(m,v_q,STORMER_VERLET);
    UI ui(sim);

    ui.start();
    
    return 0;
}
