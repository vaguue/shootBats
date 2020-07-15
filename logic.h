#include <iostream>
#include <vector>
#include <utility>
#include <QTimer>
#include <QPoint>
#include <QFrame>
#include <QRandomGenerator>
#include <QtMath>
#include <QTimerEvent>
#include "bat.h"

struct Logic : public QFrame {
    Q_OBJECT
signals:
    void movement();
    void losed();
public:
    std::vector<std::tuple<QPointF, double, double>> bullets;
    std::vector<Bat> bats;
    int tout = 20;
    int spawnTreshold = 1000;
    double speed = 0.4;
    size_t* h;
    size_t* w;
    QPointF start;
    QTimer bulletTime;
    QTimer batTime;
    Logic(size_t* h, size_t* w, QWidget* parent = nullptr);
    void initField();
    void initGun();
    void shoot(double angle);
public slots:
//    void timerEvent(QTimerEvent*);
    void timerEvent();
    void spawnerEvent();
    void batEvent();
};
