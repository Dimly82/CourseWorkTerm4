#include "framework.h"
#include "CourseWorkTerm4.h"

#include <string>

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
                      _In_ int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Ининциализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOAD_STRING);
	LoadStringW(hInstance, IDC_COURSEWORKTERM4, szWindowClass, MAX_LOAD_STRING);

	// Регистрация классов окон
	MyRegisterClass(hInstance);
	SortRegisterClass(hInstance);

	// Инициализация главного окна
	if (!InitInstance(hInstance, nCmdShow)) {
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COURSEWORKTERM4));

	MSG msg;

	// Главный цикл
	while (GetMessage(&msg, nullptr, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
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

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	hInst = hInstance;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	                          CW_USEDEFAULT, 0, 500, 200, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd) {
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE: {
		// Создание кнопок для вызова окон с примерами
		sortWndBtn = CreateWindow(L"BUTTON", L"Пример sort",
		                          WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 200, 30, hWnd,
		                          (HMENU)ID_BUTTON_SORT_EX, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
		feachWndBtn = CreateWindow(L"BUTTON", L"Пример for_each",
		                           WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 50, 200, 30, hWnd,
		                           (HMENU)ID_BUTTON_FEACH_EX, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		                           nullptr);
		transfWndBtn = CreateWindow(L"BUTTON", L"Пример transform",
		                            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 90, 200, 30, hWnd,
		                            (HMENU)ID_BUTTON_TRANSF_EX, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		                            nullptr);
	}
	break;
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		// Обработка команд
		switch (wmId) {
		case ID_BUTTON_SORT_EX: {
			sortWnd = CreateWindow(SORT_CLASS, L"Пример sort", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 500, 250, hWnd,
			                       nullptr, hInst, nullptr);
			ShowWindow(sortWnd, SW_SHOW);
		}
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
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

ATOM SortRegisterClass(HINSTANCE hInstance) {
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

LRESULT CALLBACK SortWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE: {
		// Создание подписи к текстовому полю
		sortExStat = CreateWindow(L"Static", L"Введите элементы-числа массива (через запятую, без пробелов)",
		                          WS_CHILD | WS_VISIBLE, 10, 10, 460, 25, hWnd, nullptr,
		                          (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
		// Создание текстового поля для ввода элементов массива
		sortExInp = CreateWindow(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 10, 40, 460, 25,
		                         hWnd, nullptr, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
		// Кнопка запуска примера
		sortExBtn = CreateWindow(L"Button", L"Запустить", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 170, 200, 30, hWnd,
		                         (HMENU)ID_BUTTON_SORT_EXEC, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		                         nullptr);
		// Выбор метода сортировки
		sortExRBtn1 = CreateWindow(L"Button", L"По возрастанию", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 70,
		                           150,
		                           25, hWnd, (HMENU)ID_RADBUTTON_SORT_ASC,
		                           (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
		SendMessage(sortExRBtn1, BM_SETCHECK, BST_CHECKED, 0);
		sortExRBtn2 = CreateWindow(L"Button", L"По убыванию", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 250, 70, 150,
		                           25, hWnd, (HMENU)ID_RADBUTTON_SORT_DESC,
		                           (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
	}
	break;
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		// Обработка событий
		switch (wmId) {
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
