// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#define _USE_MATH_DEFINES 
#include "framework.h"
#include "WindowsProject1.h"
#include <cmath>
#include "resource.h"
#include <commdlg.h>
#include <iostream>

#define MAX_LOADSTRING 100

LOGFONT lf;
WCHAR str[] = L"폰트 대화상자 Test 1234";
// 전역 변수:
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
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
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

    static int MousePosX = 0;
    static int MousePosY = 0;
    static int PenWidth = 1;
    static BOOL bDraw = FALSE;
    static COLORREF PenColor = RGB(0, 0, 0);

    switch (message)
    {
    case WM_COMMAND:
    {

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

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;

        hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_CREATE:
        break;
    case WM_LBUTTONDOWN:
        bDraw = TRUE;
        MousePosX = LOWORD(lParam);
        MousePosY = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        bDraw = FALSE;
        MousePosX = 0;
        MousePosY = 0;
        break;
    case WM_MOUSEMOVE:
        if (bDraw)
        {
            HPEN CurPen, OldPen;

            hdc = GetDC(hWnd);

            CurPen = CreatePen(PS_SOLID, PenWidth, PenColor);
            OldPen = (HPEN)SelectObject(hdc, CurPen);

            MoveToEx(hdc, MousePosX, MousePosY, NULL);
            MousePosX = LOWORD(lParam);
            MousePosY = HIWORD(lParam);
            LineTo(hdc, MousePosX, MousePosY);

            SelectObject(hdc, OldPen);
            DeleteObject(CurPen);

            ReleaseDC(hWnd, hdc);
        }
        break;

    case WM_RBUTTONDOWN:
    {
        // 캡쳐를 하기 위해서 화면에서 현재 프로그램을 감춘다.
        //ShowWindow(hWnd, SW_HIDE);

        // 스크린 전체를 캡쳐하기 위해서 CWindowDC 형식으로 DC를 얻는다.
        // GetDC의 파라메터에 특정 윈도우 핸들을 넣지 않고 NULL을 넣으면
        // CWindowDC 형식으로 DC를 얻게 된다.
        HDC h_screen_dc = ::GetDC(NULL);
        // 현재 스크린의 해상도를 얻는다.
        int width = ::GetDeviceCaps(h_screen_dc, HORZRES);
        int height = ::GetDeviceCaps(h_screen_dc, VERTRES);



        // DIB의 형식을 정의한다.
        BITMAPINFO dib_define;
        dib_define.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        dib_define.bmiHeader.biWidth = width;
        dib_define.bmiHeader.biHeight = height;
        dib_define.bmiHeader.biPlanes = 1;
        dib_define.bmiHeader.biBitCount = 24;
        dib_define.bmiHeader.biCompression = BI_RGB;
        dib_define.bmiHeader.biSizeImage = (((width * 24 + 31) & ~31) >> 3) * height;
        dib_define.bmiHeader.biXPelsPerMeter = 0;
        dib_define.bmiHeader.biYPelsPerMeter = 0;
        dib_define.bmiHeader.biClrImportant = 0;
        dib_define.bmiHeader.biClrUsed = 0;

        // DIB의 내부 이미지 비트 패턴을 참조할 포인터 변수
        BYTE* p_image_data = NULL;

        // dib_define에 정의된 내용으로 DIB를 생성한다.
        HBITMAP h_bitmap = ::CreateDIBSection(h_screen_dc, &dib_define, DIB_RGB_COLORS, (void**)&p_image_data, 0, 0);

        // 이미지를 추출하기 위해서 가상 DC를 생성한다. 메인 DC에서는 직접적으로 비트맵에 접근하여
        // 이미지 패턴을 얻을 수 없기 때문이다.
        HDC h_memory_dc = ::CreateCompatibleDC(h_screen_dc);

        // 가상 DC에 이미지를 추출할 비트맵을 연결한다.
        HBITMAP h_old_bitmap = (HBITMAP)::SelectObject(h_memory_dc, h_bitmap);

        // 현재 스크린 화면을 캡쳐한다.
        ::BitBlt(h_memory_dc, 0, 0, width, height, h_screen_dc, 0, 0, SRCCOPY);
        // 본래의 비트맵으로 복구한다.
        ::SelectObject(h_memory_dc, h_old_bitmap);

        // 가상 DC를 제거한다.
        DeleteDC(h_memory_dc);

        // DIB 파일의 헤더 내용을 구성한다.
        BITMAPFILEHEADER dib_format_layout;
        ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
        dib_format_layout.bfType = *(WORD*)"BM";
        dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dib_define.bmiHeader.biSizeImage;
        dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

        // DIB 파일을 생성한다.
        FILE* p_file;
        fopen_s(&p_file, "image.bmp", "wb");
        if (p_file != NULL) {
            fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
            fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), p_file);
            fwrite(p_image_data, 1, dib_define.bmiHeader.biSizeImage, p_file);
            fclose(p_file);
        }

        // 사용했던 비트맵과 DC 를 해제한다.
        if (NULL != h_bitmap) DeleteObject(h_bitmap);
        if (NULL != h_screen_dc) ::ReleaseDC(NULL, h_screen_dc);

        // 캡쳐를 하기 위해서 감춘 화면을 다시 보여준다.
        //ShowWindow(hWnd, SW_SHOW);

    }

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
