/*
�������������ݮ�ɵ�wiringPi�����ϵģ�����wiringPi��i2c�Ľӿں�����
��������ʹ�÷����ǣ�
1������ pca9685_init(�ӻ���ַ) ��ʼ�����õ�һ���豸��������int�ͣ�������豸�������������pca9685оƬ����Ϊ���ܶ��pca9685������ͨ������豸���������������ǡ�
����
2������ pca9685_setmk
*/

#ifndef PCA9685_WIRINGPI_H
#define PCA9685_WIRINGPI_H
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <unistd.h>

int pca9685_init(unsigned char addr);	// addr��7λ��i2c�ӻ���ַ�����ص���linux��׼���豸���������������ĵط�����pca9685���豸������
										//��Ϊ���Զ��pca9685������ͨ���豸��������������
										//����������Ϊ�������ʹ�ã����ڹ̶���λ20ms���������ⲿ����
void pca9685_setmk(int fd, int num, int left, int right);	//����ָ��ͨ��������fd����pca9685_initʱ��õ��豸��������num��ͨ���ţ���0��ʼ����mk������λ��us�������Ѿ��̶�Ϊ20ms��
#endif
