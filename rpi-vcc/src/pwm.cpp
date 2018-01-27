#include "pwm.h"
int cache_a = 0;
int cache_b = 0;
int b1 = -1;
int b2 = -1;
void pwmbypca9685(int fd, int c1, int c2)
{
	int range = 1000;
	int offset = 1000;
	//int offset
	int a = ((double)(c1 + 32767)) * range / (32767 * 2) + offset;
	int b = ((double)(c2 + 32767)) * range / (32767 * 2) + offset;
	printf(" (%-6d,%-6d)", a, b);
	if (a < 0 || a > 2500 || b < 0 || b > 2500) {
		printf("\tinvalid range");
	}
	if (cache_a != a) {
		cache_a = a;
		pca9685_setmk(fd, 0, 0, a);//us
		pca9685_setmk(fd, 1, 0, a);//us
	}
	if (cache_b != b) {
		cache_b = b;
		pca9685_setmk(fd, 2, 0, b);//us
		pca9685_setmk(fd, 3, 0, b);//us
	}
}
int main(void) {
	int xbox_fd;
	xbox_map_t map;
	int len, type;
	int axis_value, button_value;
	int number_of_axis, number_of_buttons;

	memset(&map, 0, sizeof(xbox_map_t));
	map.lt = -32767;
	map.rt = -32767;

	xbox_fd = xbox_open("/dev/input/js0");
	if (xbox_fd < 0) {
		return -1;
	}
	unsigned char addr = 0x40;
	int fd = pca9685_init(addr);
	//init pwm out
	pwmbypca9685(fd, map.lt, map.rt);
	while (1) {
		len = xbox_map_read(xbox_fd, &map);
		if (len < 0)
		{
			printf("N");
			usleep(10 * 1000);
			continue;
		}

		printf("\rTime:%8d A:%d B:%d X:%d Y:%d LB:%d RB:%d start:%d back:%d home:%d LO:%d RO:%d XX:%-6d YY:%-6d LX:%-6d LY:%-6d RX:%-6d RY:%-6d LT:%-6d RT:%-6d",
			map.time, map.a, map.b, map.x, map.y, map.lb, map.rb, map.start, map.back, map.home, map.lo, map.ro,
			map.xx, map.yy, map.lx, map.ly, map.rx, map.ry, map.lt, map.rt);
		fflush(stdout);
		pwmbypca9685(fd, map.lt, map.rt);
		int s = 900;
		int f = 1100;
		if (map.a == 1) {
			pca9685_setmk(fd, 0, 0, f);//us
		}
		if (map.b==1){
			pca9685_setmk(fd, 1, 0, f);//us
		}
		if (map.x == 1) {
			pca9685_setmk(fd, 2, 0, f);//us
		}
		if (map.y == 1) {
			pca9685_setmk(fd, 3, 0, f);//us
		}
		if (map.rb == 1) {
			pca9685_setmk(fd, 0, 0, s);//us
			pca9685_setmk(fd, 1, 0, s);//us
			pca9685_setmk(fd, 2, 0, s);//us
			pca9685_setmk(fd, 3, 0, s);//us
		}
	}

	xbox_close(xbox_fd);
	return 0;
}

