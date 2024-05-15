#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "framework.h"
#include "Resource.h"

// ID кнопок
constexpr auto ID_BUTTON_FEACH_EXEC = 7;
constexpr auto ID_RADBUTTON_FEACH_TO_CHAR = 8;
constexpr auto ID_RADBUTTON_FEACH_FROM_CHAR = 9;

// Класс окна
constexpr auto FEACH_CLASS = L"FeachWnd";

typedef enum
{
	to_upper,
	to_lower
} feach_method;

// Функции для окна с примером for_each
ATOM FEachRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK FEachWndProc(HWND, UINT, WPARAM, LPARAM);

// Функции примеры
void ToUpper(wchar_t& ch);
void ToLower(wchar_t& ch);

// Функция получения данных из input
int FEachGetData(std::vector<wchar_t>& array, std::wstring str);

// Функции для вызова for_each с разными функциями
int FEachWithRegular(std::vector<wchar_t>& array, feach_method fem);
int FEachWithLambda(std::vector<wchar_t>& array, feach_method fem);
