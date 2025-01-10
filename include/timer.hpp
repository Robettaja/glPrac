#pragma once
#include <chrono>
#include <string>
#include <vector>

class Timer
{
private:
    std::vector<std::chrono::time_point<std::chrono::steady_clock>> timing_points;
    std::string name;
public:
    Timer(std::string _name)
    {
        name = _name;
    }
    void start();
    void reset();
    void stop();
    size_t get_repeats();
};
