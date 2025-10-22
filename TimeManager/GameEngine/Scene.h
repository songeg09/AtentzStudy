#pragma once

enum class OBJECT_GROUP
{
	PLAYABLE,
	BULLET,
	END
};

class Object;
class Scene
{
protected:
	Vector2					m_vec2WindowStartPosition;
	Vector2					m_vec2WindowCenterPosition;
	Vector2					m_vec2WindowSize;
	std::vector<Object*>	m_arrObjects[static_cast<int>(OBJECT_GROUP::END)];
	std::wstring				m_strName;
public:
	Scene(std::wstring _strName);
	virtual ~Scene();
	virtual void Update();
	virtual void Render(HDC _memDC);
	virtual void Init() = 0;
	virtual void Release();
	void SetWindowSize(int _iWidth, int _iHeight);
	void AddObject(Object* _object, OBJECT_GROUP _eGroup);
	Vector2 GetWindowSize() { return m_vec2WindowSize; }
	void SetName(const std::wstring _strName) { m_strName = _strName; }
};

