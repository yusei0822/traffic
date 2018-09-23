#include <iostream>
#include <vector>
#include <autogl.h>
#include "pedestrian.h"

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
  AutoGL_DrawQuadrangle(-60,50,2,-60,70,2,120,70,2,120,50,2);
}

void drawWall4(){
  AutoGL_SetColor(0,0,0);
  AutoGL_DrawQuadrangle(-60,-70,3,-60,-50,3,120,-50,3,120,-70,3);
}

// 歩行者の描画
void drawPedestrian(){
  AutoGL_SetColor(0,0,0);
  for(unsigned int i=0;i<pedestrians.size();i++)
  {
    pedestrians[i].Accelerate();
    pedestrians[i].Walk();
    AutoGL_DrawCircle3D(pedestrians[i].X(),pedestrians[i].Y(),1,0,0,1,3,10);
  }
}
