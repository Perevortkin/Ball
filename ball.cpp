// ball.cpp: ���������� ����� ����� ��� ����������.
//
#include <Windows.h>
#include "stdafx.h"
#include "ball.h"

#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;								// ������� ���������
TCHAR szTitle[MAX_LOADSTRING];					// ����� ������ ���������
TCHAR szWindowClass[MAX_LOADSTRING];			// ��� ������ �������� ����

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���������� ��� �����.
	MSG msg;
	HACCEL hAccelTable;

	// ������������� ���������� �����
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BALL, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ��������� ������������� ����������:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BALL));

	// ���� ��������� ���������:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BALL));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_BALL);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND	- ��������� ���� ����������
//  WM_PAINT	-��������� ������� ����
//  WM_DESTROY	 - ������ ��������� � ������ � ���������.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//������������ ��������� ����
	static int dx = 5, dy = 5; //�����������
	//���������� ����
	static int x = 0, y = 0, oldX = 0, oldY = 0;
	HBRUSH brush;
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// ��������� ����� � ����:
		switch (wmId)
		{
		case WM_CREATE:
			MessageBox(hWnd, TEXT("YELLLO"), 0, 0);
			break;
		case WM_TIMER:
			MessageBox(hWnd, TEXT("YELLLO"), 0, 0);
			hdc = GetDC(hWnd);
			brush = (HBRUSH)SelectObject(hdc, GetStockObject(GRAY_BRUSH));

			RECT temp;
			temp.left = oldX;
			temp.top = oldY;
			temp.right = oldX+30;
			temp.bottom = oldY+30;
			//������� ���������� ������
			FillRect(hdc, &temp, brush);
			//������ �����
			brush = (HBRUSH)SelectObject(hdc, GetStockObject(GRAY_BRUSH));
			Ellipse(hdc, x, y, x + 30, y + 30);
			//��������� ��������
			oldX = x;
			oldY = y;
			//���������� ���� �����������
			x += dx;
			y += dy;
			//�������� ������ ���� � ��������� � RECT
			RECT rect;
			GetClientRect(hWnd, &rect);
			//���� ��� ������� �� ������� ������, ������ ����������
			if (x + 30 > rect.right || x < 0)
			{
				dx = -dx;
			}
			if (y + 30>rect.bottom || y < 0)
			{
				dy = -dy;
			}
			SelectObject(hdc, brush);//������� ���� �����
			ReleaseDC(hWnd, hdc);
			break;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			KillTimer(hWnd, 1);
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		SetTimer(hWnd, 1, 20, NULL);
		hdc = BeginPaint(hWnd, &ps);

		// TODO: �������� ����� ��� ���������...
		brush = (HBRUSH)SelectObject(hdc, GetStockObject(GRAY_BRUSH));

		RECT temp;
		temp.left = oldX;
		temp.top = oldY;
		temp.right = oldX + 30;
		temp.bottom = oldY + 30;
		//������� ���������� ������
		FillRect(hdc, &temp, brush);
		//������ �����
		brush = (HBRUSH)SelectObject(hdc, GetStockObject(GRAY_BRUSH));
		Ellipse(hdc, x, y, x + 30, y + 30);
		//��������� ��������
		oldX = x;
		oldY = y;
		//���������� ���� �����������
		x += dx;
		y += dy;
		//�������� ������ ���� � ��������� � RECT
		RECT rect;
		GetClientRect(hWnd, &rect);
		//���� ��� ������� �� ������� ������, ������ ����������
		if (x + 30 > rect.right || x < 0)
		{
			dx = -dx;
		}
		if (y + 30>rect.bottom || y < 0)
		{
			dy = -dy;
		}
		SelectObject(hdc, brush);//������� ���� �����

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���������� ��������� ��� ���� "� ���������".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
