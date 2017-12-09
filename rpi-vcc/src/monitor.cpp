#include <time.h>
#include <pthread.h>
#include "monitor.h"

//int time = 0;
long last_time;
int global_count = 0;
xbox_map_t global_map;

long getMillionSecond() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	//printf("second:%ld\n", tv.tv_sec);  //秒
	//printf("millisecond:%ld\n", tv.tv_sec * 1000 + tv.tv_usec / 1000);  //毫秒
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
void onInterupted(void) {
	global_count++;
	//printf("\tCNT:%-5d", global_count);
	//fflush(stdout);
	refresh(global_count);
}
void * monitorThread(void *arg)//这里是自己定义的要执行的方法它是指针函数    1，返回类型void 2，参数类型为void *
{
	while (1)
	{
		//printf("thread pid = %d tid = %ld\n",gettid(),pthread_self());
		//printf("thread pid = %d tid = %lu\n", getpid(), pthread_self());
		display(global_map);
		display(global_count);
		fflush(stdout);
		usleep(100 * 1000);
	}
}
void initMonitor(int pin) {
	/*printf("Running\n");
	fflush(stdout);*/
	pinMode(pin, INPUT);
	int i = wiringPiISR(pin, INT_EDGE_RISING, onInterupted);
	last_time = getMillionSecond();
	initDisplay();
	pthread_t tid;//pthread_t ==> long

				  //1.线程的创建 ---线程创建之后 当前程序中就有两个执行体
				  //               (1).主线程 -- 即:main函数中代表的执行流
				  //               (2).子线程 -- 即:执行函数代表的执行流                                        
	pthread_create(&tid, NULL, monitorThread, NULL); //attr == NULL表示默认属性(可结合属性)
}
void refreshAll(int count, xbox_map_t map) {
	long current = getMillionSecond();
	long interval = current - last_time;
	double velocity = ((double)(count - global_count)) / interval;
	//printf("\rLX:%-6d LY:%-6d RX:%-6d RY:%-6d LT:%-6d RT:%-6d CNT:%-10d V:%50d", map.lx, map.ly, map.rx, map.ry, map.lt, map.rt, count, velocity);
	//fflush(stdout);
	//display(map);
	//display(count, velocity);
	last_time = current;
}
void refresh(int count) {
	refreshAll(count, global_map);
	//global_count = count;
}
void refresh(xbox_map_t map) {
	refreshAll(global_count, map);
	global_map = map;
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
