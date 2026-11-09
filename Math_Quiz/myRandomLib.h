#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

namespace myRandomLib {
	int RandomNumber(int from, int to) {
		return rand() % (to - from + 1) + from;
	}
}