#include <iostream>
#include "Sound.h"
#include <Windows.h>



using namespace std;

void sound::BGM()
{
	bool music = PlaySound(L"../SP1Framework/Sound.wav", NULL, SND_FILENAME | SND_ASYNC| SND_NOSTOP | SND_LOOP);
}

void sound::BGMS()
{
	bool music = PlaySound(L"../SP1Framework/Sound.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void sound::Win()
{
	
	bool win = PlaySound(L"../SP1Framework/Cheer2.wav", NULL, SND_FILENAME | SND_ASYNC  );
}

void sound::Chase()
{
	bool chase = PlaySound(L"../SP1Framework/CHASE.wav", NULL, SND_FILENAME | SND_ASYNC );
}

void sound::BP()
{
	Beep(1500, 5);
	Beep(2000, 10);
	Beep(1500, 5);
}

void sound::appear()
{
	Beep(1000, 5);
	Beep(2000, 4);
	Beep(500, 10);
}

void sound::TP()
{
	Beep(1000, 25);
	Beep(500, 20);
	Beep(1000, 10);
}



void sound::GetK()
{
	Beep(10000, 10);
	Beep(5000, 5);
	Beep(10000, 10);
}

void sound::LDoors()
{
	Beep(100, 10);
	Beep(50, 5);
	Beep(150, 10);
}

void sound::ODoors()
{
	Beep(400, 10);
	Beep(350, 5);
	Beep(500, 10);
}
