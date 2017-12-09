#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <math.h>
#include "controller.h"
#include "monitor.h"
/*
//acc ref
digitalWrite(INT1, HIGH);
digitalWrite(INT2, LOW);
digitalWrite(INT3, LOW);
digitalWrite(INT4, HIGH);
*/
int INT1 = 3;//left
int INT2 = 4;//left
int INT3 = 0;//right
int INT4 = 2;//right


char *exitControl = "exit";
char *left = "a";
char *right = "d";
char *up = "w";
char *down = "s";
const int BUFFER_SIZE = 11;
const int EQUAL_RESULT = 10;


void initM()
{
	wiringPiSetup();
	pinMode(INT1, OUTPUT);
	pinMode(INT2, OUTPUT);
	pinMode(INT3, OUTPUT);
	pinMode(INT4, OUTPUT);
}
void leftForward (){
	digitalWrite(INT1, HIGH);
	digitalWrite(INT2, LOW);
}
void rightForward() {
	digitalWrite(INT3, LOW);
	digitalWrite(INT4, HIGH);
}
void leftBackward() {
	digitalWrite(INT1, LOW);
	digitalWrite(INT2, HIGH);
}
void rightBackward() {
	digitalWrite(INT3, HIGH);
	digitalWrite(INT4, LOW);
}
void leftBrake() {
	digitalWrite(INT1, LOW);
	digitalWrite(INT2, LOW);
}
void rightBrake() {
	digitalWrite(INT3, LOW);
	digitalWrite(INT4, LOW);
}
void brake() {
	digitalWrite(INT1, LOW);
	digitalWrite(INT2, LOW);
	digitalWrite(INT3, LOW);
	digitalWrite(INT4, LOW);
}


void keyboardDrive() {
	printf("Let's GO!\n");
	//char * te = "exit";
	//char ta [] = "abc";
	char str[BUFFER_SIZE + 1];
	while (true) {
		fgets(str, BUFFER_SIZE + 1, stdin);
		printf(">");
		//printf("%d", strlen(str));
		//printf("Compare Result:%d\n", strcmp(str, exitControl));
		//printf("Compare Result:%d\n", strcmp(str, ta));
		if (strcmp(str, exitControl) == EQUAL_RESULT) {
			printf("Exit!\n");
			break;
		}
		else if (strcmp(str, left) == EQUAL_RESULT) {
			leftBackward();
			rightForward();
		}
		else if (strcmp(str, right) == EQUAL_RESULT) {
			leftForward();
			rightBackward();
		}
		else if (strcmp(str, up) == EQUAL_RESULT) {
			leftForward();
			rightForward();
		}
		else if (strcmp(str, down) == EQUAL_RESULT) {
			leftBackward();
			rightBackward();
		}
		brake();
	}

}

void byLeftStick(xbox_map_t map) {
	printf("\tleft(%-6d,%-6d)", map.lx, map.ly);
	int x = map.lx;
	int y = map.ly;
	if ((abs(x) < 10000) ){
		x = 0;
	}
	if ((abs(y) < 10000) ){
		y = 0;
	}
	if (abs(x) > abs(y)) {
		if (x > 0) {
				//turnRR();
			}else {
				//turnLL();
			}
	}else {
		if (y < 0) {
			//forwardFF();
		}else {
			//backward();
		}
	}
	if(x==0 && y==0){
		//brakeBB();
	}
}
void byLeftAndTrigger(xbox_map_t map) {
	//printf("\tleft(%-6d,%-6d)", map.lx, map.ly);
	int x = map.lx;
	int y = map.ly;
	int lt = map.lt;
	int rt = map.rt;
	if ((abs(x) < 10000)) {
		x = 0;
	}
	if ((abs(y) < 10000)) {
		y = 0;
	}
	
	if (rt < 0 && lt < 0) {
		if (x < 0) {
			leftBackward();
			rightForward();
		}else if (x > 0) {
			leftForward();
			rightBackward();
		}else {
			brake();
		}
	}else if (rt > 0 && lt<0 ) {
		if (x > 0) {
			leftForward();
			rightBrake();
		}else if(x<0){
			rightForward();
			leftBrake();
		}else {
			leftForward();
			rightForward();
		}
	}else if(lt > 0 && rt<0){
		if (x > 0) {
			leftBackward();
			rightBrake();
		}else if (x<0) {
			rightBackward();
			leftBrake();
		}else {
			rightBackward();
			leftBackward();
		}
	}else {
		brake();
	}
	
}

int stickDrive() {
	int xbox_fd;
	xbox_map_t map;
	int len, type;
	int axis_value, button_value;
	int number_of_axis, number_of_buttons;

	memset(&map, 0, sizeof(xbox_map_t));
	map.lt = -32767;
	map.rt = -32767;

	xbox_fd = xbox_open("/dev/input/js0");
	if (xbox_fd < 0) {
		return -1;
	}

	while (1) {
		len = xbox_map_read(xbox_fd, &map);
		if (len < 0)
		{
			usleep(10 * 1000);
			continue;
		}

		/*printf("\rTime:%8d A:%d B:%d X:%d Y:%d LB:%d RB:%d start:%d back:%d home:%d LO:%d RO:%d XX:%-6d YY:%-6d LX:%-6d LY:%-6d RX:%-6d RY:%-6d LT:%-6d RT:%-6d",
			map.time, map.a, map.b, map.x, map.y, map.lb, map.rb, map.start, map.back, map.home, map.lo, map.ro,
			map.xx, map.yy, map.lx, map.ly, map.rx, map.ry, map.lt, map.rt);*/
	/*	printf("\rLX:%-6d LY:%-6d RX:%-6d RY:%-6d LT:%-6d RT:%-6d",map.lx, map.ly, map.rx, map.ry, map.lt, map.rt);
		fflush(stdout);*/
		refresh(map);

		//byLeftStick(map);
		byLeftAndTrigger(map);
	}

	xbox_close(xbox_fd);
	return 0;
}

int main(void)
{
	initM();
	initMonitor(29);
	//autoDrive();
	stickDrive();

}