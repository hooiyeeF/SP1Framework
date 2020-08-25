#include "Player.h"

int Player::getx()
{
	return x;
}

int Player::gety()
{
	return y;
}

void Player::setx(int xset)
{
	x = xset;
}

void Player::sety(int yset)
{
	y = yset;
}

void Player::xinc()
{
	x++;
}

void Player::yinc()
{
	y++;
}

void Player::xdec()
{
	x--;
}

void Player::ydec()
{
	y--;
}

void Player::draw(Console& g_console)
{
	COORD c;
	c.X = x;
	c.Y = y;
	WORD charColor = 0x0F;
	g_console.writeToBuffer(c, (char)1, charColor);
}