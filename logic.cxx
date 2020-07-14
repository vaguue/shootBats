#include "logic.h"

#define mk make_tuple

Logic::Logic(size_t* w, size_t* h, QWidget* parent) : QFrame(parent), w{w}, h{h} {
    bulletTime.setInterval(tout);
    connect(&bulletTime, SIGNAL(timeout()), this, SLOT(timerEvent()));
}

void Logic::initField() {
    field.resize(*w);
    std::cout << "initializing field " << *w << 'x'<< *h << std::endl;
    for (size_t i = 0; i < *w; ++i) {
        field[i].resize(*h);
        //field[i][0] = true;
        //field[i][*h-1] = true;
    }
    for (size_t i = 0; i < *h; ++i) {
        //field[0][i] = true;
        //field[*w-1][i] = true;
    }
}

void Logic::initGun() {
    start.setX((*w)/2);
    start.setY(10);
    bulletTime.start();
}

void Logic::shoot(double angle) {
    using namespace std;
    cout << "shooted wirh angle: " << angle << endl;
    bullets.push_back(mk(start, 0, angle));
    cout << "bullets in the air: " << bullets.size() << endl;
}

//void Logic::timerEvent(QTimerEvent* event) {
void Logic::timerEvent() {
    using namespace std;
    vector<size_t> dead;
    for (size_t i = 0; i < bullets.size(); ++i) {
        auto& e = bullets[i];
        auto& point = get<0>(e);
        auto x = point.x();
        auto y = point.y();
        auto& time = get<1>(e);
        auto angle = get<2>(e);
        if (x <= 0 || x >= *w || y <= 0 || y >= *h) {
            cout << "dead" << endl;
            dead.push_back(i);
        }
        else {
            cout << "s*t*cos:" << qCos(angle) << endl;
            point.setX(x + speed * tout * qSin(angle));
            point.setY(y + speed * tout * qCos(angle) - 0.01*tout*tout); //TODO
            cout << "x, y inside timerEvent: " << get<0>(bullets[i]).x() << ' ' << get<0>(bullets[i]).y() << endl;
            time += tout;
        }
    }
    emit movement();
    for (size_t i = 0; i < dead.size(); ++i) {
        bullets.erase(bullets.begin() + dead[i]);
        //TODO SIGNAL
    }
//    bulletTime.start();
}

#undef mk
