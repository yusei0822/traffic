//車の定義
class CAR
{
  int CarID;
  int LinkID;
  int NextLinkID;
  int CarUsed;
  int Destination;
  double CarVelocity;
  double CarAcceleration;
  double x;
  double y;

  int RightTurnDecision;
  int SignalDecision;

 public:
  void INITIAL_CONFIG(int InitialNodeID, int InitialLinkID,
                      int InitialCarID, double InitialVelocity, int InitialDestination);
  double ACCELERATE(double Distance, double DeltaV);
  void GET_ACCELERATION(double Acceleration);
  void MOVE();
  int CAR_USED();
  double X();
  double Y();
  double V();
  double LINK_ID();
  double NEXT_LINK_ID();
  double DESTINATION();

  int RIGHT_TURN_DECISION(int Decision);
  int SIGNAL_DECISION(int Decision);
};
