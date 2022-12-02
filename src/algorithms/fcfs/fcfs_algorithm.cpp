// Alex Curtis
#include "algorithms/fcfs/fcfs_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

// Tasks are scheduled in the order they are added to the ready queue
// Each runs until it's CPU burst finishes
// No preemption
// Priority ignored

FCFSScheduler::FCFSScheduler(int slice) {
    if (slice != -1) {
        throw("FCFS must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> FCFSScheduler::get_next_thread() {
        
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
            // Get the next thread to run from the front of ready queue
            decision->thread = this->ready->front();
            // Set explanation
            decision->explanation = fmt::format("Selected from {} threads. Will run to completion of burst.", this->size());
            // Pop thread from ready queue
            this->ready->pop();
        }
        
        return decision;
}

void FCFSScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
        // Push the thread onto the ready queue
        this->ready->push(thread);
}

size_t FCFSScheduler::size() const {
        // Return size of ready queue
        return this->ready->size();
}
