#include "transform.h"

using namespace std;

// Компоненты окна для transform
HWND transfExBtn;
HWND transfExStat;
HWND transfExInp;
HWND transfExRBtn1;
HWND transfExRBtn2;

ATOM TransfRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = TransfWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COURSEWORKTERM4));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = TRANSF_CLASS;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

LRESULT CALLBACK TransfWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		{
			(void)setlocale(LC_ALL, "russian");
			transfExBtn = CreateWindow(L"Button", L"Запустить", WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd,
			                           (HMENU)ID_BUTTON_TRANSF_EXEC, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			                           nullptr);
			transfExStat = CreateWindow(L"Static", L"Введите строку:", WS_CHILD | WS_VISIBLE, 10,
			                            10, 980, 25, hWnd, nullptr, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			                            nullptr);
			transfExInp = CreateWindow(L"Edit", L"Hello, World!", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 0,
			                           0, 0, 0, hWnd, nullptr, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			                           nullptr);
			transfExRBtn1 = CreateWindow(L"Button", L"К верхнему регистру", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			                             0, 0, 0, 0,
			                             hWnd, (HMENU)ID_RADBUTTON_TRANSF_TO_UPPER,
			                             (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
			SendMessage(transfExRBtn1, BM_SETCHECK, BST_CHECKED, 0);
			transfExRBtn2 = CreateWindow(L"Button", L"К нижнему регистру", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			                             0,
			                             0, 0, 0,
			                             hWnd, (HMENU)ID_RADBUTTON_TRANSF_TO_LOWER,
			                             (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);
		}
		break;
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Обработка событий
			switch (wmId)
			{
			case ID_BUTTON_TRANSF_EXEC:
				{
					int inpSize = GetWindowTextLength(transfExInp) + 1;
					LPWSTR inp = new wchar_t[inpSize];
					GetWindowText(transfExInp, inp, inpSize);

					vector<wchar_t> inpVectorReg;
					TransfGetData(inpVectorReg, inp);
					vector<wchar_t> inpVectorLambda(inpVectorReg);
					TransfWithRegular(inpVectorReg,
					                  BST_CHECKED == SendMessage(transfExRBtn1, BM_GETCHECK, 0, 0)
						                  ? to_tupper
						                  : to_tlower);
					TransfWithLambda(inpVectorLambda,
					                 BST_CHECKED == SendMessage(transfExRBtn1, BM_GETCHECK, 0, 0)
						                 ? to_tupper
						                 : to_tlower);

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

			SetWindowPos(transfExStat, nullptr, 10, 10, width - 20, 25, SWP_NOZORDER);
			SetWindowPos(transfExInp, nullptr, 10, 40, width - 20, 25, SWP_NOZORDER);
			SetWindowPos(transfExRBtn1, nullptr, 10, 70, width / 2 - 10, 25, SWP_NOZORDER);
			SetWindowPos(transfExRBtn2, nullptr, width / 2 + 10, 70, width / 2 - 20, 25, SWP_NOZORDER);
			SetWindowPos(transfExBtn, nullptr, width / 2 - width / 10, 100, width / 5, height - 110, SWP_NOZORDER);
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


wchar_t ToUpper(const wchar_t& ch)
{
	return towupper(ch);
}

wchar_t ToLower(const wchar_t& ch)
{
	return towlower(ch);
}

int TransfGetData(std::vector<wchar_t>& array, std::wstring str)
{
	if (str.empty()) return 1;
	for (auto el : str)
	{
		array.push_back(el);
	}
	return 0;
}

int TransfWithRegular(std::vector<wchar_t>& array, transf_method tm)
{
	if (tm == to_tupper)
		transform(array.cbegin(), array.cend(), array.begin(), ToUpper);
	else
		transform(array.cbegin(), array.cend(), array.begin(), ToLower);
	return 0;
}

int TransfWithLambda(std::vector<wchar_t>& array, transf_method tm)
{
	if (tm == to_tupper)
		transform(array.cbegin(), array.cend(), array.begin(), [](const wchar_t& ch) { return towupper(ch); });
	else
		transform(array.cbegin(), array.cend(), array.begin(), [](const wchar_t& ch) { return towlower(ch); });
	return 0;
}
