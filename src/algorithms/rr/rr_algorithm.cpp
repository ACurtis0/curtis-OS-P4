#include "algorithms/rr/rr_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

// Tasks are scheduled in the order they are added to the ready queue

/* Tasks are preempted if their CPU burst length is greater than the time slice
In the event of a preemption:
    a. Remove task from CPU
    b. Update the task's burst length with the additional CPU time
    c. Add the task to the back of the ready queue.
*/
// Priority ignored

RRScheduler::RRScheduler(int slice) {    
    //TODO Implement me
}

std::shared_ptr<SchedulingDecision> RRScheduler::get_next_thread() {
    // Create decision to return
    std::shared_ptr<SchedulingDecision> decision = std::make_shared<SchedulingDecision>();
        
    // TODO Set time slice
    //decision->time_slice = ;

    // if the queue is empty
    if(this->ready->empty()) {
        // Next thread is nullptr
        decision->thread = nullptr;
        // Set explanation
        decision->explanation = "No threads available for scheduling.";
    }
    // if not empty
    else {
        
        // TODO finish this
        decision->explanation = fmt::format("Selected from {} threads. Will run for at most {} ticks.", this->size(), this->time_slice);

        // if burst length is greater than time slice, preempt
        //if(decision->thread->current_burst()->length > this->time_slice) {}

    }
    
    return decision;
}

void RRScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    this->ready->push(thread);
}

size_t RRScheduler::size() const {
    return this->ready->size();
}
