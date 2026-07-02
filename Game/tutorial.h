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

//ゲームパッド　　　　キーボード　　　　　　　機能
//　　 LB1                7               タイトルへ戻る  
// 　　 A                 k                次へ ダッシュ
//      B                 j                 ジャンプ
//　　　X　　　　　　　　 i      クリスタルの動きを止める(一度だけ3秒間)
//