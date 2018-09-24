class Pedestrian{
  int id;
  double x;
  double y;
  double z;
  double velocity;
  double acceleration;

public:
  // コンストラクタ
  Pedestrian(double x, double y, double z);
  double X();
  double Y();
  double Z();
  double Velocity();
  void Accelerate();
  void Walk();
};
