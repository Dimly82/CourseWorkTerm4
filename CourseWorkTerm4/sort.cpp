#include "sort.h"

#include <algorithm>
#include <chrono>
#include <iostream>

#include "framework.h"

bool AscendingOrder(int a, int b)
{
	return a < b;
}

bool DescendingOrder(int a, int b)
{
	return a > b;
}

int GetData(std::vector<int>& array, std::wstring str)
{
	size_t pos = 0;
	std::wstring token;
	while ((pos = str.find(',')) != std::wstring::npos)
	{
		token = str.substr(0, pos);
		array.push_back(std::stoi(token));
		str.erase(0, pos + 1);
	}
	array.push_back(std::stoi(str));
	return 0;
}


int SortWithRegular(std::vector<int>& array, sort_method sm)
{
	if (sm == ascending)
		std::sort(array.begin(), array.end(), AscendingOrder);
	else
		std::sort(array.begin(), array.end(), DescendingOrder);

	std::wstring message = L"Отсортированный массив: ";
	for (auto& el : array)
		message += std::to_wstring(el) + L", ";
	MessageBox(nullptr, message.c_str(), L"Обычная функция", MB_OK);
	return 0;
}

int SortWithLambda(std::vector<int>& array, sort_method sm)
{
	if (sm == ascending)
		std::sort(array.begin(), array.end(), [](int a, int b) { return a < b; });
	else
		std::sort(array.begin(), array.end(), [](int a, int b) { return a > b; });

	std::wstring message = L"Отсортированный массив: ";
	for (auto& el : array)
		message += std::to_wstring(el) + L", ";
	MessageBox(nullptr, message.c_str(), L"Лямбда функция", MB_OK);
	return 0;
}
