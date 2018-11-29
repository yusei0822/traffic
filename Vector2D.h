#ifndef __Vector2D_H__
#define __Vector2D_H__

class Vector2D{
  double _x;
  double _y;

public:
  // コンストラクタ
  Vector2D(double x, double y);

  // デストラクタ
  ~Vector2D();

  // x座標を返す
  double x();

  // y座標を返す
  double y();

  // 大きさを返す
  double size();
};

#endif
