#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

int main(void) {
	printf("start");
	

}
void init(int intervalMilSecond) {
	wiringPiSetup();
	int targetPin = 0;
	pinMode(targetPin, OUTPUT);
	int base = 100;//us
	int count = intervalMilSecond * 1000 / base; //10000
	softPwmCreate(targetPin, 0, count);
}
void updateDuty() {

}
