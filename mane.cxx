#include "mane.h"


Background::Background(QWidget* parent = nullptr) : QWidget(parent) {
    img = new QPixmap("./png/back.png");
    gun = new QPixmap("./png/pushka.png");
    bullet = new QPixmap("./png/shar.png");
    width = img->size().width();
    height = img->size().height();
    setFixedSize(width, height);
    curGun = new QPixmap(*gun);
    eL = new Logic(&width, &height);
    eL->initField();
    QObject::connect(eL, SIGNAL(movement()), this, SLOT(redrawBullets()));
    eL->initGun();
/*  btn = new QPushButton("suks", this);
    btn->setGeometry((width>>1)-40, height-30, 80, 30);
    QObject::connect(btn, SIGNAL(clicked()), QApplication::instance(), SLOT(quit())); */
}

void Background::redrawBullets() {
    using namespace std;
    update();
}

void Background::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.drawPixmap(QRect(0,0, width, height), *img); 
    for (auto& e : eL->bullets) {
        auto x = std::get<0>(e).x();
        auto y = std::get<0>(e).y();
        //x += width>>1;
        y = height - y;
        std::cout << "x, y: " << x << "," << y << std::endl;
        painter.drawPixmap(QRect(x, y, bullet->size().width(), bullet->size().height()), *bullet);
    }
    painter.drawPixmap(QRect((width - curGun->size().width())>>1,
                height-(curGun->size().height()>>1), curGun->size().width(), curGun->size().height()), *curGun);
}

double Background::rotateGun(int x, int y) {
    using namespace std;
    x -= width>>1;
    y = height-y;
    double tg = (double)x/(double)y;
    gunAngle = qAtan(tg);
    cout << "angle: " << gunAngle << ", tg: " << tg << endl;
    QMatrix rm;
    rm.rotate(qRadiansToDegrees(gunAngle));
    delete curGun;
    curGun = new QPixmap(gun->transformed(rm));
    update();
    return tg;
}

void Background::mousePressEvent(QMouseEvent* event) {
    using namespace std;
    if (event->button() == Qt::LeftButton) {
        auto point = event->pos();
        pressed = true; 
        cout << "clicked on: " << point.x() << ' ' << point.y() << endl;
        rotateGun(point.x(), point.y());
        eL->shoot(gunAngle);
    }
}


void Background::mouseMoveEvent(QMouseEvent* event) {
    using namespace std;
    if (pressed) {
        auto point = event->pos();
        cout << "moved to: " << point.x() << ' ' << point.y() << endl;
        rotateGun(point.x(), point.y());
    }
}

void Background::mouseReleaseEvent(QMouseEvent* event) {
    pressed = false;
}

void Background::resizeEvent(QResizeEvent* event) {

}


int main(int argc, char *argv[ ])
{

QApplication app(argc, argv);
Background main;
main.show();
return app.exec();
}
