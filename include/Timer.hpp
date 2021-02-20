#include <chrono>

class Timer {
  using clock = std::chrono::high_resolution_clock;
  using duration = std::chrono::duration<double>;

 private:
  std::chrono::time_point<clock> startTime;

 public:
  double elapsed() const {
    return duration(clock::now() - startTime).count();
  }

  void reset() {
    startTime = clock::now();
  }

  void start() {
    reset();
  }
};