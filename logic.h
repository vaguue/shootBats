#include <iostream>
#include <vector>
#include <utility>
#include <QTimer>
#include <QRandomGenerator>
#include <QtMath>

struct Logic {
    std::vector<std::vector<bool>> field; 
    std::vector<std::<QPoint, int>> bullets;
    int tout = 70;
    int speed = 1;
    size_t* h;
    size_t* w;
    QPoint start;
    QTimer bulletTime;
    Logic(size_t* h, size_t* w);
    void initField();
    void initGun();
    void shoot(double angle);
    void timerEvent(QTimerEvent*);
};
