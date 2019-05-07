//
// SWRender Basic FrameWork
//
// Camera.h : DX����
//
// ==================================================================//
// 2012.7.24 : ������ ��ȯ�� ���� Ŭ����
//

#pragma once

class Camera
{
public:
	//������������������������������������������������������������������������������������������������//
	// �⺻����
	D3DXVECTOR3				m_vEye;					// ī�޶� ��ġ
	D3DXVECTOR3				m_vLookAt;				// ī�޶� �ٶ󺸴� ����
	D3DXVECTOR3				m_vUp;					// ī�޶� UP����
													//  : UP���ʹ� ���� �̵� �� ȸ�� ���� ���Ҷ� ���

	D3DXVECTOR3				m_vOrgEye;				// ī�޶� ��ġ
	D3DXVECTOR3				m_vOrgLookAt;			// ī�޶� �ٶ󺸴� ����
	D3DXVECTOR3				m_vViewDir;				// ī�޶� ���� ����

	D3DXMATRIX				m_mView;				// �亯ȯ ���
	D3DXMATRIX				m_mInvView;				// ������� ���࿭( ���� ��� )
	D3DXMATRIX				m_mProj;				// �������� ��ȯ ���

	float					m_fFov;					// �þ߰�
	float					m_fAspect;				// ���μ��� ����
	float					m_fZnear;				// �þ� �ּ� �Ÿ�
	float					m_fZfar;				// �þ� �ִ� �Ÿ�

	//������������������������������������������������������������������������������������������������//
	// �ڵ�ȸ�� ����
	bool					m_bCameraAutoRotate;	// �ڵ�ȸ��
	D3DXMATRIX				m_mRotate;



	//������������������������������������������������������������������������������������������������//
	// ���� �� �Ҹ���
public:
	Camera(void);
	Camera(D3DXVECTOR3 _vEye, D3DXVECTOR3 _vLookAt, D3DXVECTOR3 _vUp,
			float _Fov, float _Aspect, float _near, float _far);
	virtual ~Camera(void);


	//������������������������������������������������������������������������������������������������//
	// �ܺ� ȣ�� �Լ�
	void UpdateCamera(float dTime);
	void ViewTransFrom(void);
	void ProjectionTransFrom(void);
};
