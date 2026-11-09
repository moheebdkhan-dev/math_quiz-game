#pragma once

#include <iostream>

using namespace std;

namespace myInputLib {
	int readIntegerInRange(string message, int from, int to) {
		int Num;
		do {
			cout << message << endl;
			cin >> Num;
		} while (Num < from || Num > to);
		return Num;
	}
	int readIntegerInRangeWithValidation() {
		int Num;
		cout << "Please enter a number " << endl;
		cin >> Num;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid input, please enter a valid one\n";
			cin >> Num;
		}
		return Num;
	}
	void readIntegerArray(int arr[], short length) {
		for (short i = 0; i < length; i++) {
			cout << "Elment " << i + 1 << " : ";
			cin >> arr[i];
		}
	}
}