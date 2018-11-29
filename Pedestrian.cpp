#include <iostream>
#include "Pedestrian.h"
#include "Calculation.h"
#include "Vector2D.h"
#include "Route.h"

using namespace std;

Pedestrian::Pedestrian(int id, Route* route, Vector2D* velocity){
  _id = id;
  _route = route;
  _velocity = velocity;
  _acceleration = 0;
  _position = _route->next();
  _desiredSpeed = 1;

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
  _position = aVec(_position, mVec(0.1, _acceleration));

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
  cout<<"next:"<<_route->next()->x()<<endl;
  cout<<"position"<<_position->x()<<endl;
  Vector2D* f1 = mVec(1/0.1, sVec(mVec(_desiredSpeed, e_a), _velocity));

  //===============================================
  // 他のエージェントからの斥力

  //===============================================

  _acceleration = f1;
}

bool Pedestrian::isArrived(){

  bool flag = false;

  Vector2D* vec = sVec(_route->next(), _position);
  if(vec->size()<1){
    flag = true;
  };

  return flag;
}
