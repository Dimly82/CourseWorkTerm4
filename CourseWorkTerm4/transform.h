#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "framework.h"
#include "Resource.h"

// ID кнопок
constexpr auto ID_BUTTON_TRANSF_EXEC = 10;
constexpr auto ID_RADBUTTON_TRANSF_TO_UPPER = 11;
constexpr auto ID_RADBUTTON_TRANSF_TO_LOWER = 12;

// Класс окна
constexpr auto TRANSF_CLASS = L"TransfWnd";

typedef enum
{
	to_tupper,
	to_tlower
} transf_method;

// Функции для окна с примером for_each
ATOM TransfRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK TransfWndProc(HWND, UINT, WPARAM, LPARAM);

// Функции примеры
wchar_t ToUpper(const wchar_t& ch);
wchar_t ToLower(const wchar_t& ch);

// Функция получения данных из input
int TransfGetData(std::vector<wchar_t>& array, std::wstring str);

// Функции для вызова for_each с разными функциями
int TransfWithRegular(std::vector<wchar_t>& array, transf_method tm);
int TransfWithLambda(std::vector<wchar_t>& array, transf_method tm);
