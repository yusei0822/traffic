#ifndef __CARERECIPIENT_H__
#define __CARERECIPIENT_H__

#include <vector>

using namespace std;

class Vector2D;
class Route;

class CareRecipient{

protected:
  // ID
  int _crid;
  // 内部状態
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
  CareRecipient(int id, Route* route, Vector2D* velocity);
  // デストラクタ
  ~CareRecipient();
  // ステータスを返す
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
  // イベントフラグ
  void changeStatus();
  // トイレに向かう
  void restroom();
};

#endif
