#pragma once

#define g_pCamera Camera::GetInstance()

class Camera : public SingletonBase<Camera>
{
	float		m_fDistance;		// 카메라와 타겟 사이의 거리
	float		m_fRotX;
	float		m_fRotY;

	POINT		m_ptPrevMouse;
	bool		m_isRButtonDown;

	D3DXVECTOR3		m_vEye;				// 카메라의 위치
	D3DXVECTOR3		m_vLookAt;			// 카메라의 타겟 위치
	D3DXVECTOR3		m_vUp;				// 임의의 업 벡터

	ID3D11Buffer*	m_pVPBuffer;		// 뷰x프로젝션 매트릭스 버퍼
	tagVPMatrix*	m_pVPMatrix;		// 뷰x프로젝션 구조
	
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