#include <iostream>
#include "pedestrian.h"

// グローバル変数の呼び出し
extern double PresentTime;

// コンストラクタ
// 歩行者の初期設定関数
Pedestrian::Pedestrian(double X, double Y,double Z){
  x = X;
  y = Y;
  z = Z;
  velocity = 0;
  acceleration = 0.1;
}

double Pedestrian::X(){
  return x;
}

double Pedestrian::Y(){
  return y;
}

double Pedestrian::Z(){
  return z;
}

double Pedestrian::Velocity(){
  return velocity;
}

// 加速度の決定
// social force modelに基づく
void Pedestrian::Accelerate(){
  velocity += acceleration;
  if(velocity > 0.5){
    velocity = 0.5;
  }
}

// 歩行者を移動させる
void Pedestrian::Walk(){
  if(PresentTime < 30){
    y += velocity;
  }
  else if(PresentTime < 60){
    x += velocity;
  }
  else if(PresentTime < 90){
    x -= velocity;
  }
  else if(PresentTime < 105){
    y -= velocity;
  }
  else if(PresentTime < 135){
    x += velocity;
  }
  else if(PresentTime < 165){
    x -= velocity;
  }
  else if(PresentTime < 180){
    y -= velocity;
  }
  else if(PresentTime < 210){
    x += velocity;
  }
  else if(PresentTime < 240){
    x -= velocity;
  }
}
