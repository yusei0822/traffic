#ifndef __WALL_H__
#define __WALL_H__

class Wall{
  double _x;
  double _y;
  double _dx;
  double _dy;
  double _angle;
  double _theta;

public:
  // コンストラクタ
  Wall(double x, double y, double dx, double dy, double angle);

  // デストラクタ
  ~Wall();

  // x座標を返す
  double x();

  // y座標を返す
  double y();

  // x座標方向の幅を返す
  double dx();

  // y座標方向の幅を返す
  double dy();

  // 角度を返す
  double angle();
};

#endif
