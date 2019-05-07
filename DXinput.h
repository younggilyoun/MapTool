#pragma once

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARDMAX			256

#include "dinput.h"
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib") 

enum MOUSEBUTTON_TYPE { MT_LEFT, MT_RIGHT, MT_MIDDLE, MT_MAX };

#include "MySingleton.h"

class DXinput : public MySingleton<DXinput>
{
	HINSTANCE				m_hInstance;
	HWND					m_hWnd;

	LPDIRECTINPUT8			m_pDI;
	LPDIRECTINPUTDEVICE8	m_pKeyBoardDevice;				// Ű���� ����̽�
	LPDIRECTINPUTDEVICE8	m_pMouseDevice;					// ���콺 ����̽�

	DIMOUSESTATE			m_MouseState;					// ���콺 ����
	POINT					m_MousePoint;
	BYTE					m_MouseKeyState[MT_MAX];
	BYTE					m_MouseOldKeyState[MT_MAX];
	BYTE					m_MouseNewKeyState[MT_MAX];

	BYTE					m_KeyBoardState[KEYBOARDMAX];	// Ű���� ����
	BYTE					m_OldKeyState[KEYBOARDMAX];
	BYTE					m_NewKeyState[KEYBOARDMAX];

public:
	bool IintDirectInput(HINSTANCE hInst, HWND hWnd);		// �ʱ�ȭ
	void UpdateDirectInput(void);							// ������Ʈ
	void ReleaseDirectInput(void);							// ����

	bool _InitKeyBorad(void);								// Ű���� ����̽� ����
	bool _InitMouse(void);									// ���콺 ����̽� ����

	void _ReadKeyBoradState(void);							// Ű���� ���� ���
	void _ReadMouseState(void);								// ���콺 ���� ���

	void _ReadKeyUpDownBitCheck(void);
	void _ReadMouseKeyUpDownBitCheck(void);

	// ����
	bool _DXinputRestore(void);

	
public:
	// �ܺ� Ű�� ó�� //
	bool _KeyDown(BYTE value);
	bool _KeyUp(BYTE value);
	void _GetMouseRelativePt(LONG* pX, LONG* pY, LONG* pZ);
	bool _LButtonDown(BYTE value);

	// Ű ó�� Ȯ�꼺 ���� //
	friend bool KeyDown(BYTE value);
	friend bool KeyUp( BYTE value );
	friend void GetMouseRelativePt(LONG* pX, LONG* pY, LONG* pZ);
	friend bool LButtonDown(BYTE value);

public:
	DXinput(void);
	virtual ~DXinput(void);
};
