#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <math.h>
#include "controller.h"
//int L1 = 0;
//int L2 = 2;
//int R1 = 3;
//int R2 = 4;
int L1 = 0;
int L2 = 2;
int R1 = 4;
int R2 = 3;


char *exitControl = "exit";
char *left = "a";
char *right = "d";
char *up = "w";
char *down = "s";
const int BUFFER_SIZE = 11;
const int EQUAL_RESULT = 10;

void initM();
//void autoDrive();
//void keyboardDrive();

void forward(int x, int y);
void backward(int x, int y);
void brake(int x, int y);
void turnLL();
void turnRR();
void forwardFF();
void backward();
void brakeBB();

//void autoDrive()
//{
//	for (;;)
//	{
//		turnLL();
//		brake();
//		forward();
//		brake();
//		turnLL();
//		brake();
//		forward();
//		brake();
//	}
//}
void initM()
{
	wiringPiSetup();
	pinMode(L1, OUTPUT);
	pinMode(L2, OUTPUT);
	pinMode(R1, OUTPUT);
	pinMode(R2, OUTPUT);
}
void forward (int x, int y){
	digitalWrite(x, LOW);
	digitalWrite(y, HIGH);
}
void backward(int x, int y){
	digitalWrite(x, HIGH);
	digitalWrite(y, LOW);
}
void brake(int x, int y) {
	digitalWrite(x, LOW);
	digitalWrite(y, LOW);
}

void turnLL()
{
	forward(L1, L2);
	backward(R1, R2);
	//delay(1000);
}

void turnRR()
{
	forward(R1, R2);
	backward(L1, L2);
	//delay(1000);
}

void forwardFF()
{
	forward(L1, L2);
	forward(R1, R2);
	//delay(1000);
}

void backward()
{
	backward(L1, L2);
	backward(R1, R2);
	//delay(1000);
}

void brakeBB()
{
	brake(L1, L2);
	brake(R1, R2);
	//delay(1000);
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
			turnLL();
		}
		else if (strcmp(str, right) == EQUAL_RESULT) {
			turnRR();
		}
		else if (strcmp(str, up) == EQUAL_RESULT) {
			forwardFF();
		}
		else if (strcmp(str, down) == EQUAL_RESULT) {
			backward();
		}
		brakeBB();
	}

}

void checkLeftStick(xbox_map_t map) {
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
				turnRR();
			}else {
				turnLL();
			}
	}else {
		if (y < 0) {
			forwardFF();
		}else {
			backward();
		}
	}
	if(x==0 && y==0){
		brakeBB();
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

		printf("\rTime:%8d A:%d B:%d X:%d Y:%d LB:%d RB:%d start:%d back:%d home:%d LO:%d RO:%d XX:%-6d YY:%-6d LX:%-6d LY:%-6d RX:%-6d RY:%-6d LT:%-6d RT:%-6d",
			map.time, map.a, map.b, map.x, map.y, map.lb, map.rb, map.start, map.back, map.home, map.lo, map.ro,
			map.xx, map.yy, map.lx, map.ly, map.rx, map.ry, map.lt, map.rt);
		fflush(stdout);
		checkLeftStick(map);
	}

	xbox_close(xbox_fd);
	return 0;
}

int main(void)
{
	initM();
	//autoDrive();
	stickDrive();

}