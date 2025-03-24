#include "UI.hpp"
#include "Integrators.hpp"

int main(){
    ExplicitEuler sim(m,v_q);
    sim.setMaxSteps(1000000);
    UI ui(sim);

    ui.start();
    
    return 0;
}
