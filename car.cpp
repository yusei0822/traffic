#include <iostream>
#include <math.h>
#include <vector>
#include "car.h"
#include "link.h"
#include "node.h"
#include "config.h"
#include "calculation.h"

using namespace std;

// グローバル変数の呼び出し
extern double PresentTime;
extern double TimeStep;
extern double Size;
extern vector<NODE> NODE;
extern vector<LINK> LINK;

// 車の初期設定関数
void CAR::INITIAL_CONFIG(int InitialNodeID, int InitialLinkID,
			 int InitialCarID, double InitialVelocity, int InitialDestination)
{
  CarID=InitialCarID;
  LinkID=InitialLinkID;
  CarVelocity=InitialVelocity;
  x=NODE[InitialNodeID].X();
  y=NODE[InitialNodeID].Y();
  Destination=InitialDestination;

  CarUsed=1;
  SignalDecision=1;
  RightTurnDecision=0;

  // LINKIDによって曲がる方向を再設定
  if(LinkID%6==0 && Destination==TurnLeft)
    {
      NextLinkID=LinkID+1;
    }
  else if(LinkID%6==0 && Destination==GoStraight)
    {
      NextLinkID=LinkID+3;
    }
  else if(LinkID%6==0 && Destination==TurnRight)
    {
      NextLinkID=LinkID+4;
    }
}

// 加速度を決定する関数
double CAR::ACCELERATE(double Distance, double DeltaV)
{
  double V0=LINK[LinkID].SPEED_LIMIT()/3.6;//制限速度(m/s)

  static const double d=1.38;//(m)
  static const double t1=2.45;//(s)
  static const double t2=0.77;//(s)
  static const double T=0.74;//(s)
  static const double R1=5.59;//(m)
  static const double R2=98.78;//(m)


  double S=Distance;//(m)
  double dV=DeltaV;//(m/s)
  double V=CarVelocity;//(m/s)


  //S(V)=d+TV
  double fS=d+T*V;

  //V(S,V)=V0*{1-exp((-S+S(V))/R1)}
  double fV=V0*(1-exp((-S+fS)/R1));

  double fF=((fV-V0)/t1)-(dV*H(dV)*exp((-S+fS)/R2)/t2);

  CarAcceleration=((V0-V)/t1)+fF;

  return CarAcceleration;
}

// 加速度を取得する関数
void CAR::GET_ACCELERATION(double Acceleration){
  CarAcceleration=Acceleration;
}

// 計算した加速度から車を動かす関数
void CAR::MOVE(){
   double DeltaX;
   DeltaX=CarVelocity*TimeStep+0.5*CarAcceleration*TimeStep*TimeStep;

   if(DeltaX<0)
     {
       CarVelocity=0;
     }

   else
     {
       x+=DeltaX*LINK[LinkID].DIRECTION_X();
       y+=DeltaX*LINK[LinkID].DIRECTION_Y();
       CarVelocity+=CarAcceleration*TimeStep;
     }

   if((LINK[LinkID].DIRECTION_X()*(LINK[LinkID].END_X()-x)<0 ||
       LINK[LinkID].DIRECTION_Y()*(LINK[LinkID].END_Y()-y)<0) &&
       NextLinkID!=-1)
     {
       switch(LinkID%6)
	 {
	 case 0 :
	   break;
	 case 1 :
	   NextLinkID=LinkID+1;
	   break;
	 case 4 :
	   NextLinkID=LinkID+1;
	   break;

	 default :
	   NextLinkID=-1;
	   break;
	 }

	   x=LINK[LinkID].END_X();
	   y=LINK[LinkID].END_Y();
	   LinkID=NextLinkID;
     }

   if(x<=Size*(-1)||x>=Size||y<=Size*(-1)||y>=Size)
     {CarUsed=0;}
}

int CAR::CAR_USED(){
  return CarUsed;
}

double CAR::X(){
  return x;
}

double CAR::Y(){
  return y;
}

double CAR::V(){
  return CarVelocity;
}

double CAR::LINK_ID(){
  return LinkID;
}

double CAR::NEXT_LINK_ID(){
  return NextLinkID;
}

double CAR::DESTINATION(){
  return Destination;
}

int CAR::RIGHT_TURN_DECISION(int Decision){
  if(RightTurnDecision!=1)
    {
      RightTurnDecision=Decision;
    }

  return RightTurnDecision;
}

int CAR::SIGNAL_DECISION(int Decision){
  if(Decision==0)
    {
      SignalDecision=0;
    }
  else if(Decision==1)
    {
      SignalDecision=1;
    }
  return SignalDecision;
}
