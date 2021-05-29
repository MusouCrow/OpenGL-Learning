#include <time.h>
#include "timer.h"
#include "common.h"

Time* Time::GetInstance() {
    static Time instance;

    return &instance;
}

float Time::GetDeltaTime() {
    return this->dt;
}

int Time::GetFPS() {
    return this->fps;
}

void Time::Tick() {
    clock_t lateClock = this->nowClock;
    this->nowClock = clock();
    this->dt = (double)(this->nowClock - lateClock) / CLOCKS_PER_SEC * 10;
    double less = 1.0 / 60.0;

    if (this-> dt < less) {
        this-> dt = less;
    }

    this->fpsTimer += this->dt;
    this->fpsCount++;

    if (this->fpsTimer >= 1) {
        this->fps = this->fpsCount;
        this->fpsCount = 0;
        this->fpsTimer -= 1;
    }
}
