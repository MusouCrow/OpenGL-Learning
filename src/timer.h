#ifndef TIMER_H
#define TIMER_H

class Time {
public:
    static Time* GetInstance();
    float GetDeltaTime();
    void Tick();
private:
    float dt = 0;
    int nowClock = 0;
};

#endif