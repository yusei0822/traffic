#include <iostream>
#include <vector>
#include <autogl.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Calculation.h"
#include "Carer.h"
#include "CareRecipient.h"
#include "Vector2D.h"
#include "Wall.h"
#include "Route.h"

using namespace std;

// 他ファイルで定義している変数の読み込み
extern vector<Wall> walls;
extern double PresentTime;

vector<CareRecipient> careRecipients;
vector<Carer> carers;

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

  // 介護士を生成
  static int cid = 0;
  Vector2D* v0 = new Vector2D(0,0);
  // 一人目の介護士の作成
  if(PresentTime > 0.99 && PresentTime<1.01){
    Route* route1 = new Route();
    // 巡回経路作成のための経路の配列を作成
    vector<pair<double, double > > subGoal;
    subGoal.push_back(make_pair(-25,-25));
    // subGoal.push_back(make_pair(25,-25));
    // subGoal.push_back(make_pair(-25,-25));
    // subGoal.push_back(make_pair(25,-25));
    // subGoal.push_back(make_pair(-25,-25));
    // subGoal.push_back(make_pair(25,-25));
    // subGoal.push_back(make_pair(-25,-25));
    // subGoal.push_back(make_pair(25,-25));
    // 巡回経路を作成
    for(unsigned int i = 0; i < subGoal.size(); i++){
      Vector2D* vec = new Vector2D(subGoal[i].first, subGoal[i].second);
      route1->addNext(vec);
    }
    Carer *c1 = new Carer(cid, route1, v0);
    carers.push_back(*c1);
  }

  // 二人目の介護士の作成
  cid = 1;
  if(PresentTime > 0.99 && PresentTime<1.01){
    Route* route2 = new Route();
    vector<pair<double, double > > subGoal;
    // 巡回経路作成のための経路の配列を作成
    subGoal.push_back(make_pair(25,25));
    // subGoal.push_back(make_pair(0,0));
    // subGoal.push_back(make_pair(25,25));
    // subGoal.push_back(make_pair(-25,25));
    // subGoal.push_back(make_pair(0,0));
    // subGoal.push_back(make_pair(-25,25));
    // subGoal.push_back(make_pair(25,25));
    // subGoal.push_back(make_pair(-25,25));
    // 巡回経路を作成
    for(unsigned int i = 0; i < subGoal.size(); i++){
      Vector2D* vec = new Vector2D(subGoal[i].first, subGoal[i].second);
      route2->addNext(vec);
    }
    Carer *c2 = new Carer(cid, route2, v0);
    carers.push_back(*c2);
  }

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

  // 被介護者の作成
  int iniX = 15;
  int iniY = 10;
  int crid = 0;
  int d =0;
  Vector2D* v0 = new Vector2D(0,0);
  int careLevel = 0;
  vector<pair<int,int > > iniPositions;
  vector<int> careLevels;
  // 被介護者の初期位置を入力
  iniPositions.push_back(make_pair(iniX+10,d));
  iniPositions.push_back(make_pair(iniX,iniY+d));
  iniPositions.push_back(make_pair(iniX-10,d));
  iniPositions.push_back(make_pair(iniX,-iniY+d));
  iniPositions.push_back(make_pair(-iniX-10,d));
  iniPositions.push_back(make_pair(-iniX,iniY+d));
  iniPositions.push_back(make_pair(-iniX+10,d));
  iniPositions.push_back(make_pair(-iniX,-iniY+d));
  // iniPositions.push_back(make_pair(iniX+10,-d));
  // iniPositions.push_back(make_pair(iniX,iniY-d));
  // iniPositions.push_back(make_pair(iniX-10,-d));
  // iniPositions.push_back(make_pair(iniX,-iniY-d));
  // iniPositions.push_back(make_pair(-iniX-10,-d));
  // iniPositions.push_back(make_pair(-iniX,iniY-d));
  // iniPositions.push_back(make_pair(-iniX+10,-d));
  // iniPositions.push_back(make_pair(-iniX,-iniY-d));
  // 被介護者の要介護レベルを設定
  careLevels.push_back(0);
  careLevels.push_back(1);
  careLevels.push_back(0);
  careLevels.push_back(0);
  careLevels.push_back(0);
  careLevels.push_back(0);
  careLevels.push_back(0);
  careLevels.push_back(1);
  // careLevels.push_back(1);
  // careLevels.push_back(1);
  // careLevels.push_back(2);
  // careLevels.push_back(2);
  // careLevels.push_back(3);
  // careLevels.push_back(3);
  // careLevels.push_back(3);
  // careLevels.push_back(4);
  // 被介護者を作成
  srand(time(NULL));
  if(PresentTime > 0.99 && PresentTime<1.01){
    for(unsigned i = 0;i < iniPositions.size();i++){
      Vector2D* iniPosition = new Vector2D(iniPositions[i].first, iniPositions[i].second);
      Route* crRoute = new Route();
      careLevel = careLevels[i];
      crRoute->addNext(iniPosition);
      // cout << crid << endl;
      int r = rand()%80 + 1;
      cout << "初期値は" << r << "です" << endl;
      CareRecipient *cr = new CareRecipient(crid, careLevel, crRoute, v0, r);
      // cout << "crRoute:" << crRoute << endl;
      careRecipients.push_back(*cr);
      crid++;
    }
  }


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
