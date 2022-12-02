// Alex Curtis
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
    
    // Reset priority count array back to {0,0,0,0}
    this->priority_counts[0] = {0};
    this->priority_counts[1] = {0};
    this->priority_counts[2] = {0};
    this->priority_counts[3] = {0};

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
       

        // Determine counts of threads with same priority

        // Copy the ready queue to a temporary queue (I added braces to create a scope so the copy dies)
        {
        auto ready_copy = std::make_shared<PriorityQueue>(*ready);

        // Iterate through the temporary queue
        while(!ready_copy->empty()) {
            // Increment each priority count
            this->priority_counts[ready_copy->top()->priority]++;
            // Pop the top thread
            ready_copy->pop();
        }
        }

        // Get the next thread to run from the front (top) of ready queue
        decision->thread = this->ready->top();
        
        // Copy the priority array
        int priority_counts_after[4] = {this->priority_counts[0], this->priority_counts[1], this->priority_counts[2], this->priority_counts[3]};

        // Determine future priority array
        priority_counts_after[decision->thread->priority]--;

        // Set explanation
        // {S,I,N,B} = {0,1,2,3}
        decision->explanation = fmt::format("[S: {} I: {} N: {} B: {}] -> [S: {} I: {} N: {} B: {}]. Will run to completion of burst.", 
            this->priority_counts[0], this->priority_counts[1], this->priority_counts[2], this->priority_counts[3],
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
