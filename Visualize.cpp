#include <iostream>
#include <autogl.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include "Drawer.h"
#include "Pedestrian.h"
#include "Vector2D.h"
#include "Route.h"

using namespace std;

extern double PresentTime;
extern double TimeStep;

class Pedestrian;

vector<Pedestrian> pedestrians;

//再描画
static void redrawView();

//アイドルイベント
static void idleEvent();

// Animateボタン用関数
static void animateButtonCallback();

// Quitボタン用関数
static void quitButtonCallback();

double Size;

void visualize()
{
  //ビューのパラメータ設定
  AutoGL_SetBackgroundColor(1, 1, 1);
  AutoGL_SetViewSize(300);           //ビューの大きさ
  AutoGL_SetViewCenter(0, 0, 0);     //注視点
  AutoGL_SetViewDirection(0, 0, 1);  //視線方向

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
  drawPedestrian();
  drawWall();
  drawWall2();
  drawWall3();
  drawWall4();

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

  if((int)(PresentTime*10)%10 == 0)

  cout<<"Time:"<<(int)PresentTime<<endl;

  static int pid = 0;
  if((PresentTime*10)%10 == 0)
  {
    // サブゴールの設定
    vector<pair<double, double> > point;
    point.push_back(make_pair(-90, -90));
    point.push_back(make_pair(-90, 90));
    point.push_back(make_pair(90, 90));
    point.push_back(make_pair(-90, 90));
    point.push_back(make_pair(-90, 0));
    point.push_back(make_pair(90, 0));
    point.push_back(make_pair(-90, 0));
    point.push_back(make_pair(-90, -90));
    point.push_back(make_pair(90, -90));
    point.push_back(make_pair(-90, -90));

    // 経路作成
    Route* route = new Route();
    for(int i = 0; i < point.size(); i++)
    {
      Vector2D* vec = new Vector2D(point[i].first, point[i].second);
      route->addNext(vec);
    }

    // 初速度ベクトル
    Vector2D* v0 = new Vector2D(0,0);

    Pedestrian *p = new Pedestrian(pid, route, v0);
    pedestrians.push_back(*p);
    pid++;
  }


  AutoGL_DrawView();
}

void quitButtonCallback()
{
    exit(EXIT_SUCCESS);
}
