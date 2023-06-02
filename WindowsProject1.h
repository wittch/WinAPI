#pragma once
#include "resource.h"
#include <cmath>
#include <commdlg.h>
#include <iostream>

#define _USE_MATH_DEFINES 
#define MAX_LOADSTRING 100

#define ID_R1 1001
#define ID_R2 1002
#define ID_R3 1003

//전역변수
LOGFONT lf;
HWND hMainWnd;
HWND hToolDlg;
HWND hCanvasDlg;
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//BOOL	CALLBACK	DrawSettingDlg(HWND hDlg, UINT Message, WPARAM wParam, LPARAM lParam);
void DrawTempRectangle(HWND hWnd, int PosX, int PosY, int PrevPosX, int PrevPosY, LPARAM lParam);
long transformXtoY(long NumX, long Xlength, long Ylength);
void DrawTempEllipse(HWND hWnd, int PosX, int PosY, int PrevPosX, int PrevPosY, LPARAM lParam);
//HBRUSH SetCanvas(HWND hDlg, UINT Message, WPARAM wParam, LPARAM lParam);


class WindowsProject1
{
public:
	WindowsProject1();

	
	BOOL	CALLBACK	DrawSettingDlg(HWND hDlg, UINT Message, WPARAM wParam, LPARAM lParam);
	

protected:

	


private:
	
};