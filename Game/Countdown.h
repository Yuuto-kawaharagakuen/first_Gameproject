#pragma once

class Countdown : public IGameObject
{
public:
	Countdown();
	~Countdown();
	void Update() override;
	void Render(RenderContext& rc) override;
private:
	float elapsed;
	int currentCount;
	FontRender fontRender;
};
