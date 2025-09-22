#pragma once
class Texture;
class Card
{
private:
	Vector2 m_vec2Position;
	RECT m_rectClickArea;
	Texture* m_pTexture;
public:
	Card();
	~Card();
	void Update();
	void Render(HDC _hDC);
	void Init(Vector2 _vec2Position, Texture* _pTexture);

	Vector2 GetPosition() { return m_vec2Position; }
};

