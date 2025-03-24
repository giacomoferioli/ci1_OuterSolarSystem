#include "math.h"
#include "Common.hpp"
#include "Simulation.hpp"

#ifndef INTEGRATORS
#define INTEGRATORS

class ExplicitEuler : public Simulation{
    public:
    ExplicitEuler(const double* m, const double* v_q) : Simulation(m,v_q,DEFAULT_EXPLICIT_EULER_ITERATIONS,DEFAULT_EXPLICIT_EULER_H) {};

    void step() override;

    std::string toString() override {return "ExplicitEuler" + Simulation::toString();}
};

class SymplecticEuler : public Simulation{
    public:
        SymplecticEuler(const double* m, const double* v_q) : Simulation(m,v_q,DEFAULT_SYMPLECTIC_EULER_ITERATIONS,DEFAULT_SYMPLECTIC_EULER_H) {};

    void step() override;

    std::string toString() override {return "SymplecticEuler" + Simulation::toString();}
};

class StormerVerlet : public Simulation{
    private:
        Vec3 q_past[PLANETS];

        void init() override;

    public:
        StormerVerlet(const double* m, const double* v_q) : Simulation(m,v_q,DEFAULT_STORMER_VERLET_ITERATIONS,DEFAULT_STORMER_VERLET_H) {};

    void step() override;

    std::string toString() override {return "StormerVerlet" + Simulation::toString();}
};


#endif