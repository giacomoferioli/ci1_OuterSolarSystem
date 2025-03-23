#include "Common.hpp"
#include "Vector.hpp"

#ifndef SIM
#define SIM


class Simulation{
    const double* m;
    const double* v_q;
    Integrator integrator;
    unsigned int steps_done;
    unsigned int max_steps;

    Vec3 p_q[2*PLANETS];
    Vec3 p_q_prime[2*PLANETS];

    private:
        void calc_p_prime();
        void calc_q_prime();

        void symplectic_euler(double h,unsigned int steps);
        void explicit_euler(double h,unsigned int steps);

    public:
        Simulation(const double* m, const double* v_q,Integrator integrator);

        void reset();
        bool done() { return steps_done >= max_steps; };
        unsigned int steps() {return steps_done;};
        unsigned int maxSteps() {return max_steps;};
        
        void setMaxSteps(unsigned int steps) {max_steps = steps;};
        Vec3 getPlanetPos(unsigned int ix) const {return p_q[PLANETS+ix] - p_q[PLANETS];}; //ritorna la pos relativa al sole
        

        void step(double h=0,unsigned int steps=1);


        double H();
};

#endif