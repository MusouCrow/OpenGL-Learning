#ifndef TIMER_H
#define TIMER_H

class Time {
public:
    static Time* GetInstance();
    float GetDeltaTime();
    int GetFPS();
    void Tick();
private:
    double dt = 0;
    double fpsTimer = 0;
    int fpsCount = 0;
    int fps = 0;
    clock_t nowClock = 0;
};

#endif