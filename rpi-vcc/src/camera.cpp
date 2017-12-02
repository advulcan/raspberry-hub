#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

const int PIN_X = 5;//pin 18
const int PIN_Y = 6;//pin 22
const int ACR = 200;//20ms/100us
const int STEP = 1;//20ms/100us
const int BUFFER_SIZE = 11;
const int EQUAL_RESULT = 10;
const int MIN_PWM = 7;
const int MAX_PWM = 22;
int currentX = 15;
int currentY = 15;

char *exitControl = "exit";
char *left = "a";
char *right = "d";
char *up = "w";
char *down = "s";

void init();
void refreshPosition();
int add(int pos);
int minus(int pos);

int main(void) {
	init();
	printf("Let's GO!\n");
	//char * te = "exit";
	//char ta [] = "abc";
	char str[BUFFER_SIZE + 1];
	while (true) {
		printf("(%d,%d)>", currentX, currentY);
		fgets(str, BUFFER_SIZE + 1, stdin);
		//printf("%d", strlen(str));
		//printf("Compare Result:%d\n", strcmp(str, exitControl));
		//printf("Compare Result:%d\n", strcmp(str, ta));
		if (strcmp(str, exitControl) == EQUAL_RESULT) {
			printf("Exit!\n");
			break;
		}else if (strcmp(str, left) == EQUAL_RESULT) {
			currentX = minus(currentX);
		}else if (strcmp(str, right) == EQUAL_RESULT) {
			currentX = add(currentX);
		}else if (strcmp(str, up) == EQUAL_RESULT) {
			currentY = add(currentY);
		}else if (strcmp(str, down) == EQUAL_RESULT) {
			currentY = minus(currentY);
		}
		refreshPosition();
	}

}
void init() {
	wiringPiSetup();
	pinMode(PIN_X, OUTPUT);
	pinMode(PIN_Y, OUTPUT);
	softPwmCreate(PIN_X, currentX * STEP, ACR);
	softPwmCreate(PIN_Y, currentY * STEP, ACR);
}
void refreshPosition() {
	softPwmWrite(PIN_X, currentX * STEP);
	softPwmWrite(PIN_Y, currentY * STEP);
}
int add(int pos) {
	if (pos * STEP < MAX_PWM) {
		return pos + 1;
	}
	return pos;
}
int minus(int pos) {
	if (pos > MIN_PWM) {
		return pos - 1;
	}
	return pos;
}

