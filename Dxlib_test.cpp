#include "DxLib.h"

//�E�B���h�E�n���h��
HWND Dx_hwnd, Controle_hwnd;

//Dx���C�u�����p�̃E�B���h�E�v���V�[�W���A�h���X
WNDPROC dxWndProc;

//����E�B���h�E�v���V�[�W��
LRESULT CALLBACK DialogFunc_control(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

unsigned int Cr = GetColor(255, 255, 255);    // ���F�̒l���擾

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�

	Dx_hwnd = GetMainWindowHandle(); //Dx���C�u�����Ő��������E�B���h�E�n���h�����擾

	//createDialog����Dxlib�̃E�B���h�E�n���h�����w�肷��
	//�o�^�ł���(����H)�_�C�A���O��1�����炵��
	Controle_hwnd = CreateDialog(hInstance, "CONTROL_DIALOG", Dx_hwnd, (DLGPROC)DialogFunc_control);

	//��Ƀ_�C�A���O��\���A���dxlib�ɂ���dx�����A�N�e�B�u��������.(�`�悳��Ȃ��̂�)
	ShowWindow(Controle_hwnd, SW_SHOW);
	UpdateWindow(Controle_hwnd);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	while (!ProcessMessage() && !ScreenFlip() && !ClearDrawScreen()) {
		DrawPixel(320, 240, GetColor(255, 255, 255));	// �_��ł�
		DrawLine(0, 0, 640, 480, Cr);    // ����`��
		DrawBox(100, 100, 300, 300, Cr, TRUE);
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}

LRESULT CALLBACK DialogFunc_control(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wp)) {
		case IDOK:
			MessageBoxA(NULL, "�F��ς��܂�", "���b�Z�[�W����", MB_OK);
			Cr= GetColor(0, 255, 255);
			return 0;
		}
	}
	return 0;
}