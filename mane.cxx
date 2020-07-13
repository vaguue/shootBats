#include "mane.h"

Background::Background(QWidget* parent = 0) : QWidget(parent) {
    setFixedSize(width, height);
    img = new QPixmap("./png/back.png");
    btn = new QPushButton("suks", this);
    btn->setGeometry((width>>1)-40, height-30, 80, 30);
    QObject::connect(btn, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
    connect(this, SIGNAL(clicked()), this, SLOT(onclick()));
}

void Background::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.drawPixmap(QRect(0,0, width, height), *img); 
}

void Background::onclick() {
    using namespace std;
    cout << "clicked" << endl;
}

int main(int argc, char *argv[ ])
{

QApplication app(argc, argv);
Background main;
main.show();
return app.exec();
}
