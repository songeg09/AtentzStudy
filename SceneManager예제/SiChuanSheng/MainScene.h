#pragma once
#include"Scene.h"
class MainScene : public Scene
{
	enum OBJECT_GROUP
	{
		BUTTON,
		END
	};
	enum WINDOW_SIZE
	{
		WIDTH = 800,
		HEIGHT = 500,
	};
private:

public:
	MainScene(std::string _strName);
	~MainScene();
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	void StartSiChuanSheng();
	void StartMineSweeper();
};

