#pragma config(Sensor, dgtl5,  digitalMotorTest0, sensorDigitalOut)
#pragma config(Sensor, dgtl10, digitalMotorTest1, sensorDigitalHighImpedance)
#pragma config(Sensor, dgtl11, digitalMotorTest2, sensorDigitalOut)
#pragma config(Sensor, dgtl12, digitalMotorTest3, sensorDigitalHighImpedance)
#pragma config(Motor,  port2,           backRight,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           motorMotor2,   tmotorNone, openLoop)
#pragma config(Motor,  port4,           backLeft,      tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port5,           drillLeft,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           drillRight,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           frontLeft,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port8,           motorMotor,    tmotorNone, openLoop)
#pragma config(Motor,  port9,           frontRight,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port10,          anotherMotor,  tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int power5=0;
int power2=0;
int power3=0;
int power4=0;
int power6=0;
int power7=0;
int power8=0;
int power9=0;
int power10=0;
int powerWheels=0;

void motorControl(short port, int power){
	clearTimer(T1);
	while(time1[T1]<=50){
		SensorValue[port]=1;

	}
	while(time1[T1]<100){
			SensorValue[port]=0;
}
	if (time1[T1]==101) clearTimer(T1);

}

task main()
{
/*	while(true){
		motor[port2]=power2;
		motor[port3]=power3;
		motor[port4]=power4;
		motor[port5]=power5;
		motor[port6]=power6;
		motor[port7]=power7;
		motor[port8]=power8;
		motor[port9]=power9;
		motor[anotherMotor]=power10;
		//SensorValue[digitalMotorTest2]=power7;
		//SensorValue[digitalMotorTest3]=power4;
	 	while(true){
	 		motorControl("dgtl11", 127);
	}
	}*/
	while(true){
		motorControl(digitalMotorTest2,127);
	}
}