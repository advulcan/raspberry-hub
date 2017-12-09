#include "pca9685_wiringpi.h"

#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

int pca9685_init(unsigned char addr)	// addr��7λ��i2c�ӻ���ַ�����ص���linux��׼���豸���������������ĵط�����pca9685���豸������
										//��Ϊ���Զ��pca9685������ͨ���豸��������������
										//����������Ϊ�������ʹ�ã����ڹ̶���λ20ms���������ⲿ����
{
	int pca9685;
	pca9685 = wiringPiI2CSetup(addr);

	{	//��ʼ��pca9685оƬ
		double T = 20000;	//���ڣ���λ��us
		unsigned char prescale;
		double osc_clock = 25000000;
		unsigned char oldmode, newmode;
		T /= 0.915;	//��֪��Ϊʲô��������ƫ�����У׼һ�¾�ok�ˣ��������ҵ�arduino����Ҳ������У׼��
		T /= 1000000;	//��Tת������
		prescale = (unsigned char)(osc_clock / 4096 * T - 1);
		//	printf("prescale = 0x%x", prescale);
		oldmode = wiringPiI2CReadReg8(pca9685, PCA9685_MODE1);
		newmode = (oldmode & 0x7f) | 0x10;	//׼������sleep������ʱ��ǰ�����Ƚ���sleepģʽ
		wiringPiI2CWriteReg8(pca9685, PCA9685_MODE1, newmode);
		wiringPiI2CWriteReg8(pca9685, PCA9685_PRESCALE, prescale);
		oldmode &= 0xef;	//���sleepλ
		wiringPiI2CWriteReg8(pca9685, PCA9685_MODE1, oldmode);
		delay(0.005);
		wiringPiI2CWriteReg8(pca9685, PCA9685_MODE1, oldmode | 0xa1);
	}

	return pca9685;
}

void pca9685_setmk(int fd, int num, int mk)	//����ָ��ͨ��������fd����pca9685_initʱ��õ��豸��������num��ͨ���ţ���0��ʼ����mk������λ��us�������Ѿ��̶�Ϊ20ms��
{
	unsigned int ON, OFF;
	ON = 0;	//ÿ������һ��ʼ������ߵ�ƽ
	//ON = (unsigned int)((((double)1000) / 20000 * 4096)*1.0067114);
	OFF = (unsigned int)((((double)mk) / 20000 * 4096)*1.0067114);	//����1.0067114��У׼�õ�
																	//    printf("off = 0x%x", OFF);

	wiringPiI2CWriteReg16(fd, LED0_ON_L + 4 * num, ON);
	wiringPiI2CWriteReg16(fd, LED0_OFF_L + 4 * num, OFF);
}