
#pragma config(Motor,  port2,           backRight,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           drillRight,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           clawServo,     tmotorServoStandard, openLoop, reversed)
#pragma config(Motor,  port3,           frontRight,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           liftFrame,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           feeder,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           footballRotate, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           clawAngle,     tmotorServoContinuousRotation, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Mechanum wheel test
/*int frontLeftPower;
int frontRightPower;
int backLeftPower;
int backRightPower;*/
float power;
int quad;
int deadZone=50;
float rotationPower;
short frontLeft;
short drillLeft;
short backLeft;
//float drivePower;

//We are going to map the Ch3 and Ch4 to the lateral movement and the Ch1 to rotation

void getPower(){
	int x=vexRT[Ch4];
	int y=vexRT[Ch3];
	power=sqrt(x*x + y*y);

	if (vexRT[Ch1]>deadZone || vexRT[Ch1]<-deadZone){
		rotationPower=abs(vexRT[Ch1]);
	}
	else {
		rotationPower=0;
	}
}

/*void getQuad(){
int signX=sgn(vexRT[Ch4]);
int signY=sgn(vexRT[Ch3]);

if (signX==1 && signY==1){
quad=1;//angles between 0 and pi/2
} else if (signX==1 && signY==-1){
quad=4;	//angles between 0 and -pi/2
} else if (signX==-1 && signY==1){
quad=2;//angles between pi/2 and pi
} else if (signX==-1 && signY==-1){
quad=3;//angles between -pi/2 and -pi
} else if (signX==0 && signY==1){
quad=5;//pi/2
} else if (signX==0 && signY==-1){
quad=6;//-pi/2
} else if (signX==1 && signY==0){
quad=7;//0
} else if (signX==-1 && signY==0){
quad=8;//pi or -pi
} else {
quad=0;//the origin
}
}*/

/*void getRotationPower(){
int rotationChannel=vexRT[Ch1];
float lateralPower=power;

//What we want is for the thing to turn while going forward
/* So, we want one side to turn more than the other, not necessarily in the same direction... So we will be subtracting, so that if the power of the motors is zero, or close to, then one side will turn forward and the other to go backward
}*/

//Now, for the drill
int wheelSpeed;
int setSpeed;
int accelerationWheel;
int timeDelay;
bool drillsAreOn;
int maxDesiredPower;

void wheelAcceleration(){
	if (setSpeed-wheelSpeed>5 || wheelSpeed-setSpeed>5) {
		if (wheelSpeed<setSpeed){
			wheelSpeed+=accelerationWheel;
		}
		else if (wheelSpeed>setSpeed){
			wheelSpeed-=accelerationWheel;
		}
	}
	else {
		wheelSpeed=setSpeed;
	}
}

void changeWheelSpeed(){
	wheelAcceleration();
	motor[drillLeft] = wheelSpeed * drillsAreOn;
	motor[drillRight]=wheelSpeed*drillsAreOn;
}

//For other components
bool frameIsLifting;
int clawCount;

bool buttonBumped(short port){
	if (vexRT[port]==1){
		wait1MSec(500);
		if (vexRT[port]!=1){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

task main()
{
	//drillsAreOn=false;
	frameIsLifting=false;
	motor[clawServo]=127;
	clawCount=0;

	while (true){
		getPower();
		//getQuad();
		deadZone=50;
		if (vexRT[Ch4]>-deadZone && vexRT[Ch4]<deadZone && (vexRT[Ch3]>deadZone || vexRT[Ch3]<-deadZone)){
			//Full forward and backward
			if (vexRT[Ch1]>0){
				motor[frontLeft]=sgn(vexRT[Ch3])*power;
				motor[frontRight]=sgn(vexRT[Ch3])*(power-1.25*abs(vexRT[Ch1]));
				motor[backLeft]=sgn(vexRT[Ch3])*power;
				motor[backRight]=sgn(vexRT[Ch3])*(power-1.25*abs(vexRT[Ch1]));
			}
			else if (vexRT[Ch1]<0){
				motor[frontLeft]=sgn(vexRT[Ch3])*(power-1.25*abs(vexRT[Ch1]));
				motor[frontRight]=sgn(vexRT[Ch3])*power;
				motor[backLeft]=sgn(vexRT[Ch3])*(power-1.25*abs(vexRT[Ch1]));
				motor[backRight]=sgn(vexRT[Ch3])*power;
			}
			else{
				motor[frontLeft]=sgn(vexRT[Ch3])*power;
				motor[frontRight]=sgn(vexRT[Ch3])*power;
				motor[backLeft]=sgn(vexRT[Ch3])*power;
				motor[backRight]=sgn(vexRT[Ch3])*power;
			}
		}
		else if (vexRT[Ch3]>-deadZone && vexRT[Ch3]<deadZone && (vexRT[Ch4]>deadZone || vexRT[Ch4]<-deadZone)){
			//Full strafe left and right
			motor[frontLeft]=sgn(vexRT[Ch4])*power;
			motor[backRight]=sgn(vexRT[Ch4])*power;
			motor[frontRight]=-sgn(vexRT[Ch4])*power;
			motor[backLeft]=-sgn(vexRT[Ch4])*power;
		}
		else if ((vexRT[Ch4]>deadZone || vexRT[Ch4]<-deadZone) && (vexRT[Ch3]>deadZone || vexRT[Ch3]<-deadZone)){
			//The diagonal cases
			//Case 1: Top right and bottom left
			if (sgn(vexRT[Ch3])==sgn(vexRT[Ch4])){
				motor[frontLeft]=sgn(vexRT[Ch4])*power;
				motor[backRight]=sgn(vexRT[Ch4])*power;
				motor[frontRight]=-sgn(vexRT[Ch4])*0.2*power;
				motor[backLeft]=-sgn(vexRT[Ch4])*0.2*power;
			}
			//Case 2: Top left and bottom right
			else if (sgn(vexRT[Ch3])!=sgn(vexRT[Ch4])){
				motor[frontLeft]=-sgn(vexRT[Ch3])*0.2*power;
				motor[backRight]=-sgn(vexRT[Ch3])*0.2*power;
				motor[backLeft]=sgn(vexRT[Ch3])*power;
				motor[frontRight]=sgn(vexRT[Ch3])*power;
			}
		}
		else if (vexRT[Ch3]>-deadZone && vexRT[Ch3]<deadZone && vexRT[Ch4]<deadZone && vexRT[Ch4]>-deadZone){
			if (vexRT[Ch1]>deadZone || vexRT[Ch1]<-deadZone){
				motor[frontLeft]=vexRT[Ch1];
				motor[frontRight]=-vexRT[Ch1];
				motor[backLeft]=vexRT[Ch1];
				motor[backRight]=-vexRT[Ch1];
			}
			else{
				motor[frontLeft]=0;
				motor[frontRight]=0;
				motor[backLeft]=0;
				motor[backRight]=0;
			}
		}
		/*else if (vexRT[Ch1]<-deadZone && vexRT[Ch1]>deadZone){
		//Regular turning
		motor[frontLeft]=vexRT[Ch1];
		motor[backLeft]=vexRT[Ch1];
		motor[frontRight]=-vexRT[Ch1];
		motor[backRight]=-vexRT[Ch1];
		}*/
		//New rotation while moving straight
		else {
			motor[frontLeft]=0;
			motor[frontRight]=0;
			motor[backLeft]=0;
			motor[backRight]=0;
		}

		//Now, for the drill activation
		if (buttonBumped(Btn7U)){
			drillsAreOn=true;
			setSpeed=maxDesiredPower;
			accelerationWheel=5;
			timeDelay=500;
			changeWheelSpeed();
		}
		if (buttonBumped(Btn7D)){
			//drillsAreOn=false;
			accelerationWheel=2;
			timeDelay=250;
			setSpeed=0;
			changeWheelSpeed();
		}
		if (buttonBumped(Btn7R)){
			maxDesiredPower+=1;
			setSpeed=maxDesiredPower;
			changeWheelSpeed();
		}
		if (buttonBumped(Btn7L)){
			maxDesiredPower-=1;
			setSpeed=maxDesiredPower;
			changeWheelSpeed();
		}

		//Lift and lower frame
		if (vexRT[Btn5U]==1){
			motor[liftFrame]=50;
		}
		if (vexRT[Btn5D]==1){
			motor[liftFrame]=-50;
		}

		if (vexRT[Btn5D]==0 && vexRT[Btn5U]==0){
			motor[liftFrame]=0;
		}

		//adjust angle of claw
		if (vexRT[Btn6U]==1){
			motor[clawAngle]=50;
		}
		if (vexRT[Btn6D]==1){
			motor[clawAngle]=-50;
		}

		if (vexRT[Btn6D]==0 && vexRT[Btn6U]==0){
			motor[clawAngle]=0;
		}

		//trigger the reorientation and feeding
		if (vexRT[Btn8U]==1){
			motor[footballRotate]=127;
		}
		if (vexRT[Btn8U]==0){
			motor[footballRotate]=0;
		}
		if (vexRT[Btn8R]==1 && vexRT[Btn8L]==0){
			motor[feeder]=127;
		}
		if (vexRT[Btn8L]==1 && vexRT[Btn8R]==0){
			motor[feeder]=-127;
		}
		if ((vexRT[Btn8L]==0 && vexRT[Btn8R]==0)||(vexRT[Btn8L]==1 && vexRT[Btn8R]==1)){
			motor[feeder]=0;
		}
		if (buttonBumped(Btn8D)){
			switch (clawCount){
			case 0:
				clawCount++;
				motor[clawServo]=127;
				break;
			case 1:
				clawCount--;
				motor[clawServo]=-127;
				break;
			default:
				clawCount=0;
				motor[clawServo]=127;
			}
		}
	}
}
=======
#pragma config(Motor,  port2,           backRight,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           drillRight,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           clawServo,     tmotorServoStandard, openLoop, reversed)
#pragma config(Motor,  port3,           frontRight,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           liftFrame,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           feeder,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           footballRotate, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           clawAngle,     tmotorServoContinuousRotation, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Mechanum wheel test
/*int frontLeftPower;
int frontRightPower;
int backLeftPower;
int backRightPower;*/
float power;
int quad;
int deadZone=50;
float rotationPower;
short frontLeft;
short drillLeft;
short backLeft;
//float drivePower;

//We are going to map the Ch3 and Ch4 to the lateral movement and the Ch1 to rotation

void getPower(){
	int x=vexRT[Ch4];
	int y=vexRT[Ch3];
	power=sqrt(x*x + y*y);

	if (vexRT[Ch1]>deadZone || vexRT[Ch1]<-deadZone){
		rotationPower=abs(vexRT[Ch1]);
	}
	else {
		rotationPower=0;
	}
}

/*void getQuad(){
int signX=sgn(vexRT[Ch4]);
int signY=sgn(vexRT[Ch3]);

if (signX==1 && signY==1){
quad=1;//angles between 0 and pi/2
} else if (signX==1 && signY==-1){
quad=4;	//angles between 0 and -pi/2
} else if (signX==-1 && signY==1){
quad=2;//angles between pi/2 and pi
} else if (signX==-1 && signY==-1){
quad=3;//angles between -pi/2 and -pi
} else if (signX==0 && signY==1){
quad=5;//pi/2
} else if (signX==0 && signY==-1){
quad=6;//-pi/2
} else if (signX==1 && signY==0){
quad=7;//0
} else if (signX==-1 && signY==0){
quad=8;//pi or -pi
} else {
quad=0;//the origin
}
}*/

/*void getRotationPower(){
int rotationChannel=vexRT[Ch1];
float lateralPower=power;

//What we want is for the thing to turn while going forward
/* So, we want one side to turn more than the other, not necessarily in the same direction... So we will be subtracting, so that if the power of the motors is zero, or close to, then one side will turn forward and the other to go backward
}*/

//Now, for the drill
int wheelSpeed;
int setSpeed;
int accelerationWheel;
int timeDelay;
bool drillsAreOn;
int maxDesiredPower;

void wheelAcceleration(){
	if (setSpeed-wheelSpeed>5 || wheelSpeed-setSpeed>5) {
		if (wheelSpeed<setSpeed){
			wheelSpeed+=accelerationWheel;
		}
		else if (wheelSpeed>setSpeed){
			wheelSpeed-=accelerationWheel;
		}
	}
	else {
		wheelSpeed=setSpeed;
	}
}

void changeWheelSpeed(){
	wheelAcceleration();
	motor[drillLeft] = wheelSpeed * drillsAreOn;
	motor[drillRight]=wheelSpeed*drillsAreOn;
}

//For other components
bool frameIsLifting;
int clawCount;

bool buttonBumped(short port){
	if (vexRT[port]==1){
		wait1MSec(500);
		if (vexRT[port]!=1){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

task main()
{
	//drillsAreOn=false;
	frameIsLifting=false;
	motor[clawServo]=127;
	clawCount=0;

	while (true){
		getPower();
		//getQuad();
		deadZone=50;
		if (vexRT[Ch4]>-deadZone && vexRT[Ch4]<deadZone && (vexRT[Ch3]>deadZone || vexRT[Ch3]<-deadZone)){
			//Full forward and backward
			if (vexRT[Ch1]>0){
				motor[frontLeft]=sgn(vexRT[Ch3])*power;
				motor[frontRight]=sgn(vexRT[Ch3])*(power-1.25*abs(vexRT[Ch1]));
				motor[backLeft]=sgn(vexRT[Ch3])*power;
				motor[backRight]=sgn(vexRT[Ch3])*(power-1.25*abs(vexRT[Ch1]));
			}
			else if (vexRT[Ch1]<0){
				motor[frontLeft]=sgn(vexRT[Ch3])*(power-1.25*abs(vexRT[Ch1]));
				motor[frontRight]=sgn(vexRT[Ch3])*power;
				motor[backLeft]=sgn(vexRT[Ch3])*(power-1.25*abs(vexRT[Ch1]));
				motor[backRight]=sgn(vexRT[Ch3])*power;
			}
			else{
				motor[frontLeft]=sgn(vexRT[Ch3])*power;
				motor[frontRight]=sgn(vexRT[Ch3])*power;
				motor[backLeft]=sgn(vexRT[Ch3])*power;
				motor[backRight]=sgn(vexRT[Ch3])*power;
			}
		}
		else if (vexRT[Ch3]>-deadZone && vexRT[Ch3]<deadZone && (vexRT[Ch4]>deadZone || vexRT[Ch4]<-deadZone)){
			//Full strafe left and right
			motor[frontLeft]=sgn(vexRT[Ch4])*power;
			motor[backRight]=sgn(vexRT[Ch4])*power;
			motor[frontRight]=-sgn(vexRT[Ch4])*power;
			motor[backLeft]=-sgn(vexRT[Ch4])*power;
		}
		else if ((vexRT[Ch4]>deadZone || vexRT[Ch4]<-deadZone) && (vexRT[Ch3]>deadZone || vexRT[Ch3]<-deadZone)){
			//The diagonal cases
			//Case 1: Top right and bottom left
			if (sgn(vexRT[Ch3])==sgn(vexRT[Ch4])){
				motor[frontLeft]=sgn(vexRT[Ch4])*power;
				motor[backRight]=sgn(vexRT[Ch4])*power;
				motor[frontRight]=-sgn(vexRT[Ch4])*0.2*power;
				motor[backLeft]=-sgn(vexRT[Ch4])*0.2*power;
			}
			//Case 2: Top left and bottom right
			else if (sgn(vexRT[Ch3])!=sgn(vexRT[Ch4])){
				motor[frontLeft]=-sgn(vexRT[Ch3])*0.2*power;
				motor[backRight]=-sgn(vexRT[Ch3])*0.2*power;
				motor[backLeft]=sgn(vexRT[Ch3])*power;
				motor[frontRight]=sgn(vexRT[Ch3])*power;
			}
		}
		else if (vexRT[Ch3]>-deadZone && vexRT[Ch3]<deadZone && vexRT[Ch4]<deadZone && vexRT[Ch4]>-deadZone){
			if (vexRT[Ch1]>deadZone || vexRT[Ch1]<-deadZone){
				motor[frontLeft]=vexRT[Ch1];
				motor[frontRight]=-vexRT[Ch1];
				motor[backLeft]=vexRT[Ch1];
				motor[backRight]=-vexRT[Ch1];
			}
			else{
				motor[frontLeft]=0;
				motor[frontRight]=0;
				motor[backLeft]=0;
				motor[backRight]=0;
			}
		}
		/*else if (vexRT[Ch1]<-deadZone && vexRT[Ch1]>deadZone){
		//Regular turning
		motor[frontLeft]=vexRT[Ch1];
		motor[backLeft]=vexRT[Ch1];
		motor[frontRight]=-vexRT[Ch1];
		motor[backRight]=-vexRT[Ch1];
		}*/
		//New rotation while moving straight
		else {
			motor[frontLeft]=0;
			motor[frontRight]=0;
			motor[backLeft]=0;
			motor[backRight]=0;
		}

		//Now, for the drill activation
		if (vexRT[Btn7U]==1){
			drillsAreOn=true;
			setSpeed=maxDesiredPower;
			accelerationWheel=5;
			timeDelay=500;
			changeWheelSpeed();
		}
		if (vexRT[Btn7D]==1){
			//drillsAreOn=false;
			accelerationWheel=2;
			timeDelay=250;
			setSpeed=0;
			changeWheelSpeed();
		}
		if (vexRT[Btn7R]==1){
			maxDesiredPower+=1;
		}
		if (vexRT[Btn7L]==1){
			maxDesiredPower-=1;
		}

		//Lift and lower frame
		if (vexRT[Btn5U]==1){
			motor[liftFrame]=50;
		}
		if (vexRT[Btn5D]==1){
			motor[liftFrame]=-50;
		}

		if (vexRT[Btn5D]==0 && vexRT[Btn5U]==0){
			motor[liftFrame]=0;
		}

		//adjust angle of claw
		if (vexRT[Btn6U]==1){
			motor[clawAngle]=50;
		}
		if (vexRT[Btn6D]==1){
			motor[clawAngle]=-50;
		}

		if (vexRT[Btn6D]==0 && vexRT[Btn6U]==0){
			motor[clawAngle]=0;
		}

		//trigger the reorientation and feeding
		if (vexRT[Btn8U]==1){
			motor[footballRotate]=127;
		}
		if (vexRT[Btn8U]==0){
			motor[footballRotate]=0;
		}
		if (vexRT[Btn8R]==1 && vexRT[Btn8L]==0){
			motor[feeder]=127;
		}
		if (vexRT[Btn8L]==1 && vexRT[Btn8R]==0){
			motor[feeder]=-127;
		}
		if ((vexRT[Btn8L]==0 && vexRT[Btn8R]==0)||(vexRT[Btn8L]==1 && vexRT[Btn8R]==1)){
			motor[feeder]=0;
		}
		if (buttonBumped(Btn8D)){
			switch (clawCount){
			case 0:
				clawCount++;
				motor[clawServo]=127;
				break;
			case 1:
				clawCount--;
				motor[clawServo]=-127;
				break;
			default:
				clawCount=0;
				motor[clawServo]=127;
			}
		}
	}
}
