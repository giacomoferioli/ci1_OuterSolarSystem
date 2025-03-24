#include "Simulation.hpp"

Simulation::Simulation(const double* m, const double* v_q,unsigned int max_steps, double h) : m(m), v_q(v_q), steps_done(0), max_steps(max_steps), h(h){
    reset();
}

void Simulation::reset(){
    for(int i = 0; i < PLANETS;i++){
        p[i] = Vec3(
            v_q[3*i+0] * m[i],
            v_q[3*i+1] * m[i],
            v_q[3*i+2] * m[i]
        );

        q[i] = Vec3(
            v_q[3*PLANETS + 3*i+0],
            v_q[3*PLANETS + 3*i+1],
            v_q[3*PLANETS + 3*i+2]
        );
    }
    steps_done = 0;

    H0 = H();

    init();
}

void Simulation::calc_p_prime(){
    for(int i = 0; i < PLANETS;i++){
        p_prime[i] = Vec3::Zero;

        for(int j=0; j < PLANETS;j++)
            if(i != j){
                Vec3 dist = q[i] - q[j];
                p_prime[i] -= G_const * m[i] * m[j] * dist / pow(dist.mod(),3); 
            }
    }
}

void Simulation::calc_q_prime(){
    for(int i = 0; i < PLANETS;i++)
        q_prime[i] = p[i] / m[i];
}

double Simulation::H(){
    double ris = 0;

    for( int i=0; i < PLANETS;i++){
        ris += .5 / m[i] * p[i].mod2();

        for( int j=0; j < i; j++)
            ris += G_const * m[i] * m[j] / (q[i] - q[j]).mod();
    }

    return ris;
}
