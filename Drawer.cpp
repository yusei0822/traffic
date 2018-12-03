#include <iostream>
#include <vector>
#include <autogl.h>
#include <cmath>
#include "Pedestrian.h"
#include "Vector2D.h"
#include "Wall.h"

using namespace std;

// 他ファイルで定義している変数の読み込み
extern vector<Pedestrian> pedestrians;
extern vector<Wall> walls;

// 外枠の描画
void drawWall(){
  AutoGL_SetColor(0,0,0);
  // 壁の記述
  walls.push_back(Wall(0,-30,0,1,30,0));
  walls.push_back(Wall(1,0,30,1,30,M_PI_2));
  walls.push_back(Wall(2,30,0,1,30,0));
  walls.push_back(Wall(3,0,-30,1,30,M_PI_2));
  walls.push_back(Wall(4,10,10,1,20,M_PI_2));
  walls.push_back(Wall(5,10,-10,1,20,M_PI_2));
  for (unsigned int i=0;i<walls.size();i++) {
    Wall *w = &walls[i];
     // 壁を構成する4点を定義（とりあえず角度は無視）
     double x1 = w->x() - w->dx();
     double y1 = w->y() - w->dy();
     double x2 = w->x() - w->dx();
     double y2 = w->y() + w->dy();
     double x3 = w->x() + w->dx();
     double y3 = w->y() + w->dy();
     double x4 = w->x() + w->dx();
     double y4 = w->y() - w->dy();
     // 壁を構成する4点を回転させる
     double x_1 = x1 * cos(w->angle()) - y1 * sin(w->angle());
     double y_1 = x1 * sin(w->angle()) + y1 * cos(w->angle());
     double x_2 = x2 * cos(w->angle()) - y2 * sin(w->angle());
     double y_2 = x2 * sin(w->angle()) + y2 * cos(w->angle());
     double x_3 = x3 * cos(w->angle()) - y3 * sin(w->angle());
     double y_3 = x3 * sin(w->angle()) + y3 * cos(w->angle());
     double x_4 = x4 * cos(w->angle()) - y4 * sin(w->angle());
     double y_4 = x4 * sin(w->angle()) + y4 * cos(w->angle());
     AutoGL_DrawQuadrangle(x1,y1,0,x2,y2,0,x3,y3,0,x4,y4,0);
   }
 }

// 歩行者の描画
void drawPedestrian(){
  // 色の設定（青色）
  AutoGL_SetColor(0,0,1);
  for(unsigned int i=0;i<pedestrians.size();i++)
  {
      Pedestrian *p = &pedestrians[i];
      // 加速度を決定
      p->decideAcceleration();
      // 加速度を元に動かす
      p->walk();
      // 歩行者の形を定義
      AutoGL_DrawCircle3D(p->position()->x(),p->position()->y(),1,0,0,1,0.5,10);
  }
}
