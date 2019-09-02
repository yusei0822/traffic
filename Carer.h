#ifndef __CARER_H__
#define __CARER_H__

#include <vector>

using namespace std;

class Vector2D;
class Route;

class Carer{

protected:
  // ID
  int _cid;
  // 看護状況
  int _status;
  // 速度
  Vector2D* _velocity;
  // 加速度
  Vector2D* _acceleration;
  // 現在の位置
  Vector2D* _position;
  // 通過経路
  Route* _route;
  // 希望速度の大きさ
  double _desiredSpeed;

public:
  // コンストラクタ
  Carer(int id, Route* route, Vector2D* velocity);
  // デストラクタ
  ~Carer();
  // 看護状況を返す
  int status();
  // 現在の場所を返す
  Vector2D* position();
  // 速度を返す
  Vector2D* velocity();
  // 加速度を返す
  Vector2D* acceleration();
  // 通過経路を返す
  Route* route();
  // 移動する
  void walk();
  // 加速度を決定する
  void decideAcceleration();
  // 目的地に到着したか
  bool isArrived();
  // 被介護者の元へ行く
  void pick(Vector2D* next);
};

#endif
