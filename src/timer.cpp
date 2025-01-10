#include "timer.hpp"

#include <chrono>
#include <format>
#include <string>

#include "logger.hpp"

void Timer::start()
{
    timing_points.emplace(timing_points.begin(), std::chrono::high_resolution_clock::now());
}
void Timer::reset()
{
    timing_points.emplace_back(std::chrono::high_resolution_clock::now());
}
void Timer::stop()
{
    std::chrono::microseconds micros = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - timing_points.at(0));
    std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - timing_points.at(0));

    std::string avg_micros = std::to_string(micros.count() / std::max<size_t>(get_repeats(), 1));
    std::string avg_millis = std::to_string(millis.count() / std::max<size_t>(get_repeats(), 1));
    std::string format_out =
        std::format("[{}] Measured {} + 1 timing points | Total: {}us ({}ms), Average: {}us ({}ms)", name,
                    get_repeats(), micros.count(), millis.count(), avg_micros, avg_millis);
    logger::log_debug(format_out);
    timing_points.clear();
}
size_t Timer::get_repeats()
{
    return timing_points.size() - 1;
}
