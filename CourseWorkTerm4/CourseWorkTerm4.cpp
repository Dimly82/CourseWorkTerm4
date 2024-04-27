#include "framework.h"
#include "CourseWorkTerm4.h"

#include <chrono>
#include <string>

constexpr auto MAX_LOAD_STRING = 100;
constexpr auto ID_BUTTON_REGULAR = 1;
constexpr auto ID_BUTTON_LAMBDA = 2;

// Global Variables:
HINSTANCE hInst; // current instance
WCHAR szTitle[MAX_LOAD_STRING]; // The title bar text
WCHAR szWindowClass[MAX_LOAD_STRING]; // the main window class name
HWND textBox;

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// Example functions
int Square(int x) {
	int res = 0;
	for (size_t i = 0; i < 1000000000; i++) res += x;
	return res;
}

auto lambdaSquare = [](int x) {
	int res = 0;
	for (size_t i = 0; i < 1000000000; i++) res += x;
	return res;
};

// Callback functions
void OnRegularFunction(HWND hWnd, int x) {
	auto start = std::chrono::high_resolution_clock::now();
	x = Square(x);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::string res = "Result: " + std::to_string(x) + "\nTime: " + std::to_string(duration.count()) + " microseconds";
	std::wstring tmp = std::wstring(res.begin(), res.end());
	LPCWSTR wres = tmp.c_str();

	MessageBox(hWnd, wres, L"Regular Function Result", MB_OK);
}

void OnLambdaFunction(HWND hWnd, int x) {
	auto start = std::chrono::high_resolution_clock::now();
	x = lambdaSquare(x);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::string res = "Result: " + std::to_string(x) + "\nTime: " + std::to_string(duration.count()) + " microseconds";
	std::wstring tmp = std::wstring(res.begin(), res.end());
	LPCWSTR wres = tmp.c_str();

	MessageBox(hWnd, wres, L"Regular Function Result", MB_OK);
}

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
		CreateWindow(L"BUTTON", L"Regular Function",
		             WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 200, 30, hWnd,
		             (HMENU)ID_BUTTON_REGULAR, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
		CreateWindow(L"BUTTON", L"Lambda Function",
		             WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 50, 200, 30, hWnd,
		             (HMENU)ID_BUTTON_LAMBDA, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
		textBox = CreateWindow(L"Edit", L"5", WS_CHILD | WS_VISIBLE | WS_BORDER, 230, 25, 200, 30, hWnd, NULL, NULL,
		                       NULL);
	}
	break;
	case WM_COMMAND: {
		LPWSTR x = (LPWSTR)malloc(sizeof(wchar_t) * 100);
		GetWindowText(textBox, x, 100);

		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId) {
		case ID_BUTTON_REGULAR:
			OnRegularFunction(hWnd, std::stoi(x));
			break;
		case ID_BUTTON_LAMBDA:
			OnLambdaFunction(hWnd, std::stoi(x));
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

		free(x);
	}
	break;
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
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
