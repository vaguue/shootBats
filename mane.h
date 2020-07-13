#include <iostream>
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


struct Background : public QWidget {
    Q_OBJECT
    size_t height = 600, width = 430;
    bool pressed=false, init=false;
    QPushButton* btn;
    QPixmap* img;
    QPixmap* gun;
    QPixmap* curGun;
    double gunAngle = M_PI_2;
    void rotateGun(int,int);
public slots:
    void onclick();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
public:
    Background(QWidget*);
};
