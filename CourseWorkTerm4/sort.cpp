#include "sort.h"

#include <algorithm>
#include <iostream>

#include "framework.h"

using namespace std;

bool AscendingOrder(double a, double b)
{
	return a < b;
}

bool DescendingOrder(double a, double b)
{
	return a > b;
}

int GetData(vector<double>& array, wstring str)
{
	if (str.empty()) return 1;
	size_t pos = 0;
	std::wstring token;
	while (!str.empty())
	{
		pos = find_if(str.begin(), str.end(), [](wchar_t ch) { return !iswdigit(ch) && ch != L'.'; }) - str.begin();
		token = str.substr(0, pos);
		if (!iswdigit(token[0]) && token[0] != L'.')
		{
			str.erase(0, pos + 1);
			continue;
		}
		array.push_back(stod(token));
		str.erase(0, pos + 1);
	}
	// array.push_back(stod(str));
	return 0;
}


int SortWithRegular(vector<double>& array, sort_method sm)
{
	if (sm == ascending)
		sort(array.begin(), array.end(), AscendingOrder);
	else
		sort(array.begin(), array.end(), DescendingOrder);
	return 0;
}

int SortWithLambda(vector<double>& array, sort_method sm)
{
	if (sm == ascending)
		sort(array.begin(), array.end(), [](int a, int b) { return a < b; });
	else
		sort(array.begin(), array.end(), [](int a, int b) { return a > b; });
	return 0;
}
