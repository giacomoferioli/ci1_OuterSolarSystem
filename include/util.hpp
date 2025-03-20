#include <chrono>
#include <SFML/Window/Keyboard.hpp>

#ifndef UTIL
#define UTIL

using namespace std::chrono;
inline long ms(){
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

inline bool checkKey(sf::Keyboard::Key k){
    static int keystates = 0;
    bool ans = false;
    if(sf::Keyboard::isKeyPressed(k)){
        if((keystates & 1 << (k - sf::Keyboard::A)) == 0)
            ans = true;
        keystates |= 1 << (k - sf::Keyboard::A);
    }
    else{
        keystates &= 0xFFFFFFFF ^ (1 << (k - sf::Keyboard::A));
    }
    return ans;
}

inline double ipol(double input_lowerbound, double input_upperbound, double output_lowerbound,double output_upperbound, double v){
    double t = (v - input_lowerbound) / (input_upperbound - input_lowerbound);
    return output_lowerbound * ( 1.0 - t ) + t * output_upperbound;
}

#endif