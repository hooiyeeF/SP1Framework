#include <iostream>
#include "Sound.h"
#include <Windows.h>



using namespace std;

void sound::BGM()
{
	bool music = PlaySound(L"../SP1Framework/Sound/Sound.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}