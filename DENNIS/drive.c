/*

  Controller state array:
    [0]: y-axis on analog left for forward/backward(ch3)
    [1]: x-axis on analog right for rotation (ch1)
    [2]: x-axis on analog left for strafe (ch4)
    [3]: Right bumpers for rotating arm (Btn6)
    [4]: Left side pad button left and right for moving pusher (Btn7)
    [5]: Left bumpers for winching up or down (Btn5)
    [6]:
*/
void actOnController();
int getControllerState();

void moveRobot(int ctrl);
void stopRobot();
void moveArm();
void stopArm(int btn);
void openClaw();
void closeClaw();
void moveWinch();
void stopWinch();
void movePusherForward();
void movePusherBackward();
void controlDrills();
void stopDrills();
bool toggleSorter(int state);
void stopSorter();


bool toggleReady = true;
const int deadZone = 50; // TODO: calibrate
int drillSpeed = 100; // TODO: calibrate

int main()
{
  while (true)
    actOnController();

  return 0;
}

// Acts on states
void actOnController()
{
  int state[10] == getControllerState();

  // Robot motion
  if (state[0] == 1 || state[1] == 1 || state[2] == 1)
    moveRobot();
  else
    stopRobot();

  // Arm control
  if (state[3] == 1)
    moveArm(VexRT[Btn6U]);
  else
    stopArm();

  // Claw control
  if (state[4] == 1)
    openClaw();
  else
    closeClaw();

  // Winch control
  if (state[5] == 1)
    moveWinch(VexRT[Btn5U]);
  else
    stopWinch();

  // Pusher control
  if (state[6] == 1)
    movePusher(VexRT[Btn8R]);
  else
    stopPusher();

  // Drill control
  if (state[7] == 1)
    controlDrill();
  else
    stopDrills();

  // Sorter toggle and stop
  if (state[9] == 1)
    stopSorter();
  else if (state[8] == 1)
    toggleSorter(1);
  else if (state[8] == 0)
    toggleSorter(0);

  return 0;
}

// Sets states
int * getControllerState()
{
  int states[10];

  // Drive forward/back
  if (abs(VexRT[Ch3]) > deadZone)
    states[0] = 1;
  else
    states[0] = 0 ;

  // Drive rotation
  if (abs(VexRT[Ch1]) > deadZone)
    states[1] = 1;
  else
    states[1] = 0 ;

  // Drive strafe
  if (abs(VexRT[Ch4]) > deadZone)
    states[2] = 1;
  else
    states[2] = 0 ;

  // Arm control
  if (VexRT[Btn6U])
    states[3] = 1;
  else if (VexRT[Btn6D])
    states[3] = 1;
  else
    states[3] = 0;

  // Claw control
  if (VexRT[Btn7R])
    state[4] = 1;
  else if (VexRT[Btn7L])
    state[4] = 0;

  // Winch control
  if (VexRT[Btn5U])
    states[5] = 1;
  else if (VexRT[Btn5D])
    states[5] = 1;
  else
    states[5] = 0;

  //Pusher control
  if (VexRT[Btn8R])
    states[6] = 1;
  else if (VexRT[Btn8R])
    states[6] = 1;
  else
    states[6] = 0;

  // Drill control
  if (VexRT[Btn7U])
    state[7] = 1;
  else if (VexRT[Btn7D])
    state[7] = 0;

  // Sorter toggle
  if (VexRT[Btn8U])
    state[8] = 1;
  else
    state[8] = 0;

  // Sorter stop
  if (VexRT[Btn8D])
    state[9] = 1;
  else
    state[9] = 0;

  return states;
}

bool toggle(int state)
{
  if (sorterReady && state == 1)
  {
    sorterReady = false;
    return true;
  }
  if (!sorterReady && state == 0)
    sorterReady = true;

  return false;
}
void toggleSorter(int state)
{
  if (toggle(state))
    do_toggle_thing

  return;
}


void moveRobot()
{
  int control[3] = {vexRT[Ch3], vexRT[Ch1], vexRT[Ch4]}
  int frontLeftPower = 0;
  int frontRightPower = 0;
  int backLeftPower = 0;
  int backRightPower = 0;

  frontLeftPower = control[0] + control[1] + control[2];
  frontRightPower = control[0] - control[1] - control[2];
  backLeftPower = control[0] + control[1] - control[2];
  backRightPower = control[0] - control[1] + control[2];

  motor[frontLeft] = frontLeftPower;
  motor[frontRight] = frontRightPower;
  motor[backLeft] = backLeftPower;
  motor[backRight] = backRightPower;
  return;
}

void stopRobot()
{
  motor[frontLeft] = 0;
  motor[frontRight] = 0;
  motor[backLeft] = 0;
  motor[backRight] = 0;

  return;
}

void moveWinch(int btn)
{
  int liftSpeed = 127;

  if (btn == 1)
    motor[liftFrame] = liftSpeed;
  else
    motor[liftFrame] = liftSpeed*-1;
  return;
}

void stopWinch()
{
  motor[liftFrame] = 0;
  return;
}

void closeClaw()
{
  int clawCLosed = -120;
  motor[clawServo] = clawCLosed;
  return;
}

void openClaw()
{
  int clawCLosed = 120;
  motor[clawServo] = clawCLosed;
  return;
}

void moveArm(int btn)
{
  int angleSpeed = 17;

  if (btn == 1)
    motor[clawAngle] = angleSpeed;
  else
    motor[clawAngle] = angleSpeed*-1;

  return;
}


void stopArm()
{
  motor[clawAngle] = 0;

  return;
}


void movePusher(int btn)
{
  int pushSpeed = 127;

  if (btn == 1)
    motor[feeder] = pushSpeed;
  else
    motor[feeder] = pushSpeed*-1;

  return;
}

void stopPusher()
{
  motor[feeder] = 0;
  return;
}

void controlDrill()
{
    if (abs(VexRT[Ch]) > deadZone+30)
      drillSpeed += VexRT[Ch2] / abs(VexRT[Ch2]) * 3;

    if (drillSpeed > 127)
      drillSpeed = 127;
    else if (drillSpeed < 0)
      drillSpeed = 0;

    motor[drillRight] = drillSpeed;
    return;
}


void stopDrill()
{
  motor[drillRight] = 0;

  return;
}
