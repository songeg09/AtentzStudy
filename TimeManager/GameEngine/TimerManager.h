#pragma once
class TimerManager
{
	SINGLETON(TimerManager)
private:
	LARGE_INTEGER m_llPrevCount; // ���� ���� ó�� Ƚ��
	LARGE_INTEGER m_llFrequency; // 1�ʴ� ����ó�� Ƚ��

	double m_dDeltaTime;
	double m_dAccTime;
	unsigned int m_iCallCount;
	unsigned int m_iFPS;
public:
	void Init();
	void Update();
	inline double GetdDeltaTime() { return m_dDeltaTime; }
	inline float GetfDeltaTime() { return (float)m_dDeltaTime; }
	inline unsigned intGetFPS() { return m_iFPS; }
};

