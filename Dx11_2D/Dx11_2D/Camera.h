#pragma once

#define g_pCamera Camera::GetInstance()

class Camera : public SingletonBase<Camera>
{
	float		m_fDistance;		// ī�޶�� Ÿ�� ������ �Ÿ�
	float		m_fRotX;
	float		m_fRotY;

	POINT		m_ptPrevMouse;
	bool		m_isRButtonDown;

	D3DXVECTOR3		m_vEye;				// ī�޶��� ��ġ
	D3DXVECTOR3		m_vLookAt;			// ī�޶��� Ÿ�� ��ġ
	D3DXVECTOR3		m_vUp;				// ������ �� ����

	ID3D11Buffer*	m_pVPBuffer;		// ��x�������� ��Ʈ���� ����
	tagVPMatrix*	m_pVPMatrix;		// ��x�������� ����
	
public:
	Camera();
	~Camera();

	void Init();
	void Update(const D3DXVECTOR3* pTarget = NULL);

	const tagVPMatrix *GetViewProj() { return m_pVPMatrix; }

	const D3DXVECTOR3 GetDir();
	const D3DXVECTOR4 GetPos();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};