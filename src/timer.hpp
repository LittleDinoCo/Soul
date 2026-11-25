#pragma once
#include <algorithm>
class Timer {
    private:
        float duration = 0.f;
        float remaining = 0.f;
        bool ticking = false;
    public:
        void start(float dur) {
            duration = dur;
            remaining = dur;
            ticking = true;
        }
        void tick(float dt) {
            if (ticking == true && remaining > 0.f) {
                remaining -= dt;
                remaining = std::max(remaining, 0.f);
            }
        }
        float read() const {
            return remaining;
        }
        void adjust(float adjustment) {
            if (remaining + adjustment >= 0) {
                remaining += adjustment;
                return;
            }
            remaining = 0;
        }
        void pause() {
            ticking = false;
        }
        void resume() {
            ticking = true;
        }
        void stop() {
            remaining = 0;
            duration = 0;
            ticking = false;
        }
};
