#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "framework.h"
#include "Resource.h"

// ID кнопок
constexpr auto ID_BUTTON_SORT_EX = 1;
constexpr auto ID_BUTTON_FEACH_EX = 2;
constexpr auto ID_BUTTON_TRANSF_EX = 3;

constexpr auto ID_BUTTON_SORT_EXEC = 4;
constexpr auto ID_RADBUTTON_SORT_ASC = 5;
constexpr auto ID_RADBUTTON_SORT_DESC = 6;

// Класс окна
constexpr auto SORT_CLASS = L"SortWnd";

typedef enum
{
	ascending,
	descending
} sort_method;

// Функции для окна с примером sort
ATOM SortRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK SortWndProc(HWND, UINT, WPARAM, LPARAM);

// Функции для сортировки
bool AscendingOrder(double a, double b);
bool DescendingOrder(double a, double b);

// Функция получения данных из input
int GetData(std::vector<double>& array, std::wstring str);

// Функции для вызова sort с разными функциями
int SortWithRegular(std::vector<double>& array, sort_method sm);
int SortWithLambda(std::vector<double>& array, sort_method sm);
