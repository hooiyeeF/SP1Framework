#pragma once
#include "Framework\console.h"

class Map
{
private:
	int wallX, wallY;
public:
	double Dtime = 3;
	bool getTP = false;
	bool getKey = false;
	void drawR1(Console& g_console);
	void drawR2(Console& g_console);
	void drawR3(Console& g_console);
	void drawRTP(Console& g_console);
	void drawREnd(Console& g_console);
	void drawLR(Console& g_console);
};