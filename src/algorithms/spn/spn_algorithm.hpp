// Alex Curtis
#ifndef SPN_ALGORITHM_HPP
#define SPN_ALGORITHM_HPP

#include <memory>
#include "algorithms/scheduling_algorithm.hpp"
#include "utilities/stable_priority_queue/stable_priority_queue.hpp"

/*
    SPNScheduler:
        A representation of a scheduling queue that uses first-come, first-served logic.
        
        This is a derived class from the base scheduling algorithm class.

        You are free to add any member functions or member variables that you
        feel are helpful for implementing the algorithm.
*/

class SPNScheduler : public Scheduler {
public:

    //==================================================
    //  Member variables
    //==================================================

    // TODO: Add any member variables you may need.

    // Ready queue (PRIORITY queue of Thread pointers)
    // From fcfs: std::shared_ptr<std::queue<std::shared_ptr<Thread>>> ready = std::make_shared<std::queue<std::shared_ptr<Thread>>>();

    std::shared_ptr<Stable_Priority_Queue<std::shared_ptr<Thread>>> ready = std::make_shared<Stable_Priority_Queue<std::shared_ptr<Thread>>>();

    //==================================================
    //  Member functions
    //==================================================

    SPNScheduler(int slice = -1);

    std::shared_ptr<SchedulingDecision> get_next_thread();

    void add_to_ready_queue(std::shared_ptr<Thread> thread);

    size_t size() const;

};

#endif
