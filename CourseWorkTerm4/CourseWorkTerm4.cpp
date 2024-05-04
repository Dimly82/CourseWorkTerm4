#include "framework.h"
#include "CourseWorkTerm4.h"

#include <chrono>
#include <string>

constexpr auto MAX_LOAD_STRING = 100;
constexpr auto ID_BUTTON_SORT_EX = 1;
constexpr auto ID_BUTTON_FEACH_EX = 2;
constexpr auto ID_BUTTON_TRANSF_EX = 3;
constexpr auto ID_RADBUTTON_SORT_ASC = 4;
constexpr auto ID_RADBUTTON_SORT_DESC = 5;

constexpr auto SORT_CLASS = L"SortWnd";
constexpr auto FEACH_CLASS = L"FeachWnd";
constexpr auto TRANSF_CLASS = L"TransfWnd";

// Global Variables:
HINSTANCE hInst; // current instance
WCHAR szTitle[MAX_LOAD_STRING]; // The title bar text
WCHAR szWindowClass[MAX_LOAD_STRING]; // the main window class name

// Window handlers
HWND sortWnd;
HWND feachWnd;
HWND transfWnd;

// Sort example components
HWND sortExBtn;
HWND sortExStat;
HWND sortExInp;
HWND sortExRBtn1;
HWND sortExRBtn2;

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// Sort window
ATOM SortRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK SortWndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOAD_STRING);
	LoadStringW(hInstance, IDC_COURSEWORKTERM4, szWindowClass, MAX_LOAD_STRING);
	MyRegisterClass(hInstance);
	SortRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow)) {
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COURSEWORKTERM4));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

/**
    @brief  Registers the window class.
    @param  hInstance     
**/
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
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_COURSEWORKTERM4);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

/** @brief Saves instance handle and creates main window.
	@param hInstance 
	@param nCmdShow
**/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	                          CW_USEDEFAULT, 0, 500, 200, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd) {
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

/**
    @brief  Processes messages for the main window.
    @param  hWnd   
    @param  message
    @param  wParam 
    @param  lParam        
**/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE: {
		CreateWindow(L"BUTTON", L"Пример sort",
		             WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 200, 30, hWnd,
		             (HMENU)ID_BUTTON_SORT_EX, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
		CreateWindow(L"BUTTON", L"Пример for_each",
		             WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 50, 200, 30, hWnd,
		             (HMENU)ID_BUTTON_FEACH_EX, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
		CreateWindow(L"BUTTON", L"Пример transform",
		             WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 90, 200, 30, hWnd,
		             (HMENU)ID_BUTTON_TRANSF_EX, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	}
	break;
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId) {
		case ID_BUTTON_SORT_EX: {
			sortWnd = CreateWindow(SORT_CLASS, L"Пример sort", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 500, 250, hWnd,
			                       nullptr, hInst, nullptr);
			ShowWindow(sortWnd, SW_SHOW);
		}
		break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
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
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = SORT_CLASS;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

LRESULT CALLBACK SortWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE: {
		sortExStat = CreateWindow(L"Static", L"Введите элементы-числа массива (через запятую, без пробелов)",
		                          WS_CHILD | WS_VISIBLE, 10, 10, 460, 25, hWnd, nullptr,
		                          (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
		sortExInp = CreateWindow(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 10, 40, 460, 25,
		                         hWnd, nullptr, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
		sortExBtn = CreateWindow(L"Button", L"Запустить", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 170, 200, 30, hWnd,
		                         nullptr, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
		sortExRBtn1 = CreateWindow(L"Button", L"По возрастанию", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 70, 240,
		                           95, hWnd, nullptr, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
		SendMessage(sortExRBtn1, BM_SETCHECK, BST_CHECKED, 0);
		sortExRBtn2 = CreateWindow(L"Button", L"По убыванию", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 250, 70, 460,
		                           95, hWnd, nullptr, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
	}
	break;
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
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

/**
    @brief  Message handler for about box.
    @param  hDlg   
    @param  message
    @param  wParam 
    @param  lParam    
**/
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
