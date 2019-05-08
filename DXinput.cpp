#include "DXCommon.h"
#include "WinCommon.h"
#include "DXinput.h"


DXinput::DXinput(void)
:m_pDI(NULL), m_pKeyBoardDevice(NULL), m_pMouseDevice(NULL)
{

	memset(m_MouseKeyState, 0, MT_MAX);
	memset(m_MouseOldKeyState, 0, MT_MAX);
	memset(m_MouseNewKeyState, 0, MT_MAX);

	memset(m_KeyBoardState, 0, KEYBOARDMAX);
	memset(m_OldKeyState, 0, KEYBOARDMAX);
	memset(m_NewKeyState, 0, KEYBOARDMAX);
}

DXinput::~DXinput(void)
{
}

//
// ���̷�Ʈ ��ǲ �ʱ�ȭ
//
bool DXinput::IintDirectInput( HINSTANCE hInst, HWND hWnd )
{
	m_hInstance	= hInst;
	m_hWnd		= hWnd;

	// ������ ���� �ִٸ� ����
	ReleaseDirectInput();

	// dx input �������̽� ����
	if( FAILED(DirectInput8Create(m_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
									(void**)&m_pDI, NULL)))
	{
		MessageBox(m_hWnd, "Direct Input Create Failed", "error", MB_OK);
		return false;
	}

	// Ű���� ����̽� ����
	if( _InitKeyBorad() == false )
	{
		ReleaseDirectInput();
		return false;
	}

	// ���콺 ����̽� ����
	if( _InitMouse() == false )
	{
		ReleaseDirectInput();
		return false;
	}

	return true;
}


//
// ���̷�Ʈ ��ǲ ������Ʈ( ���� ������ �κ� )
//
void DXinput::UpdateDirectInput( void )
{
	_ReadKeyBoradState();
	_ReadMouseState();
}


void DXinput::_ReadKeyBoradState( void )
{
	if( m_pKeyBoardDevice == false )
		return;

	HRESULT res;

	m_pKeyBoardDevice->Poll();

	res = m_pKeyBoardDevice->GetDeviceState(sizeof(m_NewKeyState), m_NewKeyState);

	if(res != DI_OK)
	{
		_DXinputRestore();
		return;
	}

	_ReadKeyUpDownBitCheck();
}

void DXinput::_ReadKeyUpDownBitCheck( void )
{
	for( int i = 0; i < KEYBOARDMAX; ++i )
	{
		// Ű�� �������ٸ�(KeyDown)
		if( m_NewKeyState[i] & 0x80 )
		{
			// ó�� ������ Ű���
			if( !(m_OldKeyState[i] & 0x80) )
			{
				m_KeyBoardState[i] = 0x01;
			}
			// ��� �������� �ִٸ�
			else
			{
				if( m_OldKeyState[i] & 0x80 )
				{
					m_KeyBoardState[i] = 0x81;
				}
			}
		}

		// Ű�� �������� �ʾҴٸ�(KeyUp)
		else
		{
			// ������ Ű�� ���������� ���ٸ�
			if( !(m_OldKeyState[i] & 0x80) )
			{
				m_KeyBoardState[i] = 0x00;
			}
			// �����ٰ� �������ٸ�
			else
			{
				if( m_OldKeyState[i] & 0x80 )
				{
					m_KeyBoardState[i] = 0x80;
				}
			}
		}
	}

	memcpy(m_OldKeyState, m_NewKeyState, sizeof(BYTE)*KEYBOARDMAX);
}

void DXinput::_ReadMouseState( void )
{
	if( m_pMouseDevice == false ) return;

	HRESULT res;

	m_pMouseDevice->Poll();

	res = m_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_MouseState);

	if(res != DI_OK)
	{
		_DXinputRestore();
		return;
	}

	
	_ReadMouseKeyUpDownBitCheck();
}

void DXinput::_ReadMouseKeyUpDownBitCheck( void )
{
	for( int i = 0; i < MT_MAX; ++i )
	{
		m_MouseNewKeyState[i] = m_MouseState.rgbButtons[i];

		// ��ư ����
		if( m_MouseNewKeyState[i] & 0x80 )
		{
			// ó������
			if( !(m_MouseOldKeyState[i] & 0x80) )
			{
				m_MouseKeyState[i] = 0x01;
			}

			// ������ ����
			else
			{
				if( m_MouseOldKeyState[i] & 0x80 )
				{
					m_MouseKeyState[i] = 0x81;
				}
			}
		}

		// ��ư �ȴ���
		else
		{
			// ������ �ȴ���
			if( !(m_MouseOldKeyState[i] & 0x80) )
			{
				m_MouseKeyState[i] = 0x00;
			}

			// ������ �����ٰ� ������
			else
			{
				if( m_MouseOldKeyState[i] & 0x80 )
				{
					m_MouseKeyState[i] = 0x80;
				}
			}
		}
	}

	memcpy(m_MouseOldKeyState, m_MouseNewKeyState, sizeof(BYTE)*MT_MAX);
}




//
// �޸� ����
//
void DXinput::ReleaseDirectInput( void )
{
	if( m_pKeyBoardDevice )
		m_pKeyBoardDevice->Unacquire();

	if( m_pMouseDevice )
		m_pMouseDevice->Unacquire();

	SAFE_RELEASE(m_pMouseDevice);
	SAFE_RELEASE(m_pKeyBoardDevice);
	SAFE_RELEASE(m_pDI);
}

//
// Ű���� ����̽� ����
//
bool DXinput::_InitKeyBorad( void )
{
	// Ű���� ����̽� ����
	if( FAILED(m_pDI->CreateDevice(GUID_SysKeyboard, &m_pKeyBoardDevice, NULL)))
	{
		MessageBox(m_hWnd, "KeyBorad Dievce Create Failed", "error", MB_OK);
		return false;
	}

	// ������ ���� ����
	if( FAILED(m_pKeyBoardDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(m_hWnd, "KeyBorad Format Failed", "error", MB_OK);
		return false;
	}

	// ���·��� ����
	if( FAILED(m_pKeyBoardDevice->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND )))
	{
		MessageBox(m_hWnd, "KeyBorad Level Failed", "error", MB_OK);
		return false;
	}

	// Ű���� 
	m_pKeyBoardDevice->Acquire();

	return true;
}


//
// ���콺 ����̽� ����
//
bool DXinput::_InitMouse( void )
{
	// ���콺 ����̽� ����
	if( FAILED(m_pDI->CreateDevice(GUID_SysMouse, &m_pMouseDevice, NULL)))
	{
		MessageBox(m_hWnd, "Mouse Dievce Create Failed", "error", MB_OK);
		return false;
	}

	// ������ ���� ����
	if( FAILED(m_pMouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		MessageBox(m_hWnd, "Mouse Format Failed", "error", MB_OK);
		return false;
	}

	// ���·��� ����
	if( FAILED(m_pMouseDevice->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND )))
	{
		MessageBox(m_hWnd, "Mouse Level Failed", "error", MB_OK);
		return false;
	}

	// Ű���� 
	m_pMouseDevice->Acquire();

	return true;
}

bool DXinput::_DXinputRestore( void )
{
	if(m_pKeyBoardDevice)
	{
		HRESULT res = m_pKeyBoardDevice->Acquire();

		while(res == DIERR_INPUTLOST)
			res = m_pKeyBoardDevice->Acquire();
	}

	if(m_pMouseDevice)
	{
		HRESULT res = m_pMouseDevice->Acquire();

		while(res == DIERR_INPUTLOST)
			res = m_pMouseDevice->Acquire();
	}

	return true;
}

// �ܺ� Ű�� ó�� //
bool DXinput::_KeyDown( BYTE value )
{
	if( m_KeyBoardState[value] == 0x81 )
		return true;

	return false;
}

bool DXinput::_KeyUp( BYTE value )
{
	if( m_KeyBoardState[value] == 0x80 )
	{
		m_KeyBoardState[value] = 0x00;
		return true;
	}

	return false;
}


void DXinput::_GetMouseRelativePt( LONG* pX, LONG* pY, LONG* pZ )
{
	if(pX) *pX = m_MouseState.lX;
	if(pY) *pY = m_MouseState.lY;
	if(pZ) *pZ = m_MouseState.lZ;
}

bool DXinput::_LButtonDown(BYTE value)
{
	if( m_MouseKeyState[value] & 0x01 )
		return true;

	return false;
}

bool LButtonDown(BYTE value)
{
	return MYINPUT->_LButtonDown(value);
}


// Ű ó�� Ȯ�꼺 ���� //
bool KeyDown(BYTE value)
{
	if( MYINPUT->_KeyDown(value) )
		return true;

	return false;
}

bool KeyUp( BYTE value )
{
	if( MYINPUT->_KeyUp(value) )
		return true;

	return false;
}

 void GetMouseRelativePt( LONG* pX, LONG* pY, LONG* pZ )
 {
	MYINPUT->_GetMouseRelativePt(pX, pY, pZ);
 }