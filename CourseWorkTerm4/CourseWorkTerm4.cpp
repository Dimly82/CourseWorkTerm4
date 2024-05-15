#include "framework.h"
#include "CourseWorkTerm4.h"

using namespace std;

constexpr auto MAX_LOAD_STRING = 100;

// Названия классов окон
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

// Функции для главного окна
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

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
	FEachRegisterClass(hInstance);

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
					if (!IsWindow(sortWnd))
					{
						sortWnd = CreateWindow(SORT_CLASS, L"Пример sort", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 500,
						                       200,
						                       hWnd, nullptr, hInst, nullptr);
						ShowWindow(sortWnd, SW_SHOW);
					}
					else
						SetForegroundWindow(sortWnd);
				}
				break;
			case ID_BUTTON_FEACH_EX:
				{
					if (!IsWindow(feachWnd))
					{
						feachWnd = CreateWindow(FEACH_CLASS, L"Пример for_each", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0,
						                        500,
						                        200,
						                        hWnd, nullptr, hInst, nullptr);
						ShowWindow(feachWnd, SW_SHOW);
					}
					else
						SetForegroundWindow(feachWnd);
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
