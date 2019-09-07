#include <iostream>
#include <autogl.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <math.h>
#include <time.h>
#include "Drawer.h"
#include "Calculation.h"
#include "Pedestrian.h"
#include "Carer.h"
#include "CareRecipient.h"
#include "Wall.h"
#include "Vector2D.h"
#include "Route.h"
#include <unistd.h>
#include <stdio.h>

using namespace std;

extern double PresentTime;
extern double TimeStep;

// 各モデルの配列
vector<Pedestrian> pedestrians;
vector<Carer> carers;
vector<CareRecipient> careRecipients;
vector<Wall> walls;

//再描画
static void redrawView();

//アイドルイベント
static void idleEvent();

// Animateボタン用関数
static void animateButtonCallback();

// Quitボタン用関数
static void quitButtonCallback();

double Size;

// main関数の中で走る関数
void visualize()
{
  //ビューのパラメータ設定
  AutoGL_SetBackgroundColor(1, 1, 1);
  AutoGL_SetViewSize(50);           //ビューの大きさ
  AutoGL_SetViewCenter(0, 0, 0);     //注視点
  AutoGL_SetViewDirection(0, 0, 1);  //視線方向

  //歩行者と壁の記述
  AutoGL_SetViewRedrawCallback(redrawView);

 /* おまじない */
  AutoGL_SetMode2D(AUTOGL_MODE_2D_SCALE);  /* マウスで回転 */
  AutoGL_SetDefaultCallbackInMode2D(NULL);
  AutoGL_EnableDragInMode2D();             /* ドラッグ有効 */
  AutoGL_EnableIdleEvent();
  AutoGL_SetPanelInMode2D();               /* 移動拡大縮小など */

  /* Animateボタンをつける */
  AutoGL_AddCallback(animateButtonCallback, "animateButtonCallback");
  AutoGL_SetLabel("Animate");

  /* Quitボタンをつける */
  AutoGL_AddCallback(quitButtonCallback, "qiutButtonCallback");
  AutoGL_SetLabel("Quit");

  Size=AutoGL_GetViewSize();

  //乱数指定
  srand((unsigned)time(NULL));

}

// 壁と歩行者の記述
void redrawView()
{
  drawCarer();
  drawCareRecipient();
  drawWall();
}

void animateButtonCallback(void)
{
    static int idleEventIsOn = 0;

    if (idleEventIsOn)
    {
        AutoGL_SetIdleEventCallback(NULL);
        idleEventIsOn = 0;
    }
    else
    {
        AutoGL_SetIdleEventCallback(idleEvent);
        idleEventIsOn = 1;
    }
}


//一つのタイムステップで実行する操作
void idleEvent()
{
  PresentTime += TimeStep;
  // コンソール上で見やすいように時間を表示
  if((int)(PresentTime*10)%10 == 0)
  cout<<"Time:"<<(int)PresentTime<<endl;

  if(PresentTime > 7.99 && PresentTime<8.01){
    careRecipients[0].changeStatus();
  }

  if(PresentTime > 7.99 && PresentTime<8.01){
    careRecipients[6].changeStatus();
  }

  if(PresentTime > 10.99 && PresentTime<11.01){
    careRecipients[7].changeStatus();
  }

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
    subGoal.push_back(make_pair(-25,25));
    // subGoal.push_back(make_pair(-25,25));
    // subGoal.push_back(make_pair(25,25));
    // subGoal.push_back(make_pair(-25,25));
    // subGoal.push_back(make_pair(25,25));
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


  // 被介護者の作成
  int iniX = 15;
  int iniY = 7;
  int crid = 0;
  int careLevel = 0;
  vector<pair<int,int > > iniPositions;
  vector<int> careLevels;
  // 被介護者の初期位置を入力
  iniPositions.push_back(make_pair(iniX+7,0));
  iniPositions.push_back(make_pair(iniX,iniY));
  iniPositions.push_back(make_pair(iniX-7,0));
  iniPositions.push_back(make_pair(iniX,-iniY));
  iniPositions.push_back(make_pair(-iniX-7,0));
  iniPositions.push_back(make_pair(-iniX,iniY));
  iniPositions.push_back(make_pair(-iniX+7,0));
  iniPositions.push_back(make_pair(-iniX,-iniY));
  // 被介護者の要介護レベルを設定
  careLevels.push_back(1);
  careLevels.push_back(1);
  careLevels.push_back(2);
  careLevels.push_back(2);
  careLevels.push_back(3);
  careLevels.push_back(3);
  careLevels.push_back(3);
  careLevels.push_back(4);
  // 被介護者を作成
  if((int)(PresentTime*10)/10 == 1.0){
    for(unsigned i = 0;i < iniPositions.size();i++){
      Vector2D* iniPosition = new Vector2D(iniPositions[i].first, iniPositions[i].second);
      Route* crRoute = new Route();
      careLevel = careLevels[i];
      crRoute->addNext(iniPosition);
      // cout << crid << endl;
      CareRecipient *cr = new CareRecipient(crid, careLevel, crRoute, v0);
      // cout << "crRoute:" << crRoute << endl;
      careRecipients.push_back(*cr);
      crid++;
    }
  }
  AutoGL_DrawView();
  // 可視化時に見やすいように処理を一時的に止める
  usleep(1000000 * TimeStep);
}

void quitButtonCallback()
{
    exit(EXIT_SUCCESS);
}
