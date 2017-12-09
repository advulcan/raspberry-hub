#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
void main(void)
{
    
    wiringPiSetup();
    int fd = wiringPiI2CSetup (0x68);
   	while(1){
		printf("\e[H\e[J");
		for(int i =0;i<128; i++){
			wiringPiI2CWrite (fd, i);
			int res = wiringPiI2CRead (fd);
			int row = i/10 + 1;
			int col = i%10 * 10 + 1;
			printf("\e[%d;%dH|%x:%x", row, col, i, res);
		}
		printf("\n");
		sleep(1);
	}
}