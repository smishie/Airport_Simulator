#ifndef SIMULATION_H
#define SIMULATION_H
#include <cstdlib>

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

using namespace std;

//---------------------- BOOL PROBABILITY ----------------------//
class bool_probability{
public:
    bool_probability(double t_p = 0.3, double l_p = 0.4); // CTOR
    bool takeoff_query() const;
    bool landing_query() const;

private:
    double takeoff_probability;
    double landing_probability;
};

//-------------------------- AVERAGER --------------------------//
class Averager{
public:
    Averager(); // CTOR
    void next_number(double value); 
    std::size_t how_many_numbers() const {return count; }
    double average() const;

private:
    std::size_t count;
    double sum;
};

//--------------------------- AIRPLANE ---------------------------//
class Airplane{
public:
    Airplane(); // CTOR
    Airplane(unsigned int takeoffTime, unsigned int landingTime, unsigned int totalTime, unsigned int fuelLimit);

    void one_second();
    void start_landing();
    void start_takeoff();

    bool runway_taken() const {return time_left > 0; }

    int get_fuel_limit(){return fuel_limit; }

private: 
    unsigned int takeoff_time = 15;
    unsigned int landing_time = 5;

    unsigned int total_time = 2000;
    unsigned int time_left = 0;

    unsigned int fuel_limit = 20;
};

#endif /* SIMULATION_H */