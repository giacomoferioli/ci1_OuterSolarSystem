#include "Simulation.hpp"

Simulation::Simulation(const double* m, const double* v_q,Integrator integrator) : m(m), v_q(v_q), integrator(integrator), steps_done(0){
    switch(integrator){
        case EXPLICIT_EULER:
            max_steps = DEFAULT_EXPLICIT_EULER_ITERATIONS;
            break;
        case SYMPLECTIC_EULER:
            max_steps = DEFAULT_SYMPLECTIC_EULER_ITERATIONS;
            break;
        case STORMER_VERLET:
            max_steps = DEFAULT_STORMER_VERLET_ITERATIONS;
            break;
        default:
            max_steps = DEFAULT_MAX_ITERATIONS;
            break;
    }
    
    reset();
}

void Simulation::reset(){
    for(int i = 0; i < PLANETS;i++){
        p_q[i] = Vec3(
            v_q[3*i+0] * m[i],
            v_q[3*i+1] * m[i],
            v_q[3*i+2] * m[i]
        );

        p_q[6+i] = Vec3(
            v_q[3*PLANETS + 3*i+0],
            v_q[3*PLANETS + 3*i+1],
            v_q[3*PLANETS + 3*i+2]
        );
    }
    steps_done = 0;

    if(q_past != nullptr){
        delete[] q_past;
        q_past = nullptr;
    }
}

void Simulation::calc_p_prime(){
    for(int i = 0; i < PLANETS;i++){
        p_q_prime[i] = Vec3::Zero;

        for(int j=0; j < PLANETS;j++)
            if(i != j){
                Vec3 dist = p_q[PLANETS+i] - p_q[PLANETS+j];
                p_q_prime[i] -= G_const * m[i] * m[j] * dist / pow(dist.mod(),3); 
            }
    }
}

void Simulation::calc_q_prime(){
    for(int i = 0; i < PLANETS;i++)
        p_q_prime[PLANETS+i] = p_q[i] / m[i];
}

void Simulation::symplectic_euler(double h,unsigned int steps){
    for( unsigned int _i = 0; _i < steps; _i++){
        calc_p_prime();
        for(int i = 0;i<PLANETS;i++)
            p_q[i] += h * p_q_prime[i];
        calc_q_prime();
        for(int i = 0;i<PLANETS;i++)
            p_q[PLANETS+i] += h * p_q_prime[PLANETS+i];
    }
}

void Simulation::explicit_euler(double h, unsigned int steps){
    for( unsigned int _i = 0; _i < steps; _i++){
        calc_p_prime();
        calc_q_prime();
        for(int i = 0; i < PLANETS * 2;i++)
            p_q[i] += h * p_q_prime[i];
    }
}

void Simulation::stormer_verlet(double h, unsigned int steps){
    if( q_past == nullptr){
        q_past = new Vec3[PLANETS];
        for(uint i = 0; i < PLANETS;i++){
            q_past[i] = p_q[PLANETS+i];
            calc_p_prime();
            p_q[PLANETS + i] += p_q[i]/m[i]*h + p_q_prime[i] / ( 2 * m[i]) * h * h;
        }
        
    }
    
    Vec3 q_next;
    for( unsigned int _ = 0; _ < steps; _++){
        calc_p_prime();
        for( uint i = 0; i < PLANETS; i++){
            q_next = 2 * p_q[PLANETS+i] - q_past[i] + p_q_prime[i] / m[i] * h * h;
            p_q[i] = m[i] * (q_next-p_q[PLANETS+i]) / h;
            q_past[i] = p_q[PLANETS+i];
            p_q[PLANETS+i] = q_next;
        }
    }
    
}

void Simulation::step(double h, unsigned int steps){
    steps_done += steps;
    switch (integrator)
    {
        case SYMPLECTIC_EULER:
            symplectic_euler(h?h:DEFAULT_SYMPLECTIC_EULER_H,steps);
            break;
        case EXPLICIT_EULER:
            explicit_euler(h?h:DEFAULT_EXPLICIT_EULER_H,steps);
            break;
        case STORMER_VERLET:
            stormer_verlet(h?h:DEFAULT_STORMER_VERLET_H,steps);
            break;

    default:
        break;
    }
}


double Simulation::H(){
    double ris = 0;

    for( int i=0; i < PLANETS;i++){
        ris += .5 / m[i] * p_q[i].mod2();

        for( int j=0; j < i; j++)
            ris += G_const * m[i] * m[j] / (p_q[PLANETS+i] - p_q[PLANETS+j]).mod();
    }

    return ris;
}