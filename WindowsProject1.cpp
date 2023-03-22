// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject1.h"
HWND c1, c2, c3;
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

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   hMainWnd = hWnd;

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    
    static int MousePosX = 0;
    static int MousePosY = 0;
    
    static int OldMousePosX = 0;
    static int OldMousePosY = 0;



    static int PenWidth = 1;
    static BOOL bDraw = FALSE;
    static int bShape = 0;
    static BOOL bRECTANGLE = FALSE;
    static BOOL bELLIPSE = FALSE;
    static COLORREF PenColor = RGB(0, 0, 0);
    
    switch (message)
    {
    case WM_COMMAND:
    {

        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case ID_R1:
            bShape = 0;
            break;
        case ID_R2:
            bShape = 1;
            break;
        case ID_R3:
            bShape = 2;
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
        CreateWindow(L"button", L"Graph", WS_CHILD | WS_VISIBLE | BS_GROUPBOX , 5, 5, 190, 110, hWnd, (HMENU)0, hInst, NULL);

        c1 = CreateWindow(L"button", L"Line", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 20, 20, 160, 25, hWnd, (HMENU)ID_R1, hInst, NULL);
        c2 = CreateWindow(L"button", L"Rectangle", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON  , 20, 50, 160, 25, hWnd, (HMENU)ID_R2, hInst, NULL);
        c3 = CreateWindow(L"button", L"Ellipse", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON  , 20, 80, 160, 25, hWnd, (HMENU)ID_R3, hInst, NULL);

        CheckRadioButton(hWnd, ID_R1, ID_R3, ID_R1);

        break;
    case WM_LBUTTONDOWN:
        bDraw = TRUE;
        MousePosX = LOWORD(lParam);
        MousePosY = HIWORD(lParam);
        OldMousePosX = MousePosX;
        OldMousePosY = MousePosY;
        break;
    case WM_LBUTTONUP:
        bDraw = FALSE;
        
        hdc = GetDC(hWnd);
        switch (bShape)
        {
        case 0:
            break;
        case 1:
            DrawTempRectangle(hWnd, MousePosX, MousePosY, OldMousePosX, OldMousePosY, lParam);

            ReleaseDC(hWnd, hdc);
            hdc = GetDC(hWnd);

            Rectangle(hdc, OldMousePosX, OldMousePosY, MousePosX, MousePosY);
            break;
        case 2:

            DrawTempRectangle(hWnd, MousePosX, MousePosY, OldMousePosX, OldMousePosY, lParam);

            ReleaseDC(hWnd, hdc);
            hdc = GetDC(hWnd);

            Ellipse(hdc, OldMousePosX, OldMousePosY, MousePosX, MousePosY);
        break;
        }
            
        
        ReleaseDC(hWnd, hdc);
        

        break;
    case WM_MOUSEMOVE:
        if (bDraw)
        {
            
            HPEN CurPen, OldPen;

            hdc = GetDC(hWnd);

            if (!bShape) {
                CurPen = CreatePen(PS_SOLID, PenWidth, PenColor);
                OldPen = (HPEN)SelectObject(hdc, CurPen);

                MoveToEx(hdc, MousePosX, MousePosY, NULL);
                MousePosX = LOWORD(lParam);
                MousePosY = HIWORD(lParam);
                LineTo(hdc, MousePosX, MousePosY);


                SelectObject(hdc, OldPen);
                DeleteObject(CurPen);
            }
            else
            {
                ///** 그려진 선을 지우는 코드 */
                DrawTempRectangle(hWnd, MousePosX, MousePosY, OldMousePosX, OldMousePosY, lParam);
                
                OldMousePosX = LOWORD(lParam);
                OldMousePosY = HIWORD(lParam);

                ////** 선 그리기 코드 */
                DrawTempRectangle(hWnd,  MousePosX, MousePosY, OldMousePosX, OldMousePosY, lParam);

            }

            ReleaseDC(hWnd, hdc);
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

BOOL CALLBACK DrawSettingDlg(HWND hDlg, UINT Message, WPARAM wParam, LPARAM lParam)
{

    HDC hdc;

    switch (Message)
    {
    case WM_INITDIALOG:
        hdc = GetDC(hDlg);
        SetBkColor(hdc, RGB(0, 0, 0));
        ReleaseDC(hDlg, hdc);
        return TRUE;
    case WM_COMMAND:
        switch (wParam)
        {
        case ID_CHANGE:
            InvalidateRect(hMainWnd, NULL, TRUE);
            return TRUE;
        case ID_CLOSE:
            DestroyWindow(hDlg);
            hDlg = NULL;
            return TRUE;
        }
    break;
    }
    return FALSE;
}




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
    if (!InitInstance(hInstance, nCmdShow))
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

    return (int)msg.wParam;
}

void DrawTempRectangle(HWND hWnd, int PosX, int PosY, int PrevPosX, int PrevPosY, LPARAM lParam)
{

    
    HDC hdc;
    hdc = GetDC(hWnd);

    SetROP2(hdc, R2_NOT);
    //click 한 점으로 부터 마지막으로 있던 Cursor위치의 가로축
    MoveToEx(hdc, PosX, PosY, NULL);
    LineTo(hdc, PrevPosX, PosY);

    //click 한 점으로 부터 마지막으로 있던 Cursor위치의 세로축
    MoveToEx(hdc, PosX, PosY, NULL);
    LineTo(hdc, PosX, PrevPosY);


    //마지막 Cursor위치로부터 Click한 점까지의 가로축
    MoveToEx(hdc, PrevPosX, PrevPosY, NULL);
    LineTo(hdc, PrevPosX, PosY);

    //마지막 Cursor위치로부터 Click한 점까지의 세로축
    MoveToEx(hdc, PrevPosX, PrevPosY, NULL);
    LineTo(hdc, PosX, PrevPosY);

    PrevPosX = LOWORD(lParam);
    PrevPosY = HIWORD(lParam);

    ReleaseDC(hWnd, hdc);
}
