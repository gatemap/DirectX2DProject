#pragma once
#include "GameNode.h"

enum class PlayMode
{
	Once,
	Loop,
	ReverseOnce,
	ReverseLoop
};

struct Frame
{
	Sprite* pSprite;
	float	fPlayTime;

	Frame(Sprite* sprite, float playtime) {	pSprite = sprite, fPlayTime = playtime;	}
};

class Clip
{
	vector<Frame*>		m_vecFrames;		//Frame vector
	PlayMode			m_ePlayMode;		//재생 모드
	bool				m_isPlaying;			//is Playing?
	int					m_nCurrFrame;		//Current Frame index number
	int					m_nStartFrame;		//Start Frame index number
	float				m_fElapsedTime;		//누적 시간
	float				m_fSpeed;			//animation 속도
	D3DXVECTOR2			m_vPos;				//위치

	void UpdateCurrSprite();
public:
	Clip(PlayMode mode = PlayMode::Loop, float speed = 1.0f);
	~Clip();

	void Update();
	void Render();

	void AddFrame(Sprite* sprite, float playTime);
	void SetPos(float x, float y) { m_vPos.x = x; m_vPos.y = y; }
	void SetScale(float x, float y);
	void SetConstantScale(float x, float y);
	void SetSpeed(float s) { m_fSpeed = s; }
	D3DXVECTOR2 GetSize();
	bool GetIsPlaying() { return m_isPlaying; }
	PlayMode GetPlayMode() { return m_ePlayMode; }

	void Play();
	void Play(int startFrame);
	void PlayReverse();
	void Stop();
	void Pause();
	void Resume();
};