#include <math.h>
#include "calculation.h"

//二点間の距離
double length(double x1,double y1, double x2, double y2)
{
  double length=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
  return length;
}

// ヘヴィサイド関数
// ステップ関数への変換
int H(double x)
  {
    if(x>0){return 1;}
    else{return 0;}
  }
