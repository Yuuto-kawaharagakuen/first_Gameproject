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
};

