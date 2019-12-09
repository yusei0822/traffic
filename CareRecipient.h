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
  // 認知能力
  int _careLevel;
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
  // 膀胱のキャパシティ
  double _toiletCapacity;

public:
  // コンストラクタ
  CareRecipient(int id, int careLevel, Route* route, Vector2D* velocity, double r);
  // デストラクタ
  ~CareRecipient();
  // ステータスを返す
  int status();
  // 要介護度を返す
  int careLevel();
  // 現在の場所を返す
  Vector2D* position();
  // 現在の場所を返す
  Vector2D* iniPosition();
  // 速度を返す
  Vector2D* velocity();
  // 加速度を返す
  Vector2D* acceleration();
  // 通過経路を返す
  Route* route();
  // 膀胱のキャパシティを返す
  double toiletCapacity();
  // 移動する
  void walk();
  // 加速度を決定する
  void decideAcceleration();
  // 目的地に到着したか
  bool isArrived();
  // イベントフラグ
  void changeStatus();
  // トイレに向かう
  void restroom(Vector2D* position);
  // 膀胱地を加算
  void urinaryIntention();
  // トイレに行きたいと意思表示する
  void toiletIndicate();
  // 放尿する
  void urinate();
  // 最初の場所に戻る
  void goIniPosition();
};

#endif
