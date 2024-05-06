#include "sort.h"

#include <iostream>

#include "framework.h"

bool AscendingOrder(int a, int b) {
	return a < b;
}

bool DescendingOrder(int a, int b) {
	return a > b;
}

int GetData(std::vector<int>& array, std::wstring str) {
	size_t pos = 0;
	std::wstring token;
	while ((pos = str.find(',')) != std::wstring::npos) {
		token = str.substr(0, pos);
		array.push_back(std::stoi(token));
		str.erase(0, pos + 1);
	}
	return 0;
}
