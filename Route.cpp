#include "Route.h"
#include <vector>

using namespace std;

Route::Route(){
  _routeIndex = 0;
}

Route::~Route(){};

// 次のサブゴールを追加する関数
void Route::addNext(Vector2D* next){
   _route.push_back(next);
}


Vector2D* Route::next(){
   return _route[_routeIndex];
}

int Route::routeIndex(){
   return _routeIndex;
 }

void Route::incrementRouteIndex(){
  if(_routeIndex < _route.size()-1){
    _routeIndex++;
  }
}
