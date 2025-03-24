#include "Common.hpp"
#include "Vector.hpp"

#ifndef SIM
#define SIM


class Simulation{
    private:
        double H0;
    protected:
        const double* m;
        const double* v_q;
    
        unsigned int steps_done;
        unsigned int max_steps;
        double h;

        Vec3 p[PLANETS];
        Vec3 q[PLANETS];
        Vec3 p_prime[PLANETS];
        Vec3 q_prime[PLANETS];

        void calc_p_prime();
        void calc_q_prime();

        virtual void init() {};
    public:
        Simulation(const double* m, const double* v_q,unsigned int max_steps = DEFAULT_MAX_ITERATIONS, double h = DEFAULT_H);

        virtual void step() = 0;
        void reset();

        bool isDone() { return steps_done >= max_steps; }
        unsigned int getStepsDone() {return steps_done;}
        unsigned int getMaxSteps() {return max_steps;}
        double getTimeStep() {return h;}

        void setMaxSteps(unsigned int steps) {max_steps = steps;}
        void setTimeStep(double h) {this->h = h;}

        Vec3 getPlanetPos(unsigned int ix) const {return q[ix] - q[0];}; //ritorna la pos relativa al sole
        
        double H();
        double H_rel() {return H() / H0;};

        virtual std::string toString(){
            return (std::stringstream() << "-h="<<h<<"-steps="<<max_steps).str();
        }
};

#endif