#include "algorithms/priority/priority_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"


/*
    Here is where you should define the logic for the priority algorithm.
*/

PRIORITYScheduler::PRIORITYScheduler(int slice) {
    if (slice != -1) {
        throw("PRIORITY must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> PRIORITYScheduler::get_next_thread() {
    // Create decision to return
    std::shared_ptr<SchedulingDecision> decision = std::make_shared<SchedulingDecision>();
        
    // Set time slice
    decision->time_slice = -1;

    // if the queue is empty
    if(this->ready->empty()) {
        // Next thread is nullptr
        decision->thread = nullptr;
        // Set explanation
        decision->explanation = "No threads available for scheduling.";
    }
    // if not empty
    else {
        // Get the next thread to run from the front (top) of ready queue
        decision->thread = this->ready->top();

        // Determine counts of threads with same priority
        int priority_counts[4] = {0,0,0,0};
        
        // Copy the ready queue to a temporary queue
        // TODO find a more efficient way to do this
        ready_copy = std::make_shared<PriorityQueue>(*ready);

        // Iterate through the temporary queue
        while(!ready_copy->empty()) {
            // Increment each priority count
            priority_counts[ready_copy->top()->priority]++;
            // Pop the top thread
            ready_copy->pop();
        }

        // Copy the current priority array
        // std::shared_ptr<std::array<int,4>> priority_counts_after = std::make_shared<std::array<int,4>>(priority_counts);
        auto priority_counts_after = priority_counts;
        priority_counts_after[decision->thread->priority]--;

        // Set explanation
        // {S,I,N,B} = {0,1,2,3}
        decision->explanation = fmt::format("[S: {} I: {} N: {} B: {}] -> [S: {} I: {} N: {} B: {}]. Will run to completion of burst.", 
            priority_counts[0], priority_counts[1], priority_counts[2], priority_counts[3],
            priority_counts_after[0], priority_counts_after[1], priority_counts_after[2], priority_counts_after[3]);
        
        // Pop thread from ready queue
        this->ready->pop();
    }
    
    return decision;
}

void PRIORITYScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    // push with priority
    this->ready->push(thread->priority, thread);
}

size_t PRIORITYScheduler::size() const {
    
    return this->ready->size();
}
