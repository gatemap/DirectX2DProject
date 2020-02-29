#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
	//사운드 시스템 생성
	System_Create(&m_pSystem);
	//사운드 채널 수 설정
	m_pSystem->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);
	//사운드 동적 할당 및 초기화
	m_ppSound = new Sound*[TOTALSOUNDBUFFER];
	memset(m_ppSound, 0, sizeof(Sound*)* TOTALSOUNDBUFFER);
	//채널 동적 할당 및 초기화
	m_ppChannel = new Channel*[TOTALSOUNDBUFFER];
	memset(m_ppChannel, 0, sizeof(Channel*)* TOTALSOUNDBUFFER);
}


SoundManager::~SoundManager()
{
	//모든 채널 정지
	if (m_ppChannel != NULL) {
		for (int i = 0; i < TOTALSOUNDBUFFER; i++) if (m_ppChannel[i]) m_ppChannel[i]->stop();
	}
	SAFE_DELETE_ARRAY(m_ppChannel);
	//모든 사운드 해제
	if (m_ppSound != NULL) {
		for (int i = 0; i < TOTALSOUNDBUFFER; i++) if (m_ppSound[i]) m_ppSound[i]->release();
	}
	SAFE_DELETE(m_ppSound);

	if (m_pSystem != NULL) {
		m_pSystem->release();
		m_pSystem->close();
	}
}

void SoundManager::AddSound(string key, string fileName, bool bgm, bool loop)
{
	//사운드 버퍼가 꽉 찬 경우
	assert((m_mapSound.size() < SOUNDBUFFER) && "Sound Buffer is Full");

	string fullPath = "../../_Sounds/" + fileName;
	if (loop) {
		if (bgm) m_pSystem->createStream(fullPath.c_str(), FMOD_LOOP_NORMAL, NULL, &m_ppSound[m_mapSound.size()]);
		else m_pSystem->createSound(fullPath.c_str(), FMOD_LOOP_NORMAL, NULL, &m_ppSound[m_mapSound.size()]);
	}
	else {
		if (bgm) m_pSystem->createStream(fullPath.c_str(), FMOD_DEFAULT, NULL, &m_ppSound[m_mapSound.size()]);
		else m_pSystem->createSound(fullPath.c_str(), FMOD_DEFAULT, NULL, &m_ppSound[m_mapSound.size()]);
	}

	//사운드 파일 경로 또는 파일이 잘못된 경우
	assert(m_ppSound[m_mapSound.size()] && "Cannot found sound file");
	
	//맵에 사운드 추가
	m_mapSound.insert(make_pair(key, &m_ppSound[m_mapSound.size()]));
}

void SoundManager::ReleaseSound(string key)
{
	int cnt = 0;
	for (iterSound iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++, cnt++) 
	{
		if (key == iter->first) {
			//키 값에 해당하는 사운드가 할당된 채널 정지
			if (m_ppChannel != NULL) {
				if (m_ppChannel[cnt]) m_ppChannel[cnt]->stop();

			}
			if (m_ppSound != NULL) {
				if (m_ppSound[cnt]) m_ppSound[cnt]->release();
			}
		}
		m_mapSound.erase(iter);
		break;
	}
}

void SoundManager::Update()
{
	m_pSystem->update();
}

void SoundManager::Play(string key, float volume)
{
	int cnt = 0;
	for (iterSound iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++, cnt++)
	{
		if (key == iter->first) {
			m_pSystem->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &m_ppChannel[cnt]);
			m_ppChannel[cnt]->setVolume(volume);
		}
	}
}

void SoundManager::Stop(string key)
{
	int cnt = 0;
	for (iterSound iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++, cnt++)
	{
		if (key == iter->first) {
			m_ppChannel[cnt]->stop();
			break;
		}
	}
}

void SoundManager::Pause(string key)
{
	int cnt = 0;
	for (iterSound iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++, cnt++)
	{
		if (key == iter->first) {
			m_ppChannel[cnt]->setPaused(true);
			break;
		}
	}
}

void SoundManager::Resume(string key)
{
	int cnt = 0;
	for (iterSound iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++, cnt++)
	{
		if (key == iter->first) {
			m_ppChannel[cnt]->setPaused(false);
			break;
		}
	}
}

bool SoundManager::IsPlaySound(string key)
{
	bool isPlaying = false;

	int cnt = 0;
	for (iterSound iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++, cnt++)
	{
		if (key == iter->first) {
			m_ppChannel[cnt]->isPlaying(&isPlaying);
			break;
		}
	}
	return isPlaying;
}

bool SoundManager::IsPauseSound(string key)
{
	bool isPaused = false;

	int cnt = 0;
	for (iterSound iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++, cnt++)
	{
		if (key == iter->first) {
			m_ppChannel[cnt]->getPaused(&isPaused);
			break;
		}
	}
	return isPaused;
}

void SoundManager::VolumeUp(string key)
{
	float volume;
	int cnt = 0;
	for (iterSound iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++, cnt++)
	{
		if (key == iter->first) {
			m_ppChannel[cnt]->getVolume(&volume);
			m_ppChannel[cnt]->setVolume(volume + 0.1f);
			break;
		}
	}
}

void SoundManager::VolumeDown(string key)
{
	float volume;

	int cnt = 0;
	for (iterSound iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++, cnt++)
	{
		if (key == iter->first) {
			m_ppChannel[cnt]->getVolume(&volume);
			m_ppChannel[cnt]->setVolume(volume - 0.1f);
			break;
		}
	}
}
