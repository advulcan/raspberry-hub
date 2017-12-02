#include "monitor.h"

int time = 0;
int global_count = 0;
xbox_map_t global_map;

void onInterupted(void) {
	global_count++;
	//printf("\b\b\b\b\tCNT:%-5d", count);
	//fflush(stdout);
	refresh(global_count);
}
void initMonitor(int pin) {
	/*printf("Running\n");
	fflush(stdout);*/
	pinMode(pin, INPUT);
	int i = wiringPiISR(pin, INT_EDGE_RISING, onInterupted);
}
void refreshAll(int count, xbox_map_t map) {
	printf("\rLX:%-6d LY:%-6d RX:%-6d RY:%-6d LT:%-6d RT:%-6d CNT:%d", map.lx, map.ly, map.rx, map.ry, map.lt, map.rt, count);
	fflush(stdout);
}
void refresh(int count) {
	global_count = count;
	refreshAll(global_count, global_map);
}
void refresh(xbox_map_t map) {
	global_map = map;
	refreshAll(global_count, global_map);
}
int main22(void){
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
