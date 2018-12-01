#include <iostream>
#include <math.h>
#include "Pedestrian.h"
#include "Calculation.h"
#include "Vector2D.h"
#include "Route.h"

using namespace std;

extern vector<Pedestrian> pedestrians;
extern double TimeStep;

Pedestrian::Pedestrian(int id, Route* route, Vector2D* velocity){
  _id = id;
  _route = route;
  _velocity = velocity;
  _acceleration = 0;
  _position = _route->next();
  _desiredSpeed = 1.34;

  _route->incrementRouteIndex();
}

Pedestrian::~Pedestrian(){
}

Vector2D* Pedestrian::position(){
  return _position;
}

Vector2D* Pedestrian::velocity(){
  return _velocity;
}

Route* Pedestrian::route(){
  return _route;
}

void Pedestrian::walk(){
  _velocity = aVec(_velocity, mVec(TimeStep, _acceleration));
  _position = aVec(_position, _velocity);

  cout<<_position->y()<<endl;
  // 目的地に到着した場合は次の目的地を選択する
  if(isArrived()){
    _route->incrementRouteIndex();
  }
}

void Pedestrian::decideAcceleration(){
  //===============================================
  // 移動目標に近づく力
  /// 移動目標に向かう単位ベクトル
    Vector2D* e_a = uVec(sVec(_route->next(), _position));
    Vector2D* f1 = mVec(1/0.5, sVec(mVec(_desiredSpeed, e_a), _velocity));
    cout<<"f1:"<<"x="<<f1->x()<<",y="<<f1->y()<<endl;
  //===============================================
  // 他のエージェントからの斥力
  // 変数の定義
  double v0_ab = 2.1;
  double s = 0.3;
  Vector2D* f2 = new Vector2D(0,0);
  /// 自分以外の全エージェントから受ける力を計算
  for (unsigned int i=0; i<pedestrians.size(); i++){
    if(&(pedestrians[i]) == this){
      continue;
    }
    // 相対距離の計算
    Vector2D* r_a = mVec(0.2, _velocity);
    Vector2D* v_b = pedestrians[i].velocity();
    Vector2D* r_b = mVec(0.2, v_b);
    Vector2D* r_ab = sVec(r_a, r_b);
    // 相手側の希望進行方向
    Vector2D* e_b = uVec(sVec(pedestrians[i].route()->next(),pedestrians[i].position()));
    // 相手側の希望進行距離
    double s_b = v_b->size() * 0.2;
    double b = sqrt( pow((r_a->size() + (sVec(r_ab, mVec(s_b, e_b)))->size()),2.0) - pow(s_b,2.0))/2.0;
    double v_ab = v0_ab * exp(-1 * b / s);
    f2 = aVec(f2,mVec(-1 * v_ab, r_ab));
  }
    cout<<"f2:"<<"x="<<f2->x()<<",y="<<f2->y()<<endl;
  //===============================================
  _acceleration = aVec(f1,f2);
}

bool Pedestrian::isArrived(){

  bool flag = false;

  Vector2D* vec = sVec(_route->next(), _position);
  if(vec->size()<1){
    flag = true;
  };

  return flag;
}