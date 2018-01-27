#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define MPU9250_I2C_ADDRESS 0x68
#define READ_PREFIX 0x80
#define REG_WHOAMI 0x75
#define PWR_MGMT_1 0x6B
#define USER_CTRL 0x6A
void main(void)
{
    
    wiringPiSetup();
    int fd = wiringPiI2CSetup (MPU9250_I2C_ADDRESS);
	int i = wiringPiI2CReadReg8(fd, READ_PREFIX | REG_WHOAMI);
	printf("res: %d\n", i);
	wiringPiI2CWriteReg8(fd, PWR_MGMT_1, 0x80);
	delay(100);
	wiringPiI2CWriteReg8(fd, USER_CTRL, 0x10);
	delay(100);
	i = wiringPiI2CReadReg8(fd, READ_PREFIX | REG_WHOAMI);
	printf("res: %d\n", i);
   /*	while(1){
		printf("\e[H\e[J");
		for(int i =0;i<128; i++){
			wiringPiI2CWrite (fd, i);
			del
			int res = wiringPiI2CRead (fd);
			int row = i/10 + 1;
			int col = i%10 * 10 + 1;
			printf("\e[%d;%dH|%x:%x", row, col, i, res);
		}
		printf("\n");
		sleep(1);
	}*/
}