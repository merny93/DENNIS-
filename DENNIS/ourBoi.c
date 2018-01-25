#pragma config(Motor,  port1,           footballRotate, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port2,           backRight,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           frontRight,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           drillRight,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           clawServo,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftFrame,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           backLeft,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           frontLeft,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           clawAngle,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port10,          feeder,        tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

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


#define DEADZONE 50 // TODO: calibrate
#define STRAFE 20
#define ANGLESPEED 70
#define LIFTSPEED 127
#define ROTSPEED 127
int drillSpeed = 100; // TODO: calibrate



void moveRobot()
{
	int control[3];
  control[0] = vexRT[Ch3];
  control[1] = vexRT[Ch1];
  control[2] = vexRT[Ch4]/2;
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
  if (btn == 1)
    motor[liftFrame] = LIFTSPEED;
  else
    motor[liftFrame] = LIFTSPEED * -1;
  return;
}

void stopWinch()
{
  motor[liftFrame] = 0;
  return;
}

void closeClaw()
{
  int clawClosed = -127;
  motor[clawServo] = clawClosed;
  return;
}

void openClaw()
{
  int clawClosed = 127;
  motor[clawServo] = clawClosed;
  return;
}

void stopClaw()
{
	int clawStop = 0;
	motor[clawServo] = clawStop;
	return;
}

void moveArm(int btn)
{

  if (btn == 1)
    motor[clawAngle] = ANGLESPEED;
  else
    motor[clawAngle] = (ANGLESPEED) * (-1);

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
    if (abs(vexRT[Ch2]) > DEADZONE + 30)
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
  if (btn == 1)
    motor[footballRotate] = ROTSPEED;
  else
    motor[footballRotate] = ROTSPEED*(-1);

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
  if (abs(vexRT[Ch3]) > DEADZONE)
    states[0] = 1;
  else
    states[0] = 0 ;

  // Drive rotation
  if (abs(vexRT[Ch1]) > DEADZONE)
    states[1] = 1;
  else
    states[1] = 0 ;

  // Drive strafe
  if (abs(vexRT[Ch4]) > DEADZONE)
    states[2] = 1;
  else
    states[2] = 0 ;

  // Arm control
  if (vexRT[Btn6U])
    states[3] = 1;
  else if (vexRT[Btn6D])
    states[3] = 1;
  else
    states[3] = 0;

  // Claw control
  if (vexRT[Btn7R])
    states[4] = 1;
  else if (vexRT[Btn7L])
    states[4] = 2;
  else
  	states[4] = 0;

  // Winch control
  if (vexRT[Btn5U])
    states[5] = 1;
  else if (vexRT[Btn5D])
    states[5] = 1;
  else
    states[5] = 0;

  //Pusher control
  if (vexRT[Btn8R])
    states[6] = 1;
  else if (vexRT[Btn8L])
    states[6] = 1;
  else
    states[6] = 0;

  // Drill control
  if (vexRT[Btn7U])
    states[7] = 1;
  else if (vexRT[Btn7D])
    states[7] = 0;

  // Sorter control
  if (vexRT[Btn8U])
    states[9] = 1;
  else if (vexRT[Btn8D])
    states[9] = 1;
  else
    states[9] = 0;

  return states;
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
  else if (state[4] == 2)
    closeClaw();
  else
  	stopClaw();

  // Winch control
  if (state[5] == 1)
    moveWinch(vexRT[Btn5U]);
  else
    stopWinch();

  // Pusher control
  if (state[6] == 1)
    movePusher(vexRT[Btn8R]);
  else
    stopPusher();

  // Drill control
  if (state[7] == 1)
    controlDrill();
  else
    stopDrill();

  // Sorter toggle and stop
  if (state[9] == 1)
    controlSorter(vexRT[Btn8U]);
  else
    stopSorter();


  return;
}

task main()
{
  while (true)
    actOnController();
}
