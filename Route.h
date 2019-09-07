#ifndef __ROUTE_H__
#define __ROUTE_H__
#include <vector>
using namespace std;

class Vector2D;

class Route{
protected:
  // 経路本体（サブゴールの配列）
  vector<Vector2D*> _route;
  // 経路のIndex
  int _routeIndex;
public:
  Route();
  ~Route();
  int routeIndex();
  int routeSize();
  void addNext(Vector2D* next);
// 現在の目的地の座標を返す
  Vector2D* next();
// 最終目的地の座標を返す
  Vector2D* goal();
  //最初の座標を返す
  Vector2D* iniPosition(); 
  // routeIndexをプラスする
  void incrementRouteIndex();
  // 次の目的地を追加する
  void insertNext(Vector2D* next);
};

#endif
