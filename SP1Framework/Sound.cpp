#include <iostream>
#include "Sound.h"
#include <Windows.h>

using namespace std;

void sound::BGM()
{
	bool music = PlaySound(L"BGM.wav", NULL, SND_FILENAME | SND_ASYNC);
}