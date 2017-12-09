#include "display.h"

void initDisplay(){
	//printf("\e[31m\e[43mHello world\n");
	printf("\e[H\e[J");
	//1 line
	printf("+");
	for (int i = 0; i < 98; i++) {
		printf("-");
	}
	printf("+\n");
	printf("\e[1;47H");
	printf("RPI VCC");
	//2 line
	printf("\e[2;1H");
	printf("|"); printf("\e[2;100H"); printf("|\n");
	printf("|"); printf("\e[3;100H"); printf("|\n");
	printf("|"); printf("\e[4;100H"); printf("|\n");
	printf("|"); printf("\e[5;100H"); printf("|\n");

	//input line
	printf("\e[10;1H");
	printf("_>");

}
void moveToInput() {
	//printf("\e[10;3H");
}
void display(xbox_map_t map) {
	printf("\e7");
	printf("\e[2;2H");
	printf("LX:%-6d LY:%-6d RX:%-6d RY:%-6d LT:%-6d RT:%-6d",map.lx, map.ly, map.rx, map.ry, map.lt, map.rt);
	printf("\e8");
}
void display(int count) {
	printf("\e7");
	printf("\e[2;80H");
	printf("Count:%-6d", count);
	printf("\e8");
}
void display(int count, double v) {
	printf("\e7");
	printf("\e[2;60H");
	printf("V:%-6f", v);
	printf("\e[2;80H"); 
	printf("Count:%-6d", count);
	printf("\e8");
}
//int main(){
//	initDisplay();
//	xbox_map_t map;
//	memset(&map, 0, sizeof(xbox_map_t));
//	map.lt = -32767;
//	map.rt = -32767;
//	initDisplay(map);
//	initDisplay(100);
//}

