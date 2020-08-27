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

void sound::LDoor()
{
	bool Ldoor = PlaySound(L"../SP1Framework/Doorlock.wav", NULL, SND_FILENAME | SND_ASYNC );
}

void sound::GetK()
{
	bool Getk = PlaySound(L"../SP1Framework/.wav", NULL, SND_FILENAME | SND_ASYNC);
}

//void sound::OpenD()
//{
//	bool OpenD = PlaySound(L"../SP1Framework/.wav", NULL, SND_FILENAME | SND_ASYNC);
//}