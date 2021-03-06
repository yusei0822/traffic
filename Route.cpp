#include "Route.h"
#include <vector>

using namespace std;

Route::Route(){
  _routeIndex = 0;
}

Route::~Route(){};

int Route::routeSize(){
  return _route.size();
}

// 次のサブゴールを追加する関数
void Route::addNext(Vector2D* next){
   _route.push_back(next);
}


Vector2D* Route::next(){
   return _route[_routeIndex];
}

Vector2D* Route::goal(){
  return _route[_route.size()-1];
}

Vector2D* Route::iniPosition(){
  return _route[0];
}

int Route::routeIndex(){
   return _routeIndex;
 }

void Route::incrementRouteIndex(){
  if(_routeIndex < _route.size()-1){
    _routeIndex++;
  }
}

void Route::insertNext(Vector2D* next){
  _route.insert(_route.begin()+_routeIndex,next);
}
