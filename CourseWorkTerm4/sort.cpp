#include "sort.h"

using namespace std;

// Компоненты окна для sort
HWND sortExBtn;
HWND sortExStat;
HWND sortExInp;
HWND sortExRBtn1;
HWND sortExRBtn2;
HWND sortExRegStat;
HWND sortExLamStat;

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
			sortExStat = CreateWindow(L"Static", L"Введите числа массива:",
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

bool AscendingOrder(double a, double b)
{
	return a < b;
}

bool DescendingOrder(double a, double b)
{
	return a > b;
}

int GetData(vector<double>& array, wstring str)
{
	if (str.empty()) return 1;
	size_t pos = 0;
	std::wstring token;
	while (!str.empty())
	{
		pos = find_if(str.begin(), str.end(), [](wchar_t ch) { return !iswdigit(ch) && ch != L'.'; }) - str.begin();
		token = str.substr(0, pos);
		if (!iswdigit(token[0]) && token[0] != L'.')
		{
			str.erase(0, pos + 1);
			continue;
		}
		array.push_back(stod(token));
		str.erase(0, pos + 1);
	}
	return 0;
}


int SortWithRegular(vector<double>& array, sort_method sm)
{
	if (sm == ascending)
		sort(array.begin(), array.end(), AscendingOrder);
	else
		sort(array.begin(), array.end(), DescendingOrder);
	return 0;
}

int SortWithLambda(vector<double>& array, sort_method sm)
{
	if (sm == ascending)
		sort(array.begin(), array.end(), [](int a, int b) { return a < b; });
	else
		sort(array.begin(), array.end(), [](int a, int b) { return a > b; });
	return 0;
}
