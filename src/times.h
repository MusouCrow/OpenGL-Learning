#ifndef TIMES_H
#define TIMES_H

#include <time.h>

class Time {
public:
    static Time* GetInstance();
    float GetDeltaTime();
    int GetFPS();
    void Tick();
    int targetFPS = 60;
private:
    double dt = 0;
    double fpsTimer = 0;
    int fpsCount = 0;
    int fps = 0;
    clock_t nowClock = 0;
};

#endif