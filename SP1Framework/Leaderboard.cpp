#include "Leaderboard.h"


void Leaderboard::saverer(double scor)
{
	ldb.push_back(scor);
}

void Leaderboard::sorterer()
{
	sort(ldb.begin(), ldb.end());
	if (ldb.size() > 5)
	{
		ldb.pop_back();
	}
}