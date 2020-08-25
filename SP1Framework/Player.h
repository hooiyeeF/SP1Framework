#pragma once
#include "Framework\console.h"

class Player
{
private:
	int x, y;
public:
	int getx();
	int gety();
	void setx(int);
	void sety(int);
	void xinc();
	void yinc();
	void xdec();
	void ydec();
	void draw(Console& g_console);
};