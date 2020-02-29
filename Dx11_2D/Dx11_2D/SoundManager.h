#pragma once
#include "SingletonBase.h"

#include "FMOD/inc/fmod.hpp"

#pragma comment(lib, "FMOD/lib/fmodex_vc.lib")
using namespace FMOD;

#define SOUNDBUFFER 20			//���� ���� ����
#define EXTRACHANNELBUFFER 5	//������ ä�� ����
//�� ���� ���۴� ���� ���� + ���� ���� : ���۰� �۾Ƽ� ������ ���� �ذ�
#define TOTALSOUNDBUFFER (SOUNDBUFFER + EXTRACHANNELBUFFER)

#define g_pSoundManager SoundManager::GetInstance()

class SoundManager : public SingletonBase<SoundManager>
{
	typedef map<string, Sound**>			 mapSound;
	typedef map<string, Sound**>::iterator	 iterSound;

	mapSound			m_mapSound;			// Sound list

	System*				m_pSystem;			//�ý��� Ŭ���� ������
	Sound**				m_ppSound;			//���� Ŭ���� ������
	Channel**			m_ppChannel;		//ä�� Ŭ���� ������
public:
	SoundManager();
	~SoundManager();

	void AddSound(string key, string fileName, bool bgm = false, bool loop = false);
	void ReleaseSound(string key);

	void Update();
	void Play(string key, float volume = 1.f);	// volume ���� 0.f ~ 1.f
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);
	bool IsPlaySound(string key);
	bool IsPauseSound(string key);
	void VolumeUp(string key);
	void VolumeDown(string key);
};