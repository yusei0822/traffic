#ifndef __CALCULATION_H__
#define __CALCULATION_H__

class Vector2D;

// 2点間の距離を計算する関数
double length(double x1,double y1, double x2, double y2);

// 線分と点の距離を返す関数
double min_d2(x0, y0, x1, y1, x2, y2);

int H(double x);

// ベクトルの足し算をする関数
Vector2D* aVec(Vector2D* v1, Vector2D* v2);

// ベクトルの引き算をする関数
Vector2D* sVec(Vector2D* v1, Vector2D* v2);

// ベクトルを定数倍する関数
Vector2D* mVec(double k, Vector2D* v);

// 単位ベクトルを返す関数
Vector2D* uVec(Vector2D* v);

#endif
