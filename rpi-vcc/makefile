CC = g++
CFLAGS = -Wall -lwiringPi -l pthread
OBJECTS = motor.o controller.o monitor.o
OBJECTS_1 = pwm.o pca9685_wiringpi.o controller.o
#VPATH = src
vpath %.h src:src/drivers
vpath %.cpp src:src/drivers
vpath %.c src:src/drivers
#vpath %.h ./src/drivers
#vpath %.cpp ./src/drivers
#vpath %.c ./src/drivers

motor : $(OBJECTS)
	$(CC) $(CFLAGS) -o motor $(OBJECTS)

motor.o : controller.h monitor.h
#	$(CC) $(CFLAGS) -c motor.cpp
controller.o : controller.h	
#	$(CC) $(CFLAGS) -c controller.cpp
monitor.o : controller.h
mpu9250.o :
pca9685_wiringpi.o : 	
pwm : pwm.o pca9685_wiringpi.o controller.o
	$(CC) $(CFLAGS) -o pwm $(OBJECTS_1)
pwm.o : controller.h pca9685_wiringpi.h pwm.h

#mpu9250.o :
bmp280.o :
bmp : bmp280.o
	$(CC) $(CFLAGS) -o bmp280 bmp280.o
.PHONY : clean	
clean :
	rm motor $(OBJECTS) $(OBJECTS_1) pwm