#include "include/Stopwatch.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>

using namespace Logic;

std::shared_ptr<Stopwatch> Stopwatch::stopwatch_{nullptr};
std::mutex Stopwatch::mutex_;

Stopwatch::Stopwatch() {}

std::shared_ptr<Stopwatch> Stopwatch::getStopwatch() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (stopwatch_ == nullptr) {
        stopwatch_ = std::make_shared<Stopwatch>();
        stopwatch_->mLastUpdateTime = std::chrono::steady_clock::now();
        return stopwatch_;
    }
    return stopwatch_;
}

void Stopwatch::restart() { stopwatch_->mLastUpdateTime = std::chrono::steady_clock::now(); }

bool Stopwatch::behind(const double dt) {
    if (mLocked) {
        if (mUpdateElapsedTime > dt) {
            mUpdateElapsedTime -= dt;
            return true;
        }
        mLocked = false;
        restart();
    } else {
        auto temp = std::chrono::steady_clock::now();
        mUpdateElapsedTime += (temp - mLastUpdateTime).count();
        if (mUpdateElapsedTime > dt) {
            mLocked = true;
            mUpdateElapsedTime -= dt;
            return true;
        } else {
            stopwatch_->mLastUpdateTime = temp;
        }
    }
    // std::cout << mUpdateElapsedTime << "Elapsed time\n" << mLastUpdateTime.co << "Last Update Time\n";
    return false;
}