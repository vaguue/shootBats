#include <iostream>
#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsItem>

struct Widget : public QWidget {
    Q_OBJECT
    Widget* ui;
    QGraphicsScene* scene;
    //Triangle* tr;
    Widget(QWidget* parent = 0) : QWidget(parent), ui(new Widget) {

    }
};


int main(int argc, char *argv[ ])
{

QApplication app(argc, argv);
QLabel hello("<center>Welcome to my first Qt program</center>");
hello.setWindowTitle("My First Qt Program");
hello.resize(400, 400);
hello.show();
return app.exec();

}
