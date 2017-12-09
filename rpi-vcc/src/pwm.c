#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include "pca9685_wiringpi.h"
#include "pwm.h"

void pwmBypca9685()
{
	printf("starting\n");
	unsigned char addr = 0x70;
	int fd = pca9685_init(addr);
	printf("inited:%d\n", fd);
	//pca9685_setmk(fd, 0, 1 * 1000);//us
	printf("started\n");
	while(1){
	//for (int i = 0; i<10; i++) {
		int input;
		printf("(10-20)_>");
		scanf("%d", &input);
		pca9685_setmk(fd, 0, input * 100);//us
		pca9685_setmk(fd, 8, input * 100);//us
										  //sleep(1);
	}
}
void init(int intervalMilSecond) {
	wiringPiSetup();
	int targetPin = 0;
	pinMode(targetPin, OUTPUT);
	int base = 100;//us
	int count = intervalMilSecond * 1000 / base; //10000
	softPwmCreate(targetPin, 0, count);
}
int main(void) {
	pwmBypca9685();
}

