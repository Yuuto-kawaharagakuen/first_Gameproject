#pragma once
class PopupText:public IGameObject
{
public:
	PopupText();
	~PopupText();
	void Init(const wchar_t* text);
	void Update();
	void Render(RenderContext& rc);

private:
	FontRender fontRender;
	Vector3 pos;
	float lifeTimer;
	static constexpr float LifeTime = 1.0f; // 表示時間(秒)
	static constexpr float MoveSpeed = 60.0f; // 1秒あたりの移動量
};

