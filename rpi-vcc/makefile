CC = g++
CFLAGS = -Wall -lwiringPi -l pthread
OBJECTS = motor.o controller.o monitor.o
#VPATH = src
vpath %.h ./src
vpath %.cpp ./src
vpath %.c ./src

motor : $(OBJECTS)
	$(CC) $(CFLAGS) -o motor $(OBJECTS)

motor.o : controller.h monitor.h
#	$(CC) $(CFLAGS) -c motor.cpp
controller.o : controller.h	
#	$(CC) $(CFLAGS) -c controller.cpp
monitor.o : controller.h
.PHONY : clean	
clean :
	rm motor $(OBJECTS)