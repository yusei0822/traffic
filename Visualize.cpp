#include <iostream>
#include <autogl.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <math.h>
#include "Drawer.h"
#include "Pedestrian.h"
#include "Carer.h"
#include "Wall.h"
#include "Vector2D.h"
#include "Route.h"
#include <unistd.h>

using namespace std;

extern double PresentTime;
extern double TimeStep;

vector<Pedestrian> pedestrians;
vector<Carer> carers;
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
  // drawPedestrian();
  drawCarer();
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
  // 介護士を生成
  static int cid = 0;
  if((int)PresentTime == 1.0){
    Route* route1 = new Route();
    vector<pair<double, double > > subGoal;
    subGoal.push_back(make_pair(-25,-25));
    subGoal.push_back(make_pair(-25,25));
    subGoal.push_back(make_pair(-25,-25));
    subGoal.push_back(make_pair(-25,25));
    subGoal.push_back(make_pair(-25,-25));
    subGoal.push_back(make_pair(-25,25));
    for(unsigned int i = 0; i < subGoal.size(); i++){
      Vector2D* vec = new Vector2D(subGoal[i].first, subGoal[i].second);
      route1->addNext(vec);
    }
    Vector2D* v0 = new Vector2D(0,0);
    Carer *c1 = new Carer(cid, route1, v0);
    carers.push_back(*c1);
  }
  // cid++;
  // Carer *c2 = new Carer(cid, route, v0);
  // if((int)(PresentTime*10)%50 == 0 && PresentTime<25){
  //   // サブゴールの設定
  //   vector<pair<double, double> > subGoal;
  //   subGoal.push_back(make_pair(-25, -25));
  //   subGoal.push_back(make_pair(-25, 20));
  //   subGoal.push_back(make_pair(25, 20));
  //   subGoal.push_back(make_pair(-25, 20));
  //   subGoal.push_back(make_pair(-25, 0));
  //   subGoal.push_back(make_pair(25, 0));
  //   subGoal.push_back(make_pair(-25, 0));
  //   subGoal.push_back(make_pair(-25, -20));
  //   subGoal.push_back(make_pair(25, -20));
  //   subGoal.push_back(make_pair(-25, -20));
  //   // 経路作成
  //   Route* route = new Route();
  //   for(unsigned int i = 0; i < subGoal.size(); i++){
  //     Vector2D* vec = new Vector2D(subGoal[i].first, subGoal[i].second);
  //     route->addNext(vec);
  //   }
  //   // 初速度ベクトル
  //   Vector2D* v0 = new Vector2D(0,0);
  //   // Pedestrian *p = new Pedestrian(pid, route, v0);
  //   Carer *c = new Carer(cid, route, v0);
  //   carers.push_back(*c);
  //   cid++;
  // }
  AutoGL_DrawView();
  // 可視化時に見やすいように処理を一時的に止める
  usleep(500000 * TimeStep);
}

void quitButtonCallback()
{
    exit(EXIT_SUCCESS);
}
