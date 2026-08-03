#include "stdafx.h"
#include "Title.h"
#include"Tutorial.h"
#include "sound/SoundEngine.h"
Title::Title()
{
	spriteRender.Init("Assets/sprite/gamestart1.dds",1920.0f,1080.0f);
	//タイトルのBGMを読み込む
	g_soundEngine->ResistWaveFileBank(0,"Assets/sound/titlebgm.wav");
	//タイトルのBGMを再生する
	titleBGM = NewGO<SoundSource>(0);
	titleBGM->Init(0);
	titleBGM->Play(true);
}

Title::~Title()
{
	//タイトルのBGMを削除する
	DeleteGO(titleBGM);
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{   
		//BGMが一瞬重複していたので
		if (titleBGM) {
			titleBGM->Stop();
			titleBGM->Release();
			titleBGM = nullptr;
		}
		NewGO<Tutorial>(0);
		DeleteGO(this);
	}
	//7が押されたらゲームを終了する
	if (g_pad[0]->IsTrigger(enButtonRB1)) {
		exit(0);
	}
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}