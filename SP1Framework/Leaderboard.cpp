#include "Leaderboard.h"


void Leaderboard::saverer(double scor)
{
	lb.push_back(scor);
}

void Leaderboard::sorterer()
{
	sort(lb.begin(), lb.end());
	if (lb.size() > 5)
	{
		lb.pop_back();
	}
}