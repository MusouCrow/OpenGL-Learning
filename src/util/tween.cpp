#include <math.h>
#include "tween.h"

float LinearFunc(float clock, float time, float range, float from) {
    return range * clock / time + from;
}

float InQuadFunc(float clock, float time, float range, float from) {
    return range * pow(clock / time, 2) + from;
}

float OutQuadFunc(float clock, float time, float range, float from) {
    float rate = clock / time;

    return -range * rate * (rate - 2) + from;
}

float InOutQuadFunc(float clock, float time, float range, float from) {
    float rate = clock / time * 2;

    if (rate < 1) {
        return range * 0.5f * pow(rate, 2) + from;
    }

    return -range * 0.5f * ((rate - 1) * (rate - 3) - 1) + from;
}

float OutInQuadFunc(float clock, float time, float range, float from) {
    range *= 0.5f;

    if (clock < time * 0.5f) {
        return OutQuadFunc(clock * 2, time, range, from);
    }

    return InQuadFunc((clock * 2) - time, time, range, from + range);
}

Tween::Tween(function<void()> OnTween) {
    this->from = 0;
    this->to = 0;
    this->value = 0;
    this->time = 0;
    this->clock = 0;
    this->easing = Easing::Linear;
    this->isRunning = false;
    this->OnTween = OnTween;
    
    this->easingFuncs[Easing::Linear] = LinearFunc;
    this->easingFuncs[Easing::InQuad] = InQuadFunc;
    this->easingFuncs[Easing::OutQuad] = OutQuadFunc;
    this->easingFuncs[Easing::InOutQuad] = InOutQuadFunc;
    this->easingFuncs[Easing::OutInQuad] = OutInQuadFunc;
}

void Tween::Update(float dt) {
    if (!this->IsRunning()) {
        return;
    }

    this->clock += dt;

    if (this->clock > this->time) {
        this->clock = this->time;
    }

    this->Adjust();
}

void Tween::Enter(float from, float to, float time, Easing easing) {
    this->isRunning = true;
    this->from = from;
    this->to = to;
    this->time = time;
    this->easing = easing;

    this->Adjust();
}

void Tween::Exit() {
    this->isRunning = false;
}

void Tween::Adjust() {
    this->value = this->easingFuncs[this->easing](this->clock, this->time, this->GetRange(), this->from);

    if (this->OnTween) {
        this->OnTween();
    }
}

float Tween::GetValue() {
    return this->value;
}

float Tween::GetRange() {
    return this->to - this->from;
}

float Tween::GetTime() {
    return this->time;
}

float Tween::GetClock() {
    return this->clock;
}

float Tween::GetRate() {
    return this->clock / this->time;
}

Easing Tween::GetEasing() {
    return this->easing;
}

bool Tween::IsRunning() {
    return this->isRunning && this->clock < this->time;
}