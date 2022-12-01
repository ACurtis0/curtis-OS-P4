#include "algorithms/spn/spn_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

// Tasks are scheduled in order of their next CPU burst(from smallest to largest)
// Tasks run until their CPU burst is completed

// No preemption
// Process priority ignored, but queue prioritized by burst length

SPNScheduler::SPNScheduler(int slice) {
    if (slice != -1) {
        throw("SPN must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> SPNScheduler::get_next_thread() {
    
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
        // Set explanation
        decision->explanation = fmt::format("Selected from {} threads; will run to completion of burst.", this->size());
        // Pop thread from ready queue
        this->ready->pop();
    }
    
    return decision;
}

void SPNScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    // Priority based on cpu burst length
    this->ready->push(thread->get_next_burst(BurstType::CPU)->length, thread);
}

size_t SPNScheduler::size() const {
    return this->ready->size();
}
