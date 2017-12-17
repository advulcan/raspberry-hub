/*
这个驱动是在树莓派的wiringPi基础上的，基于wiringPi对i2c的接口函数。
此驱动的使用方法是：
1、先用 pca9685_init(从机地址) 初始化，得到一个设备描述符（int型），这个设备描述符代表这个pca9685芯片，因为可能多个pca9685级联，通过这个设备描述符来区分它们。
它的
2、调用 pca9685_setmk
*/

#ifndef PCA9685_WIRINGPI_H
#define PCA9685_WIRINGPI_H
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <unistd.h>

int pca9685_init(unsigned char addr);	// addr是7位的i2c从机地址，返回的是linux标准的设备描述符，调用它的地方视作pca9685的设备描述符
										//因为可以多个pca9685级联，通过设备描述符区别它们
										//此驱动仅作为驱动舵机使用，周期固定死位20ms，不允许外部设置
void pca9685_setmk(int fd, int num, int left, int right);	//设置指定通道的脉宽。fd是在pca9685_init时获得的设备描述符，num是通道号（从0开始），mk是脉宽单位是us。周期已经固定为20ms了
#endif
