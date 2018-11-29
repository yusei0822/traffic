#include "Vector2D.h"
#include <math.h>

// ベクトルの初期設定関数
Vector2D::Vector2D(double x, double y){
  _x = x;
  _y = y;
}

Vector2D::~Vector2D(){};

// 内部変数をいじれないようにする
double Vector2D::x(){
  return _x;
}

double Vector2D::y(){
  return _y;
}

double Vector2D::size(){
  double size = sqrt(_x*_x + _y*_y);
  return size;
}
