#include "framework.h"
#include "CourseWorkTerm4.h"
#include "sort.h"

#include <string>
#include <atlstr.h>
#include <gdiplus.h>

using namespace Gdiplus;
using namespace std;

constexpr auto MAX_LOAD_STRING = 100;

// ID кнопок
constexpr auto ID_BUTTON_SORT_EX = 1;
constexpr auto ID_BUTTON_FEACH_EX = 2;
constexpr auto ID_BUTTON_TRANSF_EX = 3;

constexpr auto ID_BUTTON_SORT_EXEC = 4;
constexpr auto ID_RADBUTTON_SORT_ASC = 5;
constexpr auto ID_RADBUTTON_SORT_DESC = 6;

// Названия классов окон
constexpr auto SORT_CLASS = L"SortWnd";
constexpr auto FEACH_CLASS = L"FeachWnd";
constexpr auto TRANSF_CLASS = L"TransfWnd";

// Глобальные переменные:
HINSTANCE hInst; // текущая инстанция
WCHAR szTitle[MAX_LOAD_STRING]; // имя главного окна
WCHAR szWindowClass[MAX_LOAD_STRING]; // класс главного окна

// Обработчики окон
HWND sortWnd;
HWND feachWnd;
HWND transfWnd;

// Кнопки главного окна
HWND sortWndBtn;
HWND feachWndBtn;
HWND transfWndBtn;

// Компоненты окна для sort
HWND sortExBtn;
HWND sortExStat;
HWND sortExInp;
HWND sortExRBtn1;
HWND sortExRBtn2;
HWND sortExRegStat;
HWND sortExLamStat;

// Скриншоты функций
Image* regular_sort_fns;
Image* regular_sort_call;
Image* lambda_sort_fns;
Image* lambda_sort_call;

// Функции для главного окна
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// Функции для окна с примером sort
ATOM SortRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK SortWndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Ининциализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOAD_STRING);
	LoadStringW(hInstance, IDC_COURSEWORKTERM4, szWindowClass, MAX_LOAD_STRING);

	// Регистрация классов окон
	MyRegisterClass(hInstance);
	SortRegisterClass(hInstance);

	// Инициализация GDI+
	GdiplusStartupInput gdiplus_startup_input;
	ULONG_PTR gdiplus_token;
	GdiplusStartup(&gdiplus_token, &gdiplus_startup_input, nullptr);

	// Инициализация главного окна
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COURSEWORKTERM4));

	MSG msg;

	// Главный цикл
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplus_token);
	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COURSEWORKTERM4));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	                          CW_USEDEFAULT, 0, 500, 200, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		{
			// Создание кнопок для вызова окон с примерами
			sortWndBtn = CreateWindow(L"BUTTON", L"Пример sort",
			                          WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 980, 30, hWnd,
			                          (HMENU)ID_BUTTON_SORT_EX, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			                          nullptr);
			feachWndBtn = CreateWindow(L"BUTTON", L"Пример for_each",
			                           WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 50, 980, 30, hWnd,
			                           (HMENU)ID_BUTTON_FEACH_EX, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			                           nullptr);
			transfWndBtn = CreateWindow(L"BUTTON", L"Пример transform",
			                            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 90, 980, 30, hWnd,
			                            (HMENU)ID_BUTTON_TRANSF_EX, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			                            nullptr);
		}
		break;
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Обработка команд
			switch (wmId)
			{
			case ID_BUTTON_SORT_EX:
				{
					sortWnd = CreateWindow(SORT_CLASS, L"Пример sort", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 500, 200,
					                       hWnd, nullptr, hInst, nullptr);
					ShowWindow(sortWnd, SW_SHOW);
				}
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
	case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			SetWindowPos(sortWndBtn, nullptr, 10, 10, width - 20, height / 3 - 15, SWP_NOZORDER);
			SetWindowPos(feachWndBtn, nullptr, 10, height / 3 + 10, width - 20, height / 3 - 15, SWP_NOZORDER);
			SetWindowPos(transfWndBtn, nullptr, 10, 2 * height / 3 + 10, width - 20, height / 3 - 15, SWP_NOZORDER);
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_GETMINMAXINFO:
		{
			MINMAXINFO* mmi = (MINMAXINFO*)lParam;
			mmi->ptMinTrackSize.x = 200;
			mmi->ptMinTrackSize.y = 200;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

ATOM SortRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = SortWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COURSEWORKTERM4));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = SORT_CLASS;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

LRESULT CALLBACK SortWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		{
			// Создание подписи к текстовому полю
			sortExStat = CreateWindow(L"Static", L"Введите элементы-числа массива (через запятую, без пробелов)",
			                          WS_CHILD | WS_VISIBLE, 10, 10, 980, 25, hWnd, nullptr,
			                          (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
			// Создание текстового поля для ввода элементов массива
			sortExInp = CreateWindow(L"Edit", L"10,9,8,7,6,5,4,3,2,1,0",
			                         WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 0, 0, 0, 0,
			                         hWnd, nullptr, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
			// Кнопка запуска примера
			sortExBtn = CreateWindow(L"Button", L"Запустить", WS_VISIBLE | WS_CHILD | WS_BORDER, 0, 0, 0, 0,
			                         hWnd,
			                         (HMENU)ID_BUTTON_SORT_EXEC, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			                         nullptr);
			// Выбор метода сортировки
			sortExRBtn1 = CreateWindow(L"Button", L"По возрастанию", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 0, 0,
			                           0, 0
			                           , hWnd, (HMENU)ID_RADBUTTON_SORT_ASC,
			                           (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
			SendMessage(sortExRBtn1, BM_SETCHECK, BST_CHECKED, 0);
			sortExRBtn2 = CreateWindow(L"Button", L"По убыванию", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 0, 0, 0,
			                           0, hWnd, (HMENU)ID_RADBUTTON_SORT_DESC,
			                           (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
			// Подписи к скриншотам
			// sortExRegStat = CreateWindow(L"Static", L"Сортировка через обычные функции:",
			//                              WS_CHILD | WS_VISIBLE, 10, 100, 490, 25, hWnd, nullptr,
			//                              (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
			// sortExLamStat = CreateWindow(L"Static", L"Сортировка через лямбда функции:",
			//                              WS_CHILD | WS_VISIBLE, 510, 100, 480, 25, hWnd, nullptr,
			//                              (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);

			// Загрузка скриншотов
			regular_sort_fns = new Image(L"RegularSortFns.png");
			regular_sort_call = new Image(L"RegularSortCall.png");
			lambda_sort_fns = new Image(L"LambdaSortFns.png");
			lambda_sort_call = new Image(L"LambdaSortCall.png");
		}
		break;
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Обработка событий
			switch (wmId)
			{
			case ID_BUTTON_SORT_EXEC:
				{
					int inpSize = GetWindowTextLength(sortExInp) + 1;
					LPWSTR inp = new wchar_t[inpSize];
					GetWindowText(sortExInp, inp, inpSize);

					vector<double> inpVectorReg;
					GetData(inpVectorReg, inp);
					vector<double> inpVectorLambda(inpVectorReg);
					SortWithRegular(inpVectorReg,
					                BST_CHECKED == SendMessage(sortExRBtn1, BM_GETCHECK, 0, 0)
						                ? ascending
						                : descending);
					SortWithLambda(inpVectorLambda,
					               BST_CHECKED == SendMessage(sortExRBtn1, BM_GETCHECK, 0, 0)
						               ? ascending
						               : descending);

					std::wstring out_message = L"Обычная фнукция: ";
					for (auto& el : inpVectorReg)
						out_message += std::to_wstring(el) + L", ";

					out_message += L"\nЛямбда фнукция: ";
					for (auto& el : inpVectorLambda)
						out_message += std::to_wstring(el) + L", ";

					MessageBox(hWnd, out_message.c_str(), L"Результат", MB_OK);

					delete[] inp;
				}
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			RECT wnd_rect;
			GetWindowRect(hWnd, &wnd_rect);
			int width = wnd_rect.right - wnd_rect.left;
			int height = wnd_rect.bottom - wnd_rect.top;

			// Отрисовка скриншотов
			// Graphics graphics(hdc);
			// graphics.DrawImage(regular_sort_fns, Rect(10, 125, 460, 230));
			// graphics.DrawImage(regular_sort_call, Rect(10, 135 + height / 5, width / 2 - 20, height / 5));
			// graphics.DrawImage(lambda_sort_fns, Rect(width / 2, 125, width / 2 - 20, height / 4));
			// graphics.DrawImage(lambda_sort_call, Rect(width / 2, 135 + height / 4, width / 2 - 20, height / 4));

			EndPaint(hWnd, &ps);
		}
		break;
	case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			SetWindowPos(sortExStat, nullptr, 10, 10, width - 20, 25, SWP_NOZORDER);
			SetWindowPos(sortExInp, nullptr, 10, 40, width - 20, 25, SWP_NOZORDER);
			SetWindowPos(sortExRBtn1, nullptr, 10, 70, width / 2 - 10, 25, SWP_NOZORDER);
			SetWindowPos(sortExRBtn2, nullptr, width / 2 + 10, 70, width / 2 - 20, 25, SWP_NOZORDER);
			// SetWindowPos(sortExRegStat, nullptr, 10, 100, width / 2 - 10, 25, SWP_NOZORDER);
			// SetWindowPos(sortExLamStat, nullptr, width / 2 + 10, 100, width / 2 - 20, 25, SWP_NOZORDER);
			SetWindowPos(sortExBtn, nullptr, width / 2 - width / 10, 100, width / 5, height - 110,
			             SWP_NOZORDER);
		}
		break;
	case WM_GETMINMAXINFO:
		{
			MINMAXINFO* mmi = (MINMAXINFO*)lParam;
			mmi->ptMinTrackSize.x = 500;
			mmi->ptMinTrackSize.y = 200;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
