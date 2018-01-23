#pragma config(Motor,  port2,           backRight,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           frontLeft,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           backLeft,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           drillRight,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           clawServo,     tmotorServoStandard, openLoop, reversed)
#pragma config(Motor,  port3,           frontRight,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           liftFrame,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port10,           feeder,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port1,           footballRotate, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           clawAngle,     tmotorServoContinuousRotation, openLoop, reversed)

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


bool toggleReady = true;
const int deadZone = 50; // TODO: calibrate
int drillSpeed = 100; // TODO: calibrate



void moveRobot()
{
	int control[3];
  control[0] = vexRT[Ch3];
  control[1] = vexRT[Ch1];
  control[2] = vexRT[Ch4];
  int frontLeftPower = 0;
  int frontRightPower = 0;
  int backLeftPower = 0;
  int backRightPower = 0;

  frontLeftPower = 0 - control[1] - control[0] + control[2];
  frontRightPower = 0 - control[1] + control[0] + control[2];
  backLeftPower = 0 - control[1] - control[0] - control[2];
  backRightPower = 0 - control[1] + control[0] - control[2];

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
  int clawCLosed = -127;
  motor[clawServo] = clawCLosed;
  return;
}

void openClaw()
{
  int clawCLosed = 127;
  motor[clawServo] = clawCLosed;
  return;
}

void moveArm(int btn)
{
  int angleSpeed = 37;

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
    motor[feeder] = pushSpeed*(-1);

  return;
}

void stopPusher()
{
  motor[feeder] = 0;
  return;
}

void controlDrill()
{
    if (abs(vexRT[Ch2]) > deadZone+30)
      drillSpeed += vexRT[Ch2] / abs(vexRT[Ch2]) * 3;

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

void controlSorter(int btn)
{
  int rotSpeed = 127;

  if (btn == 1)
    motor[footballRotate] = rotSpeed;
  else
    motor[footballRotate] = rotSpeed*(-1);

  return;
}

void stopSorter()
{
	motor[footballRotate] = 0;
}

// Acts on states


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
    states[4] = 1;
  else if (VexRT[Btn7L])
    states[4] = 0;

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
  else if (VexRT[Btn8L])
    states[6] = 1;
  else
    states[6] = 0;

  // Drill control
  if (VexRT[Btn7U])
    states[7] = 1;
  else if (VexRT[Btn7D])
    states[7] = 0;

  // Sorter control
  if (VexRT[Btn8U])
    states[9] = 1;
  else if (VexRT[Btn8D])
    states[9] = 1;
  else
    states[9] = 0;

  return states;
}

bool toggle(int state)
{
  if (toggleReady && state == 1)
  {
    toggleReady = false;
    return true;
  }
  if (!toggleReady && state == 0)
    toggleReady = true;

  return false;
}



void actOnController()
{
	int * state;
  state = getControllerState();

  // Robot motion
  if (state[0] == 1 || state[1] == 1 || state[2] == 1)
    moveRobot();
  else
    stopRobot();

  // Arm control
  if (state[3] == 1)
    moveArm(vexRT[Btn6U]);
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
    stopDrill();

  // Sorter toggle and stop
  if (state[9] == 1)
    controlSorter(VexRT[Btn8U]);
  else
    stopSorter();


  return;
}

task main()
{
  while (true)
    actOnController();
}
