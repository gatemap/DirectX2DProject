#pragma once
template <typename T>
class Animation
{
private:
	map<T, Clip*>		m_mapClips;
	T					m_eCurrClip;
	D3DXVECTOR2			m_vPos;

public:
	Animation();
	~Animation();

	void Update();
	void Render();

	// 애니메이션 기능 함수
	void AddClip(T type, Clip* clip);
	void Play(T type);
	void PlayReverse(T type);
	void SetStartFrame(T type, float num);

	// 겟터 셋터
	void SetPos(float x, float y) { m_vPos.x = x; m_vPos.y = y; }
	void SetSpeed(float s);
	void SetRateScale(float x, float y);
	void SetConstantScale(float x, float y);
	D3DXVECTOR2 GetSize();
	bool GetIsPlaying();
	T GetType() { return m_eCurrClip; }
};

template <typename T>
Animation<T>::Animation()
	: m_eCurrClip(T::Ready)
	, m_vPos(INITX, INITY)
{
}

template <typename T>
inline Animation<T>::~Animation()
{
	for (auto p : m_mapClips)
		SAFE_DELETE(p.second);
	m_mapClips.clear();
}

template <typename T>
inline void Animation<T>::Update()
{
	if (m_eCurrClip == T::Ready) return;

	m_mapClips[m_eCurrClip]->SetPos(m_vPos.x, m_vPos.y);

	m_mapClips[m_eCurrClip]->Update();
}

template <typename T>
inline void Animation<T>::Render()
{
	if (m_eCurrClip == T::Ready) return;

	m_mapClips[m_eCurrClip]->Render();
}

template <typename T>
inline void Animation<T>::AddClip(T type, Clip* clip)
{
	m_mapClips.insert(make_pair(type, clip));
}

template <typename T>
inline void Animation<T>::Play(T type)
{
	if (m_eCurrClip == type && m_mapClips[m_eCurrClip]->GetPlayMode() == PlayMode::Loop) return;

	// 추가 되지 않은 타입을 재생시
	if (m_mapClips.find(type) == m_mapClips.end())
	{
		m_mapClips[m_eCurrClip]->Stop();
		return;
	}

	m_eCurrClip = type;
	m_mapClips[m_eCurrClip]->Play();
}

template <typename T>
inline void Animation<T>::PlayReverse(T type)
{
	m_eCurrClip = type;
	m_mapClips[m_eCurrClip]->PlayReverse();
}

template <typename T>
inline void Animation<T>::SetStartFrame(T type, float num)
{
	m_eCurrClip = type;
	m_mapClips[m_eCurrClip]->Play(num);
}

template <typename T>
inline void Animation<T>::SetSpeed(float s)
{
	for (auto p : m_mapClips)
		p.second->SetSpeed(s);
}

template <typename T>
inline void Animation<T>::SetRateScale(float x, float y)
{
	for (auto p : m_mapClips)
		p.second->SetScale(x, y);
}

template <typename T>
inline void Animation<T>::SetConstantScale(float x, float y)
{
	for (auto p : m_mapClips)
		p.second->SetConstantScale(x, y);
}

template <typename T>
D3DXVECTOR2 Animation<T>::GetSize()
{
	return m_mapClips[m_eCurrClip]->GetSize();
}

template<typename T>
inline bool Animation<T>::GetIsPlaying()
{
	if (m_eCurrClip == T::Ready) return false;

	return m_mapClips[m_eCurrClip]->GetIsPlaying();
}
