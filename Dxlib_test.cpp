#include "DxLib.h"

//ウィンドウハンドル
HWND Dx_hwnd, Controle_hwnd;

//Dxライブラリ用のウィンドウプロシージャアドレス
WNDPROC dxWndProc;

//自作ウィンドウプロシージャ
LRESULT CALLBACK DialogFunc_control(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

unsigned int Cr = GetColor(255, 255, 255);    // 白色の値を取得

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // ウィンドウモードに設定

	Dx_hwnd = GetMainWindowHandle(); //Dxライブラリで生成されるウィンドウハンドルを取得

	//createDialog時にDxlibのウィンドウハンドルを指定する
	//登録できる(作れる？)ダイアログは1個だけらしい
	Controle_hwnd = CreateDialog(hInstance, "CONTROL_DIALOG", Dx_hwnd, (DLGPROC)DialogFunc_control);

	//先にダイアログを表示、後にdxlibにしてdx側をアクティブ化させる.(描画されないので)
	ShowWindow(Controle_hwnd, SW_SHOW);
	UpdateWindow(Controle_hwnd);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	while (!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen()) {
		DrawPixel(320, 240, GetColor(255, 255, 255));	// 点を打つ
		DrawLine(0, 0, 640, 480, Cr);    // 線を描画
		DrawBox(100, 100, 300, 300, Cr, TRUE);
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}

LRESULT CALLBACK DialogFunc_control(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wp)) {
		case IDOK:
			MessageBoxA(NULL, "色を変えます", "メッセージ発生", MB_OK);
			Cr= GetColor(0, 255, 255);
			return 0;
		}
	}
	return 0;
}