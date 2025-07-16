#include "UI.hpp"
#include "Integrators.hpp"

int main(){
    ExplicitEuler sim(m,v_q);
    UI ui(sim);

    ui.start();
    
    return 0;
}
