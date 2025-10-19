#pragma once


class Object;
class Scene
{
protected:
	Vector2					m_vec2WindowStartPosition;
	Vector2					m_vec2WindowCenterPosition;
	Vector2					m_vec2WindowSize;
	std::vector<std::vector<Object*>>	m_arrObjects;
	std::string				m_strName;
public:
	Scene(std::string _strName);
	virtual ~Scene();
	virtual void Update();
	virtual void Render(HDC _memDC);
	virtual void Init() = 0;
	virtual void Release();
	void SetWindowSize(int _iWidth, int _iHeight);
	void AddObject(Object* _object, unsigned int _eGroup);
	Vector2 GetWindowSize() { return m_vec2WindowSize; }
	void SetName(const std::string _strName) { m_strName = _strName; }
};

