#include <iostream>
#include <vector>
#include <utility>
#include <QTimer>
#include <QPoint>
#include <QFrame>
#include <QRandomGenerator>
#include <QtMath>
#include <QTimerEvent>

struct Logic : public QFrame {
    Q_OBJECT
signals:
    void movement();
public:
    std::vector<std::vector<bool>> field; 
    std::vector<std::tuple<QPointF, double, double>> bullets;
    int tout = 20;
    double speed = 0.4;
    size_t* h;
    size_t* w;
    QPointF start;
    QTimer bulletTime;
    Logic(size_t* h, size_t* w, QWidget* parent = nullptr);
    void initField();
    void initGun();
    void shoot(double angle);
public slots:
//    void timerEvent(QTimerEvent*);
    void timerEvent();
};
