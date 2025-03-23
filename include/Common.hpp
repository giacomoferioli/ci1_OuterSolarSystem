#include <SFML/Graphics.hpp>

#ifndef COMMON_DATA_TYPES
#define COMMON_DATA_TYPES

/*##############
# PHYSICS DATA #
##############*/
#define G_const 2.95912208286e-4
#define PLANETS 6
inline double m[PLANETS] = {1.00000597682,9.54786104043e-4, 2.85583733151e-4, 4.37273164546e-5, 5.17759138449e-5, 1.3e-8};
//m_q inizialmente contiene v_q, va aggiornato
inline double v_q[6*PLANETS]={
    0,0,0,
    0.00565429,-0.00412490,-0.00190589, //v0 giove
    0.00168318,0.00483525,0.00192462,
    0.00354178,0.00137102,0.00055029,
    0.00288930,0.00114527,0.00039677,
    0.00276725,-0.00170702,-0.00136504,
    0,0,0,
    -3.5023653,-3.8169847,-1.5507963,   //q0 giove
    9.0755314,-3.0458353,-1.6483708,
    8.3101420,-16.2901086,-7.2521278,
    1.4707666,-25.7294829,-10.8169456,
    -15.5387357,-25.2225594,-3.1902382
};

/*
###################
# INTEGRATOR DATA #
###################
*/

enum Integrator{
    EXPLICIT_EULER,
    SYMPLECTIC_EULER
};

#define DEFAULT_MAX_ITERATIONS 1000

#define DEFAULT_EXPLICIT_EULER_ITERATIONS 50000
#define DEFAULT_EXPLICIT_EULER_H 10

#define DEFAULT_SYMPLECTIC_EULER_ITERATIONS 3000
#define DEFAULT_SYMPLECTIC_EULER_H 100


inline unsigned int steps_done = 0;

/*
###############
# RENDER DATA #
###############
*/

#define FRAMELENGTH 25
#define ANGLUAR_MOVEMENT_INCREMENT 0.03
inline unsigned int colors[6] = {0xFFFFFFFF, 0xFF4D00FF,0xFFdF00FF,0x4444FFFF,0x0000FFFF,0x888888FF}; 

#define SIZE 800
#define DRAWRANGE 50

#define KEY(x) sf::Keyboard::x
#define ISDOWN(key) sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key)


#define ANGULAR_SPEED M_PI

#define GRAPH_PADDING 20


#endif