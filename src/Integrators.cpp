#include "Integrators.hpp"

void ExplicitEuler::step(){
    steps_done++;

    calc_p_prime(); //calcola la p primo e lo salva nel buffer Vec3 p_prime[6]
    calc_q_prime();
    for(int i = 0; i < PLANETS;i++){ //aggiorna p e q, h è il passo temporale
        p[i] += h * p_prime[i];
        q[i] += h * q_prime[i];
    }
}

void SymplecticEuler::step(){
    steps_done++;

    calc_p_prime();
    for(int i = 0;i<PLANETS;i++)
        p[i] += h * p_prime[i];
    calc_q_prime();
    for(int i = 0;i<PLANETS;i++)
        q[i] += h * q_prime[i];
}

void StormerVerlet::init(){
    //calcola q1 partendo da q0
    for(uint i = 0; i < PLANETS;i++){
        q_past[i] = q[i];
        calc_p_prime();
        q[i] += p[i]/m[i]*DEFAULT_STORMER_VERLET_H + p_prime[i] / 
            ( 2 * m[i]) * DEFAULT_STORMER_VERLET_H * DEFAULT_STORMER_VERLET_H;
    }    
}

void StormerVerlet::step(){
    steps_done++;

    Vec3 q_next;
    calc_p_prime();
    for( uint i = 0; i < PLANETS; i++){
        q_next = 2 * q[i] - q_past[i] + p_prime[i] / m[i] * h * h;
        p[i] = m[i] * (q_next-q[i]) / h;
        q_past[i] = q[i];
        q[i] = q_next;
    }
}

