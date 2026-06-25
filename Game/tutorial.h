#pragma once
//#include "sound/SoundSource.h"
class Tutorial:public IGameObject
{
public:
	Tutorial();
	~Tutorial();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender spriteRender;
	FontRender fontRender;
	Vector3 position = Vector3::Zero;
};

