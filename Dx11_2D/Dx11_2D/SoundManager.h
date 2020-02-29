#pragma once
#include "SingletonBase.h"

#include "FMOD/inc/fmod.hpp"

#pragma comment(lib, "FMOD/lib/fmodex_vc.lib")
using namespace FMOD;

#define SOUNDBUFFER 20			//사운드 갯수 설정
#define EXTRACHANNELBUFFER 5	//여분의 채널 버퍼
//총 사운드 버퍼는 사운드 갯수 + 여분 버퍼 : 버퍼가 작아서 씹히는 문제 해결
#define TOTALSOUNDBUFFER (SOUNDBUFFER + EXTRACHANNELBUFFER)

#define g_pSoundManager SoundManager::GetInstance()

class SoundManager : public SingletonBase<SoundManager>
{
	typedef map<string, Sound**>			 mapSound;
	typedef map<string, Sound**>::iterator	 iterSound;

	mapSound			m_mapSound;			// Sound list

	System*				m_pSystem;			//시스템 클래스 포인터
	Sound**				m_ppSound;			//사운드 클래스 포인터
	Channel**			m_ppChannel;		//채널 클래스 포인터
public:
	SoundManager();
	~SoundManager();

	void AddSound(string key, string fileName, bool bgm = false, bool loop = false);
	void ReleaseSound(string key);

	void Update();
	void Play(string key, float volume = 1.f);	// volume 범위 0.f ~ 1.f
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);
	bool IsPlaySound(string key);
	bool IsPauseSound(string key);
	void VolumeUp(string key);
	void VolumeDown(string key);
};