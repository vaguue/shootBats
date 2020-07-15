#include <iostream>
#include <chrono>
#include <sstream>
#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsItem>
#include <QSlider>
#include <QProgressBar>
#include <QMouseEvent>
#include <QtMath>
#include <QMessageBox>
#include "logic.h"


struct Background : public QWidget {
    Q_OBJECT
    size_t height = 600, width = 430;
    bool pressed = false;
    std::chrono::time_point<std::chrono::system_clock> startTime;
    QPushButton* btn;
    QPixmap* img;
    QPixmap* gun;
    QPixmap* curGun;
    QPixmap* bullet;
    QPixmap* bat;
    double gunAngle = M_PI_2;
    double rotateGun(int,int);
    Logic* eL;
public slots:
    void redrawBullets();
    void finish();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
public:
    Background(QWidget*);
    ~Background();
};
