#pragma once
#include <string>
#include <vector>

typedef enum {
	ascending,
	descending
} sort_method;

// Функции для сортировки
bool AscendingOrder(int a, int b);
bool DescendingOrder(int a, int b);

// Функция получения данных из input
int GetData(std::vector<int>& array, std::wstring str);

// Функции для вызова sort с разными функциями
int SortWithRegular(std::vector<int> array, sort_method sm);
int SortWithLambda(std::vector<int> array, sort_method sm);
