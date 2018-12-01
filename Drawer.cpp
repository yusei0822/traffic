#include <iostream>
#include <vector>
#include <autogl.h>
#include "Pedestrian.h"
#include "Vector2D.h"

using namespace std;

class Pedestrian;

extern vector<Pedestrian> pedestrians;

// 外枠の描画
 void drawWall(){
   AutoGL_SetColor(0,0,0);
   AutoGL_DrawQuadrangle(-120,-120,0,-120,120,0,120,120,0,120,-120,0);
 }

void drawWall2(){
  AutoGL_SetColor(1,1,1);
  AutoGL_DrawQuadrangle(-115,-115,1,-115,115,1,115,115,1,115,-115,1);
}

void drawWall3(){
  AutoGL_SetColor(0,0,0);
  AutoGL_DrawQuadrangle(-60,35,2,-60,40,2,120,40,2,120,35,2);
}

void drawWall4(){
  AutoGL_SetColor(0,0,0);
  AutoGL_DrawQuadrangle(-60,-40,3,-60,-35,3,120,-35,3,120,-40,3);
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
