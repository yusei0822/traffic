// クラスの定義と関数の定義を行う

class Carer : public Pedestrian
{
private:
  // ID
  int _cid;
public:
  // イベントフラグを認知したか
  vool check();
  // 介護対象の座標を取得
  Vector2D* carePosition();
  // 介護行動を開始
  void care();
};
