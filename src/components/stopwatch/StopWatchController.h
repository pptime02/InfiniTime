#pragma once

#include <FreeRTOS.h>
#include <timers.h>

#define LAP_CAPACITY 2

namespace Pinetime {
  namespace System {
    class SystemTask;
  }
  namespace Controllers {

    enum class StopWatchStates { Cleared, Running, Paused };

    struct LapInfo_t {
      int count = 0;       // Used to label the lap
      TickType_t time = 0; // Delta time from beginning of stopwatch
    };

    class StopWatchController {
    public:
      StopWatchController();

      // StopWatch functionality and data
      void Start();
      void Pause();
      void Clear();

      TickType_t GetElapsedTime();

      // Lap functionality

      /// Only the latest laps are stored, the lap count is saved until reset
      void PushLap();

      /// Returns actual count of stored laps
      int GetLapNum();

      /// Returns lapCount
      int GetLapCount();

      /// Indexes into lap history, with 0 being the latest lap.
      /// If the lap is unavailable, count and time will be 0. If there is a
      /// real value, count should be above 0
      LapInfo_t* LastLap(int lap = 0);

      bool IsRunning();
      bool IsCleared();
      bool IsPaused();

    private:
      // Current state of stopwatch
      StopWatchStates currentState = StopWatchStates::Cleared;
      // Start time of current duration
      TickType_t startTime = 0;
      // How much time was elapsed before current duration
      TickType_t timeElapsedPreviously = 0;
      // Stores lap times
      LapInfo_t laps[LAP_CAPACITY];
      LapInfo_t emptyLapInfo = {.count = 0, .time = 0};
      int lapCount = 0;
      int lapHead = 0;
    };
  }
}
