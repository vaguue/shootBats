#include "logic.h"

#define F first
#define S second
#define mk make_pair

Logic::Logic(size_t* w, size_t* h) : w{w}, h{h} {
    bulletTime.setInterval(tout);
}

void Logic::initField() {
    field.resize(*w);
    for (size_t i = 0; i < *w; ++i) {
        field[i].resize(*h);
        field[i][0] = true;
        field[i][*h-1] = true;
    }
    for (size_t i = 0; i < *h; ++i) {
        field[0][i] = true;
        field[*w-1][i] = true;
    }
}

void Logic::initGun() {
    bulletTime.start();
}

void Logic::shoot(double angle) {
    using namespace std;
    bullets.push_back(mk(start, 0));
}

void Logic::timerEvent(QTimerEvent* event) {
if (event->timerId() == bulletTime.timerId()) {
    for (size_t i = 0; i < bullets.size(); ++i) {
        auto& e = bullets[i];
        e.S += tout;
        e.F.setY(e.F.y() + )
    }
}
}

#undef F
#undef S
#undef mk
