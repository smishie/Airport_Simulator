#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "includes/airport/simulation.h"
#include "includes/queue/MyQueue.h"
#include "includes/stack/MyStack.h"

using namespace std;

void simulate_airport(bool debugAirport = false);

int main(int argv, char** argc) {

    cout << "\n\n==================================================" << endl;
    srand(time(0));
    bool debugAirport = true;

    for (int i=0; i<20; i++){
        cout << "-------------------- [" << i << "] -------------------------" << endl;
        simulate_airport(debugAirport);
    }
    simulate_airport(true);
    cout << "\n\n================= END SIMULATION =======================" << endl;
    return 0;
}

void simulate_airport(bool debugAirport){
    if(debugAirport){
        int landing_time, takeoff_time, total_time, fuel_limit;
        double takeoff_prob, landing_prob;
            
        cout << setw(22) << left << "time to land: ";
        cin >> landing_time;
        cout << setw(22) << left << "time to take off: ";
        cin >> takeoff_time;

        cout << setw(22) << left << "landing probability: ";
        cin >> landing_prob;
        cout << setw(22) << left << "takeoff probability: ";
        cin >> takeoff_prob;

        cout << setw(22) << left << "fuel limit: ";
        cin >> fuel_limit;
        cout << setw(22) << left << "total time: ";
        cin >> total_time;

        Queue<unsigned int> takeoff_queue; // takeoff airplane queue
        Queue<unsigned int> landing_queue; // landing airplane queue

        bool_probability arrival(takeoff_prob, landing_prob);  //.query: has a new car arrived?
        Airplane airplane(takeoff_time, landing_time, total_time, fuel_limit);
        
        Averager takeoff_wait;
        Averager landing_wait;
        unsigned int current_second;
        unsigned int planes_crashed = 0;
        unsigned int planes_landed = 0;
        unsigned int planes_tookoff = 0;

        for (current_second = 1; current_second <= total_time; ++current_second){   // Simulate the passage of one second of time.
            // if (debug){
            //     cout<<"-------------------------------------------"<<endl;
            //     cout<<"second: "<<current_second<<endl;
            // }

            if(arrival.landing_query()){ // Check whether there is a plane waiting to land
                landing_queue.push(current_second);
            }            
            
            
            if (arrival.takeoff_query()){ // Check whether there is a plane waiting to takeoff
                takeoff_queue.push(current_second);
            }

            // Check if there is an element in either landing or takeoff queue.
            // Check whether the runway is NOT taken.
            if ((!takeoff_queue.empty() || !landing_queue.empty())  &&  (!airplane.runway_taken())){
                // if (debug) cout<<"main(): machine is not busy: washing car.. ";
                // if (debug) cout<<"         car timestamp: "<<next<<endl;
                int popped;

                if(!landing_queue.empty()){
                    popped = landing_queue.pop();
                    planes_landed++;

                    landing_wait.next_number(current_second - popped);

                    if(current_second - popped >= airplane.get_fuel_limit())
                        planes_crashed++;                    
                    
                    airplane.start_landing();
                }
                else if(!takeoff_queue.empty()){ // no plane in landing queue
                    popped = takeoff_queue.pop();
                    planes_tookoff++;

                    takeoff_wait.next_number(current_second - popped);

                    airplane.start_takeoff();
                }

            }

            // Tell the washer to simulate the passage of one second.
            // if (debug) cout<<"main(): tell machine one second has passed..."<<endl;
            airplane.one_second( ); //advance the Washer object's timer by one unit
        }
        // Write the parameters to cout.
        cout << "\n. . . . . . . . . . . . . . . . . . . . . . ." << endl;
        cout << setw(22) << left << "Planes landed: " << planes_landed << endl;
        cout << setw(22) << left << "Planes took off: " << planes_tookoff << endl;
        cout << setw(22) << left << "Planes crashed: " << planes_crashed << "  :((" << endl;
        cout << setw(22) << left << "Average waiting time to land: " << int(landing_wait.average()) << endl;
        cout << setw(22) << left << "Aveage waiting time to takeoff: " << int(takeoff_wait.average()) << endl;
        cout << setw(22) << left << "Planes in landing queue: " << landing_queue.size() << endl;
        cout << setw(22) << left << "Planes in takeoff queue: " << takeoff_queue.size() << endl;

    }
}
