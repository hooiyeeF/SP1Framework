
#include "Framework\console.h"
#include "Guard.h"


void Guard::drawG1(Console& g_console)
{
	COORD c;
	c.X = 50;
	c.Y = 5;
	WORD charColor = 0x0c;
	g_console.writeToBuffer(c, (char)1, charColor);
};

void Guard::drawG2(Console& g_console)
{

	COORD c;
	COORD d;
	c.X = 28;
	c.Y = 5;
	d.X = 44;
	d.Y = 8;
	WORD charColor = 0x0c;
	g_console.writeToBuffer(c, (char)1, charColor);
	g_console.writeToBuffer(d, (char)1, charColor);
};

void Guard::drawG3(Console& g_console)
{
	COORD c;
	COORD d;
	COORD e;
	c.X = 36;
	c.Y = 5;
	d.X = 36;
	d.Y = 11;
	e.X = 55;
	e.Y = 8;
	WORD charColor = 0x0c;
	g_console.writeToBuffer(c, (char)1, charColor);
	g_console.writeToBuffer(d, (char)1, charColor);
	g_console.writeToBuffer(e, (char)1, charColor);
};