/**
 * @file Timer.h
 * A class to provide timing routines
 * @author Jennifer Coy
 * @date Nov 2016
 */

#ifndef TIMER_H
#define TIMER_H

#include <chrono>       // for high_resolution_clock
#include <stdexcept>    // for exception handling

class Timer {

private:
    bool timer_running = false;                                                     // is the timer running?
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;          // the starting time
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;            // the ending time

public:
    /**
     * Record the starting time.
     * @throws logic_error if timer has already started
     */
    void startTimer() throw(std::logic_error);

    /**
     * Record the ending time.
     * @throws logic_error if timer has has not been started
     */
    void stopTimer() throw(std::logic_error);

    /**
     * Returns the elapsed time in microseconds
     * @return the elapsed time (microseconds)
     * @throws logic_error if timer has has not been stopped before measuring
     */
    double elapsedTime() throw(std::logic_error);
};

#endif //TIMER_H
