#include "stdafx.h"
#include "GameCamera.h"
#include"Player.h"

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}
bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定
	m_toCameraPos.Set(200.0f, 90.0f, -250.0f);
	// 180度回転 (Y軸回転) -> x,z を反転
	m_toCameraPos.x = -m_toCameraPos.x;
	m_toCameraPos.z = -m_toCameraPos.z;

	// 初期カメラを左に45度傾ける (Y軸周りに50度回転)
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, -50.0f);
	qRot.Apply(m_toCameraPos);

	//プレイヤーのインスタンスを探す
	m_player = FindGO<Player>("player");

	//カメラのニアクリップとファークリップを設定する
	g_camera3D->SetNear(0.1f);
	g_camera3D->SetFar(50000.0f);

	//バネカメラの初期化
	m_springCamera.Init(
		*g_camera3D,	//バネカメラの処理を行うカメラ
		1000.0f,		//カメラの移動速度の最大値
		true,			//地形とのあたり判定を取るかどうか(true=取る)
		5.0f			//カメラに設定される球体コリジョンの半径
	);

	return true;
}
void GameCamera::Update()
{
	//カメラを更新
	//注視点を計算する
	Vector3 target = m_player->position;
	//プレイヤーの足元からちょっと上を注視点とする
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_toCameraPos;
	//パッドの入力を使ってカメラを回す
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * x);
	qRot.Apply(m_toCameraPos);
	//X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Apply(m_toCameraPos);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.4f) {
		//カメラが上向きすぎ
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		//カメラが下向きすぎ
		m_toCameraPos = toCameraPosOld;
	}

	//視点を計算する。
	Vector3 pos = target + m_toCameraPos;
	//メインカメラに注視点と視点を設定する。
	//バネカメラに注視点と視点を設定する
	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(target);

	//カメラの更新
	m_springCamera.Update();
}