#include <iostream>
#include <autogl.h>
#include "visualize.h"

double PresentTime = 0;
double TimeStep = 0.1; //[s]

//メイン関数
void AutoGL_SetUp(int argc, char *argv[])
{
  //可視化開始
  visualize();
}
