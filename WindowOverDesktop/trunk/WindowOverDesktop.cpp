// WindowOverDesktop.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "WindowOverDesktop.h"
#include <string>
#include <iostream>
#include <sstream>

#define MAX_LOADSTRING 100

int widthMax = 0L;
int heightMax = 0L;

// グローバル変数:
HINSTANCE hInst;								// 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING];					// タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING];			// メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
int outputWindowSize( HWND hWnd, std::string title );

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ここにコードを挿入してください。
	MSG msg;
	HACCEL hAccelTable;

	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINDOWOVERDESKTOP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	widthMax = GetSystemMetrics( SM_CXMAXTRACK );
	heightMax = GetSystemMetrics( SM_CYMAXTRACK );
	// アプリケーションの初期化を実行します:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWOVERDESKTOP));

	// メイン メッセージ ループ:
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
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
//  コメント:
//
//    この関数および使い方は、'RegisterClassEx' 関数が追加された
//    Windows 95 より前の Win32 システムと互換させる場合にのみ必要です。
//    アプリケーションが、関連付けられた
//    正しい形式の小さいアイコンを取得できるようにするには、
//    この関数を呼び出してください。
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWOVERDESKTOP));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WINDOWOVERDESKTOP);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します。
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // グローバル変数にインスタンス処理を格納します。

	HWND	hWnd = CreateWindow(szWindowClass,
								szTitle,
								WS_OVERLAPPEDWINDOW,
								0,
								0,
								widthMax + 100,
								heightMax + 100,
								NULL,
								NULL,
								hInstance,
								NULL);
	if (!hWnd)
	{
		return FALSE;
	}

	outputWindowSize( hWnd, "after CreateWindow" );

	MoveWindow( hWnd, 0, 0, widthMax + 100, heightMax + 100, TRUE );

	outputWindowSize( hWnd, "after MoveWindow" );

	ShowWindow(hWnd, nCmdShow);

	outputWindowSize( hWnd, "after ShowWindow" );

	UpdateWindow(hWnd);

	outputWindowSize( hWnd, "after UpdateWindow" );

	return TRUE;
}

//	デスクトップとウィンドウのサイズをメッセージボックスに出力する。
int outputWindowSize( HWND hWnd, std::string title )
{
	std::string	desktopInfo = "Desktop Size : width = ";
	std::ostringstream oss;
	oss << GetSystemMetrics( SM_CXFULLSCREEN );
	desktopInfo += oss.str();
	oss.str( "" );
	desktopInfo += ", height = ";
	oss << GetSystemMetrics( SM_CYFULLSCREEN );
	desktopInfo += oss.str();
	oss.str( "" );

	RECT rect;
	GetWindowRect( hWnd, &rect );
	std::string	windowInfo = "Window Size : width = ";
	oss << rect.right - rect.left;
	windowInfo += oss.str();
	oss.str( "" );
	windowInfo += ", height = ";
	oss << rect.bottom - rect.top;
	windowInfo += oss.str();
	oss.str( "" );

	std::string	message = desktopInfo;
	message += "\n";
	message += windowInfo;
	return	MessageBoxA( hWnd, message.c_str(), title.c_str(), MB_OK );
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:  メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND	- アプリケーション メニューの処理
//  WM_PAINT	- メイン ウィンドウの描画
//  WM_DESTROY	- 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 選択されたメニューの解析:
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
		break;

    case WM_GETMINMAXINFO:
		{
			outputWindowSize( hWnd, "WM_GETMINMAXINFO" );
			LPMINMAXINFO	lpmm = (LPMINMAXINFO)lParam;
			lpmm->ptMinTrackSize.x = widthMax + 100;
			lpmm->ptMinTrackSize.y = heightMax + 100;
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 描画コードをここに追加してください...
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

// バージョン情報ボックスのメッセージ ハンドラーです。
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
