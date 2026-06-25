#pragma once
class Player;
class GameClear;
class CountUI:public IGameObject
{
public:
	CountUI();
	 ~CountUI();
	void Update();
	void Render(RenderContext& rc);

	FontRender fontRender;
	Vector3 position=Vector3::Zero;
	int UInum = 0;

	int Score = 0;
	Player* player;
	GameClear* gameClear;
	float elapsedTime = 0.0f;

	float GetElapsedTime() const { return elapsedTime; }
};

