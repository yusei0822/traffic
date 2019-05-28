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

  void incrementRouteIndex();

  void insertNext();
};

#endif
