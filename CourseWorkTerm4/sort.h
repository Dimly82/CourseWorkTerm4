#pragma once
#include <string>
#include <vector>

typedef enum
{
	ascending,
	descending
} sort_method;

// Функции для сортировки
bool AscendingOrder(double a, double b);
bool DescendingOrder(double a, double b);

// Функция получения данных из input
int GetData(std::vector<double>& array, std::wstring str);

// Функции для вызова sort с разными функциями
int SortWithRegular(std::vector<double>& array, sort_method sm);
int SortWithLambda(std::vector<double>& array, sort_method sm);
