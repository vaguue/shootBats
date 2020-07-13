#include <iostream>
#include <vector>
#include <utility>
#include <QTimer>
#include <QPoint>
#include <QRandomGenerator>
#include <QtMath>
#include <QTimerEvent>

struct Logic {
    std::vector<std::vector<bool>> field; 
    std::vector<std::tuple<QPointF, double, double>> bullets;
    int tout = 70;
    int speed = 1;
    size_t* h;
    size_t* w;
    QPointF start;
    QTimer bulletTime;
    Logic(size_t* h, size_t* w);
    void initField();
    void initGun();
    void shoot(double angle);
    void timerEvent(QTimerEvent*);
};
