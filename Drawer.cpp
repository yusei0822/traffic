#include <iostream>
#include <vector>
#include <autogl.h>
#include <cmath>
#include "Calculation.h"
#include "Pedestrian.h"
#include "Carer.h"
#include "CareRecipient.h"
#include "Vector2D.h"
#include "Wall.h"
#include "Route.h"

using namespace std;

// 他ファイルで定義している変数の読み込み
extern vector<Pedestrian> pedestrians;
extern vector<Carer> carers;
extern vector<CareRecipient> careRecipients;
extern vector<Wall> walls;

// 環境の描画
void drawWall(){
  AutoGL_SetColor(0,0,0);
  // 壁の記述
  int x = 30;
  int y = 30;
  // int desk_dx = 2;
  // int desk_dy = 2;
  walls.push_back(Wall(0,-x,0,1,30,0));
  walls.push_back(Wall(1,0,y,1,30,M_PI/2));
  walls.push_back(Wall(2,x,0,1,30,0));
  walls.push_back(Wall(3,0,-y,1,30,M_PI/2));
  // 机の記述
  // walls.push_back(Wall(4,x/2,0,desk_dx,desk_dy,0));
  // walls.push_back(Wall(5,-x/2,0,desk_dx,desk_dy,0));
  // トイレの記述
  walls.push_back(Wall(6,x-5,y+10,1,5,M_PI/2));
  walls.push_back(Wall(7,x,y+5,1,5,0));
  walls.push_back(Wall(8,x-10,y+5,1,5,0));
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

// 介護士の描画
void drawCarer(){
  // 色の設定（青色）
  AutoGL_SetColor(0,0,1);
  vector<Carer> tmpCarers;
  tmpCarers.clear();
  for(unsigned int i=0;i<carers.size();i++){
    Carer *c = &carers[i];
    // 加速度を決定
    c->decideAcceleration();
    // 加速度を元に動かす
    c->walk();
    // 最終地点に到達した歩行者を静止させる
    if(c->isArrived() && c->route()->routeSize()-1 == c->route()->routeIndex()){
      // c->stop();
      tmpCarers.push_back(*c);
    }
    else{
      tmpCarers.push_back(*c);
    }
    // 歩行者の形を定義
    AutoGL_DrawCircle3D(c->position()->x(),c->position()->y(),1,0,0,1,0.5,5);
  }
  carers = tmpCarers;
}

void drawCareRecipient(){
  vector<CareRecipient> tmpCareRecipients;
  tmpCareRecipients.clear();
  for(unsigned int i=0;i<careRecipients.size();i++){
    CareRecipient *cr = &careRecipients[i];
    // // 加速度を決定
    cr->decideAcceleration();
    // // 加速度を元に動かす
    cr->walk();
    // // 被介護者リストに追加
    tmpCareRecipients.push_back(*cr);
    // 色を定義
    if(cr->status()==0){
      AutoGL_SetColor(0,1,0);
    // } else if (cr->status()==2){
    //   AutoGL_SetColor(1,1,1);
    } else {
      AutoGL_SetColor(1,0,0);
    }
    // 被介護者の形を定義
    if(cr->careLevel()==0){
      AutoGL_DrawCircle3D(cr->position()->x(),cr->position()->y(),1,0,0,1,0.5,5);
    } else {
      AutoGL_DrawTriangle(cr->position()->x(),cr->position()->y(),0,cr->position()->x()+2,cr->position()->y()-1,0,cr->position()->x(),cr->position()->y()-2,0);
      // AutoGL_DrawCircle3D(cr->position()->x(),cr->position()->y(),1,0,0,1,0.5,5);
    }
  }
  careRecipients = tmpCareRecipients;
}
