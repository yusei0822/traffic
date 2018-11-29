#ifndef __ROUTE_H__
#define __ROUTE_H__

#include <vector>

using namespace std;

class Vector2D;

class Route{

protected:
  // 経路本体
  vector<Vector2D*> _route;

  // 経路のIndex
  int _routeIndex;

public:

  Route();
  ~Route();

  void addNext(Vector2D* next);

  Vector2D* next();

  int routeIndex();

  void incrementRouteIndex();
};

#endif
