#include "Wall.h"

// Wallの初期設定関数
Wall::Wall(double x, double y, double dx, double dy, double angle){
  _x = x;
  _y = y;
  _dx = dx;
  _dy = dy;
  _angle = angle;
}

Wall::~Wall(){};

// 内部変数をいじれないようにする
double Wall::x(){
  return _x;
}

double Wall::y(){
  return _y;
}

double Wall::dx(){
  return _dx;
}

double Wall::dy(){
  return _dy;
}

double Wall::angle(){
  return _angle;
}
