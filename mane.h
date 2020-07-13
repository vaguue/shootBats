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

struct Background : public QWidget {
    Q_OBJECT
    size_t height = 600, width = 430;
    QPushButton* btn;
    QPixmap* img;
public slots:
    void onclick();
public:
    Background(QWidget*);
    void paintEvent(QPaintEvent* event) override;
};
