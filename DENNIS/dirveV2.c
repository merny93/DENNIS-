/*

From magicode's (very well-done) tutorial:
FrontLeft = Ch3 + Ch1 + Ch4
RearLeft = Ch3 + Ch1 - Ch4
FrontRight = Ch3 - Ch1 - Ch4
RearRight = Ch3 - Ch1 + Ch4

Where:
Ch1 = Right joystick X-axis
Ch3 = Left joystick Y-axis
Ch4 = Left joystick X-axis
Where positive is to the right or up on the joysticks.

*/

//logic for the wheelSpeed

void moveRobot(){

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

}

void stopRobot(){

  motor[frontLeft] = 0;
  motor[frontRight] = 0;
  motor[backLeft] = 0;
  motor[backRight] = 0;

}

void moveWinch(int btn){

  int liftSpeed = 127;

  if (btn == 1)
    motor[liftFrame] = liftSpeed;
  else
    motor[liftFrame] = liftSpeed*-1;

}

void stopWinch(){

  motor[liftFrame] = 0;

}

void closeClaw(){

  int clawCLosed = -120;
  motor[clawServo] = clawCLosed;

}

void openClaw(){

  int clawCLosed = 120;
  motor[clawServo] = clawCLosed;

}


void moveArm(int btn){

  int angleSpeed = 17;

  if (btn == 1)
    motor[clawAngle] = angleSpeed;
  else
    motor[clawAngle] = angleSpeed*-1;

}


void stopArm(){

  motor[clawAngle] = 0;

}


void movePusher(int btn){

  int pushSpeed = 127;

  if (btn == 1)
    motor[feeder] = pushSpeed;
  else
    motor[feeder] = pushSpeed*-1;

}


void stopPusher(){

  motor[feeder] = 0;

}

void controlDrill() {

    if (abs(VexRT[Ch]) > deadZone+30)
      drillSpeed += VexRT[Ch2] / abs(VexRT[Ch2]) * 3;

    if (drillSpeed > 127)
      drillSpeed = 127;
    else if (drillSpeed < 0)
      drillSpeed = 0;

    motor[drillRight] = drillSpeed;

}


void stopDrill() {

  motor[drillRight] = 0;

}
