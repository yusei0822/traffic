#include <iostream>
#include <autogl.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <math.h>
#include <time.h>
#include <algorithm>
#include "Drawer.h"
#include "Calculation.h"
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
extern vector<CareRecipient> careRecipients;
extern vector<Carer> carers;

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
  clock_t drawStart = clock();
  AutoGL_SetViewRedrawCallback(redrawView);
  clock_t drawEnd = clock();
  const double time = static_cast<double>(drawEnd - drawStart)/CLOCKS_PER_SEC*1000.0;
  cout << "歩行者と壁の記述にかかった時間は" << time << "秒です" << endl;

 /* おまじない */
  AutoGL_SetMode2D(AUTOGL_MODE_2D_SCALE);  /* マウスで回転 */
  AutoGL_SetDefaultCallbackInMode2D(NULL);
  AutoGL_EnableDragInMode2D();             /* ドラッグ有効 */
  AutoGL_EnableIdleEvent();
  AutoGL_SetPanelInMode2D();               /* 移動拡大縮小など */

  /* Animateボタンをつける */
  clock_t animateStart = clock();
  AutoGL_AddCallback(animateButtonCallback, "animateButtonCallback");
  AutoGL_SetLabel("Animate");
  clock_t animateEnd = clock();
  const double time_a = static_cast<double>(animateEnd - animateStart)/CLOCKS_PER_SEC*1000.0;
  cout << "animateにかかった時間は" << time_a << "秒です" << endl;


  /* Quitボタンをつける */
  AutoGL_AddCallback(quitButtonCallback, "qiutButtonCallback");
  AutoGL_SetLabel("Quit");

  Size=AutoGL_GetViewSize();
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

  // コンソール上で見やすいように1分ごとに時間を表示
  if((int)(PresentTime*10)%600 == 0){
    cout<<"Time:"<<(int)PresentTime/60<<"分"<<endl;
  }

// 2時間ごとに結果を出力する
  if((int)(PresentTime*10)%72000 == 0){
    int success = 0;
    int totalNumber = 0;
    double totalSeconds = 0;
    for(unsigned int i = 0;i<careRecipients.size();i++){
      success += careRecipients[i].numberOfSuccess();
      totalNumber += careRecipients[i].numberOfGoingToToilet();
      totalSeconds += careRecipients[i].numberOfEndureSeconds();
    }
    cout << "今回の結果は" << totalNumber << "回中" <<  success << "回介護に成功し、延べ我慢時間は" << totalSeconds << "秒でした。" << endl;
  }

  // 毎秒ごとに被介護者の膀胱の値を加算
  for(unsigned i=0;i < careRecipients.size();i++){
    // 実際には72秒で1追加する
    if((int)(PresentTime*10)%720 == 0){
      careRecipients[i].urinaryIntention();
    }
  }

  // トイレを我慢している人がいればその人が我慢している秒数を加算
  for(unsigned int i = 0;i<careRecipients.size();i++){
    if(careRecipients[i].toiletCapacity()>100.0){
      careRecipients[i].addEnduringSeconds();
    }
  }

  // 毎秒ごとにトイレに行きたいかどうかを判定
  for(unsigned i=0;i < careRecipients.size();i++){
    careRecipients[i].toiletIndicate();
  }

  // 要介護イベントが発生した時に、距離的に近い介護者が非介護者の元へ向かう
  if((int)(PresentTime*10)%10 == 0){

      vector <Carer> preCarers;
      for(unsigned int i = 0;i<carers.size();i++)
      {
        if(carers[i].status()==0)
        {
          preCarers.push_back(carers[i]);
        }
      }

      vector <CareRecipient> precareRecipients;
      for(unsigned int i = 0;i<careRecipients.size();i++)
      {
        if(careRecipients[i].status()==1)
        {
          precareRecipients.push_back(careRecipients[i]);
        }
      }

      vector <vector <double> > lengthTable;
      for(unsigned int i = 0; i < precareRecipients.size(); i++)
      {
        vector<double> tmpLengths;
        for(unsigned int j = 0; j < preCarers.size(); j++)
        {
          double tmpLength = length(precareRecipients[i].position(),preCarers[j].position());
          tmpLengths.push_back(tmpLength);
        }
        lengthTable.push_back(tmpLengths);
      }

      int numCarers = preCarers.size();
      int numCareRecipients = precareRecipients.size();
      while( numCarers != 0 && numCareRecipients != 0)
      {
        double minLength = 10000000;
        int minCareIndex;
        int minReciIndex;
        for(unsigned int i = 0; i < precareRecipients.size(); i++)
        {
          int index = min_element(lengthTable[i].begin(),lengthTable[i].end()) - lengthTable[i].begin();

//          cout << "debug1 " <<  index << endl;
          if (minLength > lengthTable[i][index])
          {
            minLength = lengthTable[i][index];
            minCareIndex = index;
            minReciIndex = i;
          }
        }
//        cout << "debug2 " << minCareIndex << " " << minReciIndex << endl;
        int crid = precareRecipients[minReciIndex].id();
        int cid = preCarers[minCareIndex].id();

        Vector2D* pickup = precareRecipients[crid].position();
        preCarers[cid].changeStatus();
        preCarers[cid].restroom(pickup);
        precareRecipients[crid].changeStatus();

        for(unsigned int i = 0; i < precareRecipients.size(); i++)
        {
          lengthTable[i][minCareIndex] = 10000000;
        }

        for(unsigned int i = 0; i < preCarers.size(); i++)
        {
          lengthTable[minCareIndex][i] = 10000000;
        }
        numCarers--;
        numCareRecipients--;
      }
    }

    AutoGL_DrawView();
  // 可視化時に見やすいように処理を一時的に止める
  // usleep(100000 * TimeStep);

  //2時間たったら強制的にシミュレーションを終わる
  if((int)(PresentTime*10)%72000 == 0){
    exit(EXIT_SUCCESS);
  }
}

void quitButtonCallback(){
    exit(EXIT_SUCCESS);
}
