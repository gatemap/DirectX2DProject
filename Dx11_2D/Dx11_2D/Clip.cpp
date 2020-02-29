#include "stdafx.h"
#include "Clip.h"


Clip::Clip(PlayMode mode, float speed)
	: m_ePlayMode(mode), m_isPlaying(false), m_nCurrFrame(0)
	, m_nStartFrame(0), m_fElapsedTime(0)
	, m_fSpeed(speed), m_vPos(INITX, INITY)
{
}

Clip::~Clip()
{
	for (Frame* frame : m_vecFrames)
	{
		SAFE_DELETE(frame->pSprite);
		SAFE_DELETE(frame);
	}
	m_vecFrames.clear();
}

void Clip::Update()
{
	if (m_isPlaying == false)
	{
		UpdateCurrSprite();
		return;
	}

	// 지정 된 속도에 따른 플레이 타임 값 계산
	float playTime = m_vecFrames[m_nCurrFrame]->fPlayTime * (1 / m_fSpeed);
	m_fElapsedTime += g_pTimeManager->GetDeltaTime();

	// 프레임 변경 없음
	if (playTime > m_fElapsedTime)
	{
		// 지정 위치 변경 및 적용
		UpdateCurrSprite();
		return;
	}

	// 다음 프레임으로 현재 프레임 변경
	switch (m_ePlayMode)
	{
	case PlayMode::Once:
		m_nCurrFrame++;
		if (m_nCurrFrame >= m_vecFrames.size() - 1)
			Stop();
		break;
	case PlayMode::Loop:
		m_nCurrFrame++;
		if (m_nCurrFrame >= m_vecFrames.size())
			m_nCurrFrame = m_nStartFrame;
		break;
	case PlayMode::ReverseOnce:
		m_nCurrFrame--;
		if (m_nCurrFrame <= m_nStartFrame)
			Stop();
		break;
	case PlayMode::ReverseLoop:
		m_nCurrFrame--;
		if (m_nCurrFrame < m_nStartFrame)
			m_nCurrFrame = m_vecFrames.size() - 1;
		break;
	}

	m_fElapsedTime = 0.0f;

	// 지정 위치 변경 및 적용
	UpdateCurrSprite();
}

void Clip::Render()
{
	m_vecFrames[m_nCurrFrame]->pSprite->Render();
}

void Clip::UpdateCurrSprite()
{
	m_vecFrames[m_nCurrFrame]->pSprite->SetPos(m_vPos.x, m_vPos.y);
	m_vecFrames[m_nCurrFrame]->pSprite->Update();
}

void Clip::AddFrame(Sprite* sprite, float playTime)
{
	m_vecFrames.push_back(new Frame(sprite, playTime));
}

void Clip::SetScale(float x, float y)
{
	for (Frame* frame : m_vecFrames)
		frame->pSprite->SetScale(x, y);
}

void Clip::SetConstantScale(float x, float y)
{
	for (Frame* frame : m_vecFrames)
		frame->pSprite->SetConstantScale(x, y);
}

D3DXVECTOR2 Clip::GetSize()
{
	return m_vecFrames[m_nCurrFrame]->pSprite->GetSize();
}

void Clip::Play()
{
	m_isPlaying = true;
	if (m_ePlayMode == PlayMode::Once || m_ePlayMode == PlayMode::Loop)
		m_nCurrFrame = m_nStartFrame;
	else
		m_nCurrFrame = m_vecFrames.size() - 1;
}

void Clip::Play(int startFrame)
{
	m_isPlaying = true;
	m_nCurrFrame = m_nStartFrame = startFrame;
}

void Clip::PlayReverse()
{
	m_isPlaying = true;

	switch (m_ePlayMode)
	{
	case PlayMode::Once:
		m_ePlayMode = PlayMode::ReverseOnce;
		break;
	case PlayMode::Loop:
		m_ePlayMode = PlayMode::ReverseLoop;
		break;
	case PlayMode::ReverseOnce:
		m_ePlayMode = PlayMode::Once;
		break;
	case PlayMode::ReverseLoop:
		m_ePlayMode = PlayMode::Loop;
		break;
	}
}

void Clip::Stop()
{
	m_isPlaying = false;
}

void Clip::Pause()
{
	m_isPlaying = false;
}

void Clip::Resume()
{
	m_isPlaying = true;
}
