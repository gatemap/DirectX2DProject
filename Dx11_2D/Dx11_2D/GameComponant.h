#pragma once

// ���� �Լ�
inline bool AABB(float x1, float y1, int sx1, int sy1,			//x, y = ����, sx, sy = scale��
	float x2, float y2, int sx2, int sy2)
{
	float L1 = x1 - sx1 * 0.5f;
	float R1 = x1 + sx1 * 0.5f;
	float T1 = y1 + sy1 * 0.5f;
	float B1 = y1 - sy1 * 0.5f;

	float L2 = x2 - sx2 * 0.5f;
	float R2 = x2 + sx2 * 0.5f;
	float T2 = y2 + sy2 * 0.5f;
	float B2 = y2 - sy2 * 0.5f;

	if (((L2 > L1 && L2 < R1) || (R2 > L1 && R2 < R1)) &&
		((B2 > B1 && B2 < T1) || (T2 > B1 && T2 < T1)))
		return true;

	return false;
}

// �� �浹
inline bool CircleCollision(float x1, float y1, int sx1, int sy1,
	float x2, float y2, int sx2, int sy2)
{
	float disX = x1 - x2;
	float disY = y1 - y2;
	float distance = sqrtf(disX * disX + disY * disY);

	int radius1 = (sx1 + sy1) * 0.25f;
	int radius2 = (sx2 + sy2) * 0.25f;

	if (distance < radius1 + radius2)
		return true;

	return false;
}

inline bool CheckOBB2D(D3DXVECTOR2 PivotDir, D3DXVECTOR2 PivotCenter, D3DXVECTOR2 Center,
	float L1, D3DXVECTOR2* vertex)
{
	float L0, L2;
	// A_03 ���Ϳ� ���� �� �簢���� ���� ���� ���� ������ �Ÿ�
	L0 = fabs(D3DXVec2Dot(&PivotCenter, &PivotDir) - D3DXVec2Dot(&Center, &PivotDir));

	// A_03 ���Ϳ� ���� "1��" ������� ���� ���� ũ�� == L1

	// A_03 ���Ϳ� ���� "2��" ������� ���� ���� ũ��
	float left = D3D11_FLOAT32_MAX;

	for (int i = 0; i < 4; i++) // 4���� ������ �� ���� ���� ���� ���� ���� ���� ã�´�.
	{
		float l = D3DXVec2Dot(&vertex[i], &PivotDir);

		if (l < left)
			left = l;
	}

	L2 = fabs(left - D3DXVec2Dot(&Center, &PivotDir));

	if (L0 > L1 + L2)
		return false;

	return true;
}

//	����1, ���� ��Ʈ����1, ����2, ���� ��Ʈ����2
inline bool OBB2D(D3DXMATRIX m1, D3DXMATRIX m2)
{
	D3DXVECTOR2 vertexA[4];	// ������ �������� ��� ���� 1 �������� ������ ����
	vertexA[0] = D3DXVECTOR2(-0.5f, -0.5f);
	vertexA[1] = D3DXVECTOR2(-0.5f, 0.5f);
	vertexA[2] = D3DXVECTOR2(0.5f, 0.5f);
	vertexA[3] = D3DXVECTOR2(0.5f, -0.5f);

	for (int i = 0; i < 4; i++) // ��Ʈ������ ���ؼ� ũ��, ����(ȸ����), ��ġ �� ����
	{
		D3DXVec2TransformCoord(&vertexA[i], &vertexA[i], &m1);
	}

	D3DXVECTOR2 vertexB[4];
	vertexB[0] = D3DXVECTOR2(-0.5f, -0.5f);
	vertexB[1] = D3DXVECTOR2(-0.5f, 0.5f);
	vertexB[2] = D3DXVECTOR2(0.5f, 0.5f);
	vertexB[3] = D3DXVECTOR2(0.5f, -0.5f);

	for (int i = 0; i < 4; i++)
	{
		D3DXVec2TransformCoord(&vertexB[i], &vertexB[i], &m2);
	}

	// ������� ����
	D3DXVECTOR2 A_Center((vertexA[0] + vertexA[2]) * 0.5f);
	D3DXVECTOR2 B_Center((vertexB[0] + vertexB[2]) * 0.5f);

	// �簢���� ���� �� �࿡ ���� ���� ���� ���
	D3DXVECTOR2 A_03, A_01, B_03, B_01;
	A_03 = vertexA[3] - vertexA[0];
	A_01 = vertexA[1] - vertexA[0];
	B_03 = vertexB[3] - vertexB[0];
	B_01 = vertexB[1] - vertexB[0];

	// �簢���� 2���� ���� ���� ����
	float A_03_Half = D3DXVec2Length(&A_03) * 0.5f;
	float A_01_Half = D3DXVec2Length(&A_01) * 0.5f;
	float B_03_Half = D3DXVec2Length(&B_03) * 0.5f;
	float B_01_Half = D3DXVec2Length(&B_01) * 0.5f;

	// �� �������� ���� ����
	D3DXVec2Normalize(&A_03, &A_03);
	D3DXVec2Normalize(&A_01, &A_01);
	D3DXVec2Normalize(&B_03, &B_03);
	D3DXVec2Normalize(&B_01, &B_01);

	if (!CheckOBB2D(A_03, A_Center, B_Center, A_03_Half, vertexB))
		return false;

	if (!CheckOBB2D(A_01, A_Center, B_Center, A_01_Half, vertexB))
		return false;

	if (!CheckOBB2D(B_03, B_Center, A_Center, B_03_Half, vertexA))
		return false;

	if (!CheckOBB2D(B_01, B_Center, A_Center, B_01_Half, vertexA))
		return false;

	return true;
}

inline bool PtInObject(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT pt)
{
	RECT rt;
	rt.left = pos.x - size.x * 0.5f;
	rt.right = pos.x + size.x * 0.5f;
	rt.top = pos.y + size.y * 0.5f;
	rt.bottom = pos.y - size.y * 0.5f;

	if (pt.x >= rt.left && pt.x <= rt.right &&
		pt.y >= rt.bottom && pt.y <= rt.top)
		return true;

	return false;
}

// ���� ����
inline void LinearInterpolation(OUT float& x, OUT float& y,
	IN float fromX, IN float fromY, IN float toX, IN float toY,
	IN float t)
{
	x = fromX * (1.0f - t) + toX * t;
	y = fromY * (1.0f - t) + toY * t;
}

#define DEG_TO_RAD 0.01745329f
#define EPSILON 0.0001f