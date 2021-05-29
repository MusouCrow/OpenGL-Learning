#ifndef UTIL_TWEEN_H
#define UTIL_TWEEN_H

#include <map>
#include <functional>
#include "../common.h"

enum Easing {
    Linear, InQuad, OutQuad, InOutQuad, OutInQuad
};

class Tween {
public:
    Tween(function<void()> OnTween);
    void Update(float dt);
    void Enter(float from, float to, float time, Easing easing);
    void Exit();
    float GetValue();
    float GetRange();
    float GetTime();
    float GetClock();
    float GetRate();
    Easing GetEasing();
    bool IsRunning();
    
    float from;
    float to;
    function<void()> OnTween;
private:
    void Adjust();

    float value;
    float time;
    float clock;
    Easing easing;
    bool isRunning;
    map<Easing, function<float(float, float, float, float)>> easingFuncs;
};

#endif