#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

void onInterupted(void);
int count = 0;

int main(void){
	wiringPiSetup();
	pinMode(29, INPUT);
	//pullUpDnControl(29, PUD_DOWN);
	printf("Running\n");
	//printf("get%d", digitalRead(29));
	//int i = wiringPiISR(29, INT_EDGE_FALLING, onInterupted);
	int i = wiringPiISR(29, INT_EDGE_RISING, onInterupted);
	//printf("get%d", digitalRead(29));
	//int i = wiringPiISR(29, INT_EDGE_BOTH, onInterupted);
	//printf("reg result:%d\n", i);
	while(true){
		//printf("get\n");
		//i = digitalRead(29);
		//printf("get %d", i);
		//printf("get");
		delay(1000 * 1000);
	}
	printf("end\n");
	return 0;
}
void onInterupted(void) {
	count++;
	printf("called: %d\n", count);
}
