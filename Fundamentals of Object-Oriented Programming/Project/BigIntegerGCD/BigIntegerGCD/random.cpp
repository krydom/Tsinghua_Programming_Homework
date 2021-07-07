#include "random.h"
#include <ctime>
#include <cstdlib>

using namespace std;

void randomSet()
{
	srand(time(0));
}

int random()
{
	int tmp = (rand() << 15) | rand();
	if (rand() % 2) tmp = -tmp;
	return tmp;
}