#include<stdio.h> 
#include<stdint.h> 
#include<fcntl.h> 
#include <unistd.h>
#include<sys/ioctl.h> 
#include<linux/i2c.h> 
#include<linux/i2c-dev.h>

#define BMP280_ADDRESS 0x76

//bit 3 conversion is running, bit 0 NVM copying
#define REG_STATUS 0xF3 

//bit 765 oversampling of temperature, 432 oversampling of pressure ,10 power mode(00sleep 10,10 focus, 11 normal)
#define REG_CTRL_MEAS 0xF4
//01011111
//11100011 e3
//00011111 1f
//01011111 5f temp x2 press x16 recommended
#define REG_CTRL_MEAS_VALUE 0x5f

//765 duration standby in normal mode. 432 time constant of the IIR filter, bit 0 = 1 enable spi
//00011100
#define REG_CONFIG 0x1c
//00011100=0x60
#define REG_CONFIG_VALUE 0x00

//88-8D 6 bytes
#define TEMP_DIG_START 0x88
//3 bytes
#define TEMP_RAW_START 0xF7

//8E-9F 18 bytes
#define PRES_DIG_START 0x8E
//3 bytes
#define PRES_RAW_START 0xFA

typedef int32_t  BMP280_S32_t;
typedef uint32_t  BMP280_U32_t;
typedef int64_t  BMP280_S64_t;
typedef uint64_t  BMP280_U64_t;

//#define TEMP_ONLY_NORMAL_MODE 0xE3 // 111 000 11

int writeReg(int pt, unsigned char add, char value) {
	unsigned char w_buff[2];
	w_buff[0] = add;
	w_buff[1] = value;
	if (write(pt, w_buff, 2) != 2) {
		perror("Failed write to device");
		return 1;
	}
	return 0;
}
int readReg(int pt, unsigned char s_add, char buf[], int size) {
	char writeBuff[1] = { s_add };
	if (write(pt, writeBuff, 1) != 1) {
		perror("Failed to reset the read address\n");
		return 1;
	}
	if (read(pt, buf, size) != size) {
		perror("Failed to read in the buffer\n");
		return 1;
	}
	return 0;
}
void resetSensor(int file) {
	writeReg(file, 0xe0, 0xb6);
}
float calculateTemperature(uint32_t adc_T, unsigned short dig_T1, short dig_T2, short dig_T3) {
	/*printf("adc_T is : %d \n", adc_T);
	printf("dig_T1 is : %d \n", dig_T1);
	printf("dig_T2 is : %d \n", dig_T2);
	printf("dig_T3 is : %d \n", dig_T3);*/
	uint32_t var1, var2;
	float T;
	var1 = (((double)adc_T) / 16384.0 - ((double)dig_T1) / 1024.0)*((double)dig_T2);
	var2 = ((((double)adc_T) / 131072.0 - ((double)dig_T1) / 8192.0)*(((double)adc_T) / 131072.0 - ((double)dig_T1) / 8192.0))*((double)dig_T2);
	T = (var1 + var2) / 5120.0;
	printf("ADT %d\t", adc_T);
	printf("%d\t", dig_T1);
	printf("%d\t", dig_T2);
	printf("%d\t", dig_T3);
	printf("V1 %d\t\t", var1);
	printf("V2 %d\t\t", var2);
	printf("TF %d\t", 0);
	printf("TEM %f\n", T);
	return T;
}
BMP280_S32_t t_fine;
BMP280_S32_t bmp280_compensate_T_int32(BMP280_S32_t adc_T, unsigned short dig_T1, short dig_T2, short dig_T3)
{
	BMP280_S32_t var1, var2, T;
	var1 = ((((adc_T >> 3)-((BMP280_S32_t)dig_T1 << 1))) * ((BMP280_S32_t)dig_T2)) >> 11;
	var2 = (((((adc_T >> 4) -((BMP280_S32_t)dig_T1)) * ((adc_T >> 4) -((BMP280_S32_t)dig_T1))) >> 12) *
		((BMP280_S32_t)dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;

	/*printf("ADT %d\t", adc_T);
	printf("%d\t", dig_T1);
	printf("%d\t", dig_T2);
	printf("%d\t", dig_T3);
	printf("V1 %d\t\t", var1);
	printf("V2 %d\t\t", var2);
	printf("TF %d\t", t_fine);
	printf("TEM %d\n", T);*/
	return T;
}
BMP280_U32_t bmp280_compensate_P_int64(BMP280_S32_t adc_P, unsigned short dig_P1, short dig_P2, short dig_P3, short dig_P4, short dig_P5, short dig_P6, short dig_P7, short dig_P8, short dig_P9)
{
	BMP280_S64_t var1, var2, p;
	var1 = ((BMP280_S64_t)t_fine) - 128000;
	var2 = var1 * var1 * (BMP280_S64_t)dig_P6;
	var2 = var2 + ((var1*(BMP280_S64_t)dig_P5) << 17);
	var2 = var2 + (((BMP280_S64_t)dig_P4) << 35);
	var1 = ((var1 * var1 * (BMP280_S64_t)dig_P3) >> 8) + ((var1 * (BMP280_S64_t)dig_P2) << 12);
	var1 = (((((BMP280_S64_t)1) << 47) + var1))*((BMP280_S64_t)dig_P1) >> 33;
	if (var1 == 0)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576 - adc_P;
	p = (((p << 31) - var2) * 3125) / var1;
	var1 = (((BMP280_S64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
	var2 = (((BMP280_S64_t)dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((BMP280_S64_t)dig_P7) << 4);
	return (BMP280_U32_t)p;
}
//BMP280_S32_t t_fine;
double bmp280_compensate_T_double(BMP280_S32_t adc_T, unsigned short dig_T1, short dig_T2, short dig_T3)
{
	double var1, var2, T;
	var1 = (((double)adc_T) / 16384.0 -((double)dig_T1) / 1024.0) * ((double)dig_T2);
	var2 = ((((double)adc_T) / 131072.0 -((double)dig_T1) / 8192.0) *
		(((double)adc_T) / 131072.0 -((double)dig_T1) / 8192.0)) * ((double)dig_T3);
	t_fine = (BMP280_S32_t)(var1 + var2);
	T = (var1 + var2) / 5120.0;
	/*printf("ADT %d\t", adc_T);
	printf("%d\t", dig_T1);
	printf("%d\t", dig_T2);
	printf("%d\t", dig_T3);
	printf("V1 %f\t", var1);
	printf("V2 %f\t", var2);
	printf("TF %d\t", t_fine);
	printf("TEM %f\n", T);*/

	return T;
}
double bmp280_compensate_P_double(BMP280_S32_t adc_P, unsigned short dig_P1, short dig_P2, short dig_P3, short dig_P4, short dig_P5, short dig_P6, short dig_P7, short dig_P8, short dig_P9)
{
	double var1, var2, p;
	var1 = ((double)t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double)dig_P5) * 2.0;
	var2 = (var2 / 4.0) + (((double)dig_P4) * 65536.0);
	var1 = (((double)dig_P3) * var1 * var1 / 524288.0 + ((double)dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0)*((double)dig_P1);
	if (var1 == 0.0)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576.0 -(double)adc_P;
	p = (p -(var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((double)dig_P9) * p * p / 2147483648.0;
	var2 = p * ((double)dig_P8) / 32768.0;
	p = p + (var1 + var2 + ((double)dig_P7)) / 16.0;
	return p;
}
double bmp280_compensate_TnP_double(double* result, long adc_T, unsigned short dig_T1, short dig_T2, short dig_T3, long adc_P,
	unsigned short dig_P1, short dig_P2, short dig_P3, short dig_P4, short dig_P5, short dig_P6, short dig_P7, short dig_P8, short dig_P9)
{
	double var1, var2, temperature, pressure;
	var1 = (((double)adc_T) / 16384.0 - ((double)dig_T1) / 1024.0) * ((double)dig_T2);
	var2 = ((((double)adc_T) / 131072.0 - ((double)dig_T1) / 8192.0) *
		(((double)adc_T) / 131072.0 - ((double)dig_T1) / 8192.0)) * ((double)dig_T3);
	long t_fine = (long)(var1 + var2);
	temperature = (var1 + var2) / 5120.0;

	printf("ADT %d\t", adc_T);
	printf("%d\t", dig_T1);
	printf("%d\t", dig_T2);
	printf("%d\t", dig_T3);
	printf("V1 %f\t", var1);
	printf("V2 %f\t", var2);
	printf("TF %d\t", t_fine);
	printf("TEM %f\n", temperature);

	var1 = ((double)t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double)dig_P5) * 2.0;
	var2 = (var2 / 4.0) + (((double)dig_P4) * 65536.0);
	var1 = (((double)dig_P3) * var1 * var1 / 524288.0 + ((double)dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0)*((double)dig_P1);
	if (var1 == 0.0)
	{
		return 0; // avoid exception caused by division by zero
	}
	pressure = 1048576.0 -(double)adc_P;
	pressure = (pressure -(var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((double)dig_P9) * pressure * pressure / 2147483648.0;
	var2 = pressure * ((double)dig_P8) / 32768.0;
	pressure = pressure + (var1 + var2 + ((double)dig_P7)) / 16.0;
	result[0] = temperature;
	result[1] = pressure;
	printf("D :%f, %f\n", result[0], result[1]);
	//return result;
}
int main() {
	
	int file;
	if ((file = open("/dev/i2c-1", O_RDWR)) < 0) {
		perror("failed to open the bus\n");
		return 1;
	}
	if (ioctl(file, I2C_SLAVE, BMP280_ADDRESS) < 0) {
		perror("Failed to connect to the sensor\n");
		return 1;
	}
	//set sensor
	resetSensor(file);
	writeReg(file, REG_CONFIG, REG_CONFIG_VALUE);
	writeReg(file, REG_CTRL_MEAS, REG_CTRL_MEAS_VALUE);
	usleep(888000);
	char buff_dig[24];
	char buff_m[6];
	while (1) {
		//resetSensor(file);
		readReg(file, 0x88, buff_dig, 24);
		readReg(file, 0xF7, buff_m, 6);
		/*for (int i = 0; i < sizeof(buff_dig); i++) {
			printf("%x,", buff_dig[i]);
		}
		printf(" M ");
		for (int i = 0; i < sizeof(buff_m); i++) {
			printf("%x,", buff_m[i]);
		}*/
		//prepare temperature
		BMP280_S32_t adc_T = ((buff_m[3] << 16) | (buff_m[4] << 8) | (buff_m[5])) >> 4;
		unsigned 
		short dig_T1 = (buff_dig[1] << 8) | (buff_dig[0]);
		short dig_T2 = (buff_dig[3] << 8) | (buff_dig[2]);
		short dig_T3 = (buff_dig[5] << 8) | (buff_dig[4]);
		//float temperature = calculateTemperature(adc_T, dig_T1, dig_T2, dig_T3);

		BMP280_S32_t adc_P = ((buff_m[0] << 16) | (buff_m[1] << 8) | (buff_m[2])) >> 4;
		unsigned 
		short dig_P1 = (buff_dig[7] << 8) | (buff_dig[6]);
		short dig_P2 = (buff_dig[9] << 8) | (buff_dig[8]);
		short dig_P3 = (buff_dig[11] << 8) | (buff_dig[10]);
		short dig_P4 = (buff_dig[13] << 8) | (buff_dig[12]);
		short dig_P5 = (buff_dig[15] << 8) | (buff_dig[14]);
		short dig_P6 = (buff_dig[17] << 8) | (buff_dig[16]);
		short dig_P7 = (buff_dig[19] << 8) | (buff_dig[18]);
		short dig_P8 = (buff_dig[21] << 8) | (buff_dig[20]);
		short dig_P9 = (buff_dig[23] << 8) | (buff_dig[22]);
		/*printf("\t%d,", dig_P1);
		printf("%d,", dig_P2);
		printf("%d,", dig_P3);
		printf("%d,", dig_P4);
		printf("%d,", dig_P5);
		printf("%d,", dig_P6);
		printf("%d,", dig_P7);
		printf("%d,", dig_P8);
		printf("%d,", dig_P9);*/


		//float pressure = calculatePressure(adc_P, dig_P1, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9);
		double result[2];
		BMP280_S32_t teperature = bmp280_compensate_T_int32(adc_T, dig_T1, dig_T2, dig_T3);
		double t_int = teperature / 100.0;//degree c
		double t = bmp280_compensate_T_double(adc_T, dig_T1, dig_T2, dig_T3);
		BMP280_S32_t pressure = bmp280_compensate_P_int64(adc_P, dig_P1, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9);
		double p_int = pressure / 256.0;//pa
		double p = bmp280_compensate_P_double(adc_P, dig_P1, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9);
		//calculateTemperature(adc_T, dig_T1, dig_T2, dig_T3);
		//bmp280_compensate_TnP_double(result, adc_T,dig_T1, dig_T2, dig_T3, adc_P, dig_P1, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9);
		//printf("R: %d, %d\n", teperature, pressure);
		printf("R: %f, %f\t", t_int, p_int);
		printf("R: %f, %f\n", t, p);
		break;
		usleep(888000);

	}
	resetSensor(file);
	close(file);
	return 0;
}
