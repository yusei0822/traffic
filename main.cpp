#include <iostream>
#include <autogl.h>
#include "Visualize.h"

double PresentTime = 0.0;
double TimeStep = 2.0; //[s]

//メイン関数
void AutoGL_SetUp(int argc, char *argv[])
{
  //可視化開始
  visualize();
}
