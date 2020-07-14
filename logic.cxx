#include "logic.h"

#define mk make_tuple

Logic::Logic(size_t* w, size_t* h, QWidget* parent) : QFrame(parent), w{w}, h{h} {
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
    start.setX(*w/2);
    start.setY(0);
    bulletTime.start();
}

void Logic::shoot(double angle) {
    using namespace std;
    bullets.push_back(mk(start, 0, angle));
}

void Logic::timerEvent(QTimerEvent* event) {
    using namespace std;
if (event->timerId() == bulletTime.timerId()) {
    vector<size_t> dead;
    for (size_t i = 0; i < bullets.size(); ++i) {
        auto& e = bullets[i];
        auto& point = get<0>(e);
        auto x = point.x();
        auto y = point.y();
        auto time = get<1>(e);
        auto angle = get<2>(e);
        if (field[qCeil(x)][qCeil(y)]) {
            dead.push_back(i);
        }
        else {
            point.setX(speed * time * qCos(angle));
            point.setY(speed * time * qSin(angle) - 3*time*time); //TODO
            get<2>(e) += tout/1000;
        }
    }
    //TODO SIGNAL
    for (size_t i = 0; i < dead.size(); ++i) {
        bullets.erase(bullets.begin() + dead[i]);
        //TODO SIGNAL
    }
}
}

#undef mk
