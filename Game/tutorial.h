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
//     RB1                7                 強制終了
//　　 LB1                B               タイトルへ戻る  
// 　　 A                 J               次へ ダッシュ
//      B                 K                 ジャンプ
//　　　X　　　　　　　　 L      クリスタルの動きを止める(一度だけ3秒間)
//