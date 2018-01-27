#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
void main(void)
{
    int spi1;
    unsigned char date[2],rec[2];
    int spiChannel = 1;
    int clock = 500 * 000;
    wiringPiSetup();
	/*int pinnum=11;
	pinMode(pinnum, OUTPUT);
	digitalWrite(pinnum, HIGH);
	digitalWrite(pinnum, LOW);*/
    spi1 = wiringPiSPISetup(spiChannel,clock);
    if(spi1!=-1)
    {
        printf("Starting SPI Test\n");
  //      printf("Write:\n");
		//date[0]=0x6B;//寄存器地址
  //      date[1]=0x80;//要写的数据
  //      wiringPiSPIDataRW(spiChannel,date,2);
		//delay(100);
		//date[0]=0x6A;//寄存器地址
  //      date[1]=0x1C;//要写的数据
  //      wiringPiSPIDataRW(spiChannel,date,2);
		//delay(100);      
		printf("Read:\n");
        rec[0]=0x75 | 0x80;//寄存器地址
        rec[1]=0x00;
        wiringPiSPIDataRW(spiChannel,rec,2);
		delay(100);
        printf("rec[0] : %d  ",rec[0]);
        printf("rec[1] : %d  \n",rec[1]);//返回的数据是这个
	}
}
