#include <stdio.h>
#include <wiringPi.h>
#include <stdint.h>
#include <wiringPiSPI.h>
void main(void)
{
    unsigned char buff[2];
    int spiChannel = 0;
    wiringPiSetup();
    int spi1 = wiringPiSPISetup(spiChannel, 1000000);
	printf("id:%d\n",spi1);
	while(1){
		printf("\e[2;1H\e[J");
		for(uint8_t i =0;i<128; i++){
			buff[0]=i | 0x80;
			buff[1]=0;
			int row =i/5 +2;
			int col = i%5 * 12 + 1;
			wiringPiSPIDataRW(spiChannel, buff, 2);
			delay(5);
			printf("\e[%d;%dH|%x:%x", row, col, i, buff[1]);
			//printf("|%x:%x",buff[0],buff[1]);
		}
		printf("\n");
		sleep(1);
	}
}
