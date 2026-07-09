#include "stdafx.h"
#include "Controller.h"
#include"Title.h"
#include"Tutorial.h"
#include "sound/SoundEngine.h"
Controller::Controller()
{
	spriteRender.Init("Assets/sprite/controller.dds", 1700.0f, 1080.0f);
	NextRender.SetPosition({ 350.0f,515.0f,0.0f });
	NextRender.SetColor(g_vec4Black);
	NextRender.SetText(L"NEXT-ゲーム説明");
	NextRender.SetScale(1.5f);
}
Controller::~Controller() {
}

void Controller::Update() {
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Tutorial>(0);
		DeleteGO(this);
	}
	if (g_pad[0]->IsTrigger(enButtonRB1)) {
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void Controller::Render(RenderContext& rc)
{
	// スプライトを先に描画し、文字を上に重ねる
	spriteRender.Draw(rc);
	NextRender.Draw(rc);
}