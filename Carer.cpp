#include <iostream>
#include <math.h>
#include <vector>
#include "Carer.h"
#include "CareRecipient.h"
#include "Calculation.h"
#include "Vector2D.h"
#include "Wall.h"
#include "Route.h"

using namespace std;

// 他のファイルで定義している変数を読み込む
extern vector<Carer> carers;
extern vector<CareRecipient> careRecipients;
extern vector<Wall> walls;
extern double TimeStep;

Carer::Carer(int id, Route* route, Vector2D* velocity){
  _cid = id;
  _route = route;
  _velocity = velocity;
  _acceleration = 0;
  _position = _route->next();
  // _carePosition = velocity;
  _status = 0;
  // _desiredSpeed = 1.34;
  _desiredSpeed = 0.5;
  _route->incrementRouteIndex();
}

Carer::~Carer(){
}

int Carer::status(){
  return _status;
}

Vector2D* Carer::position(){
  return _position;
}

Vector2D* Carer::carePosition(){
  return _carePosition;
}

Vector2D* Carer::velocity(){
  return _velocity;
}

Route* Carer::route(){
  return _route;
}

// 歩行者を移動させる関数
void Carer::walk(){
  // 現在の速度に加速度を加算する
  _velocity = aVec(_velocity, mVec(TimeStep, _acceleration));
  // 現在の座標に速度を加算する
  _position = aVec(_position, _velocity);
  //
  // cout<<_position->y()<<endl;
  // 目的地に到着した場合は次の目的地を選択する
  if(isArrived()){
    _route->incrementRouteIndex();
  }
}

// その場で止まる関数
void Carer::stop(){
  _velocity = 0;
  _acceleration = 0;
}

// 加速度を決定する関数
void Carer::decideAcceleration(){
  //===============================================
  // 移動目標に近づく力
  /// 移動目標に向かう単位ベクトル
    Vector2D* e_a = uVec(sVec(_route->next(), _position));
    Vector2D* f1 = mVec(1/0.5, sVec(mVec(_desiredSpeed, e_a), _velocity));
    // cout<<"f1:"<<"x="<<f1->x()<<",y="<<f1->y()<<endl;
  //===============================================
    // 他のエージェントからの斥力
    Vector2D* f2 = new Vector2D(0,0);
    // 変数の定義
    double v0_ab = 2.1;
    double s = 0.3;
    // 自分との距離が最小のエージェントを特定する変数
    int min_i = 0;
    Vector2D* iniR = new Vector2D(0,0);
    double comparedLength = 0.0;
    /// 自分に最も近いエージェントからの斥力を計算
    // 自分に最も近いエージェントを特定
    for (unsigned int i=0; i<carers.size(); i++){
      if(&(carers[i]) == this){
        continue;
      }
      Vector2D* r_a = _position;
      Vector2D* v_b = carers[i].velocity();
      Vector2D* r_b = carers[i].position();
      Vector2D* r_ab = sVec(r_a, r_b);
      comparedLength = min(iniR->size(),r_ab->size());
      if(comparedLength == r_ab->size()){
        min_i += 1;
        iniR = r_ab;
      }
    }
    // 斥力の計算
    Vector2D* r_a = _position;
    Vector2D* v_b = carers[min_i].velocity();
    Vector2D* r_b = carers[min_i].position();
    Vector2D* r_ab = sVec(r_a, r_b);
    // 相手側の希望進行方向
    Vector2D* e_b = uVec(sVec(carers[min_i].route()->next(),carers[min_i].position()));
    // 相手側の希望進行距離
    double s_b = v_b->size() * 0.1;
    double b = sqrt( pow((r_ab->size() + (sVec(r_ab, mVec(s_b, e_b)))->size()),2.0) - pow(s_b,2.0))/2.0;
    // ポテンシャル場の計算
    double v_ab = v0_ab * exp(-1 * b / s);
    f2 = aVec(f2,mVec(-1*v_ab,uVec(r_ab)));
  //===============================================
  // 壁からの斥力
  // 変数の定義
  // double u0_ab = 10;
  // double r = 0.2;
  Vector2D* f4 = new Vector2D(0,0);
  // 壁から受ける力を計算
  // for (unsigned int i=0; i<walls.size(); i++)
  // {
  //     Wall *w = &walls[i];
  //     // 壁を構成する直線を定義するための点を定義
  //     double x_1,y_1,x_2,y_2,x_3,y_3,x_4,y_4;
  //     rotation2D(&x_1,&y_1, w->dx(),w->dy(),w->x(),w->y(),w->angle());
  //     rotation2D(&x_2,&y_2, -1 * w->dx(),w->dy(),w->x(),w->y(),w->angle());
  //     rotation2D(&x_3,&y_3, -1 * w->dx(), -1 * w->dy(),w->x(),w->y(),w->angle());
  //     rotation2D(&x_4,&y_4, w->dx(),-1 * w->dy(),w->x(),w->y(),w->angle());
  //     // 壁を近似する直線となる2点の座標
  //     double x_5 = (x_1+x_2)/2;
  //     double y_5 = (y_1+y_2)/2;
  //     double x_6 = (x_3+x_4)/2;
  //     double y_6 = (y_3+y_4)/2;
  //     // 最短距離を求める
  //     double r_ab = min(r_ab,min_d2(_position->x(),_position->y(),x_5,y_5,x_6,y_6));
  //     // 介護者と壁の垂線の足の座標を求める
  //     Vector2D* p = new Vector2D(0,0);
  //     p = getpPoint(x_1,y_1,x_5,y_5,x_6,y_6);
  //     // 介護者と壁との相対距離ベクトルを求める
  //     Vector2D* r_aB = sVec(p,_position);
  //     // ポテンシャル場の計算
  //     double u_ab = u0_ab * exp(-1 * r_ab / r);
  //     // cout << u_ab << endl;
  //     f4 = mVec(-1*u_ab,uVec(r_aB));
  // }
  // cout<<"f4:"<<"x="<<f4->x()<<",y="<<f4->y()<<endl;
  //===============================================
  // attractive effects
  // 変数の定義
  // 本モデルでは発生しないので記述しない
  //===============================================
  _acceleration = aVec(aVec(f1,f2),f4);
}

// 目的地に到達したかどうかを判定する関数
bool Carer::isArrived(){
  bool flag = false;
  Vector2D* vec = sVec(_route->next(), _position);
  // 目的地から1m以内になると目的地に到達したと判定
  if(vec->size()<1){
    flag = true;
    // cout << "到着しました" << endl;
  };
  // cout << "到着しました" << endl;
  return flag;
}

// 指定された被介護者の位置を次の目的地に設定する
void Carer::pick(Vector2D* next){
  _route->insertNext(next);
}

// restroomを次の目的地に設定する
void Carer::restroom(Vector2D* CareRecipient){
  Vector2D* restroom = new Vector2D(25,30);
  _route->insertNext(CareRecipient);
  _route->insertNext(restroom);
  _route->insertNext(CareRecipient);
}

// 最終目的地に到着したかどうかを判定する関数
bool Carer::restroomArrived(){
  bool flag = false;
  Vector2D* restroom = new Vector2D(25,30);
  Vector2D* vec = sVec(restroom,_position);
  // 最終目的地から距離が1m以内になると目的地に到達したと判定
  if(vec->size()<5){
      flag = true;
  };
  return flag;
}

void Carer::changeStatus(){
  if (_status == 0 ){
    _status = 1;
  } else if(_status == 1) {
    _status = 2;
  } else if (_status == 2){
    _status = 3;
  } else if (_status == 3){
    _status = 0;
  }
}
//
bool Carer::care_is_finished(){
  bool flag = false;
  Vector2D* vec = sVec(_carePosition,_position);
  if (vec->size()<3){
    flag = true;
  };
  return flag;
}

void Carer::enter_care_position(Vector2D* carePosition){
  _carePosition = carePosition;
}
