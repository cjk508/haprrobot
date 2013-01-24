
// 0xC1 - M1 forward
// 0xC2 - M1 backward
// 0xC5 - M2 forward
// 0xC6 - M2 backward
// robotCommand(hex, data)
int current_motor_speed_left;
int current_motor_speed_right;


void speedCheck(int speed) {
	if(speed > 25) speed = 25;
}


void se
tLeftMotor(int left) {
	current_motor_speed_left = left;
	if(left < 0 ) {
		left = left*-1;
		speedCheck(left);
		robotCommand(0xC2, left);
	}
	else {
		speedCheck(left);
		robotCommand(0xC1, left);
	}
}

void setRightMotor(int right) {
	current_motor_speed_right = right;
	if(right < 0 ) {
		right = right*-1;
		speedCheck(right);
		robotCommand(0xC2, right);
	}
	else {
		speedCheck(right);
		robotCommand(0xC1, right);
	}
}

void setMotors(int lm, int rm) {
	setLeftMotor(lm);
	setRightMotor(rm);
	//uart.c stuff to do here
}

void forwards(int s) {
	setMotors(s, s);

}

void backwards(int s) {
	setMotors(s, s);
}

void slowDown() {
	int lm, rm, s;
	lm = current_motor_speed_left;
	rm = current_motor_speed_right;
	if(rm == lm) s = lm;
	else s = ((lm+rm)/2);
	brake();
	fowards(s);
}

void right() {
	setMotors(15, 0);
}

void left() {
	setMotors(0, 15);
}

void brake() {
	setMotors(0, 0);
}

void spinLeft() {
	setMotors(-25, 25);

}

void spinRight() {
	setMotors(25, -25);
}

void delay() {
	20000*20000;
}

