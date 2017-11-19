/**
 * @file Timer.cpp
 * A class to provide timing routines
 * @author Jennifer Coy
 * @date Nov 2016
 */

#include "Timer.h"

// record the starting time, and set the boolean
void Timer::startTimer() throw(std::logic_error) {
    if (timer_running == true) {
        throw std::logic_error("Error:  Attempt to start a timer that was already running.");
    }
    startTime = std::chrono::high_resolution_clock::now();
    timer_running = true;
}

// record the ending time, and set the boolean
void Timer::stopTimer() throw(std::logic_error) {
    if (timer_running == false) {
        throw std::logic_error("Error:  Attempt to stop a timer that was not running.");
    }
    endTime = std::chrono::high_resolution_clock::now();
    timer_running = false;
}

// return time in microseconds
double Timer::elapsedTime() throw(std::logic_error) {
    if (timer_running == true) {
        throw std::logic_error("Error:  Attempt to measure a timer that is still running.");
    }
    return std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
}
