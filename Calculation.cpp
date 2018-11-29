#include <math.h>
#include "Calculation.h"
#include "Vector2D.h"

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

  double x = v->x()/v->size();
  double y = v->y()/v->size();

  Vector2D* vec = new Vector2D(x, y);

  return vec;
}
