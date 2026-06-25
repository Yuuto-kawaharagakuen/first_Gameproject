#pragma once
class Player;
class Goal:public IGameObject
{
public:
	Goal();
	~Goal();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

	ModelRender modelRender;
	Vector3 position;
	FontRender fontRender;
	Player* player;
	Quaternion rot;
	bool getGoal = false;

};

