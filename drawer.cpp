#include <iostream>
#include <vector>
#include <autogl.h>
#include "pedestrian.h"

using namespace std;

class Pedestrian;

extern vector<Pedestrian> pedestrians;

void drawWall(){
  AutoGL_SetColor(1,0,0);
  AutoGL_DrawQuadrangle(100,100,0,200,100,0,200,200,0,100,200,0);
}

void drawPedestrian(){
  AutoGL_SetColor(0,0,1);

  for(unsigned int i=0;i<pedestrians.size();i++)
  {
    pedestrians[i].Accelerate();
    pedestrians[i].Walk();
    AutoGL_DrawCircle3D(pedestrians[i].X(),pedestrians[i].Y(),1,0,0,1,3,10);
  }

}
