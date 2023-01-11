#ifndef LOGIC_STOPWATCH_HPP
#define LOGIC_STOPWATCH_HPP

#include <chrono>
#include <memory>
#include <mutex>

namespace Logic {

struct Clock {
    using duration = std::chrono::milliseconds;
    using rep = duration::rep;
    using period = duration::period;
    using time_point = std::chrono::time_point<Clock>;
    static constexpr bool is_steady = true;
};

class Stopwatch {
public:
    Stopwatch(Stopwatch& other) = delete;      // Singleton pattern does not allow cloning
    void operator=(const Stopwatch&) = delete; // Singleton pattern does not allow assinging

    static std::shared_ptr<Stopwatch> getStopwatch();

    void restart();
    bool behind(const double dt);

    Stopwatch();
    ~Stopwatch() = default;

private:
    static std::shared_ptr<Stopwatch> stopwatch_;
    static std::mutex mutex_; // Used to make threadsafe

    std::chrono::time_point<std::chrono::steady_clock> mLastUpdateTime;
    double mUpdateElapsedTime = 0.0;
    bool mLocked = false;
};
} // namespace Logic

#endif
