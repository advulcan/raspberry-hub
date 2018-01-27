#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h> 
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define PIN_TRIG 4
#define PIN_ECHO 5

//int echo_start = 0;
//int echo_end = 0;
int waiting_fall = 0;
struct timeval tv_start, tv_end;
struct timespec start, end;
double sum;
double varianceSum;
int count;

long calc_interval_us(struct timeval tv_start, struct timeval tv_end) {
	return ((tv_end.tv_sec - tv_start.tv_sec) * 1000 * 1000 + (tv_end.tv_usec - tv_start.tv_usec));
}
long calc_interval_ns(struct timespec start, struct timespec end) {
	struct timespec diff;
	diff.tv_sec = (end.tv_sec - start.tv_sec);
	diff.tv_nsec = (end.tv_nsec - start.tv_nsec);
	if (diff.tv_nsec < 0) {
		diff.tv_sec--;
		diff.tv_nsec += 1000000000;
	}
	long nsec = diff.tv_nsec + diff.tv_sec * 100000000;
	//printf("TimeMeasure: used time %9.1lf[ns]\n", nsec);
	return nsec;
}
void reset() {
	//printf("reset");
	tv_start.tv_sec = 0;
	tv_start.tv_usec = 0;
	tv_end.tv_sec = 0;
	tv_end.tv_usec = 0;
	start.tv_sec = 0;
	start.tv_nsec = 0;
	end.tv_sec = 0;
	end.tv_nsec = 0;
}
void onChange(void) {
	int current = digitalRead(PIN_ECHO);
	if (current == HIGH) {
		//printf("echo HIGH\n");
		//gettimeofday(&tv_start, NULL);
		clock_gettime(CLOCK_REALTIME, &start);
		waiting_fall = 1;
	}
	else if (current == LOW) {
		//printf("echo LOW\n");
		if (waiting_fall == 1) {
			//gettimeofday(&tv_end, NULL);
			//long usecond = calc_interval_us(tv_start, tv_end);
			//double distance = 340.0 * usecond / 1000.0; //mm
			clock_gettime(CLOCK_REALTIME, &end);
			long usecond = calc_interval_ns(start, end);
			double distance = 340.0 * usecond /2 / 1000000.0; //mm
			sum += distance;
			count++;
			double avg = sum / count;
			double variance = (distance - avg) * (distance - avg);
			varianceSum += variance;
			double varAvg = varianceSum / count;
			//printf("elps :%ld\n", usecond);
			printf("dis: %f, elps:%ld, avg: %f, var: %f\n", distance, usecond, avg, varAvg);
			waiting_fall = 0;
			reset();
		}
		else {
			printf("invalid LOW\n");
		}
	}
}
//void onFall(void) {
//	printf("echo end");
//	gettimeofday(&tv_end, NULL);
//	long usecond = calc_interval(tv_start, tv_end);
//	double distance = 340 * usecond / 1000; //mm
//	printf("elps :%ld\n", usecond);
//	printf("distance: %f\n", distance);
//}
void main(void)
{
	//gettimeofday(&tv_start, NULL);
	//delay(2);
	//gettimeofday(&tv_end, NULL);
	//printf("second :%ld\n", calc_interval(tv_start, tv_end)); 
	wiringPiSetup();
	pinMode(PIN_ECHO, INPUT);
	int i = wiringPiISR(PIN_ECHO, INT_EDGE_BOTH, onChange);
	while (1) {
		pinMode(PIN_TRIG, OUTPUT);
		//printf("trigger.\n");
		digitalWrite(PIN_TRIG, HIGH);
		usleep(15);
		digitalWrite(PIN_TRIG, LOW);
		usleep(100000);
	}
	printf("end");
}