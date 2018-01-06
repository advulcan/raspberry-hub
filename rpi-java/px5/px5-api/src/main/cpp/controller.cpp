#include "controller.h"

int Controller::xbox_open(char *file_name){
	int xbox_fd = open(file_name, O_RDONLY);
	if (xbox_fd < 0){
		perror("open");
		return -1;
	}
	return xbox_fd;
}
int * Controller::xbox_event_read(){
	int len, type, number, value;
	struct js_event js;
	int result [4] = {0,0,0,0};
	//block until new event
	len = read(xbox_fd, &js, sizeof(struct js_event));
	if (len > 0){
		perror("read");
		result[0] = js.type;
		result[0] = js.number;
		result[0] = js.value;
		result[0] = js.time;
	}
	return result;
}
int Controller::xbox_map_read(){
	int len, type, number, value;
	struct js_event js;
	//block until new event
	len = read(xbox_fd, &js, sizeof(struct js_event));
	if (len < 0){
		perror("read");
		return -1;
	}
	type = js.type;
	number = js.number;
	value = js.value;
	map.time = js.time;
	
	if (type == JS_EVENT_BUTTON){
		switch (number)	{
		case XBOX_BUTTON_A:
			map.a = value;
			break;

		case XBOX_BUTTON_B:
			map.b = value;
			break;

		case XBOX_BUTTON_X:
			map.x = value;
			break;

		case XBOX_BUTTON_Y:
			map.y = value;
			break;

		case XBOX_BUTTON_LB:
			map.lb = value;
			break;

		case XBOX_BUTTON_RB:
			map.rb = value;
			break;

		case XBOX_BUTTON_START:
			map.start = value;
			break;

		case XBOX_BUTTON_BACK:
			map.back = value;
			break;

		case XBOX_BUTTON_HOME:
			map.home = value;
			break;

		case XBOX_BUTTON_LO:
			map.lo = value;
			break;

		case XBOX_BUTTON_RO:
			map.ro = value;
			break;

		default:
			break;
		}
	}
	else if (type == JS_EVENT_AXIS)
	{
		switch (number)
		{
		case XBOX_AXIS_LX:
			map.lx = value;
			break;

		case XBOX_AXIS_LY:
			map.ly = value;
			break;

		case XBOX_AXIS_RX:
			map.rx = value;
			break;

		case XBOX_AXIS_RY:
			map.ry = value;
			break;

		case XBOX_AXIS_LT:
			map.lt = value;
			break;

		case XBOX_AXIS_RT:
			map.rt = value;
			break;

		case XBOX_AXIS_XX:
			map.xx = value;
			break;

		case XBOX_AXIS_YY:
			map.yy = value;
			break;

		default:
			break;
		}
	}
	else
	{
		/* Init do nothing */
	}
	printf("\rTime:%8d A:%d B:%d X:%d Y:%d LB:%d RB:%d start:%d back:%d home:%d LO:%d RO:%d XX:%-6d YY:%-6d LX:%-6d LY:%-6d RX:%-6d RY:%-6d LT:%-6d RT:%-6d",
				map.time, map.a, map.b, map.x, map.y, map.lb, map.rb, map.start, map.back, map.home, map.lo, map.ro,
				map.xx, map.yy, map.lx, map.ly, map.rx, map.ry, map.lt, map.rt);
	fflush(stdout);
	return len;
}

void Controller::xbox_close(int xbox_fd){
	close(xbox_fd);
	return;
}

int main(){
	int len = 0;
	Controller controller;
	while (1){
		len = controller.xbox_map_read();
		if (len < 0)
		{
			usleep(1000 * 1000);
			continue;
		}
		//printf("123");
	}
	//controller = npt
	//return 0;
}
