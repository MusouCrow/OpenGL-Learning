#include <time.h>
#include "timer.h"

Time* Time::GetInstance() {
    static Time instance;

    return &instance;
}

float Time::GetDeltaTime() {
    return this->dt;
}

void Time::Tick() {
    int lateClock = this->nowClock;
    this->nowClock = clock();
    this->dt = (double)(this->nowClock - lateClock) / CLOCKS_PER_SEC;
}
