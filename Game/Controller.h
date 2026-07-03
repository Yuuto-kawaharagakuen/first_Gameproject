#pragma once
class Controller:public IGameObject
{
public:
	Controller();
	~Controller();
	void Update();
	void Render(RenderContext& rc);
	
	FontRender NextRender;
	SpriteRender spriteRender;
	SoundSource* soundSource;
};

