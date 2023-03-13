// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#define _USE_MATH_DEFINES 
#include "framework.h"
#include "WindowsProject1.h"
#include <cmath>
#define MAX_LOADSTRING 100

#define ID_R1 101
#define ID_R2 102
#define ID_R3 103
#define ID_R4 1014
#define ID_R5 1015
#define ID_R6 1016

// 전역 변수:
int GRAPH = 0;
int COLOR = 0;

HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));
    //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDR_MENU1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}




//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    static HWND r1,r2,r3,r4,r5,r6;
    static BOOL ELLIPSE = FALSE;
    HBRUSH MyBrush = nullptr;
    HBRUSH OldBrush = nullptr;
    switch (message)
    {
    case WM_COMMAND:
        {
            /*if (HIWORD(lParam) == BN_CLICKED)
            {
                switch (LOWORD(wParam))
                {
                case ID_R1:
                    GRAPH = 0;
                    break;
                case ID_R2:
                    GRAPH = 1;
                    break;
                case ID_R3:
                    GRAPH = 2;
                    break;
                case ID_R4:
                    COLOR = 0;
                    break;
                case ID_R5:
                    COLOR = 1;
                    break;
                case ID_R6:
                    COLOR = 2;
                    break;
                }
                InvalidateRect(hWnd, NULL, TRUE);
            }*/
            //else {
                int wmId = LOWORD(wParam);
                // 메뉴 선택을 구문 분석합니다:
                switch (wmId)
                {

                case IDM_ABOUT:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case IDM_EXIT:
                    DestroyWindow(hWnd);
                    break;
                case ID_R1:
                    GRAPH = 0;
                    break;
                case ID_R2:
                    GRAPH = 1;
                    break;
                case ID_R3:
                    GRAPH = 2;
                    break;
                case ID_R4:
                    COLOR = 0;
                    break;
                case ID_R5:
                    COLOR = 1;
                    break;
                case ID_R6:
                    COLOR = 2;
                    break;

                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
                }
                InvalidateRect(hWnd, NULL, TRUE);
            //}
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            switch (COLOR)
            {
            case 0:
                MyBrush = CreateSolidBrush(RGB(0, 0, 0));
                break;
            case 1:
                MyBrush = CreateSolidBrush(RGB(255, 0, 0));
                break;
            case 2:
                MyBrush = CreateSolidBrush(RGB(0, 0, 255));
                break;
            }
            OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
            switch (GRAPH)
            {
            case 0:
                Rectangle(hdc, 10, 200, 200, 300);
                break;
            case 1:
                Ellipse(hdc, 10, 200, 200, 300);
                break;
            case 2:
                MoveToEx(hdc, 10, 200, NULL);
                LineTo(hdc, 200, 300);
                break;
            }
            SelectObject(hdc, OldBrush);
            DeleteObject(MyBrush);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_CREATE:
        CreateWindow(L"button", L"Graph", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 5, 120, 110, hWnd, (HMENU)0, hInst, NULL);
        CreateWindow(L"button", L"Color", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 145, 5, 120, 110, hWnd, (HMENU)0, hInst, NULL);
        r1 = CreateWindow(L"Button", L"Rectangle", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 10, 20, 100, 30, hWnd, (HMENU)ID_R1, hInst, NULL);
        r2 = CreateWindow(L"Button", L"Ellipse", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON , 10, 50, 100, 30, hWnd, (HMENU)ID_R2, hInst, NULL);
        r3 = CreateWindow(L"Button", L"Line", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 80, 100, 30, hWnd, (HMENU)ID_R3, hInst, NULL);


        r4 = CreateWindow(L"Button", L"Black", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150,20, 100, 30, hWnd, (HMENU)ID_R4, hInst, NULL);
        r5 = CreateWindow(L"Button", L"Red", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 50, 100, 30, hWnd, (HMENU)ID_R5, hInst, NULL);
        r6 = CreateWindow(L"Button", L"Blue", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 80, 100, 30, hWnd, (HMENU)ID_R6, hInst, NULL);
        CheckRadioButton(hWnd, ID_R1, ID_R3, ID_R1);
        CheckRadioButton(hWnd, ID_R4, ID_R6, ID_R4);
        break;
 
    case WM_SIZE://윈도우의 크기가 변경될 때 호출
        InvalidateRect(hWnd, NULL, TRUE);

        //같은 방법으로 lParam 이용
        /*rt.right = LOWORD(lParam);
        rt.bottom = HIWORD(lParam);
        InvalidateRect(hWnd, NULL, TRUE);
        */
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
