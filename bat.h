#include <iostream>
#include <QRandomGenerator>
#include <QtMath>
#include <QPoint>

struct Bat {
   Bat(QPointF,int hitH=5,int hitW=5); 
   int state = 0;
   int maxState = 5;
   int timeBuff = 0;
   QPointF coord; 
   size_t hitH, hitW;
   double Yspeed = 0.8;
   double Xspeed = 5;
   int changeDelay = 100;
};
