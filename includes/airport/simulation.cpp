#include "simulation.h"
#include <assert.h>

using namespace std;

//---------------------- BOOL PROBABILITY ----------------------//
bool_probability::bool_probability(double t_p, double l_p){ // CTOR
    assert(t_p >= 0 && t_p <= 1 && "takeoff probability must be in between 0-1");
    assert(l_p >= 0 && l_p <= 1 && "landing probability must be in between 0-1");
    takeoff_probability = t_p;
    landing_probability = l_p;
}

bool bool_probability::takeoff_query() const{
    return (rand() < takeoff_probability * RAND_MAX);
}

bool bool_probability::landing_query() const{
    return (rand() < landing_probability * RAND_MAX);
}

//-------------------------- AVERAGER --------------------------//
Averager::Averager(){ // CTOR
    count = 0;
    sum = 0;
}

void Averager::next_number(double value){
    sum += value;
    count++;
}

double Averager::average() const{
    assert(count > 0 && "to take average, must have at least one input");
    return sum / count;
}

//--------------------------- AIRPORT ---------------------------//
Airplane::Airplane(){
    takeoff_time = 0;
    landing_time = 0;
}

Airplane::Airplane(unsigned int takeoffTime, unsigned int landingTime, unsigned int totalTime, unsigned int fuelLimit){
    takeoff_time = takeoffTime;
    landing_time = landingTime;
    total_time = totalTime;
    fuel_limit = fuelLimit;
}

void Airplane::one_second(){
    if(runway_taken())
        time_left--;
}

void Airplane::start_landing(){
    assert(!runway_taken() && "cannot start landing while runway is taken");
    time_left = landing_time;
}

void Airplane::start_takeoff(){
    assert(!runway_taken() && "cannot start takeoff while runway is taken");
    time_left = takeoff_time;
}