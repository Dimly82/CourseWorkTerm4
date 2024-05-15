#include "for_each.h"

using namespace std;

// Компоненты окна для for_each
HWND feachExBtn;
HWND feachExStat;
HWND feachExInp;
HWND feachExRBtn1;
HWND feachExRBtn2;

ATOM FEachRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = FEachWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COURSEWORKTERM4));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = FEACH_CLASS;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

LRESULT CALLBACK FEachWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		{
			(void)setlocale(LC_ALL, "russian");
			feachExBtn = CreateWindow(L"Button", L"Запустить", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd,
			                          (HMENU)ID_BUTTON_FEACH_EXEC, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			                          nullptr);
			feachExStat = CreateWindow(L"Static", L"Введите строку:", WS_CHILD | WS_VISIBLE, 10,
			                           10, 980, 25, hWnd, nullptr, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			                           nullptr);
			feachExInp = CreateWindow(L"Edit", L"Hello, World!", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 0,
			                          0, 0, 0, hWnd, nullptr, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			                          nullptr);
			feachExRBtn1 = CreateWindow(L"Button", L"К верхнему регистру", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			                            0, 0, 0, 0,
			                            hWnd, (HMENU)ID_RADBUTTON_FEACH_FROM_CHAR,
			                            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
			SendMessage(feachExRBtn1, BM_SETCHECK, BST_CHECKED, 0);
			feachExRBtn2 = CreateWindow(L"Button", L"К нижнему регистру", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 0,
			                            0, 0, 0,
			                            hWnd, (HMENU)ID_RADBUTTON_FEACH_FROM_CHAR,
			                            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
		}
		break;
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Обработка событий
			switch (wmId)
			{
			case ID_BUTTON_FEACH_EXEC:
				{
					int inpSize = GetWindowTextLength(feachExInp) + 1;
					LPWSTR inp = new wchar_t[inpSize];
					GetWindowText(feachExInp, inp, inpSize);

					vector<wchar_t> inpVectorReg;
					FEachGetData(inpVectorReg, inp);
					vector<wchar_t> inpVectorLambda(inpVectorReg);
					FEachWithRegular(inpVectorReg,
					                 BST_CHECKED == SendMessage(feachExRBtn1, BM_GETCHECK, 0, 0)
						                 ? to_upper
						                 : to_lower);
					FEachWithLambda(inpVectorLambda,
					                BST_CHECKED == SendMessage(feachExRBtn1, BM_GETCHECK, 0, 0)
						                ? to_upper
						                : to_lower);

					std::wstring out_message = L"Обычная фнукция: " + wstring(inpVectorReg.begin(), inpVectorReg.end());
					out_message += L"\nЛямбда фнукция: " + wstring(inpVectorLambda.begin(), inpVectorLambda.end());

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
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			SetWindowPos(feachExStat, nullptr, 10, 10, width - 20, 25, SWP_NOZORDER);
			SetWindowPos(feachExInp, nullptr, 10, 40, width - 20, 25, SWP_NOZORDER);
			SetWindowPos(feachExRBtn1, nullptr, 10, 70, width / 2 - 10, 25, SWP_NOZORDER);
			SetWindowPos(feachExRBtn2, nullptr, width / 2 + 10, 70, width / 2 - 20, 25, SWP_NOZORDER);
			SetWindowPos(feachExBtn, nullptr, width / 2 - width / 10, 100, width / 5, height - 110, SWP_NOZORDER);
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


void ToUpper(wchar_t& ch)
{
	ch = towupper(ch);
}

void ToLower(wchar_t& ch)
{
	ch = towlower(ch);
}

int FEachGetData(std::vector<wchar_t>& array, std::wstring str)
{
	if (str.empty()) return 1;
	for (auto el : str)
	{
		array.push_back(el);
	}
	return 0;
}

int FEachWithRegular(std::vector<wchar_t>& array, feach_method fem)
{
	if (fem == to_upper)
		for_each(array.begin(), array.end(), ToUpper);
	else
		for_each(array.begin(), array.end(), ToLower);
	return 0;
}

int FEachWithLambda(std::vector<wchar_t>& array, feach_method fem)
{
	if (fem == to_upper)
		for_each(array.begin(), array.end(), [](wchar_t& ch) { ch = towupper(ch); });
	else
		for_each(array.begin(), array.end(), [](wchar_t& ch) { ch = towlower(ch); });
	return 0;
}
