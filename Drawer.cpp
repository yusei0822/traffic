#include <iostream>
#include <vector>
#include <autogl.h>
#include <cmath>
#include "Calculation.h"
#include "Pedestrian.h"
#include "Carer.h"
#include "Vector2D.h"
#include "Wall.h"
#include "Route.h"

using namespace std;

// 他ファイルで定義している変数の読み込み
extern vector<Pedestrian> pedestrians;
extern vector<Carer> carers;
extern vector<Wall> walls;

// 外枠の描画
void drawWall(){
  AutoGL_SetColor(0,0,0);
  // 壁の記述
  int x = 30;
  int y = 30;
  walls.push_back(Wall(0,-x,0,1,30,0));
  walls.push_back(Wall(1,0,y,1,30,M_PI/2));
  walls.push_back(Wall(2,x,0,1,30,0));
  walls.push_back(Wall(3,0,-y,1,30,M_PI/2));
  walls.push_back(Wall(4,0,0,5,5,0));
  // walls.push_back(Wall(4,15,10,1,15,M_PI/2));
  // walls.push_back(Wall(5,15,-10,1,15,M_PI/2));
  for (unsigned int i=0;i<walls.size();i++) {
    Wall *w = &walls[i];
     // 壁を構成する4点を回転させる
     double x_1,y_1,x_2,y_2,x_3,y_3,x_4,y_4;
     rotation2D(&x_1,&y_1, w->dx(),w->dy(),w->x(),w->y(),w->angle());
     rotation2D(&x_2,&y_2, -1 * w->dx(),w->dy(),w->x(),w->y(),w->angle());
     rotation2D(&x_3,&y_3, -1 * w->dx(), -1 * w->dy(),w->x(),w->y(),w->angle());
     rotation2D(&x_4,&y_4, w->dx(),-1 * w->dy(),w->x(),w->y(),w->angle());
     AutoGL_DrawQuadrangle(x_4,y_4,0,x_1,y_1,0,x_2,y_2,0,x_3,y_3,0);
   }
 }

// // 歩行者の描画
// void drawPedestrian(){
//   // 色の設定（青色）
//   AutoGL_SetColor(0,0,1);
//   vector<Pedestrian> tmpPedestrians;
//   tmpPedestrians.clear();
//   for(unsigned int i=0;i<pedestrians.size();i++)
//   {
//       Pedestrian *p = &pedestrians[i];
//       // 加速度を決定
//       p->decideAcceleration();
//       // 加速度を元に動かす
//       p->walk();
//       // 最終地点に到達した歩行者を削除する
//       if(p->isArrived() && p->route()->routeSize()-1 == p->route()->routeIndex()){
//         //delete p;
//       }
//       else{
//         tmpPedestrians.push_back(*p);
//       }
//
//       // 歩行者の形を定義
//       AutoGL_DrawCircle3D(p->position()->x(),p->position()->y(),1,0,0,1,0.5,5);
//   }
//   pedestrians = tmpPedestrians;
// }

// 介護士の描画
void drawCarer(){
  // 色の設定（青色）
  AutoGL_SetColor(0,0,1);
  vector<Carer> tmpCarers;
  tmpCarers.clear();
  for(unsigned int i=0;i<carers.size();i++)
  {
      Carer *c = &carers[i];
      // 加速度を決定
      c->decideAcceleration();
      // 加速度を元に動かす
      c->walk();
      // 最終地点に到達した歩行者を削除する
      if(c->isArrived() && c->route()->routeSize()-1 == c->route()->routeIndex()){
        //delete p;
      }
      else{
        tmpCarers.push_back(*c);
      }
      // 歩行者の形を定義
      AutoGL_DrawCircle3D(c->position()->x(),c->position()->y(),1,0,0,1,0.5,5);
  }
  carers = tmpCarers;
}
