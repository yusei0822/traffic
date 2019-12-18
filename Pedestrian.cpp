#include <iostream>
#include <math.h>
#include <vector>
#include "Pedestrian.h"
#include "Calculation.h"
#include "Vector2D.h"
#include "Wall.h"
#include "Route.h"

using namespace std;

// 他のファイルで定義している変数を読み込む
extern vector<Pedestrian> pedestrians;
extern vector<Wall> walls;
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

// 歩行者を移動させる関数
void Pedestrian::walk(){
  // social force modelで記述されている最高速度を超えない場合、現在の速度に加速度を加算する
  if(_velocity->size()<1.3*1.34){
    _velocity = aVec(_velocity, mVec(TimeStep, _acceleration));
  }
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
void Pedestrian::stop(){
  _velocity = 0;
  _acceleration = 0;
}

// 加速度を決定する関数
void Pedestrian::decideAcceleration(){
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
    for (unsigned int i=0; i<pedestrians.size(); i++){
      if(&(pedestrians[i]) == this){
        continue;
      }
      Vector2D* r_a = _position;
      Vector2D* v_b = pedestrians[i].velocity();
      Vector2D* r_b = pedestrians[i].position();
      Vector2D* r_ab = sVec(r_a, r_b);
      comparedLength = min(iniR->size(),r_ab->size());
      if(comparedLength == r_ab->size()){
        min_i += 1;
        iniR = r_ab;
      }
    }
    // 斥力の計算
    Vector2D* r_a = _position;
    Vector2D* v_b = pedestrians[min_i].velocity();
    Vector2D* r_b = pedestrians[min_i].position();
    Vector2D* r_ab = sVec(r_a, r_b);
    // 相手側の希望進行方向
    Vector2D* e_b = uVec(sVec(pedestrians[min_i].route()->next(),pedestrians[min_i].position()));
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
bool Pedestrian::isArrived(){
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
