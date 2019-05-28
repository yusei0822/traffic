#include <math.h>
#include "Calculation.h"
#include "Vector2D.h"

// 線分と点の距離を計算する
double min_d2(double x0,double y0,double x1,double y1,double x2,double y2)
{
  double a = x2 - x1;
  double b = y2 - y1;
  double a2 = a * a;
  double b2 = b * b;
  double r2 = a2 + b2;
  double tt = -(a*(x1-x0)+b*(y1-y0));
  if( tt < 0 ) {
    return (x1-x0)*(x1-x0) + (y1-y0)*(y1-y0);
  }
  else if( tt > r2 ) {
    return (x2-x0)*(x2-x0) + (y2-y0)*(y2-y0);
  }
  else{
    return 0;
  }
  double f1 = a*(y1-y0)-b*(x1-x0);
  return (f1*f1)/r2;
}

// ベクトルの足し算を行う
Vector2D* aVec(Vector2D* v1, Vector2D* v2){

  double x = v1->x() + v2->x();
  double y = v1->y() + v2->y();

  Vector2D* vec = new Vector2D(x, y);

  return vec;
}

// ベクトルの引き算を行う
Vector2D* sVec(Vector2D* v1, Vector2D* v2){

  double x = v1->x() - v2->x();
  double y = v1->y() - v2->y();

  Vector2D* vec = new Vector2D(x, y);

  return vec;
}

// ベクトルの定数倍を行う
Vector2D* mVec(double k, Vector2D* v){

  double x = v->x()*k;
  double y = v->y()*k;

  Vector2D* vec = new Vector2D(x, y);

  return vec;
}

// 単位ベクトルを返す
Vector2D* uVec(Vector2D* v){
  if (v->size()==0){
    return v;
  } else {
  double x = v->x()/v->size();
  double y = v->y()/v->size();

  Vector2D* vec = new Vector2D(x, y);

  return vec;
  }
}

void rotation2D(double * xp, double * yp, double dx, double dy, double xc, double yc, double theta){
    // 数学座標と同じ様にするためにy座標値を反転
    dy = -dy; yc = -yc;
    *xp = dx * cos(theta) - dy * sin(theta) + xc;
    *yp = -1.0 * ( dx * sin(theta) + dy * cos(theta) + yc );
}
