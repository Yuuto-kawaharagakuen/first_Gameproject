#pragma once
class GoalUI: public IGameObject
{
public:
	GoalUI();
	~GoalUI();
	void Update();
	void Render(RenderContext& rc);
	FontRender fontRender;
	Vector3 position = Vector3::Zero;

	// テキスト表示用タイマー
	float displayTimer = -1.0f;
	// テキスト表示フラグ
	bool visible = true;
};


