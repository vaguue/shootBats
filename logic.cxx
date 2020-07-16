#include "logic.h"

#define mk make_tuple
#define randDouble QRandomGenerator::global()->generateDouble()

Logic::Logic(size_t* w, size_t* h, QWidget* parent) : QFrame(parent), w{w}, h{h} {
    bulletTime.setInterval(tout);
    batTime.setInterval(tout);
    connect(&bulletTime, SIGNAL(timeout()), this, SLOT(timerEvent()));
    connect(&batTime, SIGNAL(timeout()), this, SLOT(batEvent()));
}

void Logic::initField() {

}

void Logic::initGun() {
    start.setX((*w)/2);
    start.setY(15);
    bulletTime.start();
    batTime.start();
    QTimer::singleShot(randDouble * spawnTreshold, this, &Logic::spawnerEvent);
}

void Logic::batEvent() {
    using namespace std;
    for (size_t i = 0; i < bats.size(); ++i) {
        //cout << i << " bat coordinates: " << bats[i].coord.x() << " " << bats[i].coord.x() << endl;
        auto x = bats[i].coord.x();  
        auto y = bats[i].coord.y();  
        if (y >= *h) {
            cout << "LOSED" << endl;
            emit losed();
        }
        else {
            //cout << "raw: " << x << " " << y << endl;
            //cout << "ceil: " << qCeil(x) << " " << qCeil(y) << endl;
            y += bats[i].Yspeed;
            bats[i].coord.setY(y);
            x = min(max(double{0+10}, x + bats[i].Xspeed*(randDouble-0.5)), double{*w-10});
            bats[i].coord.setX(x);
            bats[i].timeBuff += tout;
            if (bats[i].timeBuff >= bats[i].changeDelay) {
                bats[i].timeBuff = 0;
                bats[i].state = (bats[i].state + 1) % bats[i].maxState;
            }
        }

    }
}

void Logic::spawnerEvent() {
    using namespace std;
    cout << "lets spawn some bat " << randDouble*(*w) << endl;
    bats.push_back(Bat(QPointF(randDouble*(*w), 0), 10, 10));
    QTimer::singleShot(randDouble * spawnTreshold, this, &Logic::spawnerEvent);
}

void Logic::shoot(double angle) {
    using namespace std;
    cout << "shooted wirh angle: " << angle << endl;
    bullets.push_back(mk(start, 0, angle));
    cout << "bullets in the air: " << bullets.size() << endl;
}

void Logic::timerEvent() {
    using namespace std;
    vector<size_t> dead;
    for (size_t i = 0; i < bullets.size(); ++i) {
        auto& e     = bullets[i];
        auto& point = get<0>(e);
        auto x      = point.x();
        auto y      = point.y();
        auto& time  = get<1>(e);
        auto angle  = get<2>(e);
        if (x <= 0 || x >= *w || y <= 0 || y >= *h) {
            cout << "dead" << endl;
            dead.push_back(i);
        }
        else {
            bool ok = false;
            auto _x = x;
            auto _y = (*h) - y;
            for (size_t i = 0; i < bats.size(); ++i) {
                if ((_x >= bats[i].coord.x() - bats[i].hitW && _x <= bats[i].coord.x() + bats[i].hitW) 
                        && (_y >= bats[i].coord.y() - bats[i].hitH && _y <= bats[i].coord.y() + bats[i].hitH)) {
                    ok = true;
                    cout << "killed " << i << endl;
                    dead.push_back(i);
                    //TODO SIGNAL
                    bats.erase(bats.begin() + i);
                    break;
                }
            }
            if (!ok) {
                cout << "s*t*cos:" << qCos(angle) << endl;
                point.setX(x + speed * tout * qSin(angle));
                point.setY(y + speed * tout * qCos(angle) - 0.01*tout*tout); //TODO
                cout << "x, y inside timerEvent: " << get<0>(bullets[i]).x() << ' ' << get<0>(bullets[i]).y() << endl;
                time += tout;
            }
        }
    }
    emit movement();
    for (size_t i = 0; i < dead.size(); ++i) {
        bullets.erase(bullets.begin() + dead[i]);
        //TODO SIGNAL
    }
}

#undef mk
