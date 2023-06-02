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

//��������
LOGFONT lf;
HWND hMainWnd;
HWND hToolDlg;
HWND hCanvasDlg;
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

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