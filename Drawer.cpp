#include <iostream>
#include <vector>
#include <autogl.h>
#include "Pedestrian.h"
#include "Vector2D.h"
#include "Wall.h"

using namespace std;

class Pedestrian;
class Wall;

extern vector<Pedestrian> pedestrians;
extern vector<wall> walls;

// 外枠の描画
 void drawWall(){
   AutoGL_SetColor(0,0,0);
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
     // 壁の記述
     AutoGL_DrawQuadrangle(x1,y1,0,x2,y2,0,x3,y3,0,x4,y4,0);
   }
 }

void drawPedestrian(){
  AutoGL_SetColor(0,0,1);

  for(unsigned int i=0;i<pedestrians.size();i++)
  {
    Pedestrian *p = &pedestrians[i];
    p->decideAcceleration();
    p->walk();
    AutoGL_DrawCircle3D(p->position()->x(),p->position()->y(),1,0,0,1,0.5,10);
  }
}
